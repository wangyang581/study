<script setup>
// -------------------------------------------------------------------
// 面板组件：演示三种插槽
//   1. 默认插槽 <slot />
//   2. 具名插槽 <slot name="header" />
//   3. 作用域插槽 <slot name="list" :items="..." />
//      把子组件内部的数据「反向」交给父组件决定怎么渲染
// -------------------------------------------------------------------
defineProps({
  title: { type: String, default: '面板' },
  items: { type: Array, default: () => [] },
})
</script>

<template>
  <div class="panel">
    <!-- 具名插槽：父组件用 <template #header> 填充 -->
    <header class="panel-head">
      <slot name="header">{{ title }}</slot>
    </header>

    <div class="panel-body">
      <!-- 默认插槽：父组件直接写在标签中间的内容 -->
      <slot>
        <em style="color: var(--muted)">（这里还没有内容）</em>
      </slot>
    </div>

    <footer v-if="items.length" class="panel-foot">
      <!--
        作用域插槽：把 items 作为 props 传给父组件的模板，
        父组件通过 v-slot="{ items }" 取到它。
      -->
      <slot name="list" :items="items" :count="items.length" />
    </footer>
  </div>
</template>

<style scoped>
.panel { border: 1px solid var(--border); border-radius: 10px; overflow: hidden; background: #fff; }
.panel-head {
  padding: 10px 14px; background: var(--code-bg);
  font-size: 13px; font-weight: 600;
}
.panel-body { padding: 14px; }
.panel-foot { padding: 10px 14px; border-top: 1px dashed var(--border); }
</style>
