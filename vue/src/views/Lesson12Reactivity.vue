<script setup>
// ===================================================================
// 第 12 课：组合式 API 与响应式原理
//   ref      → 任意类型的响应式包装，脚本里用 .value
//   reactive → 对象的响应式代理，直接访问属性（不用 .value）
//   两者最终都靠 Proxy 拦截读写，从而「知道」数据何时变化。
// ===================================================================
import { computed, reactive, readonly, ref, shallowRef, toRefs } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'
import { useCounter } from '@/composables/useCounter'

// ---------- 1. ref 与 reactive 对比 ----------
const count = ref(0)                 // 基础类型必须用 ref
const user = reactive({ name: '小明', age: 18, address: { city: '杭州' } })

function ageUp() {
  count.value++          // ref 脚本里要 .value
  user.age++             // reactive 直接改
}

// ---------- 2. reactive 的坑：解构会丢失响应式 ----------
const state = reactive({ a: 1, b: 2 })

// ❌ 错误示范：直接解构得到的只是「当时的快照」，永远不再变化
const plainA = state.a

// ✅ 正确示范：toRefs 把每个属性转成 ref，并且和源对象保持连接
const { a, b } = toRefs(state)

function bumpA() {
  state.a++ // 改 state.a，a.value 会跟着变；而 plainA 永远是 1
}

// ---------- 3. shallowRef：只有整体替换才触发更新 ----------
const shallow = shallowRef({ deep: { n: 1 } })
const shallowLog = ref([])
function mutateDeep() {
  shallow.value.deep.n++ // ❌ 不会触发视图更新（内部属性不是响应式的）
  shallowLog.value.unshift(`改了深层属性 n=${shallow.value.deep.n}，但视图没变`)
}
function replaceWhole() {
  shallow.value = { deep: { n: shallow.value.deep.n + 1 } } // ✅ 整体替换会触发
  shallowLog.value.unshift(`整体替换了对象 → n=${shallow.value.deep.n}，视图更新`)
}

// ---------- 4. readonly：防止下游随意改动 ----------
const config = reactive({ api: '/api', retries: 3 })
const safeConfig = readonly(config)
function tryBypassReadonly() {
  // safeConfig.retries = 99  // 控制台会警告，且赋值无效
  config.retries++           // 通过原始对象改是允许的
  shallowLog.value.unshift(`readonly 代理值 = ${safeConfig.retries}（跟随源对象变化）`)
}

// ---------- 5. 使用组合式函数 ----------
// 一行代码就获得一整套计数器逻辑：状态 + 派生状态 + 方法
const c1 = useCounter(0, { min: 0, max: 10, step: 1 })
const c2 = useCounter(100, { step: 10 })
const c3 = useCounter(0, { min: 0, max: 3, step: 1 })

// ---------- 6. 响应式原理小实验 ----------
// 用一个 computed 来展示「依赖收集」：只有它依赖的数据变化时，它才重新计算
const x = ref(1)
const y = ref(10)
const reCalcTimes = ref(0)
const xTimesY = computed(() => {
  reCalcTimes.value++
  return x.value * y.value
})
// 注意：computed 内部读取 x、y → 建立依赖；读取 reCalcTimes 只写不读，不建立依赖
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. ref vs reactive" hint="选择建议：基础类型用 ref；表单/对象集合用 reactive；不确定就用 ref。">
    <div class="demo-row">
      <button class="primary" @click="ageUp">count++ / age++</button>
      <span class="tag">count(ref) = {{ count }}</span>
      <span class="tag">user(reactive).age = {{ user.age }}</span>
    </div>

    <pre v-pre class="code">const count = ref(0)          // 脚本里：count.value
const user = reactive({ age: 18 })   // 脚本里：user.age

// 模板里两者都自动解包，直接写 count / user.age
// 注意：模板中 ref 只有作为「顶层属性」时才自动解包：
//   {{ count }}        ✅ 0
//   {{ {count}.count }} ❌ 得到的是 ref 对象</pre>

    <p class="note">
      <code>ref</code> 本质上是一个带 <code>.value</code> getter/setter 的对象，
      对象类型时内部会用 <code>reactive</code> 做深层代理。
      所以「ref 能包所有类型，reactive 只能包对象」。
    </p>
  </DemoCard>

  <DemoCard title="2. reactive 解构会丢失响应式" hint="这是初学者最容易踩的坑之一，用 toRefs 解决。">
    <div class="demo-row">
      <button class="primary" @click="bumpA">state.a++（当前 state.a = {{ state.a }}）</button>
    </div>

    <div class="demo-row" style="margin-top: 10px">
      <span class="tag">✅ toRefs 解构出的 a = {{ a }}（跟着变）</span>
      <span class="tag">✅ toRefs 解构出的 b = {{ b }}</span>
      <span class="tag">❌ 普通快照 plainA = {{ plainA }}（永远不变）</span>
    </div>

    <pre class="code">const state = reactive({ a: 1, b: 2 })

// ❌ 丢失响应式：plainA 只是「1」这个数字的副本
const plainA = state.a

// ✅ 用 toRefs 转成 ref，与源对象保持连接
const { a, b } = toRefs(state)
a.value = 5      // 等价于 state.a = 5
state.a = 9      // 反过来，a.value 也变成 9</pre>
  </DemoCard>

  <DemoCard title="3. shallowRef 与 readonly" hint="性能优化与「数据保护」的两个工具。">
    <div class="demo-row">
      <button @click="mutateDeep">改 shallowRef 深层属性（视图不变）</button>
      <button class="primary" @click="replaceWhole">整体替换 shallowRef（视图更新）</button>
      <button @click="tryBypassReadonly">通过源对象改 readonly 包装值</button>
    </div>

    <p style="margin-top: 10px">
      shallowRef 当前值：<span class="tag">n = {{ shallow.deep.n }}</span>
      · readonly 当前值：<span class="tag">retries = {{ safeConfig.retries }}</span>
    </p>

    <div class="code">
      <div v-for="(l, i) in shallowLog" :key="i">{{ l }}</div>
      <div v-if="!shallowLog.length">（点上面的按钮看日志）</div>
    </div>

    <pre class="code">shallowRef(obj)  // 只代理 obj 本身，深层变化不触发更新 —— 适合大数据/第三方实例
readonly(obj)    // 只读代理，写入会警告；但源对象变化时它仍会更新</pre>
  </DemoCard>

  <DemoCard title="4. 组合式函数（Composable）：逻辑复用" hint="同一套逻辑用三份，各自独立，互不干扰 —— 这就是「组合」的威力。">
    <div class="grid-2">
      <div>
        <strong>计数器 1（0~10，步长 1）</strong>
        <div class="demo-row">
          <button :disabled="!c1.canDecrease.value" @click="c1.decrease">-</button>
          <span class="tag">{{ c1.count.value }}</span>
          <button :disabled="!c1.canIncrease.value" @click="c1.increase">+</button>
          <button @click="c1.reset">重置</button>
        </div>
      </div>

      <div>
        <strong>计数器 2（步长 10）</strong>
        <div class="demo-row">
          <button @click="c2.decrease">-10</button>
          <span class="tag">{{ c2.count.value }}</span>
          <button @click="c2.increase">+10</button>
        </div>
      </div>

      <div>
        <strong>计数器 3（0~3，有奇偶判断）</strong>
        <div class="demo-row">
          <button :disabled="!c3.canDecrease.value" @click="c3.decrease">-</button>
          <span class="tag">{{ c3.count.value }} · {{ c3.isEven.value ? '偶数' : '奇数' }}</span>
          <button :disabled="!c3.canIncrease.value" @click="c3.increase">+</button>
        </div>
      </div>
    </div>

    <pre class="code">// composables/useCounter.js
export function useCounter(initial = 0, options = {}) {
  const count = ref(initial)
  const canIncrease = computed(() => count.value + step &lt;= max)
  function increase() { if (canIncrease.value) count.value += step }
  return { count, canIncrease, canDecrease, isEven, increase, decrease, reset }
}

// 组件里
const c1 = useCounter(0, { max: 10 })
const c2 = useCounter(100, { step: 10 })</pre>

    <p class="note">
      注意：composable 返回的 ref 在 <code>&lt;script setup&gt;</code> 里要写
      <code>c1.count.value</code>，而 <code>c1.count</code> 在模板里会自动解包。
      这是 Vue 3.5+ 仍存在的一个心智负担，习惯就好。
    </p>
  </DemoCard>

  <DemoCard title="5. 响应式是怎么做到「自动更新」的？" hint="依赖收集：谁读了数据，就被记下来；数据变了，就去通知它们。">
    <div class="demo-row">
      <button @click="x++">x++ ({{ x }})</button>
      <button @click="y++">y++ ({{ y }})</button>
      <span class="tag">x × y = {{ xTimesY }}</span>
      <span class="tag">computed 实际重算 {{ reCalcTimes }} 次</span>
    </div>

    <pre class="code">// computed 第一次求值时「读取」了 x 和 y → 被记录为依赖
const xTimesY = computed(() => x.value * y.value)

// x 或 y 变化 → 标记 computed 为「脏」→ 下次被读取时重新计算
// 多次修改但在同一个 tick 内 → 只重新计算一次（批量更新）</pre>

    <p class="note">
      想深入了解，可以搜索：<strong>Proxy / Reflect、依赖收集（track）、派发更新（trigger）、
      effect、调度器（scheduler）</strong>。Vue 3 用 Proxy 替代了 Vue 2 的
      <code>Object.defineProperty</code>，因此能侦测新增/删除属性、数组下标赋值。
    </p>
  </DemoCard>
</template>
