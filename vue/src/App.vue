<script setup>
// App.vue 是根组件：整个页面「外壳」，左侧导航 + 右侧路由内容。
import { RouterView } from 'vue-router'
import { lessons } from '@/course'

// 简单统计一下总课时，展示在侧边栏
const total = lessons.reduce((n, g) => n + g.items.length, 0)

// 计算每个分组之前已有多少课，让编号连续（01 ~ 17），和文档里的编号对应
const groupOffsets = []
let acc = 0
for (const g of lessons) {
  groupOffsets.push(acc)
  acc += g.items.length
}
</script>

<template>
  <div class="app-shell">
    <aside class="sidebar">
      <h1>Vue 3 <span>学习实验室</span></h1>
      <p class="sub">共 {{ total }} 课 · 边看边改边运行</p>

      <!-- 用 v-for 渲染分组，二级 v-for 渲染每门课 -->
      <nav v-for="(group, gi) in lessons" :key="group.group">
        <p class="nav-group-title">{{ group.group }}</p>
        <RouterLink
          v-for="(item, i) in group.items"
          :key="item.path"
          :to="item.path"
          class="nav-link"
        >
          <span class="idx">{{ String(groupOffsets[gi] + i + 1).padStart(2, '0') }}</span>
          <span>{{ item.title }}</span>
        </RouterLink>
      </nav>
    </aside>

    <main class="content">
      <!-- 当前路由匹配的课程页面会渲染在这里 -->
      <RouterView v-slot="{ Component }">
        <component :is="Component" />
      </RouterView>
    </main>
  </div>
</template>
