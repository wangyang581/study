/**
 * 最小 DeepSeek Harness 插件。
 *
 * 加载方式：作为 --patch overlay 插入运行中的 dsh（见同目录 cordis.yml）。
 * 插件路径必须是绝对路径。
 */
import type { Context } from '@deepseek-ai/cordis'

export const name = 'hello-plugin'

export function apply(ctx: Context) {
  // 依赖在 apply 运行前已经就绪。这里的 console.log 会打印到启动 dsh 的终端。
  console.log('[hello-plugin] plugin loaded!')

  // 任何通过 ctx 注册的东西都会在插件卸载时自动清理。
  // 需要手动清理的资源用 ctx.effect(() => { ...; return () => cleanup() })。
}
