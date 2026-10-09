<script setup>
// -------------------------------------------------------------------
// 星级评分：演示「组件上的 v-model」
// Vue 3.4+ 提供 defineModel()，一行代码就实现了 v-model 双向绑定。
//   defineModel() 返回一个 ref：
//   父组件写 <StarRating v-model="score" />，等价于
//   :model-value="score" + @update:model-value="score = $event"
// -------------------------------------------------------------------
import { ref } from 'vue'

const model = defineModel({ type: Number, default: 0 })

const props = defineProps({
  max: { type: Number, default: 5 },
})

// 鼠标悬停时高亮到第几颗星（纯 UI 状态，属于组件内部私有）
const hovered = ref(0)

function set(n) {
  // 点击同一颗星再点一次 = 取消评分
  model.value = model.value === n ? 0 : n
}

// 当前应该点亮到第几颗：优先用悬停值
function isOn(n) {
  return n <= (hovered.value || model.value)
}
</script>

<template>
  <div class="stars">
    <span
      v-for="n in props.max"
      :key="n"
      class="star"
      :class="{ on: isOn(n) }"
      @click="set(n)"
      @mouseenter="hovered = n"
      @mouseleave="hovered = 0"
      >★</span
    >
    <small>{{ model ? `${model} 分` : '未评分' }}</small>
  </div>
</template>

<style scoped>
.stars { display: inline-flex; align-items: center; gap: 2px; }
.star { font-size: 22px; color: #d0d5dd; cursor: pointer; transition: .12s; user-select: none; }
.star.on { color: #f7b500; }
.star:hover { transform: scale(1.15); }
small { margin-left: 8px; color: var(--muted); }
</style>
