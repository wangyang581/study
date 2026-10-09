<script setup>
// ===================================================================
// 第 9 课：插槽 slot
// 组件既可以接收「数据」（props），也可以接收「模板内容」（slot）。
// 如果说 props 让组件可配置，插槽就让组件可「包裹」和「定制」。
// ===================================================================
import { ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'
import BasePanel from '@/components/BasePanel.vue'

const fruits = ref(['🍎 苹果', '🍌 香蕉', '🍇 葡萄'])
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. 默认插槽" hint="写在组件标签「中间」的内容，会替换掉子组件里的 <slot />。">
    <div class="grid-2">
      <BasePanel title="没传内容时">
        这里的内容会填充到子组件的默认插槽里。
      </BasePanel>

      <BasePanel title="传了内容（覆盖默认）">
        <p>我可以放任意内容：</p>
        <strong style="color: var(--primary-dark)">加粗文本</strong>
        <button class="primary" style="margin-left: 8px">一个按钮</button>
      </BasePanel>
    </div>

    <pre class="code">&lt;!-- 子组件 BasePanel.vue --&gt;
&lt;div class="panel-body"&gt;
  &lt;slot&gt;这里是没有内容时的兜底&lt;/slot&gt;
&lt;/div&gt;

&lt;!-- 父组件 --&gt;
&lt;BasePanel&gt;这段文字被放进插槽&lt;/BasePanel&gt;</pre>
  </DemoCard>

  <DemoCard title="2. 具名插槽" hint="一个组件里有多个插槽位置时，用 name 区分，父组件用 #名字 指定。">
    <BasePanel :items="fruits">
      <!-- #header 是 v-slot:header 的缩写 -->
      <template #header>
        <span style="color: #d92d20">🔴 自定义的头部（来自父组件）</span>
      </template>

      <!-- 没写 template 的内容都进入默认插槽 -->
      <p>中间区域是默认插槽的内容。</p>

      <!-- 作用域插槽：子组件把 items 暴露出来，父组件决定怎么渲染 -->
      <template #list="{ items, count }">
        <em>底部由作用域插槽渲染（共 {{ count }} 项）：{{ items.join('，') }}</em>
      </template>
    </BasePanel>

    <p class="note">
      <code>#list="{ items, count }"</code> 用的是「解构赋值」语法，
      相当于 <code>v-slot:list="slotProps"</code> 然后取 <code>slotProps.items</code>。
    </p>
  </DemoCard>

  <DemoCard title="3. 作用域插槽：为什么它很强大？" hint="数据在子组件里，但「长什么样」由父组件决定。表格、列表、下拉框组件都靠它实现高度可定制。">
    <BasePanel :items="fruits">
      <template #header>用作用域插槽自定义每一项</template>

      <template #list="{ items }">
        <ul class="plain" style="margin: 0; padding-left: 18px">
          <!-- 父组件拿到 items 后自由渲染 -->
          <li v-for="(f, i) in items" :key="i">
            {{ i + 1 }}. {{ f }}
            <span class="tag">第 {{ i + 1 }} 项</span>
          </li>
        </ul>
      </template>
    </BasePanel>

    <hr />
    <p>同一个组件，换个父组件写法就完全不同：</p>

    <BasePanel :items="fruits">
      <template #header>渲染成标签列表</template>
      <template #list="{ items }">
        <div class="demo-row">
          <span v-for="(f, i) in items" :key="i" class="tag">{{ f }}</span>
        </div>
      </template>
    </BasePanel>

    <pre v-pre class="code">&lt;!-- 子组件 --&gt;
&lt;slot name="list" :items="items" :count="items.length" /&gt;

&lt;!-- 父组件：拿到子组件的数据，自己决定渲染 --&gt;
&lt;template #list="{ items }"&gt;
  &lt;li v-for="f in items"&gt;{{ f }}&lt;/li&gt;
&lt;/template&gt;</pre>
  </DemoCard>

  <DemoCard title="4. 插槽的兜底内容与作用域规则" hint="父组件插槽里的数据来自父组件，不能直接访问子组件的数据（除非通过作用域插槽显式传出来）。">
    <div class="grid-2">
      <BasePanel title="这个 header 是子组件的兜底内容">
        没传 header 插槽，子组件 slot 内部的兜底文本就会生效。
      </BasePanel>

      <BasePanel>
        <template #header>
          <span class="tag">父组件提供的 header</span>
        </template>
        传了 header 插槽，就覆盖掉兜底内容。
      </BasePanel>
    </div>

    <p class="note warn">
      「编译作用域」：插槽里的内容属于<strong>父组件</strong>作用域，
      它访问不到子组件内部的变量。这也是为什么需要「作用域插槽」——它是唯一的反向通道。
    </p>
  </DemoCard>
</template>
