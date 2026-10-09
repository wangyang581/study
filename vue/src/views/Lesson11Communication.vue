<script setup>
// ===================================================================
// 第 11 课：组件通信全景
//   父 → 子：props
//   子 → 父：emit
//   双向：  组件 v-model（defineModel）
//   跨层级：provide / inject
//   父调子方法：模板引用 + defineExpose
//   任意组件：Pinia（第 16 课）
// ===================================================================
import { provide, ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'
import StarRating from '@/components/StarRating.vue'
import ThemeChild from '@/components/ThemeChild.vue'
import ExposeChild from '@/components/ExposeChild.vue'

// ---------- 组件 v-model ----------
const score = ref(3)
const anotherScore = ref(0)

// ---------- provide / inject ----------
const themes = [
  { name: 'Vue 绿', color: '#42b883' },
  { name: '天空蓝', color: '#38bdf8' },
  { name: '活力橙', color: '#f97316' },
  { name: '优雅紫', color: '#8b5cf6' },
]
const themeIndex = ref(0)
const theme = ref(themes[0])

function switchTheme() {
  themeIndex.value = (themeIndex.value + 1) % themes.length
  theme.value = themes[themeIndex.value]
}

// provide 让「所有后代」都能注入这些值。
// 这里直接把 ref 提供出去，后代注入后仍是响应式的。
provide('theme', theme)
provide('switchTheme', switchTheme)

// ---------- 父组件调用子组件方法 ----------
const childRef = ref(null)
const exposed = ref('（还没调用）')

function callChildFocus() {
  childRef.value.focus()
  exposed.value = '已调用子组件的 focus()'
}
function callChildSet() {
  childRef.value.setValue('被父组件写入的内容')
  exposed.value = `已调用 setValue() → 现在内部值是「${childRef.value.getValue()}」`
}
function callChildClear() {
  childRef.value.clear()
  exposed.value = '已调用 clear()'
}
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. 组件上的 v-model（子组件用 defineModel）" hint="让子组件像输入框一样支持 v-model，实现「父子双向绑定」。">
    <div class="demo-row">
      <span>评分：</span>
      <StarRating v-model="score" />
      <span class="tag">父组件里的 score = {{ score }}</span>
    </div>

    <div class="demo-row" style="margin-top: 10px">
      <span>另一个：</span>
      <StarRating v-model="anotherScore" :max="10" />
      <span class="tag">anotherScore = {{ anotherScore }}</span>
    </div>

    <pre class="code">// 子组件 StarRating.vue —— 一行搞定双向绑定
const model = defineModel({ type: Number, default: 0 })
model.value = 5   // 会同步给父组件

// 父组件
&lt;StarRating v-model="score" :max="10" /&gt;</pre>

    <p class="note">
      它的原理其实就是：<code>v-model="score"</code> ≡
      <code>:model-value="score"</code> + <code>@update:model-value="score = $event"</code>。
      想用别的名字？写 <code>v-model:score</code> 和 <code>defineModel('score')</code> 即可。
    </p>
  </DemoCard>

  <DemoCard title="2. provide / inject：跨层级传值" hint="不用一层层写 props，祖先直接「广播」，任意深度的后代都能「注入」。">
    <div class="demo-row">
      <span class="tag">祖先组件当前主题：{{ theme.name }}</span>
      <button @click="switchTheme">在祖先组件里切换</button>
    </div>

    <!-- 中间隔了一层普通 div，ThemeChild 依然能拿到数据 -->
    <div style="margin-top: 12px; padding: 12px; border: 1px solid var(--border); border-radius: 8px">
      <p style="font-size: 13px; color: var(--muted); margin: 0 0 8px">
        第 1 层（不传递任何 props）
      </p>
      <div style="padding: 12px; background: var(--code-bg); border-radius: 8px">
        <p style="font-size: 13px; color: var(--muted); margin: 0 0 8px">第 2 层（还是不传）</p>
        <ThemeChild />
      </div>
    </div>

    <pre class="code">// 祖先
provide('theme', theme)          // 也可以 provide 一个函数
// 任意深度后代
const theme = inject('theme', defaultValue)</pre>

    <p class="note warn">
      用 provide/inject 传递的是「长期存在的配置」比较合适（主题、国际化、表单上下文）。
      业务数据仍然优先用 props / store，否则组件之间的依赖关系会变得隐晦。
    </p>
  </DemoCard>

  <DemoCard title="3. 父组件调用子组件的方法（模板引用 + defineExpose）" hint="适合「命令式」操作：让输入框聚焦、让弹窗打开、让图表重新渲染。">
    <div class="demo-row">
      <button @click="callChildFocus">聚焦子输入框</button>
      <button @click="callChildSet">写入内容</button>
      <button @click="callChildClear">清空</button>
    </div>
    <p style="font-size: 13px">{{ exposed }}</p>

    <ExposeChild ref="childRef" style="margin-top: 8px" />

    <pre class="code">// 子组件
defineExpose({ focus, clear, setValue, getValue })

// 父组件
const childRef = ref(null)
childRef.value.focus()</pre>
  </DemoCard>

  <DemoCard title="4. 通信方式怎么选？" hint="从简单到复杂，按需升级。">
    <pre class="code">父子直接（1~2 层）       props ↓ + emit ↑        ← 首选，最清晰
父子双向绑定             v-model / defineModel    ← 表单类组件
跨多层、配置类            provide / inject         ← 主题、i18n、表单上下文
父组件需要命令式控制子组件  ref + defineExpose      ← 聚焦、弹窗、图表
完全无关的组件 / 全局数据  Pinia store              ← 用户信息、购物车、路由级共享
兄弟组件通信             提升到共同父组件 或 Pinia  ← 别用事件总线</pre>

    <p class="note">
      一句话原则：<strong>能让数据流向清晰的方式就是好方式</strong>。
      遇到「不知道谁改了我的数据」，通常就是通信方式选错了。
    </p>
  </DemoCard>
</template>
