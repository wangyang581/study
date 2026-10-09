// ===================================================================
// Pinia Store：跨组件共享的状态仓库。
// 与组件里的 ref 不同，store 的数据在整个应用生命周期内共享，
// 任何组件读到的都是同一份。
// ===================================================================
import { defineStore } from 'pinia'
import { computed, ref } from 'vue'

export const useCounterStore = defineStore('counter', () => {
  // ---------- state：状态（相当于组件里的 ref） ----------
  const count = ref(0)
  const history = ref([])

  // ---------- getters：派生状态（相当于 computed） ----------
  const double = computed(() => count.value * 2)
  const isPositive = computed(() => count.value > 0)

  // ---------- actions：修改状态的方法 ----------
  function increase(step = 1) {
    count.value += step
    record(`+${step}`)
  }

  function decrease(step = 1) {
    count.value -= step
    record(`-${step}`)
  }

  function reset() {
    count.value = 0
    history.value = []
  }

  function record(op) {
    history.value.unshift({ op, value: count.value, at: new Date().toLocaleTimeString() })
    // 只保留最近 8 条，演示「数组截断」
    if (history.value.length > 8) history.value.length = 8
  }

  return { count, history, double, isPositive, increase, decrease, reset }
})
