<script setup>
// 深层子组件：演示 provide / inject
// 注意：它并没有通过 props 接收 theme —— 数据是从祖先组件「注入」进来的。
import { inject } from 'vue'

// 第二个参数是默认值：找不到 provider 时使用，避免 undefined 报错
const theme = inject('theme', { color: '#42b883', name: '默认绿' })
const switchTheme = inject('switchTheme', () => {})
</script>

<template>
  <div class="deep" :style="{ borderColor: theme.color }">
    <p>我是第 3 层子组件，通过 <code>inject('theme')</code> 直接拿到祖先的数据：</p>
    <p>
      当前主题：<strong :style="{ color: theme.color }">{{ theme.name }}</strong>
    </p>
    <button @click="switchTheme">切换主题（调用的是祖先提供的方法）</button>
  </div>
</template>

<style scoped>
.deep { border: 2px dashed; border-radius: 8px; padding: 12px; }
p { margin: 4px 0; font-size: 14px; }
</style>
