<script setup>
// ===================================================================
// 第 15 课：路由 Vue Router
// 路由 = 「地址 ↔ 组件」的映射。有了它，单页应用才有了「多页面」的感觉。
// ===================================================================
import { computed } from 'vue'
import { useRoute, useRouter } from 'vue-router'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'

const route = useRoute()   // 读当前路由信息（响应式）
const router = useRouter() // 执行跳转

// 演示 query 参数：?page=2&sort=stars
const page = computed({
  get: () => Number(route.query.page ?? 1),
  set: (v) => router.push({ query: { ...route.query, page: String(v) } }),
})
const sort = computed({
  get: () => route.query.sort ?? 'default',
  set: (v) => router.push({ query: { ...route.query, sort: v } }),
})

// 编程式跳转
function gotoUser(id) {
  router.push(`/engineering/router/user/${id}`)
}
function gotoWithQuery() {
  router.push({ path: route.path, query: { page: '3', sort: 'stars' } })
}
const currentRoute = computed(() => ({
  path: route.path,
  name: route.name,
  params: route.params,
  query: route.query,
  fullPath: route.fullPath,
}))
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. 当前路由信息" hint="useRoute() 返回的对象是响应式的，地址一变它自动更新。">
    <pre class="code">{{ currentRoute }}</pre>
  </DemoCard>

  <DemoCard title="2. 声明式导航 RouterLink" hint="RouterLink 渲染成 <a>，但不会真正刷新页面。">
    <div class="demo-row">
      <RouterLink class="nav-link" to="/basic/template">← 去第 1 课</RouterLink>
      <RouterLink class="nav-link" :to="{ name: 'pinia' }">用 name 跳转到 Pinia 课</RouterLink>
      <RouterLink class="nav-link" :to="{ path: '/engineering/router/user/2' }">带参数的动态路由</RouterLink>
      <a class="nav-link" href="/basic/template">普通 a 标签（会整页刷新，不推荐）</a>
    </div>

    <p class="note">
      推荐用「命名路由 + 对象参数」的写法 <code>:to="{ name: 'user-detail', params: { id: 1 } }"</code>，
      这样路径改了也不用全项目搜字符串替换。
    </p>
  </DemoCard>

  <DemoCard title="3. 动态路由参数" hint="路径里的 :id 会出现在 route.params 中。">
    <div class="demo-row">
      <button v-for="id in [1, 2, 3, 99]" :key="id" @click="gotoUser(id)">
        查看用户 {{ id }}
      </button>
    </div>

    <pre class="code">// 路由表
{ path: '/user/:id', name: 'user-detail', component: UserDetail }

// 参数
route.params.id

// 组件复用注意：/user/1 → /user/2 时组件不会重新创建，
// 所以「监听 id 变化」要靠 watch(() => route.params.id, ...) 或
// beforeRouteUpdate 守卫，而不是 onMounted。</pre>
  </DemoCard>

  <DemoCard title="4. query 参数：用于「可分享的筛选/分页状态」" hint="改 URL 就能改页面状态，刷新不丢失，还能直接分享链接。">
    <div class="demo-row">
      <button :disabled="page <= 1" @click="page--">上一页</button>
      <span class="tag">当前第 {{ page }} 页</span>
      <button class="primary" @click="page++">下一页</button>

      <select v-model="sort">
        <option value="default">默认排序</option>
        <option value="stars">按星数</option>
        <option value="updated">按更新时间</option>
      </select>

      <button @click="gotoWithQuery">跳到第 3 页（编程式）</button>
    </div>

    <p style="margin-top: 10px">
      注意地址栏：<code>{{ route.fullPath }}</code> —— 每次操作都变了，刷新页面状态还在。
    </p>

    <pre class="code">// 读
route.query.page            // 字符串 '2'
// 写：用 push 而不是直接改对象
router.push({ query: { page: '3', sort: 'stars' } })</pre>
  </DemoCard>

  <DemoCard title="5. 编程式导航" hint="在 JS 里控制跳转：提交成功后跳转、登录失效跳登录页等。">
    <pre class="code">const router = useRouter()

router.push('/home')                    // 字符串
router.push({ path: '/home' })
router.push({ name: 'user-detail', params: { id: 3 } })
router.push({ query: { page: '2' } })
router.replace('/login')                // 不留历史记录（登录后返回不会回到登录页）
router.back()
router.go(-1) / router.go(1)</pre>
  </DemoCard>

  <DemoCard title="6. 懒加载、路由守卫与元信息" hint="工程化部分，实际项目必用。">
    <pre class="code">// ① 懒加载：访问时才下载对应代码，首屏体积更小
{ path: '/big', component: () => import('@/views/BigPage.vue') }

// ② 路由元信息：把「权限、标题」写在路由上
{ path: '/admin', meta: { requiresAuth: true, title: '后台' } }

// ③ 全局前置守卫：登录校验、动态标题
router.beforeEach((to, from) => {
  document.title = to.meta.title ?? 'Vue 学习'
  const isLogin = !!localStorage.getItem('token')
  if (to.meta.requiresAuth && !isLogin) {
    return { path: '/login', query: { redirect: to.fullPath } }   // 返回路由 = 重定向
  }
  return true   // 放行；返回 false 则取消导航
})

// ④ 组件内守卫（组合式 API）
onBeforeRouteLeave((to) => {
  if (hasUnsavedChanges.value) return window.confirm('确定离开？')
})

// ⑤ 路由懒加载 + 加载状态
router.beforeEach(() => (loading.value = true))
router.afterEach(() => (loading.value = false))

// ⑥ 布局路由：用嵌套路由做「侧边栏 + 内容区」
{ path: '/admin', component: AdminLayout,
  children: [
    { path: '', component: Dashboard },        // /admin
    { path: 'users', component: UserList },    // /admin/users
  ] }
// 父组件模板里放 <RouterView />，子路由就渲染在那儿</pre>

    <p class="note">
      本学习站点本身就是个例子：<code>App.vue</code> 里的
      <code>&lt;RouterView /&gt;</code> 负责渲染当前课程，
      侧边栏则通过 <code>router-link-active</code> 自动高亮当前菜单。
    </p>
  </DemoCard>
</template>
