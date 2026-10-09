<script setup>
// -------------------------------------------------------------------
// 用户卡片
// 知识点：对象型 prop、withDefaults、计算属性、emit 抛事件
// -------------------------------------------------------------------
import { computed } from 'vue'

// 复杂类型（对象/数组）的默认值必须用工厂函数返回：
//   default: () => ({ ... })
// 这里不需要 withDefaults，因为每个 prop 都已给出 default。
const props = defineProps({
  user: {
    type: Object,
    default: () => ({ name: '匿名', role: '访客', color: '#94a3b8' }),
  },
  following: { type: Boolean, default: false },
  compact: { type: Boolean, default: false },
})

const emit = defineEmits(['toggle-follow'])

// computed：根据已有数据「算」出新数据。依赖变化时自动重新计算并缓存。
const initial = computed(() => (props.user.name || '?').slice(0, 1).toUpperCase())
</script>

<template>
  <article class="user-card" :class="{ compact }">
    <!-- 用 :style 绑定动态样式 -->
    <div class="avatar" :style="{ background: user.color }">{{ initial }}</div>

    <div class="meta">
      <strong>{{ user.name }}</strong>
      <span class="tag">{{ user.role }}</span>
    </div>

    <button :class="{ primary: !following }" @click="emit('toggle-follow', user.name)">
      {{ following ? '已关注' : '关注' }}
    </button>
  </article>
</template>

<style scoped>
.user-card {
  display: flex;
  align-items: center;
  gap: 12px;
  padding: 12px;
  border: 1px solid var(--border);
  border-radius: 10px;
  background: #fff;
}
.avatar {
  width: 42px; height: 42px; flex: 0 0 42px;
  border-radius: 50%;
  display: grid; place-items: center;
  color: #fff; font-weight: 700;
}
.meta { display: flex; flex-direction: column; margin-right: auto; }
.meta strong { font-size: 14px; }
.compact { padding: 8px; }
.compact .avatar { width: 32px; height: 32px; flex-basis: 32px; }
</style>
