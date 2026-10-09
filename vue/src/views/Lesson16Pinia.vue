<script setup>
// ===================================================================
// 第 16 课：状态管理 Pinia
// 什么时候需要 store？—— 当多个「互不相关」的组件需要读写同一份数据时。
// 判断标准：如果数据提升到共同父组件后要层层透传 props，就该用 store 了。
// ===================================================================
import { storeToRefs } from 'pinia'
import { useCounterStore } from '@/stores/counter'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'
import PiniaCounter from '@/components/PiniaCounter.vue'

const counter = useCounterStore()

// 用 storeToRefs 解构出保持响应式的状态
const { count, double, history, isPositive } = storeToRefs(counter)

// actions 直接解构
const { increase, decrease, reset } = counter
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. store 就是一个「全局的响应式对象」" hint="任何组件引入同一个 store，读写的都是同一份数据。">
    <div class="demo-row">
      <button @click="decrease(5)">-5</button>
      <button @click="decrease()">-1</button>
      <span class="tag">count = {{ count }}</span>
      <button class="primary" @click="increase()">+1</button>
      <button class="primary" @click="increase(5)">+5</button>
      <button @click="reset">reset</button>
    </div>

    <p style="margin-top: 10px">
      <span class="tag">double = {{ double }}</span>
      <span class="tag">isPositive = {{ isPositive }}</span>
      <span class="tag">历史记录 {{ history.length }} 条</span>
    </p>
  </DemoCard>

  <DemoCard title="2. 两个独立组件共享同一状态" hint="在左边组件里点 +1，右边立刻变化。这就是 store 的价值。">
    <div class="grid-2">
      <PiniaCounter title="组件 A（购物车角标）" />
      <PiniaCounter title="组件 B（结算页）" />
    </div>

    <p class="note">
      如果用 props/emit 实现，你得把状态提升到共同父组件，再一层层传/接 —— 组件越深越痛苦。
    </p>
  </DemoCard>

  <DemoCard title="3. 操作历史（由 action 记录）" hint="把所有「改数据」的逻辑都收进 action，便于维护和调试。">
    <div class="code" style="max-height: 220px; overflow: auto">
      <div v-for="(h, i) in history" :key="i">
        {{ h.at }}　{{ h.op }}　→ count = {{ h.value }}
      </div>
      <div v-if="!history.length">（点上面的按钮产生记录）</div>
    </div>
  </DemoCard>

  <DemoCard title="4. store 的三种写法" hint="推荐「组合式（setup）写法」，和组件里的写法完全一致。">
    <pre class="code">// stores/counter.js —— 组合式写法（本项目采用）
export const useCounterStore = defineStore('counter', () => {
  const count = ref(0)                       // state
  const double = computed(() => count.value * 2)   // getters
  function increase() { count.value++ }      // actions
  return { count, double, increase }
})

// 选项式写法（等价）
export const useCounterStore = defineStore('counter', {
  state: () => ({ count: 0 }),
  getters: { double: (state) => state.count * 2 },
  actions: { increase() { this.count++ } },
})

// 组件中使用
const store = useCounterStore()
store.count++                                  // 直接改 state（允许）
store.increase()                               // 或调用 action
const { count } = storeToRefs(store)           // 解构必须用 storeToRefs</pre>
  </DemoCard>

  <DemoCard title="5. 常见问题与最佳实践" hint="踩坑清单。">
    <pre class="code">// ❌ 解构丢响应式
const { count } = store

// ✅ 用 storeToRefs（action 不需要，直接解构）
const { count } = storeToRefs(store)
const { increase } = store

// ✅ 异步 action：直接在 action 里写 async/await
async function fetchUser() {
  this.loading = true
  try { this.user = await api.getUser() } finally { this.loading = false }
}

// ✅ 拆分多个 store，按业务域划分，而不是一个巨型 store
//    stores/user.js  stores/cart.js  stores/ui.js

// ✅ 需要跨页面保留的数据放 store；只在一个页面用的状态放组件里
// ✅ 不要在 store 里放 DOM 节点、组件实例

// 🔧 调试：安装 Vue DevTools，可以看到每个 store 的状态变化时间线</pre>

    <p class="note">
      Pinia 与 Vuex 的区别：Pinia 没有 mutation（直接改 state 或在 action 里改）、
      对 TypeScript 支持更好、模块化天然（每个 store 独立文件）、体积更小。
      新项目直接用 Pinia。
    </p>
  </DemoCard>
</template>
