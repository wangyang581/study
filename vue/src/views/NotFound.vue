<script setup>
// 404 页面：由路由表最后的通配规则匹配
import { useRoute } from 'vue-router'
const route = useRoute()
</script>

<template>
  <div class="card">
    <h2>404 · 页面不存在</h2>
    <p>你访问的地址 <code>{{ route.fullPath }}</code> 没有对应的路由。</p>
    <RouterLink to="/">← 回到第一课</RouterLink>
  </div>
</template>
