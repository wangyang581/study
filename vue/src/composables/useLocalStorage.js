// ===================================================================
// 组合式函数：把 ref 和 localStorage 同步起来。
// 这是一个非常典型的「可复用逻辑」——任何需要持久化的状态都能用。
// ===================================================================
import { ref, watch } from 'vue'

// 某些环境（SSR、隐私模式、老浏览器）可能没有可用的 localStorage，
// 所以这里做一层安全封装，保证业务代码不会因此报错。
const storage = {
  get(key) {
    try {
      if (typeof localStorage === 'undefined') return null
      return localStorage.getItem(key)
    } catch {
      return null
    }
  },
  set(key, value) {
    try {
      if (typeof localStorage === 'undefined') return
      localStorage.setItem(key, value)
    } catch (e) {
      console.warn(`写入 localStorage["${key}"] 失败：`, e)
    }
  },
}

export function useLocalStorage(key, defaultValue) {
  // 1) 初始化：尝试从 localStorage 读取
  let initial = defaultValue
  try {
    const raw = storage.get(key)
    if (raw !== null && raw !== undefined) initial = JSON.parse(raw)
  } catch (e) {
    console.warn(`解析 localStorage["${key}"] 失败：`, e)
  }

  const state = ref(initial)

  // 2) 变化时写回 localStorage（深度监听，数组/对象内部变化也能捕获）
  watch(
    state,
    (val) => storage.set(key, JSON.stringify(val)),
    { deep: true },
  )

  return state
}
