<script setup>
// ===================================================================
// 第 1 课：模板语法与插值
// 核心思想：你只描述「数据长什么样」，Vue 负责把页面对应地更新。
// ===================================================================
import { ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'

// ref() 创建一个「响应式」的变量。
// 在 <script> 里读写要加 .value；在 <template> 里 Vue 会自动解包，直接写名字。
const message = ref('你好，Vue！')
const name = ref('小明')
const count = ref(3)
const rawHtml = ref('<strong style="color:#42b883">我是被 v-html 解析的粗体</strong>')
const dynamicId = ref('box-1')
const isDisabled = ref(false)
const imgSize = ref(60)
const link = ref('https://cn.vuejs.org')

// 在模板里可以调用函数
function greet(who) {
  return `Hello, ${who}!`
}
</script>

<template>
  <LessonHeader />

  <DemoCard
    title="1. 文本插值 {{ }}"
    hint="双大括号里可以放任意 JS 表达式：变量、运算、三元、函数调用、数组下标……"
  >
    <p>基础插值：<strong>{{ message }}</strong></p>
    <p>表达式运算：{{ count }} × 2 = {{ count * 2 }}</p>
    <p>三元运算：{{ count > 2 ? 'count 大于 2' : 'count 不大于 2' }}</p>
    <p>函数调用：{{ greet(name) }}</p>
    <p>字符串拼接：{{ `${name} 有 ${count} 个苹果` }}</p>

    <input v-model="message" placeholder="改我，上面会实时变化" />
    <p class="note">
      在浏览器里改上面的输入框，页面会立刻更新 —— 这就是「响应式」。
      注意：<code v-pre>{{ }}</code> 只能用在「文本内容」位置，不能用来设置属性。
    </p>
  </DemoCard>

  <DemoCard
    title="2. 属性绑定 v-bind（简写 :）"
    hint="要把数据绑到 HTML 属性上，必须用 v-bind，简写是一个冒号。"
  >
    <div class="demo-row">
      <button :id="dynamicId" :disabled="isDisabled" @click="isDisabled = !isDisabled">
        我的 id 是 {{ dynamicId }}（点我切换禁用）
      </button>
      <span class="tag">:disabled="isDisabled"</span>
    </div>

    <div class="demo-row" style="margin-top: 12px">
      <label>控制头像大小：</label>
      <input v-model.number="imgSize" type="range" min="24" max="120" />
      <span class="tag">{{ imgSize }}px</span>
    </div>

    <!-- 用 :width / :height 绑定数值属性 -->
    <div class="demo-row" style="margin-top: 12px">
      <div
        :style="{
          width: imgSize + 'px',
          height: imgSize + 'px',
          background: '#42b883',
          borderRadius: '50%',
        }"
      />
      <a :href="link" target="_blank">Vue 官方文档（:href 绑定）</a>
    </div>

    <pre v-pre class="code">&lt;img :src="url" :width="size" /&gt;   ← 属性用 : 绑定
&lt;p&gt;{{ msg }}&lt;/p&gt;                ← 文本用双大括号</pre>
  </DemoCard>

  <DemoCard
    title="3. 一次性插值 v-once 与 v-html"
    hint="v-once 让内容只渲染一次（性能优化）；v-html 会解析 HTML 字符串（注意 XSS 风险）。"
  >
    <p>普通插值（会随 count 变化）：{{ count }}</p>
    <p v-once>v-once 插值（永远是第一次的值：{{ count }}）</p>
    <button @click="count++">count++</button>

    <hr />
    <p>v-html 渲染结果：</p>
    <div v-html="rawHtml" />
    <p class="note warn">
      ⚠️ 永远不要对「用户输入」使用 v-html，否则可能被注入恶意脚本（XSS）。
      它只适合渲染你信得过的、自己拼好的 HTML。
    </p>
  </DemoCard>

  <DemoCard
    title="4. v-pre 跳过编译"
    hint="给元素加 v-pre，Vue 不会编译它内部的双大括号，原样显示。用来展示「Vue 代码本身」。"
  >
    <div class="grid-2">
      <div>
        <p>不加 v-pre：</p>
        <p>{{ message }}</p>
      </div>
      <div>
        <p>加了 v-pre：</p>
        <p v-pre>{{ message }}</p>
      </div>
    </div>
  </DemoCard>
</template>

<style scoped>
p { margin: 6px 0; }
</style>
