<script setup>
// 一个「独立的小组件」，它自己直接访问 store。
// 重复使用两次，你会看到两边的数字永远一致 —— 因为它们读的是同一份状态。
import { storeToRefs } from 'pinia'
import { useCounterStore } from '@/stores/counter'

defineProps({ title: { type: String, default: '计数器' } })

const store = useCounterStore()

// ⚠️ 关键细节：直接解构 store 会丢失响应式！
// const { count } = store          // ❌ count 变成普通数字
const { count, double, isPositive } = storeToRefs(store) // ✅ 用 storeToRefs
// 方法（actions）不是响应式数据，直接解构即可
const { increase, decrease, reset } = store
</script>

<template>
  <div class="mini">
    <strong>{{ title }}</strong>
    <div class="demo-row">
      <button @click="decrease()">-1</button>
      <span class="tag">{{ count }}</span>
      <button class="primary" @click="increase()">+1</button>
      <button @click="increase(10)">+10</button>
      <button @click="reset">重置</button>
    </div>
    <p style="font-size: 12px; color: var(--muted); margin: 6px 0 0">
      double = {{ double }} · isPositive = {{ isPositive }}
    </p>
  </div>
</template>

<style scoped>
.mini { border: 1px solid var(--border); border-radius: 8px; padding: 12px; background: #fff; }
</style>
