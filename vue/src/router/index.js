// 路由表：把「网址」和「组件」对应起来。
// 这里的数据来自 course.js，所以新增课程无需改两处。
import { createRouter, createWebHistory } from 'vue-router'
import { flatLessons } from '@/course'

const routes = [
  // 默认进入第一课
  { path: '/', redirect: flatLessons[0].path },

  // 用课程清单生成每一条路由
  ...flatLessons.map((lesson) => ({
    path: lesson.path,
    name: lesson.name,
    // 懒加载：只有访问到这一课才下载对应代码，首屏更快
    component: lesson.load,
    meta: { title: lesson.title, goal: lesson.goal },
  })),

  // 动态路由示例：/engineering/router/user/3
  // 冒号开头的是「路由参数」，可通过 route.params.id 读取
  {
    path: '/engineering/router/user/:id',
    name: 'user-detail',
    component: () => import('@/views/UserDetail.vue'),
  },

  // 404 兜底
  { path: '/:pathMatch(.*)*', name: 'not-found', component: () => import('@/views/NotFound.vue') },
]

const router = createRouter({
  // history 模式：地址栏是正常的 /basic/template（没有 # 号）
  history: createWebHistory(),
  routes,
  // 切换页面时回到顶部
  scrollBehavior: () => ({ top: 0 }),
})

export default router
