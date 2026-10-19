/**
 * 一个带配置的自定义工具：greet。
 *
 * 演示：
 *  - inject 声明依赖服务（tools）
 *  - defineTool 定义参数 schema、规范输出与渲染
 *  - Config + Schemastery schema 让问候语可配置
 *
 * 加载后，模型可以调用 greet 工具；在 Web UI 里输入
 * "Use the greet tool to greet Ada." 即可看到效果。
 */
import type { Context } from '@deepseek-ai/cordis'
import { defineTool } from '@deepseek-ai/dsh-tools'
import Schema from '@deepseek-ai/schemastery'

export const name = 'greet-tool'

// Cordis 会等 tools 服务就绪后才执行 apply。
export const inject = ['tools']

export interface Config {
  /** 问候语前缀，例如 Hello / Hi there。 */
  greeting: string
}

// 默认值直接写在 schema 里；配置非法时插件加载失败并给出明确错误。
export const Config: Schema<Config> = Schema.object({
  greeting: Schema.string().default('Hello'),
})

export function apply(ctx: Context, config: Config) {
  ctx.tools.register(
    defineTool({
      name: 'greet',
      description: 'Greet someone by name.',
      parameters: {
        name: { type: 'string', required: true, description: 'The name to greet' },
      },
      output: {
        // execute 返回 output.schema 声明的规范化值，render 再转成面向模型的内容。
        schema: { type: 'string' },
        render: (_args, value) => [{ type: 'text', text: value }],
      },
      async execute(args) {
        // args 由 parameters 推导并已校验：{ name: string }
        return `${config.greeting}, ${args.name}!`
      },
    }),
  )
}
