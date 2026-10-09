<script setup>
// 所有课程页都复用这个小结构：标题 + 学习目标 + 内容插槽。
import { useRoute } from 'vue-router'

const route = useRoute()
</script>

<template>
  <header class="lesson-header">
    <h2>{{ route.meta.title }}</h2>
    <p class="goal">🎯 {{ route.meta.goal }}</p>
  </header>

  <!-- 课程页面的具体内容会被塞进这个 slot -->
  <slot />
</template>
