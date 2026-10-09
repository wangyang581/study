// ===================================================================
// 组合式函数（Composable）：把「带状态的逻辑」抽出来复用。
// 约定：文件名以 use 开头，内部可以使用 ref / computed / 生命周期钩子。
// ===================================================================
import { computed, ref } from 'vue'

/**
 * 一个多功能计数器。
 * @param {number} initial 初始值
 * @param {{ min?: number, max?: number, step?: number }} options 边界与步长
 */
export function useCounter(initial = 0, options = {}) {
  const { min = -Infinity, max = Infinity, step = 1 } = options

  const count = ref(initial)

  // 用 computed 派生「能否再加/再减」，模板里直接用，逻辑集中在函数内部
  const canIncrease = computed(() => count.value + step <= max)
  const canDecrease = computed(() => count.value - step >= min)
  const isEven = computed(() => count.value % 2 === 0)

  function increase() {
    if (canIncrease.value) count.value += step
  }
  function decrease() {
    if (canDecrease.value) count.value -= step
  }
  function reset() {
    count.value = initial
  }

  // 返回模板/组件需要用到的一切
  return { count, canIncrease, canDecrease, isEven, increase, decrease, reset }
}
