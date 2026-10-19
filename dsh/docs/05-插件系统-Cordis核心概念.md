# 05 · 插件系统：Cordis 核心概念

> 这一课讲「一个 dsh 插件由什么构成」。想边动手边学，先看官方 [`docs/cordis-tutorial/`](https://github.com/deepseek-ai/deepseek-harness/tree/main/docs/cordis-tutorial)（在临时目录里从零搭 Cordis，不需要 API key），或看下一课直接写 harness 插件。

## 1. 插件就是导出 `apply` 的模块

一个 dsh 插件导出 `apply` 函数，框架在加载时调用它并传入 `ctx`（上下文）。你通过 `ctx` 注册能力：

```ts
import type { Context } from '@deepseek-ai/cordis'

export const name = 'my-plugin'

export function apply(ctx: Context) {
  // 在这里注册能力
}
```

**这就是全部。** `name` 是可选的稳定标识，`inject` 声明依赖。

## 2. 插件的三种形态

### 函数形态（最常用）

```ts
import type { Context } from '@deepseek-ai/cordis'

export const name = 'my-plugin'
export const inject = ['tools']      // 依赖声明

export function apply(ctx: Context, config: Config) {
  ctx.tools.register(/* ... */)
}
```

### 对象形态

```ts
import type { Context } from '@deepseek-ai/cordis'

export default {
  name: 'my-plugin',
  inject: ['tools'],
  apply(ctx: Context) {
    // ...
  },
}
```

### 类形态（当你的插件要对外提供服务时）

```ts
import { Service, type Context } from '@deepseek-ai/cordis'

export default class MyService extends Service {
  static inject = ['tools']

  constructor(ctx: Context) {
    super(ctx, 'myService')   // 服务名 -> ctx.myService
    // 在构造函数里做同步初始化
  }
}
```

> 大多数情况函数形态就够了；只有需要向其他插件**提供服务**时才用类形态。

## 3. 依赖注入：`inject`

声明所需服务后，框架**保证 `apply` 执行时它们已经就绪**；服务不齐时插件不会执行。

```ts
export const inject = ['tools', 'llm']

export function apply(ctx: Context) {
  // ctx.tools 和 ctx.llm 已就绪
}
```

- **必需依赖**：用 `inject` 数组；服务消失时插件自动卸载（ACTIVE → DISPOSED），服务恢复后自动重新加载。
- **可选依赖**：不写 `inject`，在使用处用 `ctx.get('serviceName')` 查询：

```ts
export function apply(ctx: Context) {
  const metrics = ctx.get('metrics')
  metrics?.record('plugin_loaded', 1)
}
```

## 4. 自动清理：注册都是副作用

通过 `ctx` 做的任何注册，在插件卸载时**自动撤销**：

```ts
export function apply(ctx: Context) {
  ctx.on('some-event', handler)            // 卸载时自动移除
  ctx.tools.register(tool)                 // 卸载时自动注销
  ctx.llm.registerAdapter(names, adapter)  // 自动撤销

  ctx.effect(() => {                       // 自定义资源
    const connection = createConnection()
    return () => connection.close()        // 返回 disposer
  })
}
```

- 你**不需要**手动 `removeListener` / `clearInterval`。
- 处置器按注册顺序的**逆序**开始调用，但多个异步处置器会**并发**执行。有顺序依赖的清理必须放进**同一个** `ctx.effect()` 返回的 disposer 里串行等待。
- 定时器要这样写：

```ts
export function apply(ctx: Context) {
  ctx.effect(() => {
    const timer = setInterval(() => console.log('heartbeat'), 5000)
    return () => clearInterval(timer)
  })
}
```

## 5. 子插件与上下文

`ctx.plugin()` 创建子 Fiber，继承父上下文但有独立生命周期：

```ts
export function apply(ctx: Context) {
  ctx.plugin(childPlugin)   // 子插件随父插件一起卸载
}
```

你也可以在子上下文里注册只在某个 scope 生效的东西（例如按 agent 隔离）。

## 6. 生命周期状态机（Fiber）

每个被加载的插件都拥有一个 **Fiber** 作用域：

```
PENDING → LOADING → ACTIVE
                 ↘ FAILED
ACTIVE → UNLOADING → DISPOSED
```

| 状态 | 含义 |
| --- | --- |
| PENDING | 已声明，但所需依赖未就绪 |
| LOADING | 依赖就绪，正在执行 `apply` |
| ACTIVE | 插件运行中 |
| FAILED | `apply` 抛异常 |
| UNLOADING | 正在卸载并释放资源 |
| DISPOSED | 已完全卸载 |

提前终止一个插件实例：

```ts
const fiber = ctx.plugin(myPlugin)
await fiber.dispose()   // 移除其全部注册、递归卸载子插件、等待异步清理完成
```

## 7. 事件：插件间通信

### 监听与触发

```ts
ctx.on('my-plugin/ready', (payload) => { /* ... */ })
ctx.emit('my-plugin/ready', { id: 'worker-1' })
```

### 五种分发模式

| 模式 | 语义 |
| --- | --- |
| `emit` | 广播，所有监听器同步执行，忽略返回值 |
| `bail` | 按序执行，首个非 `null`/`false`/`undefined` 的返回值成为最终结果并终止后续 |
| `serial` | 按序 await 执行，首个非空值终止 |
| `parallel` | 并行 await，无返回值 |
| `waterfall` | 环绕中间件，**必须调用 `next()`**；不调用即短路 |

`waterfall` 示例：

```ts
// 分发
const output = await ctx.waterfall('my-plugin/transform', input, async () => input)

// 监听：next() 是强制的
ctx.on('my-plugin/transform', async (_input, next) => {
  const downstream = await next()
  return downstream.trim()
})
```

### 类型安全的事件

用 TypeScript 声明合并注册事件签名：

```ts
import '@deepseek-ai/cordis'

declare module '@deepseek-ai/cordis' {
  interface Events {
    'my-plugin/ready': (payload: { id: string }) => void
    'my-plugin/check': (input: string) => boolean | undefined
    'my-plugin/transform': (input: string, next: () => Promise<string>) => Promise<string>
  }
}
```

### 事件监听器也是副作用

`ctx.on()` 注册的监听器随插件卸载自动移除。

## 8. Harness 的命名约定

- Cordis 事件遵循 `namespace/action`：`agent/pre-step`、`agent/request`、`agent/request-error`、`tools/result`、`session/event`…
- **持久化会话事件**（`turn/*`、`step/*`、`tool/call`、`tool/result`、`compaction/*`）要用 `session/event` 观察，检查 `event.type`。
- 完整签名与分发模式见各子系统的生成区块（`docs/subsystems/*.zh.md` 的 `cordis-surface`）。

### 一个日志插件示例

```ts
import type { Context } from '@deepseek-ai/cordis'
import '@deepseek-ai/dsh-tools'

export const name = 'tool-logger'

export function apply(ctx: Context) {
  ctx.on('tools/result', (exec, result) => {
    console.log(`[tool] ${exec.name}(${JSON.stringify(exec.arguments)})`)
    const text = result.content
      .map(block => (block.type === 'text' ? block.text : ''))
      .join('')
    console.log(`[tool result] ${text.slice(0, 100)}`)
  })
}
```

## 9. 组合与 HMR

`cordis.yml` 把插件写成一棵条目树；同一份文档既描述**有哪些插件**，也描述**如何配置它们**：

```yaml
- id: my-plugin
  name: './src/my-plugin.ts'
  config:
    greeting: 'Hi'
```

- **HMR（热模块替换）**：base profile 启用 `dsh-hmr` 后，修改插件源码会**卸载旧插件 → 重载新代码 → 执行新 `apply`**。因为注册都会被清理，热替换不会保留旧实例的注册。
- 配置变更也会触发插件热替换。
- Headless、SDK、ACP 禁用 HMR；`sdk-minimal` 不含它。

## 10. 实践规则

- **行为都封装成插件**：工具流水线事件属于 `ctx.tools`，模型流式输出属于 `ctx.llm`，实时 agent 协调属于 `ctx.agents`。
- **拦截/策略优先用事件；直接能力调用优先用服务方法。**
- **每个注册都要有对应 disposer**：要么从 `ctx.effect()` 返回，要么用 Cordis 提供的辅助方法自动处理。
- **长生命周期资源不要放在工厂函数里**：放到插件加载后或首次使用时，并在 disposer 里关闭。
- **依赖用 `inject` 表达**，不要手动编排启动顺序。

下一课：[开发第一个插件与工具](06-开发第一个插件与工具.md)
