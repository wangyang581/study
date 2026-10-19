/**
 * dsh-study-helper —— 一个最小但完整的 DSH 组合包插件。
 *
 * 特点：**零运行时依赖**。使用原始 ToolDefinition，不 import 任何 dsh 包，
 * 因此可以 `dsh plugin add` 直接安装，无需 pnpm install、无需 allowBuilds。
 *
 * 演示：
 *  - inject 声明依赖服务（tools）
 *  - ctx.tools.register 注册模型可调用的工具
 *  - ctx.get('commands') 做可选依赖，存在时注册 /focus 斜杠命令
 */

export const name = 'dsh-study-helper'

// Cordis 会等 tools 服务就绪后才执行 apply。
export const inject = ['tools']

const TIPS = [
  '把今天学的东西用自己的话讲一遍，讲不清的地方就是没懂的地方。',
  '每学一个 API，立刻写一个最小可运行示例。',
  '先修好一个失败的小测试，再开始下一个功能。',
  '读源码时先看类型定义和公开接口，再看实现。',
  '卡住超过 20 分钟就先记录下来，换个任务再回来。',
]

const FOCUS = [
  '读概念 + 记下 3 个疑问',
  '跟着官方示例写一个最小 demo',
  '脱离示例独立重写一遍',
  '做 2 道练习题并解释为什么',
  '复述 + 整理成笔记',
  '读相关源码，理解它如何实现',
  '做一个整合小项目或重构',
]

export function apply(ctx) {
  // 1) 工具：模型可调用。register 返回 disposer，插件卸载时自动注销。
  ctx.tools.register({
    name: 'study_plan',
    description: 'Generate a short, concrete study plan for a topic.',
    parameters: {
      topic: { type: 'string', required: true, description: 'What to study' },
      days: { type: 'number', description: 'How many days the plan should cover (default 3)' },
    },
    output: {
      // execute 只返回规范值；render 转成面向模型的内容块。
      schema: { type: 'string' },
      render: (_args, value) => [{ type: 'text', text: value }],
    },
    async execute(args) {
      const days = typeof args.days === 'number' && args.days > 0 ? Math.floor(args.days) : 3
      const lines = [`${args.topic} · ${days} 天学习计划`, '']
      for (let i = 1; i <= days; i++) {
        lines.push(`第 ${i} 天：${FOCUS[(i - 1) % FOCUS.length]}`)
      }
      lines.push('', '每天结束时用自己的话复述一遍，并写一个最小示例。')
      return lines.join('\n')
    },
  })

  // 2) 命令：可选依赖。headless 等无 UI 模式可能没有 commands 服务。
  const commands = ctx.get('commands')
  if (commands) {
    commands.register({
      name: 'focus',
      description: 'Show a random study tip',
      handler: () => ({
        kind: 'success',
        text: TIPS[Math.floor(Math.random() * TIPS.length)],
      }),
    })
  }
}
