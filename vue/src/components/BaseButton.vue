<script setup>
// -------------------------------------------------------------------
// 通用按钮组件
// 知识点：defineProps 声明「输入」，defineEmits 声明「输出」
// -------------------------------------------------------------------

// 1) props：父组件传给子组件的只读数据
const props = defineProps({
  // 类型 + 默认值 + 必填，都在这里声明；相当于组件的「接口文档」
  label: { type: String, default: '按钮' },
  variant: {
    type: String,
    default: 'default',
    // validator 可以做运行时的值校验，写错会给出警告
    validator: (v) => ['default', 'primary', 'danger'].includes(v),
  },
  disabled: { type: Boolean, default: false },
  count: { type: Number, default: 0 },
})

// 2) emits：子组件要向父组件「说话」时，用 emit 抛事件
const emit = defineEmits(['action'])

function handleClick() {
  if (props.disabled) return
  // 第一个参数是事件名，后面的参数会原样传给父组件的处理函数
  emit('action', { label: props.label, at: Date.now() })
}
</script>

<template>
  <button
    :class="['btn', variant]"
    :disabled="disabled"
    @click="handleClick"
  >
    <!-- 插槽作为兜底：父组件没传内容时，显示 label prop -->
    <slot>{{ label }}<template v-if="count">（{{ count }}）</template></slot>
  </button>
</template>

<style scoped>
/* scoped：样式只作用于当前组件，不会污染别处。
   原理是给元素加上唯一的 data-v-xxx 属性。 */
.btn { border-radius: 8px; }
</style>
