// ===================================================================
// 课程清单（唯一数据源）
// 侧边栏导航和路由表都由这份清单生成 —— 这就是「数据驱动 UI」的思想。
// 新增一课时，只要在这里加一条记录即可。
// ===================================================================

export const lessons = [
  {
    group: '第一阶段 · Vue 基础',
    items: [
      {
        path: '/basic/template',
        name: 'template',
        title: '模板语法与插值',
        goal: '理解 Vue 如何把数据「渲染」到页面上：插值、指令、动态属性。',
        load: () => import('@/views/Lesson01Template.vue'),
      },
      {
        path: '/basic/conditional',
        name: 'conditional',
        title: '条件渲染 v-if / v-show',
        goal: '根据数据决定元素是否显示，以及 v-if 与 v-show 的区别与取舍。',
        load: () => import('@/views/Lesson02Conditional.vue'),
      },
      {
        path: '/basic/list',
        name: 'list',
        title: '列表渲染 v-for 与 :key',
        goal: '渲染数组/对象列表，理解 :key 为什么重要。',
        load: () => import('@/views/Lesson03List.vue'),
      },
      {
        path: '/basic/event',
        name: 'event',
        title: '事件处理 v-on 与修饰符',
        goal: '响应用户点击/输入，掌握事件传参和 .prevent/.stop 等修饰符。',
        load: () => import('@/views/Lesson04Event.vue'),
      },
      {
        path: '/basic/form',
        name: 'form',
        title: '表单绑定 v-model',
        goal: '把输入框、复选框、下拉框等表单控件和状态双向绑定。',
        load: () => import('@/views/Lesson05Form.vue'),
      },
      {
        path: '/basic/computed',
        name: 'computed',
        title: '计算属性 computed 与侦听 watch',
        goal: '派生数据用 computed，副作用用 watch，并学会拆分逻辑。',
        load: () => import('@/views/Lesson06Computed.vue'),
      },
      {
        path: '/basic/style',
        name: 'style',
        title: 'Class / Style 动态绑定',
        goal: '根据状态动态切换样式，写出「有反应」的交互界面。',
        load: () => import('@/views/Lesson07Style.vue'),
      },
    ],
  },
  {
    group: '第二阶段 · 组件化',
    items: [
      {
        path: '/component/props',
        name: 'props',
        title: '组件基础：props 与 emit',
        goal: '把页面拆成可复用组件，用 props 传数据、用 emit 往外发事件。',
        load: () => import('@/views/Lesson08Props.vue'),
      },
      {
        path: '/component/slot',
        name: 'slot',
        title: '插槽 slot',
        goal: '让组件接收「内容」，掌握默认插槽、具名插槽、作用域插槽。',
        load: () => import('@/views/Lesson09Slot.vue'),
      },
      {
        path: '/component/lifecycle',
        name: 'lifecycle',
        title: '生命周期与模板引用',
        goal: '在正确的时机执行代码（onMounted 等），并用 ref 拿到真实 DOM。',
        load: () => import('@/views/Lesson10Lifecycle.vue'),
      },
      {
        path: '/component/communication',
        name: 'communication',
        title: '组件通信：v-model / provide-inject',
        goal: '处理父子双向绑定、跨层级传值，理解不同通信方式的适用场景。',
        load: () => import('@/views/Lesson11Communication.vue'),
      },
    ],
  },
  {
    group: '第三阶段 · 进阶能力',
    items: [
      {
        path: '/advanced/reactivity',
        name: 'reactivity',
        title: '组合式 API 与响应式原理',
        goal: '深入 ref / reactive / watchEffect，并抽离可复用的组合式函数。',
        load: () => import('@/views/Lesson12Reactivity.vue'),
      },
      {
        path: '/advanced/async',
        name: 'async',
        title: '异步数据与网络请求',
        goal: '请求接口、处理 loading / error / 空状态，理解挂载时机。',
        load: () => import('@/views/Lesson13Async.vue'),
      },
      {
        path: '/advanced/animation',
        name: 'animation',
        title: '过渡与动画 Transition',
        goal: '给进入/离开、列表增删加上平滑的过渡效果。',
        load: () => import('@/views/Lesson14Animation.vue'),
      },
    ],
  },
  {
    group: '第四阶段 · 工程与实战',
    items: [
      {
        path: '/engineering/router',
        name: 'router',
        title: '路由 Vue Router',
        goal: '多页面导航、动态路由、路由参数与编程式跳转。',
        load: () => import('@/views/Lesson15Router.vue'),
      },
      {
        path: '/engineering/pinia',
        name: 'pinia',
        title: '状态管理 Pinia',
        goal: '用 store 集中管理跨组件共享状态，告别层层传递 props。',
        load: () => import('@/views/Lesson16Pinia.vue'),
      },
      {
        path: '/engineering/todo',
        name: 'todo',
        title: '综合实战：待办清单',
        goal: '把前面所学串起来，做一个读写本地存储的完整小应用。',
        load: () => import('@/views/Lesson17Todo.vue'),
      },
    ],
  },
]

// 把清单拍平成一个数组，方便生成路由表
export const flatLessons = lessons.flatMap((g) => g.items)
