# 04 · 使用 Web UI 与 CLI 模式

## 一、Web UI

### 1. 启动

```sh
npx @deepseek-ai/dsh web
# 打开 http://127.0.0.1:3080
```

进程把**启动时所在目录**作为默认文件系统位置。全新的 Web UI 不会选中任何工作区。

### 2. 三步开始

1. **配置模型**：设置 → 模型，填 DeepSeek API Key 保存（见第 03 课）。
2. **选择工作区**：点**选择工作区**，添加启动 `dsh` 时所在的项目目录并选中它。
   **未选中工作区前，会话输入框不可用。**
3. **运行任务**：启动会话，发送：

   > Summarize this repository and identify its main packages.

Agent 可以读取/编辑工作区文件、运行命令、委派工作并维护计划。若某项操作按当前权限策略需要审批，UI 会先问你。

### 3. Agent 能做什么

- **读写工作区文件、运行命令**
- **委派工作**（subagent）
- **维护计划**（plan / todo / goal 等子系统）
- **技能（skills）**：按需加载的能力包
- **MCP**：接入外部工具服务器

### 4. 插件页

Web 侧边栏的**插件**页（`ui-plugin-manager`）可以：

- 查看/启停 profile 的插件条目
- 选择已安装的组合包
- 安装或删除外部组合包

设置页里的插件列表是**只读**清单；Agent 预设条目保持只读。也可以在对话里用 `plugin_manager` 工具做同样的事（见第 09 课）。

## 二、other CLI 模式

### headless：一次性任务

```sh
dsh --profile headless "run the tests"
# 或从源码
pnpm dsh --profile headless "summarize this workspace"
```

- 通过核心注册表创建全新的**持久化** Agent，提交任务，等完全停稳并 flush 会话。
- 非空 reasoning 增量以 `dsh: reasoning:` 标题流式写入 **stderr**；**stdout 只打印最终文本**。
- 原因为 `completed` 时退出码 0，否则 1；没有任务的调用是用法错误。
- 不挂浏览器/HTTP/Web 运行时，也不打开监听端口。

### SDK

TypeScript SDK 解析同版本的 `dsh` 依赖并选择 `sdk` profile，stdio 承载 JSON-RPC。Python SDK 的运行时 wheel 把普通 `dsh` CLI 打包为 `deepseek-harness-sdk-runtime-<platform>-<arch>`，默认以显式 Harness home 启动 `dsh --profile sdk`。见官方 `docs/user/guide/python-sdk.zh.md` 和 `packages/sdk/*`。

### ACP

`--profile acp` 通过 Agent Client Protocol JSON-RPC stdio 提供全新文本会话，发出已提交的助手文本，并为其拥有的 agent 注册一次性机器权限应答器。仅面向自动化。

### 代码式工具（PTC）

```sh
pnpm run demo:ptc -- "summarize this workspace"
```

PTC mode 让每个可见工具都能以 `await tools.<name>(args)` 调用（代码式工具展示），无需额外集成。

## 三、权限与沙箱

基于 base 的 profile 中，新会话默认使用 **`workspace-write`** 权限预设：

- Bash 与文件系统修改仅限会话 workspace 与平台临时根目录；
- 读取和网络访问不受限制；
- 进程可见性取决于沙箱后端：bwrap 在私有 PID 命名空间运行命令并隐藏宿主进程；Landlock 与 Seatbelt 保持宿主进程可见性。

相关开关：

| 变量 | 作用 |
| --- | --- |
| `DSH_PERMISSION_MODE` | 改进程后备权限模式 |
| `DSH_TOOLS_MODE` | 选 `native`、`ptc` 或 `both`；其他值启动失败 |
| `DSH_TELEMETRY_MODE=DISABLED` | 禁止 OTel 投递（`FULL` 被拒绝） |
| `DSH_TELEMETRY_OTLP_URL` | 选择采集端 |
| `DSH_TELEMETRY_DISABLED` | 非空即禁用对应配置行 |

独立的 `sdk-minimal` profile 固定 `danger-full-access`，且不挂审批/权限 settings 服务。

> **重要**：General settings 中存储的权限影响**后续** Web 会话，不改变已打开的会话。

## 四、网络代理

出站代理在 agent 启动前从环境快照解析，因此 `HTTP_PROXY` / `HTTPS_PROXY`（或写进 `.env` 层）无需额外开关即可生效。见官方 `docs/user/guide/network-proxy.zh.md`。

## 五、遥测与隐私

- **DeepSeek 会话日志上传**：base 默认开启，随后续 DeepSeek 请求发送尚未确认接收的日志后缀。可在 Web **设置 → 通用 → 在使用官方模型 API 时上传 Session Log** 关闭，或把其 `enabled` 设为 `false`。
- **OTel**：base 默认 `FEEDBACK_ONLY`——新的自身文本反馈、评分、编辑与撤回会释放截至该事件的日志前缀。`DSH_TELEMETRY_MODE=DISABLED` 禁止投递。
- 两条路径都不改变模型输入，但导出可能包含消息文本、工具参数与结果、工作区路径。

## 六、反向代理部署

在反代之后发布 Web UI：

- `--public-url <url>` 公告唯一的 HTTP(S) 应用根（可带转发前缀），替代监听器的 loopback URL。它**不授予信任**。
- 浏览器可见的 authority 仍需用 `--trusted-host <host>` 点名（可重复）。
- 前置代理必须提供的内容见官方 `docs/user/guide/public-deployments.zh.md`。

```sh
dsh web --public-url https://dsh.example.com --trusted-host dsh.example.com
```

下一课：[插件系统：Cordis 核心概念](05-插件系统-Cordis核心概念.md)
