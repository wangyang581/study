# dsh-study-helper

一个最小但完整的 DeepSeek Harness **组合包（bundle）**示例，对应教程
[`docs/08-Profile与组合包.md`](../../docs/08-Profile与组合包.md)。

它注册：

| 类型 | 名称 | 说明 |
| --- | --- | --- |
| 工具 | `study_plan` | 根据主题和天数生成一份学习计划，模型可调用 |
| 命令 | `/focus` | 随机显示一条学习建议（可选依赖 `commands` 服务） |

**零运行时依赖**：使用原始 ToolDefinition，不 import 任何 dsh 包，因此安装时无需
`pnpm install`，也无需 `allowBuilds` 授权。

## 安装

```sh
# 在包含本目录的路径下执行（相对 spec 会锚定到调用目录）
dsh plugin --profile web add /Users/wang/Code/study/dsh/examples/study-bundle

# 验证层已加入（应看到 dsh-study-helper 层）
dsh --profile web --dump-config

# 组合包成员变化需要重启 profile
dsh --profile web
```

> 从源码运行时把 `dsh ...` 换成 `pnpm dsh ...`。

## 使用

启动 Web UI 后，在会话里：

```text
帮我用 study_plan 工具制定一个 5 天的 Vue 3 学习计划。
```

或在输入框输入斜杠命令：

```text
/focus
```

## 卸载

```sh
dsh plugin --profile web remove dsh-study-helper
```

## 发布

```sh
pnpm publish --access public
# 之后别人可：
dsh plugin --profile web add dsh-study-helper
```
