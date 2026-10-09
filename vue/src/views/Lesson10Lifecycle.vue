<script setup>
// ===================================================================
// 第 10 课：生命周期钩子 与 模板引用（template ref）
// 生命周期 = 组件从创建到销毁经历的几个阶段。你在对应阶段注册回调，
// 就能在「正确的时机」做「正确的事」。
// ===================================================================
import { nextTick, onBeforeMount, onBeforeUnmount, onMounted, onUpdated, ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'
import LifecycleChild from '@/components/LifecycleChild.vue'

// ---------- 生命周期日志 ----------
const logs = ref([])
function log(msg) {
  logs.value.unshift(`${new Date().toLocaleTimeString()}  ${msg}`)
}
log('setup 执行：数据初始化，尚无 DOM')

onBeforeMount(() => log('onBeforeMount：DOM 即将挂载'))
onMounted(() => log('onMounted：DOM 已就绪（最常用：发请求、拿 DOM、注册事件）'))

// ⚠️ 注意：onUpdated 里修改响应式数据会导致「无限循环」——
// 修改数据 → 重新渲染 → onUpdated → 又修改数据 → ……
// 所以这里加个上限保护，实际开发中也应尽量避免在 onUpdated 里改状态。
let updatedLogged = 0
onUpdated(() => {
  if (updatedLogged++ < 3) log('onUpdated：数据变化导致重新渲染完成（只记录前 3 次）')
})

onBeforeUnmount(() => log('onBeforeUnmount：组件即将卸载（清理副作用）'))

// ---------- 模板引用：拿到真实 DOM ----------
const inputEl = ref(null)
const boxEl = ref(null)
const boxSize = ref({ w: 0, h: 0 })

onMounted(() => {
  // 挂载后才能拿到 DOM，直接调用原生 API 聚焦
  inputEl.value?.focus()
  measure()
  window.addEventListener('resize', measure)
})

function measure() {
  if (!boxEl.value) return
  // getBoundingClientRect 是原生 DOM API，Vue 并不限制你用它
  const rect = boxEl.value.getBoundingClientRect()
  boxSize.value = { w: Math.round(rect.width), h: Math.round(rect.height) }
}

// 卸载时一定要移除全局事件监听，否则会内存泄漏
onBeforeUnmount(() => window.removeEventListener('resize', measure))

// ---------- 计时器：一定要在卸载时清理 ----------
const seconds = ref(0)
let timer = null

onMounted(() => {
  timer = setInterval(() => seconds.value++, 1000)
})
onBeforeUnmount(() => {
  clearInterval(timer)
  log('已清理计时器')
})

// ---------- nextTick：等 DOM 更新完再做操作 ----------
const items = ref(['A'])
const listEl = ref(null)
const lastHeight = ref(0)

async function addAndMeasure() {
  items.value.push(String.fromCharCode(65 + items.value.length))
  // 此刻 DOM 还没更新，直接量高度会得到旧值
  log(`push 之后立刻量：${listEl.value?.offsetHeight}px（旧值）`)
  await nextTick()
  lastHeight.value = listEl.value?.offsetHeight
  log(`await nextTick() 之后量：${lastHeight.value}px（新值）`)
}

// ---------- 控制子组件的挂载/卸载，观察父子的顺序 ----------
const showChild = ref(true)
const childValue = ref(0)
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. 生命周期执行顺序" hint="打开浏览器控制台，与页面上的日志对照看。">
    <div class="demo-row">
      <button @click="childValue++">改变子组件 props（触发更新）</button>
      <button :class="{ danger: showChild }" @click="showChild = !showChild">
        {{ showChild ? '卸载子组件' : '挂载子组件' }}
      </button>
    </div>

    <LifecycleChild v-if="showChild" :value="childValue" style="margin-top: 12px" />

    <p class="hint" style="margin-top: 14px">生命周期日志（最新在上）：</p>
    <div class="code" style="max-height: 220px; overflow: auto">
      <div v-for="(l, i) in logs" :key="i">{{ l }}</div>
    </div>

    <pre class="code">父 beforeCreate → 父 created → 父 beforeMount
  → 子 beforeCreate → 子 created → 子 beforeMount → 子 mounted
→ 父 mounted
（卸载时正好相反：父先开始卸载，子先完成卸载）</pre>

    <p class="note">
      Vue 3 组合式 API 里没有 <code>beforeCreate</code> / <code>created</code>：
      <code>&lt;script setup&gt;</code> 的函数体本身就相当于它们的时机
      ——「数据已初始化、DOM 还没有」。
    </p>
  </DemoCard>

  <DemoCard title="2. 模板引用 ref：拿到真实 DOM" hint="在元素上写 ref='名字'，再用同名的 ref 变量接收。注意变量名要和 ref 属性的字符串一致。"
  >
    <div class="demo-row">
      <input ref="inputEl" placeholder="页面加载后我会自动获得焦点" />
      <button @click="inputEl?.focus()">再次聚焦</button>
      <button @click="measure">重新测量盒子</button>
    </div>

    <div ref="boxEl" class="measure-box" style="margin-top: 12px">
      我可以被测量
    </div>
    <p>
      盒子尺寸：<span class="tag">{{ boxSize.w }} × {{ boxSize.h }} px</span>
      <small style="color: var(--muted)">（拖动窗口大小会实时更新）</small>
    </p>

    <pre class="code">const inputEl = ref(null)
onMounted(() => inputEl.value.focus())   // 必须在挂载后才能访问</pre>
  </DemoCard>

  <DemoCard title="3. 清理副作用：计时器与全局事件" hint="组件卸载后如果定时器还在跑，它会继续引用组件数据 → 内存泄漏 + 报错。">
    <div class="demo-row">
      <span class="tag">已运行 {{ seconds }} 秒</span>
    </div>
    <p class="note warn">
      规律：<strong>onMounted 里注册了什么，onBeforeUnmount 里就要清理什么</strong>。
      典型对象：setInterval、window/document 事件、WebSocket、第三方实例。
    </p>
  </DemoCard>

  <DemoCard title="4. nextTick：等待 DOM 更新完成" hint="Vue 的更新是「异步批量」的。改完数据后，DOM 不会立刻变化。">
    <ul class="plain" ref="listEl">
      <li v-for="i in items" :key="i">{{ i }}</li>
    </ul>
    <div class="demo-row">
      <button class="primary" @click="addAndMeasure">添加一项并测量高度</button>
      <span class="tag">当前高度 {{ lastHeight }}px</span>
    </div>

    <pre class="code">items.value.push('B')          // DOM 还没变
await nextTick()               // 等这一轮渲染完成
console.log(listEl.value.offsetHeight)  // 现在才是新高度</pre>
  </DemoCard>

  <DemoCard title="5. 钩子速查表" hint="常用的其实只有两三个，其余了解即可。">
    <pre class="code">onBeforeMount     挂载前（DOM 还没生成）
onMounted         挂载完成 ← 最常用：请求数据、初始化第三方库、拿 DOM
onBeforeUpdate    数据更新、DOM 尚未重新渲染
onUpdated         数据更新、DOM 已重新渲染 ← 慎用，容易造成死循环
onBeforeUnmount   卸载前 ← 清理副作用
onUnmounted       卸载完成
onActivated       keep-alive 缓存的组件被激活
onDeactivated     keep-alive 缓存的组件被停用
onErrorCaptured   捕获后代组件抛出的错误
onServerPrefetch  SSR 时预取数据</pre>
  </DemoCard>
</template>

<style scoped>
.measure-box {
  padding: 24px;
  background: var(--code-bg);
  border-radius: 8px;
  display: inline-block;
  resize: both;
  overflow: auto;
  border: 1px dashed var(--border);
}
</style>
