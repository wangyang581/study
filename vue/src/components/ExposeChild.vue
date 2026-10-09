<script setup>
// 演示 defineExpose：把子组件内部的方法「暴露」给父组件调用。
// 默认情况下，<script setup> 组件是封闭的，父组件拿不到内部任何东西。
import { ref } from 'vue'

const input = ref(null)
const value = ref('')

function focus() {
  input.value?.focus()
}

function clear() {
  value.value = ''
  input.value?.focus()
}

function setValue(v) {
  value.value = v
}

function getValue() {
  return value.value
}

// 只暴露这几个方法，其他内部状态保持私有（信息隐藏）
defineExpose({ focus, clear, setValue, getValue })
</script>

<template>
  <input ref="input" v-model="value" placeholder="父组件可以远程控制我" />
  <p style="font-size: 12px; color: var(--muted)">内部 value：{{ value || '（空）' }}</p>
</template>
