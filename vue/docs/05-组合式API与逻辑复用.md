# 05 · 组合式 API 与逻辑复用

> 对应课程：[12 响应式与组合式 API](../src/views/Lesson12Reactivity.vue)

## 1. 两种写法的对比

**选项式 API（Vue 2 风格，Vue 3 仍支持）**

```js
export default {
  data: () => ({ count: 0, list: [] }),
  computed: { double() { return this.count * 2 } },
  methods: { add() { this.count++ } },
  mounted() { this.fetch() },
}
```

**组合式 API（`<script setup>`，Vue 3 推荐）**

```js
const count = ref(0)
const list = ref([])
const double = computed(() => count.value * 2)
function add() { count.value++ }
onMounted(() => fetch())
```

### 组合式 API 解决了什么问题？

选项式 API 的痛点是**逻辑按「选项类型」被切散**：
一个「搜索功能」需要的数据在 `data`、计算在 `computed`、请求在 `mounted`、
取消逻辑在 `beforeUnmount` —— 散落在文件各处。功能一多就变成「跳来跳去地读」。

组合式 API 让你**按「功能」组织代码**：

```js
// 搜索功能
const keyword = ref('')
const results = ref([])
const status = ref('idle')
// ...所有搜索相关逻辑集中在一起

// 分页功能
const page = ref(1)
// ...所有分页相关逻辑集中在一起
```

而且这些逻辑可以**整块抽出去复用**（就是下面的 composable）。

> Vue 3 的 `<script setup>` 编译后仍然是选项式结构，只是写法变了。

## 2. `<script setup>` 的规则

```vue
<script setup>
// ① 顶层绑定自动暴露给模板（不用 return）
const msg = ref('hi')
function fn() {}

// ② 组件、指令、宏都可用
import Child from './Child.vue'
defineProps({ a: String })
defineEmits(['b'])
defineModel()
defineExpose({ fn })
defineOptions({ name: 'MyComp' })     // 设置组件名等

// ③ 顶层 await 可用（组件会变成异步组件）
const data = await fetch('/api').then(r => r.json())

// ④ 不能使用 this
</script>
```

编译器宏（`defineProps` 等）**不需要 import，也不能在普通 `.js` 文件里用**。

## 3. Composable：组合式函数

**定义**：一个以 `use` 开头的函数，内部使用 Vue 的响应式 API，返回状态或方法。

本项目里的例子（`src/composables/useCounter.js`）：

```js
import { computed, ref } from 'vue'

export function useCounter(initial = 0, options = {}) {
  const { min = -Infinity, max = Infinity, step = 1 } = options

  const count = ref(initial)
  const canIncrease = computed(() => count.value + step <= max)
  const canDecrease = computed(() => count.value - step >= min)

  function increase() { if (canIncrease.value) count.value += step }
  function decrease() { if (canDecrease.value) count.value -= step }
  function reset() { count.value = initial }

  return { count, canIncrease, canDecrease, increase, decrease, reset }
}
```

组件里使用：

```js
const c1 = useCounter(0, { max: 10 })
const c2 = useCounter(100, { step: 10 })
// 两份状态完全独立
```

### 为什么这是「真复用」？

- 每次调用 `useCounter` 都会创建**独立的 `ref`**，互不干扰
- 逻辑（含 `computed`、方法、生命周期）全部打包进去
- 对比 mixin：没有命名冲突、来源清晰、类型友好

### 常用 composable 模式

```js
// ① 生命周期封装
export function useInterval(fn, delay) {
  let timer
  onMounted(() => { timer = setInterval(fn, delay) })
  onBeforeUnmount(() => clearInterval(timer))
}

// ② 异步请求封装
export function useRequest(fetcher, { immediate = true } = {}) {
  const data = ref(null), status = ref('idle'), error = ref(null)
  async function run(...args) {
    status.value = 'loading'
    try { data.value = await fetcher(...args); status.value = 'success' }
    catch (e) { error.value = e; status.value = 'error' }
  }
  if (immediate) run()
  return { data, status, error, run }
}

// ③ 本地存储
export function useLocalStorage(key, defaultValue) { /* 见 src/composables/ */ }

// ④ 鼠标位置、窗口尺寸、IntersectionObserver、WebSocket、倒计时、防抖节流…
```

### 编写规范

1. 文件名和函数名都以 `use` 开头：`useMouse.js` → `useMouse()`
2. 只在 `setup` 里调用（依赖 `onMounted` 等需在当前组件实例上下文中执行）
3. **返回 ref，不要返回 `reactive` 解构后的值**，保持响应式
4. 返回值用对象（可按需解构），不要返回长数组
5. 参数用 options 对象，便于扩展：

```js
useRequest(fn, { immediate: false, retry: 3 })   // ✅ 比 fn, false, 3 清晰
```

### 注意：解构返回值时

```js
const { count, increase } = useCounter()
// count 仍然是 ref，脚本里要 count.value
// 如果想直接当普通值用：
const { count } = toRefs(...) // 不适用于此
```

Vue 3.5 引入了**响应式 props 解构**，但 composable 的返回值解构仍需注意 `ref` 特性。
团队里常约定：**composable 返回 ref，调用方负责 `.value`**。

## 4. 逻辑复用的三种方式对比

| 方式 | 是否推荐 | 说明 |
| --- | --- | --- |
| **Composable** | ✅ 首选 | 组合式 API 时代的复用单元 |
| Mixin | ❌ 已淘汰 | 命名冲突、来源不透明 |
| 高阶组件 / render props | ⚠️ 少数场景 | Vue 里用插槽或 composable 更自然 |
| 工具函数（纯函数） | ✅ | 无状态的逻辑，如格式化日期、校验 |

## 5. 常见坑

| 坑 | 说明 |
| --- | --- |
| 在 composable 外调用 `onMounted` | 要在 `setup` 调用链里执行 |
| 用 `reactive` 返回并解构 | 丢响应式，返回 `ref` 或用 `toRefs` |
| composable 里忘记清理副作用 | 同样要 `onBeforeUnmount` |
| 一个 composable 做太多事 | 拆分职责，如 `useForm` + `useValidation` |
| 在 composable 里访问组件实例 | 会破坏复用性（除非明确设计） |

## 6. 练习

1. 写 `useMouse()`：返回鼠标的 `x`、`y`，组件卸载时移除监听。
2. 写 `useWindowSize()`：返回 `width`、`height`，可用于响应式布局判断。
3. 写 `useDebounce(valueRef, delay)`：返回一个防抖后的 ref，用于搜索输入。
4. 写 `useForm(initial)`：返回 `values`、`errors`、`validate()`、`reset()`。
5. 把第 17 课 Todo 的所有逻辑抽成 `useTodos()`，让视图文件只剩模板。
