# DeepSeek Harness（`dsh`）学习教程

本目录是一套渐进式教程，教你使用 **DeepSeek Harness**（命令行名 `dsh`）——DeepSeek AI 开源的 agent harness，以及它的**社区插件生态**来搭建自己的 Agent。

> 官方仓库：<https://github.com/deepseek-ai/deepseek-harness>
> 官方文档站：<https://deepseek-harness.github.io/deepseek-harness/>
> 运行方式：`npx @deepseek-ai/dsh web`

## 它是什么

DeepSeek Harness 既是一个**可直接运行的 Coding Agent**（Web UI / headless），又是一套**「一切皆插件」的框架**：

- 底层是 [Cordis](https://github.com/cordiverse/cordis) 插件框架——模型适配器、工具、沙箱、会话存储、UI，**乃至 Agent Loop 本身都是插件**。
- 没有需要打补丁的特权内核：扩展 dsh 的方式是把插件挂到其他插件旁边；每个注册都是可逆副作用，插件卸载时自动撤销。
- 插件可以打包成 **bundle（组合包）**，通过 npm / git 分发；社区插件通过 `dsh plugin add` 安装。

```
┌─────────────────────────── dsh = 一棵插件树 ───────────────────────────┐
│  profile（web / headless / sdk / sdk-minimal / acp）                     │
│    └─ bundles（dsh-base, dsh-web-app, 你安装的社区组合包…）               │
│         └─ 每一行是一个插件：llm / tools / agent-loop / session / ui …    │
│  Cordis Context：ctx.tools、ctx.llm、ctx.agents、ctx.sessions …          │
└─────────────────────────────────────────────────────────────────────────┘
```

## 学习路线

| # | 文档 | 你将学会 |
| - | --- | --- |
| 01 | [项目概览与核心概念](docs/01-项目概览与核心概念.md) | `dsh` 是什么、Cordis 五个核心概念、profile/bundle/层 |
| 02 | [安装与运行](docs/02-安装与运行.md) | `npx` 运行、源码运行、profile、CLI 参数、Harness home |
| 03 | [配置模型：DeepSeek 与第三方](docs/03-配置模型-DeepSeek与第三方.md) | API Key、内置/自定义 provider、推理档位、兼容开关 |
| 04 | [使用 Web UI 与 CLI 模式](docs/04-使用WebUI与CLI模式.md) | 工作区、会话、审批、headless / SDK / ACP、沙箱与权限 |
| 05 | [插件系统：Cordis 核心概念](docs/05-插件系统-Cordis核心概念.md) | 插件形态、`apply(ctx)`、`inject`、事件分发、自动清理 |
| 06 | [开发第一个插件与工具](docs/06-开发第一个插件与工具.md) | `cordis.yml` 加载、`defineTool`、配置 schema、HMR |
| 07 | [配置、事件、服务与生命周期](docs/07-配置-事件-服务与生命周期.md) | Schemastery 配置、Service、五种事件模式、工具流水线钩子 |
| 08 | [Profile 与组合包](docs/08-Profile与组合包.md) | bundle manifest、`dsh plugin add`、层顺序、版本兼容 |
| 09 | [社区插件安装与使用](docs/09-社区插件安装与使用.md) | 在哪找、`dsh-market`、`plugin_manager`、分类推荐、安全 |
| 10 | [开发贡献与进阶](docs/10-开发贡献与进阶.md) | 仓库开发环境、检查命令、cookbook、架构文档导航 |

## 配套示例

```
dsh/examples/
├── scratch-plugin/        # 对应官方「第一个插件 / 第一个工具」教程
│   ├── src/my-plugin.ts
│   ├── src/greet-tool.ts
│   └── cordis.yml
└── study-bundle/          # 一个可 dsh plugin add 安装的组合包
    ├── package.json
    ├── index.js
    ├── cordis.patch.yml
    └── README.md
```

## 30 秒上手

```sh
# 直接运行（推荐先体验）
npx @deepseek-ai/dsh web
# 打开 http://127.0.0.1:3080 → 设置 → 模型 → 填 DeepSeek API Key
# → 选择工作区 → 开始对话
```

从源码运行（要开发插件时）：

```sh
git clone https://github.com/deepseek-ai/deepseek-harness.git
cd deepseek-harness
pnpm install
pnpm run build
pnpm dsh web
```

## 重要提醒

> ⚠️ **DeepSeek Harness 处于 developer preview**，会有破坏兼容性的变更。运行前请阅读官方 [`SAFETY.md`](https://github.com/deepseek-ai/deepseek-harness/blob/main/SAFETY.md)。
>
> ⚠️ **安装社区插件 = 在你的机器上运行第三方代码**，权限和你本人一样大，能读文件、用凭据、访问网络，工具审批管不到插件代码。收录不等于安全审查——装之前先看源码，不熟的插件尽量放在没有密钥/重要资料的环境里试。

## 官方文档索引（仓库内）

| 主题 | 路径 |
| --- | --- |
| Web UI 入门 | `docs/user/guide/index.zh.md` |
| 配置模型 | `docs/user/guide/providers.zh.md` |
| 第一个插件 | `docs/user/develop/basic/index.zh.md` |
| 开发工具 | `docs/user/develop/basic/tool.zh.md` |
| 插件配置 | `docs/user/develop/basic/config.zh.md` |
| 打包与安装 | `docs/user/develop/basic/publish.zh.md` |
| 插件/生命周期 | `docs/user/develop/framework/index.zh.md` |
| 服务与依赖 | `docs/user/develop/framework/service.zh.md` |
| 事件系统 | `docs/user/develop/framework/events.zh.md` |
| Cordis 教程（动手） | `docs/cordis-tutorial/index.zh.md` |
| Cordis 入门（概念） | `docs/cordis-primer.zh.md` |
| 架构 | `docs/architecture.zh.md` |
| 工具编写参考 | `docs/cookbook/adding-a-tool.zh.md` |
| CLI 行为参考 | `apps/cli/reference/README.zh.md` |
| 开发指南 | `docs/development.zh.md` |
| 子系统参考（逐包） | `docs/subsystems/README.zh.md` |
| 配置字段总目录 | `docs/config-catalog.zh.md` |
| 工具目录 | `docs/tool-catalog.md` |
