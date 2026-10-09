<script setup>
// 通用「知识点卡片」：标题 + 说明 + 内容 + 可选的代码展示。
// 有了它，每节课的模板都更短、更整齐 —— 这就是组件的价值。
defineProps({
  title: { type: String, required: true },
  hint: { type: String, default: '' },
  code: { type: String, default: '' },
})
</script>

<template>
  <section class="card">
    <h3>{{ title }}</h3>
    <p v-if="hint" class="hint">{{ hint }}</p>

    <slot />

    <pre v-if="code" class="code">{{ code }}</pre>
  </section>
</template>
