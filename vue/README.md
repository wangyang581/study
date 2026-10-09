# Vue 3 学习实验室

一个**可运行、可交互**的 Vue 3 学习工程。每一课都是一个真实页面，
你可以一边看说明、一边改代码、一边在浏览器里看到结果。

- 技术栈：**Vite 6 + Vue 3.5 + Vue Router 4 + Pinia 2**（纯 JavaScript，无 TypeScript）
- 共 **17 节课**，从「模板语法」一路到「综合实战 Todo」
- 配套 **10 篇文档**（`docs/` 目录），讲原理、讲坑、讲最佳实践

---

## 一、怎么跑起来

```bash
cd vue
npm install      # 只需第一次（已经装过就跳过）
npm run dev      # 启动开发服务器，浏览器会自动打开 http://localhost:5173
```

其他命令：

```bash
npm run build     # 打包到 dist/，可以拿去看产物体积
npm run preview   # 本地预览打包结果
```

> 强烈建议：**边改代码边看效果**。改 `.vue` 文件保存后浏览器会立即热更新（HMR），
> 不用手动刷新。学习 Vue 最快的方式就是「改一下、看变化」。

---

## 二、建议的学习顺序

不要一口气看完 17 课。推荐按下面的节奏：

| 阶段 | 课程 | 你要达到的状态 |
| --- | --- | --- |
| **1. 会用** | 01~07 | 能独立写出一个「列表 + 表单 + 搜索筛选」的静态交互页面 |
| **2. 会拆** | 08~11 | 能把页面拆成组件，知道 props / emit / slot 分别解决什么问题 |
| **3. 会想** | 12~14 | 理解响应式原理，会抽 composable，会处理异步和动画 |
| **4. 会做** | 15~17 | 会用路由和 Pinia 组织一个多页面应用，能独立完成 Todo 实战 |

每节课的页面里都有 **「留给你的练习」** 或提示，**务必动手做**。
看懂 ≠ 会写，前端是手艺活。

---

## 三、课程地图（17 课）

### 第一阶段 · Vue 基础（`/basic/*`）

| # | 课程 | 核心知识点 | 源码 |
| --- | --- | --- | --- |
| 01 | 模板语法与插值 | `{{ }}`、`v-bind`/`:`、`v-once`、`v-html`、`v-pre` | `src/views/Lesson01Template.vue` |
| 02 | 条件渲染 | `v-if` / `v-else-if` / `v-else`、`v-show`、`<template>` | `Lesson02Conditional.vue` |
| 03 | 列表渲染 | `v-for`、`:key`、过滤排序、遍历对象/数字 | `Lesson03List.vue` |
| 04 | 事件处理 | `v-on`/`@`、传参、`$event`、`.prevent`/`.stop`/`.once` | `Lesson04Event.vue` |
| 05 | 表单绑定 | `v-model`、checkbox/radio/select、`.lazy`/`.number`/`.trim` | `Lesson05Form.vue` |
| 06 | 计算与侦听 | `computed`（含缓存）、`watch`、`watchEffect` | `Lesson06Computed.vue` |
| 07 | 动态样式 | `:class` 对象/数组、`:style`、CSS 变量主题 | `Lesson07Style.vue` |

### 第二阶段 · 组件化（`/component/*`）

| # | 课程 | 核心知识点 | 源码 |
| --- | --- | --- | --- |
| 08 | props 与 emit | 组件拆分、`defineProps`、`defineEmits`、单向数据流 | `Lesson08Props.vue` |
| 09 | 插槽 slot | 默认/具名/作用域插槽、编译作用域 | `Lesson09Slot.vue` |
| 10 | 生命周期与 ref | `onMounted`、清理副作用、模板引用、`nextTick` | `Lesson10Lifecycle.vue` |
| 11 | 组件通信 | `defineModel`（组件 v-model）、`provide/inject`、`defineExpose` | `Lesson11Communication.vue` |

### 第三阶段 · 进阶能力（`/advanced/*`）

| # | 课程 | 核心知识点 | 源码 |
| --- | --- | --- | --- |
| 12 | 响应式与组合式 API | `ref` / `reactive` / `toRefs` / `shallowRef` / `readonly`、composable | `Lesson12Reactivity.vue` |
| 13 | 异步数据 | loading/error/空状态、`Promise.all`、竞态、`fetch` + `AbortController` | `Lesson13Async.vue` |
| 14 | 过渡与动画 | `<Transition>`、`<TransitionGroup>`、`.move`、JS 钩子 | `Lesson14Animation.vue` |

### 第四阶段 · 工程与实战（`/engineering/*`）

| # | 课程 | 核心知识点 | 源码 |
| --- | --- | --- | --- |
| 15 | 路由 Vue Router | `RouterLink`、动态路由 `:id`、query、编程式导航、守卫、嵌套路由 | `Lesson15Router.vue` |
| 16 | 状态管理 Pinia | `defineStore`、state/getters/actions、`storeToRefs`、解构陷阱 | `Lesson16Pinia.vue` |
| 17 | 综合实战 Todo | 全流程串联 + `localStorage` 持久化 + 列表动画 | `Lesson17Todo.vue` |

---

## 四、文档目录（`docs/`）

| 文档 | 内容 |
| --- | --- |
| [01-快速开始与核心概念](docs/01-快速开始与核心概念.md) | 项目结构、SPA 是什么、MVVM/声明式渲染、SFC 语法 |
| [02-模板语法与指令](docs/02-模板语法与指令.md) | 插值、常用指令、修饰符全表、`v-if` vs `v-show` |
| [03-响应式-计算属性-侦听器](docs/03-响应式-计算属性-侦听器.md) | `ref`/`reactive` 区别、`computed` 缓存、`watch` 用法与竞态 |
| [04-组件化-插槽-通信-生命周期](docs/04-组件化-插槽-通信-生命周期.md) | 组件设计、props 契约、插槽、6 种通信方式选型、生命周期 |
| [05-组合式API与逻辑复用](docs/05-组合式API与逻辑复用.md) | Composition API 心智模型、composable 写法与规范 |
| [06-样式与动画](docs/06-样式与动画.md) | `scoped` 原理、`:deep()`、动态 class/style、过渡类名 |
| [07-异步数据与网络请求](docs/07-异步数据与网络请求.md) | 四态 UI、封装 request、取消请求、错误处理 |
| [08-路由与状态管理](docs/08-路由与状态管理.md) | Vue Router 全解、Pinia 全解、该不该用 store |
| [09-工程化与最佳实践](docs/09-工程化与最佳实践.md) | 目录结构、命名、性能优化、调试、常见坑清单 |
| [10-练习与进阶路线](docs/10-练习与进阶路线.md) | 分级练习题 + 后续要学什么（TS、测试、SSR…） |

---

## 五、项目结构

```
vue/
├── index.html              # 页面模板，Vue 会挂载到 <div id="app">
├── vite.config.js          # Vite 配置（Vue 插件 + @ 别名）
├── package.json
├── docs/                   # 📘 配套文档
└── src/
    ├── main.js             # 入口：createApp / use(router) / use(pinia) / mount
    ├── App.vue             # 根组件：左侧导航 + <RouterView>
    ├── course.js           # 课程清单（唯一数据源，驱动导航和路由）
    ├── router/index.js     # 路由表
    ├── styles/main.css     # 全局样式（含 CSS 变量主题）
    ├── components/         # 可复用组件（BaseButton / UserCard / BasePanel ...）
    ├── composables/        # 组合式函数（useCounter / useLocalStorage）
    ├── stores/             # Pinia store（counter）
    └── views/              # 17 个课程页面 + UserDetail + NotFound
```

> 💡 **小彩蛋**：这个学习站点本身就是一个小型 Vue 应用。
> 左边导航是用 `v-for` 渲染 `course.js` 的数据，右侧内容由 `<RouterView>` 渲染，
> 当前菜单靠 `router-link-active` 自动高亮 —— 你学完第 15 课就知道它怎么工作了。

---

## 六、一张「速查卡」

```vue
<script setup>
import { ref, computed, watch, onMounted } from 'vue'

defineProps({ title: String })          // 父 → 子
const emit = defineEmits(['change'])    // 子 → 父
const model = defineModel()             // 双向 v-model

const count = ref(0)                    // 脚本里要 .value，模板里自动解包
const double = computed(() => count.value * 2)   // 派生数据（有缓存）
watch(count, (n, o) => console.log(n, o))        // 副作用
onMounted(() => { /* DOM 已就绪 */ })
</script>

<template>
  <h1 :class="{ active: count > 0 }">{{ title }} × {{ double }}</h1>
  <button @click="count++">+1</button>
  <li v-for="item in list" :key="item.id">{{ item.name }}</li>
  <input v-model="keyword" />
  <Child :title="title" @change="onChange" />
  <Child v-model="count" />
</template>

<style scoped>
.active { color: #42b883; }
</style>
```

**三条最重要的心法**：

1. **声明式**：描述「数据长什么样」，不要手动操作 DOM。
2. **单向数据流**：数据往下（props），事件往上（emit）；要改数据就回到源头改。
3. **一切从状态推导**：能用 `computed` 算出来的，就不要单独存一份。

---

开始吧 👉 `cd vue && npm run dev`
