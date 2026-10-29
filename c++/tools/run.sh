#!/usr/bin/env bash
# 编译并运行某一节，例如：
#   ./tools/run.sh chapter04/04.09-if.cpp
#   ./tools/run.sh chapter16/16.03-vec-loop.cpp
set -euo pipefail

if [ $# -lt 1 ]; then
  echo "用法: $0 <章节目录/文件.cpp> [编译选项...]" >&2
  echo "例:   $0 chapter04/04.09-if.cpp" >&2
  exit 1
fi

src="$1"
shift
if [ ! -f "$src" ]; then
  echo "找不到文件: $src" >&2
  exit 1
fi

out="$(mktemp -t cpplearn)"
trap 'rm -f "$out"' EXIT

CXX_BIN="${CXX:-}"
if [ -z "$CXX_BIN" ]; then
  if command -v clang++ >/dev/null 2>&1; then CXX_BIN=clang++; else CXX_BIN=g++; fi
fi

echo "== 编译 $src"
"$CXX_BIN" -std=c++20 -Wall -Wextra -g "$@" "$src" -o "$out"
echo "== 运行"
"$out"
