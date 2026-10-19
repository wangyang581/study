# scratch-plugin：第一个插件与工具

对应教程 [`docs/06-开发第一个插件与工具.md`](../../docs/06-开发第一个插件与工具.md)。

## 文件

| 文件 | 作用 |
| --- | --- |
| `src/my-plugin.ts` | 最小插件：`apply(ctx)`，启动时打印日志 |
| `src/greet-tool.ts` | 带配置的自定义工具 `greet` |
| `cordis.yml` | `--patch` 覆盖层，把上面两个插件插入运行中的 dsh |

## 运行

1. 把 `cordis.yml` 里的 `/absolute/path/to/deepseek-harness` 换成你本地 repo 的绝对路径。
2. 在 deepseek-harness 仓库根目录（已 `pnpm install && pnpm run build`）执行：

```sh
pnpm dsh web --patch /Users/wang/Code/study/dsh/examples/scratch-plugin/cordis.yml
```

3. 打开 `http://127.0.0.1:3080`，终端应出现 `[hello-plugin] plugin loaded!`。
4. 在会话里输入：`Use the greet tool to greet Ada.`，模型应调用 `greet` 并收到 `Hi there, Ada!`。

## 调试

- 改源码或 `cordis.yml` 后，配置了 HMR 的 base profile 会自动热替换插件。
- 想让插件加载失败时看到原因：启动诊断会打印失败插件与原始堆栈，完整日志在 `$DSH_HOME/logs/startup-*.log`。
