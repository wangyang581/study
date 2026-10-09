<script setup>
// ===================================================================
// 第 6 课：计算属性 computed 与侦听器 watch / watchEffect
// 判断标准：
//   「由其他状态算出来的值」 → computed
//   「状态变化后要做别的事（副作用）」 → watch / watchEffect
// ===================================================================
import { computed, reactive, ref, watch, watchEffect } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'

// ---------- 1. computed 基础 ----------
const firstName = ref('张')
const lastName = ref('三')
// 只读计算属性：函数体里必须 return 一个值
const fullName = computed(() => firstName.value + lastName.value)

// 可写计算属性：提供 get / set
const fullNameWritable = computed({
  get: () => `${firstName.value}${lastName.value}`,
  set(val) {
    firstName.value = val[0] ?? ''
    lastName.value = val.slice(1)
  },
})

// ---------- 2. computed 的缓存特性 ----------
const price = ref(100)
const qty = ref(2)
// 用 ref 计数，才能让模板实时显示（副作用只为教学演示）
const totalCalls = ref(0)
const methodCalls = ref(0)

const total = computed(() => {
  totalCalls.value++ // 统计「实际重算了几次」
  return price.value * qty.value
})

function getTotalByMethod() {
  methodCalls.value++
  return price.value * qty.value
}

// ---------- 3. 购物车综合例子 ----------
const cart = ref([
  { name: '键盘', price: 299, count: 1 },
  { name: '鼠标', price: 99, count: 2 },
])
const totalPrice = computed(() => cart.value.reduce((s, i) => s + i.price * i.count, 0))
const totalCount = computed(() => cart.value.reduce((s, i) => s + i.count, 0))
const discount = computed(() => (totalPrice.value >= 500 ? 0.9 : 1))
const payable = computed(() => (totalPrice.value * discount.value).toFixed(2))

// ---------- 4. watch 侦听 ----------
const keyword = ref('')
const searchLog = ref([])
const status = ref('idle') // 用来展示异步请求的“旧请求作废”技巧

// 侦听单个 ref
watch(keyword, (newVal, oldVal) => {
  searchLog.value.unshift(`"${oldVal}" → "${newVal}"`)
  if (searchLog.value.length > 5) searchLog.value.pop()
})

// 侦听多个源：用数组
const min = ref(0)
const max = ref(100)
watch([min, max], ([newMin, newMax], [oldMin, oldMax]) => {
  if (newMin > newMax) {
    // 可以做校验、纠正
    searchLog.value.unshift(`⚠️ 最小值(${newMin})不能大于最大值(${newMax})`)
  }
})

// ---------- 5. 深度侦听 ----------
const settings = reactive({ theme: 'light', size: 'medium', nested: { dark: false } })
const settingChanged = ref(0)
// 侦听 reactive 对象时，默认就是深度侦听
watch(
  settings,
  () => {
    settingChanged.value++
  },
  { deep: true },
)

// immediate：立即执行一次
const counter = ref(0)
watch(
  counter,
  (v) => {
    if (v >= 5) searchLog.value.unshift(`🎉 到达 ${v}，触发一次副作用`)
  },
  { immediate: true },
)

// ---------- 6. watchEffect：自动收集依赖 ----------
const a = ref(1)
const b = ref(2)
const effectLog = ref('')
watchEffect(() => {
  // 用到了 a 和 b，Vue 自动把两者都作为依赖
  effectLog.value = `a=${a.value}, b=${b.value}, a+b=${a.value + b.value}`
})
// 注意：watchEffect 里用到了 effectLog，会造成循环？
// 不会 —— 对 effectLog 是「写」，只有「读」才会被收集为依赖。
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. computed 基础与可写计算属性" hint="computed 的返回值也是一个 ref，模板里会自动解包。">
    <div class="demo-row">
      <input v-model="firstName" style="width: 80px" />
      <input v-model="lastName" style="width: 80px" />
      <span class="tag">fullName = {{ fullName }}</span>
    </div>

    <div class="demo-row" style="margin-top: 12px">
      <label>直接改 fullName：</label>
      <input v-model="fullNameWritable" />
      <span class="tag">通过 setter 反推 firstName/lastName</span>
    </div>
  </DemoCard>

  <DemoCard title="2. computed 会缓存，方法不会" hint="这是 computed 与方法最大的区别：依赖不变就直接返回缓存值。">
    <div class="demo-row">
      <button @click="price++">price++ ({{ price }})</button>
      <button @click="qty++">qty++ ({{ qty }})</button>
      <button @click="getTotalByMethod()">调用方法 getTotalByMethod()</button>
      <span class="tag">total = {{ total }}</span>
    </div>

    <pre class="code">computed 实际重算了 {{ totalCalls }} 次
方法被调用了 {{ methodCalls }} 次
（多点几次页面上无关的按钮，你会发现调用方法时 totalCalls 不变、methodCalls 却在涨）</pre>

    <p class="note">
      规则：只要值能被「算出来」，就用 <code>computed</code>；只有需要在特定时机执行动作时才用函数。
      模板里也尽量别写复杂表达式，抽成 computed 更清晰。
    </p>
  </DemoCard>

  <DemoCard title="3. 购物车：链式计算属性" hint="computed 可以依赖另一个 computed，像流水线一样逐层推导。">
    <div class="demo-row">
      <span class="tag">商品种类 {{ cart.length }}</span>
      <span class="tag">总件数 {{ totalCount }}</span>
      <span class="tag">原价 ¥{{ totalPrice }}</span>
      <span class="tag">折扣 {{ discount === 1 ? '无' : '9 折' }}</span>
      <strong>应付 ¥{{ payable }}</strong>
    </div>

    <ul class="plain" style="margin-top: 12px">
      <li v-for="item in cart" :key="item.name">
        {{ item.name }} ¥{{ item.price }} ×
        <button style="padding: 0 8px" @click="item.count = Math.max(1, item.count - 1)">-</button>
        {{ item.count }}
        <button style="padding: 0 8px" @click="item.count++">+</button>
      </li>
    </ul>

    <pre class="code">const totalPrice = computed(() => cart.value.reduce((s, i) => s + i.price * i.count, 0))
const discount   = computed(() => (totalPrice.value >= 500 ? 0.9 : 1))
const payable    = computed(() => (totalPrice.value * discount.value).toFixed(2))</pre>
  </DemoCard>

  <DemoCard title="4. watch 侦听器" hint="watch 用来「状态变化后做点什么」，比如发请求、写 localStorage、打印日志。">
    <div class="demo-row">
      <label>关键词：</label>
      <input v-model="keyword" placeholder="输入观察变化" />
    </div>

    <div class="demo-row" style="margin-top: 10px">
      <label>范围：</label>
      <input v-model.number="min" type="number" style="width: 90px" />
      —
      <input v-model.number="max" type="number" style="width: 90px" />
    </div>

    <div class="demo-row" style="margin-top: 10px">
      <button @click="settings.theme = settings.theme === 'light' ? 'dark' : 'light'">
        切换主题（当前 {{ settings.theme }}）
      </button>
      <button @click="settings.nested.dark = !settings.nested.dark">
        切换深层 nested.dark（{{ settings.nested.dark }}）
      </button>
      <span class="tag">深度侦听触发 {{ settingChanged }} 次</span>
    </div>

    <div class="demo-row" style="margin-top: 10px">
      <button @click="counter++">counter++ ({{ counter }})</button>
    </div>

    <div class="code" style="margin-top: 14px">
      <div v-for="(l, i) in searchLog" :key="i">{{ l }}</div>
      <div v-if="!searchLog.length">（暂无日志，试试上面的输入）</div>
    </div>
  </DemoCard>

  <DemoCard title="5. watchEffect 自动收集依赖" hint="写代码时用到了哪些响应式数据，就自动监听哪些，不用显式列出。">
    <div class="demo-row">
      <button @click="a++">a++ ({{ a }})</button>
      <button @click="b++">b++ ({{ b }})</button>
      <span class="tag">{{ effectLog }}</span>
    </div>

    <pre class="code">watch(source, cb)     —— 明确指定监听谁，能拿到新旧值，默认懒执行
watchEffect(fn)      —— 自动收集 fn 中用到的响应式依赖，立即执行一次
{ immediate: true }  —— watch 也立即执行一次
{ deep: true }       —— 深度侦听对象内部变化（侦听 reactive 时默认开启）</pre>
  </DemoCard>

  <DemoCard title="6. 一个实用套路：避免请求竞态" hint="当你在 watch 里发异步请求时，要处理「旧请求晚于新请求返回」的问题。">
    <pre class="code">let token = 0
watch(keyword, async (kw) => {
  const myToken = ++token
  status.value = 'loading'
  const data = await fetchList(kw)
  // 如果期间 keyword 又变了，说明我这次请求已经过期，直接丢弃
  if (myToken !== token) return
  list.value = data
  status.value = 'done'
})</pre>
    <p class="note">
      更完整的写法还会配合 <code>AbortController</code> 取消请求。
      第 13 课「异步数据」会再演示一次。
    </p>
  </DemoCard>
</template>

<style scoped>
label { display: inline-flex; align-items: center; gap: 6px; font-size: 14px; }
</style>
