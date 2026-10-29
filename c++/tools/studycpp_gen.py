#!/usr/bin/env python3
"""
studycpp_gen.py —— 把 https://www.studycpp.cn/ 的 C++ 教程抓取下来，
按「章 -> 节」生成带完整正文注释的 .cpp 学习文件。

用法:
    python3 tools/studycpp_gen.py fetch      # 只抓取(带缓存)
    python3 tools/studycpp_gen.py gen        # 只生成 .cpp
    python3 tools/studycpp_gen.py all        # 抓取 + 生成(默认)

生成的目录结构:
    c++/chapter00/00.0-introduction-to-site.cpp
    c++/chapter04/04.10-char.cpp
    ...

每个 .cpp 文件包含:
    1. 文件头: 章节 / 标题 / 原文链接 / 编译命令 / 本节目录
    2. 「教程正文」: 完整正文、代码块、习题答案(以 // 注释保存)
    3. 「可运行示例」: 从教程代码块中挑一个能通过编译的完整程序,
       若无则给一个最小的占位 main()
"""

from __future__ import annotations

import html
import os
import re
import subprocess
import sys
import tempfile
import time
import unicodedata
import urllib.error
import urllib.request
from concurrent.futures import ThreadPoolExecutor
from html.parser import HTMLParser

BASE = "https://www.studycpp.cn"
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))  # c++/
CACHE = os.path.join(ROOT, "tools", ".cache")
UA = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) studycpp-notebook/1.0"

WRAP = 78  # 注释每行显示宽度

# --------------------------------------------------------------------------
# 1. 抓取
# --------------------------------------------------------------------------


def cache_path(url: str) -> str:
    rel = url[len(BASE):].strip("/").replace("/", "_") or "index"
    return os.path.join(CACHE, rel + ".html")


def fetch(url: str, tries: int = 4) -> str:
    path = cache_path(url)
    if os.path.exists(path) and os.path.getsize(path) > 2000:
        return open(path, encoding="utf-8").read()
    last = None
    for i in range(tries):
        try:
            req = urllib.request.Request(url, headers={"User-Agent": UA})
            with urllib.request.urlopen(req, timeout=30) as r:
                text = r.read().decode("utf-8", "replace")
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w", encoding="utf-8") as f:
                f.write(text)
            return text
        except Exception as e:  # noqa: BLE001
            last = e
            time.sleep(1.0 + i * 1.5)
    raise RuntimeError(f"抓取失败 {url}: {last}")


# --------------------------------------------------------------------------
# 2. 解析站点侧边栏: 章节名 + 每节标题/链接
# --------------------------------------------------------------------------


def parse_sidebar(page: str):
    s = page.find('<div class="bg-body sticky-top scroll-container"')
    e = page.find('<div class="col-md-8')
    if s < 0 or e < 0:
        raise RuntimeError("未找到侧边栏")
    sb = page[s:e]
    parts = re.split(r'(<button class="btn btn-toggle.*?</button>)', sb, flags=re.S)
    chapters: list[dict] = []
    for p in parts:
        m = re.match(r'<button class="btn btn-toggle.*?>(.*?)</button>', p, flags=re.S)
        if m:
            name = html.unescape(re.sub("<[^>]+>", "", m.group(1))).strip()
            chapters.append({"name": name, "lessons": []})
            continue
        for href, title in re.findall(
            r'<a href="(/basic/[^"]+)"[^>]*>(.*?)</a>', p, flags=re.S
        ):
            t = html.unescape(re.sub("<[^>]+>", "", title)).strip()
            if chapters:
                chapters[-1]["lessons"].append({"href": href, "title": t})
    return chapters


# --------------------------------------------------------------------------
# 3. 正文抽取 + HTML -> 文本块
# --------------------------------------------------------------------------

WIDE = "WF"


def cw(ch: str) -> int:
    return 2 if unicodedata.east_asian_width(ch) in WIDE else 1


def width(s: str) -> int:
    return sum(cw(c) for c in s)


NO_LINE_START = "，。、；：）》」』】！？…%,.;:)]}!?"


def wrap(text: str, limit: int = WRAP) -> list[str]:
    """按显示宽度折行, 中文可任意断行。"""
    text = re.sub(r"\s+", " ", text).strip()
    if not text:
        return []
    tokens: list[str] = []
    buf = ""
    for ch in text:
        if cw(ch) == 2 or ch == " ":
            if buf:
                tokens.append(buf)
                buf = ""
            tokens.append(ch)
        else:
            buf += ch
    if buf:
        tokens.append(buf)

    lines: list[str] = []
    cur = ""
    for tok in tokens:
        if tok == " ":
            if cur and not cur.endswith(" "):
                cur += " "
            continue
        if width(cur) + width(tok) > limit and cur.strip():
            if tok[0] in NO_LINE_START:  # 标点不置于行首, 允许略微超出宽度
                lines.append((cur + tok).rstrip())
                cur = ""
                continue
            lines.append(cur.rstrip())
            cur = ""
        cur += tok
    if cur.strip():
        lines.append(cur.rstrip())
    return lines


class BodyParser(HTMLParser):
    """把正文 HTML 转成 (kind, text) 块序列。

    kind: h2/h3/h4/p/code/li/hr/quote/table/answer/summary/note
    """

    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.blocks: list[tuple[str, object]] = []
        self.buf: list[str] = []
        self.in_pre = False
        self.pre_buf: list[str] = []
        self.list_stack: list[str] = []
        self.li_depth = 0
        self.quote = 0
        self.in_table = False
        self.rows: list[list[str]] = []
        self.cell: list[str] | None = None
        self.heading: str | None = None
        self.details = 0
        self.summary_buf: list[str] | None = None
        self.skip = 0
        self.inline_code = 0
        self.img_alt: str | None = None

    # -- helpers --
    def flush(self) -> None:
        txt = "".join(self.buf)
        self.buf = []
        txt = re.sub(r"\s+", " ", txt).strip()
        if not txt:
            return
        if self.cell is not None:
            self.cell.append(txt)
            return
        if self.heading:
            self.blocks.append((self.heading, txt))
            return
        if self.li_depth:
            self.blocks.append(("li", (self.li_depth, txt)))
            return
        if self.quote:
            self.blocks.append(("quote", txt))
            return
        self.blocks.append(("p", txt))

    # -- parser callbacks --
    def handle_starttag(self, tag, attrs):
        a = dict(attrs)
        cls = a.get("class", "") or ""
        if self.skip:
            return
        if tag in ("script", "style", "svg", "nav", "button"):
            self.skip += 1
            return
        if tag == "pre":
            self.in_pre = True
            self.pre_buf = []
            return
        if tag in ("h1", "h2", "h3", "h4", "h5", "h6"):
            self.flush()
            lvl = int(tag[1])
            self.heading = None if lvl == 1 else f"h{lvl}"
            if lvl == 1:
                self.heading = None
            return
        if tag == "p":
            self.flush()
            return
        if tag in ("ul", "ol"):
            self.flush()
            self.list_stack.append(tag)
            return
        if tag == "li":
            self.flush()
            self.li_depth = len(self.list_stack) or 1
            return
        if tag == "blockquote":
            self.flush()
            self.quote += 1
            return
        if tag == "hr":
            self.flush()
            self.blocks.append(("hr", None))
            return
        if tag == "table":
            self.flush()
            self.in_table = True
            self.rows = []
            return
        if tag == "tr":
            self.rows.append([])
            return
        if tag in ("td", "th"):
            self.flush()
            self.cell = []
            return
        if tag == "code":
            if not self.in_pre:
                self.buf.append("`")
                self.inline_code += 1
            return
        if tag == "br":
            self.buf.append(" ")
            return
        if tag == "img":
            alt = (a.get("alt") or "").strip()
            src = (a.get("src") or "").strip()
            if "katex" in src:
                return
            self.flush()
            self.blocks.append(("note", f"[图片] {alt or src}"))
            return
        if tag == "details":
            self.flush()
            self.details += 1
            return
        if tag == "summary":
            self.flush()
            self.summary_buf = []
            return
        if "cpp-solution-body" in cls:
            self.flush()
            return
        if tag == "div" and "note" in cls:
            self.flush()
            return

    def handle_endtag(self, tag):
        if self.skip:
            if tag in ("script", "style", "svg", "nav", "button"):
                self.skip -= 1
            return
        if tag == "pre":
            self.in_pre = False
            txt = "".join(self.pre_buf).replace("\r\n", "\n")
            self.pre_buf = []
            lines = [ln.rstrip() for ln in txt.split("\n")]
            while lines and not lines[0].strip():
                lines.pop(0)
            while lines and not lines[-1].strip():
                lines.pop()
            # 行号列 (纯数字的 pre) 直接丢弃
            if lines and all(re.fullmatch(r"\s*\d+\s*", ln) for ln in lines):
                return
            if lines:
                self.blocks.append(("code", lines))
            return
        if tag in ("h1", "h2", "h3", "h4", "h5", "h6"):
            self.flush()
            self.heading = None
            return
        if tag == "p":
            self.flush()
            return
        if tag in ("ul", "ol"):
            self.flush()
            if self.list_stack:
                self.list_stack.pop()
            self.li_depth = len(self.list_stack)
            return
        if tag == "li":
            self.flush()
            self.li_depth = 0
            return
        if tag == "blockquote":
            self.flush()
            self.quote = max(0, self.quote - 1)
            return
        if tag in ("td", "th"):
            self.flush()
            if self.cell is not None:
                if self.rows:
                    self.rows[-1].append(" ".join(self.cell).strip())
            self.cell = None
            return
        if tag == "table":
            self.flush()
            self.in_table = False
            rows = [r for r in self.rows if any(c for c in r)]
            if rows:
                self.blocks.append(("table", rows))
            self.rows = []
            return
        if tag == "code":
            if not self.in_pre and self.inline_code:
                self.buf.append("`")
                self.inline_code -= 1
            return
        if tag == "summary":
            txt = re.sub(r"\s+", " ", "".join(self.summary_buf or [])).strip()
            self.summary_buf = None
            if txt:
                self.blocks.append(("summary", txt if not self.details else f"答案 · {txt}"))
            return
        if tag == "details":
            self.details = max(0, self.details - 1)
            return

    def handle_data(self, data):
        if self.skip:
            return
        if self.in_pre:
            self.pre_buf.append(data)
            return
        if self.summary_buf is not None:
            self.summary_buf.append(data)
            return
        self.buf.append(data)


def extract_body(page: str) -> tuple[str, str]:
    """返回 (标题, 正文 HTML)。"""
    m = re.search(r"<h1>(.*?)</h1>", page, flags=re.S)
    title = html.unescape(re.sub("<[^>]+>", "", m.group(1))).strip() if m else ""
    col = page.find('class="col-md-8')
    if col < 0:
        col = 0
    h1 = page.find("</h1>", col)
    if h1 < 0:
        h1 = page.find("</h1>")
    start = h1 + 5 if h1 >= 0 else col
    end = page.find('<img src="/images/zan.jpg"')
    if end < 0:
        end = len(page)
    # 去掉正文后面的 上一节/下一节 卡片
    row = page.rfind('<div class="row">', start, end)
    if row > 0 and end - row < 4000:
        end = row
    body = page[start:end]
    body = re.sub(r"本节阅读量.*?</span>", "", body, flags=re.S)
    return title, body


def html_to_blocks(body: str) -> list[tuple[str, object]]:
    p = BodyParser()
    p.feed(body)
    p.close()
    p.flush()
    return p.blocks


# --------------------------------------------------------------------------
# 4. 生成 .cpp
# --------------------------------------------------------------------------


def is_output_block(lines: list[str]) -> bool:
    """判断一个代码块是“程序输出/纯文本”而不是代码。"""
    joined = "\n".join(lines)
    return not re.search(r"[;{}#=]", joined)


def blocks_to_comment_lines(blocks) -> list[str]:
    out: list[str] = []
    code_no = 0
    table_no = 0
    prev = ""  # 上一个块的类型, 用于段落间空行

    def emit(prefix: str, text: str, limit: int = WRAP - 3) -> None:
        for ln in wrap(text, limit) or [""]:
            out.append((prefix + ln).rstrip())

    def gap() -> None:
        if out and out[-1] != "//":
            out.append("//")

    for kind, payload in blocks:
        if kind == "h2":
            out.append("")
            out.append("// ―――― " + payload + " ――――")
            out.append("")
        elif kind in ("h3", "h4", "h5", "h6"):
            out.append("")
            out.append("// ▼ " + payload)
        elif kind == "p":
            if prev in ("p", "li", "quote", "table"):
                gap()
            emit("// ", payload)
        elif kind == "li":
            depth, text = payload
            pad = "  " * (depth - 1)
            first = True
            for ln in wrap(text, WRAP - 6 - 2 * (depth - 1)) or [""]:
                out.append(("//" + pad + (" - " if first else "   ") + ln).rstrip())
                first = False
        elif kind == "quote":
            emit("// > ", payload)
        elif kind == "code":
            label = "输出" if is_output_block(payload) else "代码"  # type: ignore[arg-type]
            if label == "代码":
                code_no += 1
            out.append("")
            out.append(f"// [{label} {code_no}]" if label == "代码" else "// [文本/输出]")
            for ln in payload:  # type: ignore[union-attr]
                if ln.endswith("\\"):
                    ln += " "  # 防止行尾反斜杠把下一行拼接进注释
                out.append(("// " + ln).rstrip())
            out.append("")
        elif kind == "table":
            table_no += 1
            out.append("")
            out.append(f"// [表格 {table_no}]")
            for r in payload:  # type: ignore[union-attr]
                emit("//   | ", " | ".join(r))
            out.append("")
        elif kind == "hr":
            out.append("//")
        elif kind == "summary":
            out.append("")
            out.append(f"// 【{payload}】")
        elif kind == "note":
            note = str(payload)
            if note.startswith("[图片]"):  # 图片地址不折行, 方便复制
                out.append("// " + note)
            else:
                emit("// ", note)
        prev = kind
    return out


def pick_runnable(blocks) -> str | None:
    """从代码块里挑一个能独立编译的完整程序(优先取最后一个)。"""
    candidates: list[str] = []
    for kind, payload in blocks:
        if kind != "code":
            continue
        code = "\n".join(payload)  # type: ignore[arg-type]
        if "int main" not in code:
            continue
        first = next((ln for ln in code.split("\n") if ln.strip()), "")
        if not first.startswith("#") and "main" not in first:
            continue
        candidates.append(code)
    for code in candidates:
        if compiles(code):
            return code
    return None


def compiles(code: str) -> bool:
    with tempfile.TemporaryDirectory() as d:
        src = os.path.join(d, "a.cpp")
        with open(src, "w", encoding="utf-8") as f:
            f.write(code + "\n")
        for std in ("c++20", "c++17"):
            r = subprocess.run(
                ["clang++", f"-std={std}", "-fsyntax-only", "-w", src],
                capture_output=True,
            )
            if r.returncode == 0:
                return True
    return False


STUB = """#include <iostream>

int main()
{
    // 本节教程的代码是多文件示例、片段或概念性内容，没有可直接编译的完整程序。
    // 请对照上面的注释和代码块，自己动手补全并运行验证。
    std::cout << "本节无独立可运行示例, 请阅读文件中的教程正文。\\n";
    return 0;
}"""


def lesson_number(title: str) -> tuple[int, int] | None:
    m = re.match(r"^\s*(\d+)\.(\d+)", title)
    if m:
        return int(m.group(1)), int(m.group(2))
    return None


def build_cpp(ch: int, lesson_idx: int, ch_name: str, title: str, href: str, page: str) -> tuple[str, str]:
    """返回 (相对文件名, 文件内容)。"""
    page_title, body = extract_body(page)
    blocks = html_to_blocks(body)
    # 图片相对路径 -> 完整 URL
    for i, (k, p) in enumerate(blocks):
        if k == "note" and isinstance(p, str) and p.startswith("[图片]"):
            rel = p[len("[图片]"):].strip()
            if rel.startswith("./"):
                full = f"{BASE}{href}{rel[2:]}"
            elif rel.startswith("/"):
                full = BASE + rel
            else:
                full = rel
            blocks[i] = ("note", f"[图片] {full}")
    num = lesson_number(title) or lesson_number(page_title)
    les_no = num[1] if num else lesson_idx
    slug = href.rstrip("/").split("/")[-1]
    fname = f"{ch:02d}.{les_no:02d}-{slug}.cpp"

    # 本节目录 (h2)
    toc = [b[1] for b in blocks if b[0] == "h2"]
    code = pick_runnable(blocks)

    L: list[str] = []
    bar = "// " + "=" * 74
    L.append(bar)
    L.append(f"// {title}")
    L.append("// " + "-" * 74)
    L.append(f"// 课程: C++学习网 · {ch_name}")
    L.append(f"// 原文: {BASE}{href}")
    L.append("// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。")
    if code:
        L.append("//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。")
    else:
        L.append("//       本节示例为片段或多文件程序，文末仅有占位 main()。")
    L.append(f'// 编译: g++ -std=c++20 -Wall -Wextra "{fname}" -o /tmp/a.out && /tmp/a.out')
    L.append(bar)
    if toc:
        L.append("//")
        L.append("// 本节内容:")
        for t in toc:
            L.append(f"//   · {t}")
    L.append("")
    L.append("// " + "=" * 74)
    L.append("// 教程正文")
    L.append("// " + "=" * 74)
    L.append("")
    body_lines = blocks_to_comment_lines(blocks)
    while body_lines and body_lines[0] in ("", "//"):
        body_lines.pop(0)
    L.extend(body_lines)
    L.append("")
    L.append("// " + "=" * 74)
    L.append("// 可运行示例（来自教程代码块）")
    L.append("// " + "=" * 74)
    L.append("")
    L.append(code if code else STUB)
    L.append("")

    out: list[str] = []
    for ln in L:
        if ln == "//" and out and out[-1] == "//":
            continue  # 合并连续空注释行
        out.append(ln)
    while len(out) > 1 and out[-1] == "//":
        out.pop()
    return fname, "\n".join(out)


# --------------------------------------------------------------------------
# 5. 主流程
# --------------------------------------------------------------------------


def chapter_dir_name(ch: int) -> str:
    return f"chapter{ch:02d}"


def main(argv: list[str]) -> int:
    mode = argv[1] if len(argv) > 1 else "all"

    print("抓取章节列表 ...")
    chapters = []
    for probe in ("/", "/basic/chapter4/if/"):
        try:
            chapters = parse_sidebar(fetch(BASE + probe))
        except Exception:  # noqa: BLE001
            continue
        if chapters:
            break
    if not chapters:
        print("无法解析章节列表")
        return 1
    total = sum(len(c["lessons"]) for c in chapters)
    print(f"共 {len(chapters)} 章 / {total} 节")

    urls = [BASE + l["href"] for c in chapters for l in c["lessons"]]
    if mode in ("fetch", "all"):
        done = 0

        def job(u: str):
            nonlocal done
            try:
                fetch(u)
            except Exception as e:  # noqa: BLE001
                print(f"  !! {e}")
            done += 1
            if done % 25 == 0:
                print(f"  抓取 {done}/{len(urls)}")

        with ThreadPoolExecutor(max_workers=6) as ex:
            list(ex.map(job, urls))
        print("抓取完成")

    if mode == "fetch":
        return 0

    pages: dict[str, str] = {}
    for u in urls:
        try:
            pages[u] = fetch(u)
        except Exception as e:  # noqa: BLE001
            print(f"  !! 缺少页面 {u}: {e}")

    stats = []
    for ch_idx, ch in enumerate(chapters):
        cdir = os.path.join(ROOT, chapter_dir_name(ch_idx))
        os.makedirs(cdir, exist_ok=True)
        rows = []
        for li, lesson in enumerate(ch["lessons"]):
            url = BASE + lesson["href"]
            page = pages.get(url)
            if not page:
                rows.append((lesson["title"], "(抓取失败)", ""))
                continue
            fname, content = build_cpp(ch_idx, li, ch["name"], lesson["title"], lesson["href"], page)
            if len(content) < 800:
                print(f"  ?? 内容过短 {lesson['href']}")
            with open(os.path.join(cdir, fname), "w", encoding="utf-8") as f:
                f.write(content)
            size = len(content)
            stats.append((ch_idx, lesson["title"], fname, size))
            rows.append((lesson["title"], fname, f"{size // 1024}KB" if size > 1024 else f"{size}B"))

        # 章节 README
        md = [f"# {ch['name']}", ""]
        md.append(f"共 {len(ch['lessons'])} 节。")
        md.append("")
        md.append("| 节 | 文件 | 大小 |")
        md.append("| --- | --- | --- |")
        for t, f, s in rows:
            md.append(f"| {t} | [`{f}`](./{f}) | {s} |")
        md.append("")
        md.append("```bash")
        md.append(f'# 编译并运行某一节 (以第 1 节为例)')
        first = rows[0][1] if rows and rows[0][1].startswith(tuple("0123456789")) else ""
        if first:
            md.append(f'g++ -std=c++20 -Wall -Wextra "{first}" -o /tmp/a.out && /tmp/a.out')
        md.append("```")
        with open(os.path.join(cdir, "README.md"), "w", encoding="utf-8") as f:
            f.write("\n".join(md) + "\n")
        print(f"  {chapter_dir_name(ch_idx)}  {ch['name']}  {len(ch['lessons'])} 节")

    # 顶层 README
    md = [
        "# C++ 学习笔记（基于 C++学习网）",
        "",
        "本站内容按照 [C++学习网](https://www.studycpp.cn/) 的教程组织：**每章一个目录，每节一个可编译的 `.cpp` 文件**。",
        "",
        "每个 `.cpp` 文件里包含：",
        "",
        "1. **文件头**：章节、节号、原文链接、编译命令、本节目录；",
        "2. **教程正文**：把原文（含代码块、表格、习题答案）以 `//` 注释形式完整收录，便于对照学习；",
        "3. **可运行示例**：从教程代码块中挑出的完整程序（已通过 `clang++ -std=c++20` 语法校验），",
        "   没有完整程序时给出占位 `main()`。",
        "",
        "## 编译方式",
        "",
        "```bash",
        '# 推荐：直接编译并运行某一节',
        './tools/run.sh chapter04/04.09-if.cpp',
        '',
        '# 手动编译单个文件',
        'g++ -std=c++20 -Wall -Wextra "chapter04/04.09-if.cpp" -o /tmp/a.out && /tmp/a.out',
        '',
        '# macOS 自带的 clang++',
        'clang++ -std=c++20 -Wall -Wextra "chapter04/04.09-if.cpp" -o /tmp/a.out && /tmp/a.out',
        '```',
        "",
        "## 目录约定",
        "",
        "```",
        "c++/",
        "├── README.md              # 本文件（含全部 313 节的学习进度清单）",
        "├── chapter00 ~ chapter28/ # 每章一个目录，内含 README + 每节一个 .cpp",
        "└── tools/",
        "    ├── run.sh             # 一键编译运行脚本",
        "    └── studycpp_gen.py    # 抓取/生成脚本（页面缓存在 tools/.cache）",
        "```",
        "",
        "## 章节",
        "",
        "| 章 | 目录 | 节数 | 内容 |",
        "| --- | --- | --- | --- |",
    ]
    for ch_idx, ch in enumerate(chapters):
        md.append(
            f"| {ch_idx} | [`{chapter_dir_name(ch_idx)}/`](./{chapter_dir_name(ch_idx)}) | "
            f"{len(ch['lessons'])} | {ch['name']} |"
        )
    md += [
        "",
        "## 学习进度",
        "",
    ]
    for ch_idx, ch in enumerate(chapters):
        md.append(f"### {ch['name']}")
        md.append("")
        for lesson in ch["lessons"]:
            num = lesson_number(lesson["title"])
            les_no = num[1] if num else 0
            slug = lesson["href"].rstrip("/").split("/")[-1]
            md.append(
                f"- [ ] [`{ch_idx:02d}.{les_no:02d}-{slug}.cpp`]"
                f"(./{chapter_dir_name(ch_idx)}/{ch_idx:02d}.{les_no:02d}-{slug}.cpp) {lesson['title']}"
            )
        md.append("")
    md += [
        "## 重新生成",
        "",
        "```bash",
        "python3 tools/studycpp_gen.py all     # 抓取 + 生成（页面缓存在 tools/.cache）",
        "python3 tools/studycpp_gen.py fetch    # 只抓取",
        "python3 tools/studycpp_gen.py gen      # 只生成",
        "```",
        "",
        "> 内容版权归 [C++学习网](https://www.studycpp.cn/) 所有，本目录仅用于个人学习。",
        "",
    ]
    with open(os.path.join(ROOT, "README.md"), "w", encoding="utf-8") as f:
        f.write("\n".join(md))

    print(f"\n完成: {len(stats)} 个 .cpp 文件, 共 {sum(s[3] for s in stats) // 1024} KB")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
