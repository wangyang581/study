<script setup>
// 演示子组件的生命周期，用来对比「父/子」的执行顺序
import { onBeforeMount, onBeforeUnmount, onMounted, onUpdated } from 'vue'

defineProps({ value: { type: Number, default: 0 } })

const log = (msg) => console.log(`[子组件] ${msg}`)

log('setup 执行（此时还没有 DOM）')

onBeforeMount(() => log('onBeforeMount'))
onMounted(() => log('onMounted  ← 此时可以访问真实 DOM'))

// ⚠️ onUpdated 里绝对不能修改响应式数据！
// 修改 → 触发重新渲染 → 又一次 onUpdated → 无限循环。
// 所以这里只打印日志（纯副作用），不碰任何 ref。
onUpdated(() => log('onUpdated（props.value 变化导致重新渲染）'))

onBeforeUnmount(() => log('onBeforeUnmount  ← 清理定时器/事件监听的好时机'))
</script>

<template>
  <div class="child">
    <p>我是子组件，收到的 value = <strong>{{ value }}</strong></p>
    <p style="color: var(--muted); font-size: 12px">
      打开浏览器控制台，可以按顺序看到我的生命周期日志
    </p>
  </div>
</template>

<style scoped>
.child { border: 1px dashed var(--primary); border-radius: 8px; padding: 10px 14px; background: rgba(66,184,131,.05); }
p { margin: 4px 0; }
</style>
