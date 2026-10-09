<script setup>
// ===================================================================
// 第 2 课：条件渲染 v-if / v-else-if / v-else 与 v-show
// v-if  ：真正地创建/销毁 DOM（切换有成本）
// v-show：只是切换 CSS 的 display:none（初始渲染有成本，切换便宜）
// ===================================================================
import { ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'

const score = ref(85)
const loggedIn = ref(true)
const tab = ref('vue')
const loading = ref(false)
const dialogOpen = ref(false)
const mode = ref('v-if') // 用于对比 v-if / v-show
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. v-if / v-else-if / v-else" hint="像 if-else 一样，从上往下第一个成立的分支会被渲染。">
    <div class="demo-row">
      <label>分数：</label>
      <input v-model.number="score" type="number" min="0" max="100" />
    </div>

    <!-- 只有满足条件的那一块会被创建到 DOM 里 -->
    <p v-if="score >= 90">🏆 优秀（{{ score }}）</p>
    <p v-else-if="score >= 60">🙂 及格（{{ score }}）</p>
    <p v-else>😢 不及格（{{ score }}）</p>

    <pre class="code">&lt;p v-if="score &gt;= 90"&gt;优秀&lt;/p&gt;
&lt;p v-else-if="score &gt;= 60"&gt;及格&lt;/p&gt;
&lt;p v-else&gt;不及格&lt;/p&gt;</pre>
  </DemoCard>

  <DemoCard title="2. v-if 与 v-show 的区别" hint="打开浏览器开发者工具看 DOM，切换下面两种模式观察元素是否真的消失。">
    <div class="demo-row">
      <button :class="{ primary: mode === 'v-if' }" @click="mode = 'v-if'">用 v-if</button>
      <button :class="{ primary: mode === 'v-show' }" @click="mode = 'v-show'">用 v-show</button>
      <button @click="loggedIn = !loggedIn">切换显示（当前 {{ loggedIn }}）</button>
    </div>

    <div style="margin-top: 14px">
      <template v-if="mode === 'v-if'">
        <p v-if="loggedIn">✅ 你已登录（v-if：未登录时这段 DOM 被移除）</p>
      </template>
      <template v-else>
        <p v-show="loggedIn">✅ 你已登录（v-show：未登录时这段 DOM 仍在，只是 display:none）</p>
      </template>
    </div>

    <div class="grid-2" style="margin-top: 16px">
      <div>
        <strong>v-if 适合</strong>
        <ul class="plain">
          <li>条件很少变化</li>
          <li>初始就不该渲染（如权限内容）</li>
          <li>切换时要触发子组件生命周期</li>
        </ul>
      </div>
      <div>
        <strong>v-show 适合</strong>
        <ul class="plain">
          <li>需要频繁切换（如 Tab、tooltip）</li>
          <li>希望保留组件内部状态</li>
        </ul>
      </div>
    </div>
  </DemoCard>

  <DemoCard title="3. 常见场景：Tab 切换 + 加载态 + 弹窗" hint="这些组合是页面开发里出现频率最高的模式。">
    <div class="demo-row">
      <button :class="{ primary: tab === 'vue' }" @click="tab = 'vue'">Vue</button>
      <button :class="{ primary: tab === 'react' }" @click="tab = 'react'">React</button>
      <button :class="{ primary: tab === 'svelte' }" @click="tab = 'svelte'">Svelte</button>
    </div>

    <!-- 配合 <template> 可以一次控制多个元素，且不产生多余包裹节点 -->
    <div style="margin-top: 12px">
      <template v-if="tab === 'vue'">
        <strong>Vue</strong>
        <p>渐进式框架，模板 + 响应式，上手快，生态完善。</p>
      </template>
      <template v-else-if="tab === 'react'">
        <strong>React</strong>
        <p>用 JS/JSX 描述 UI，函数式思想，生态庞大。</p>
      </template>
      <template v-else>
        <strong>Svelte</strong>
        <p>编译期框架，运行时体积小。</p>
      </template>
    </div>

    <hr />

    <div class="demo-row">
      <button @click="loading = !loading">{{ loading ? '结束加载' : '模拟加载' }}</button>
      <button class="primary" @click="dialogOpen = true">打开弹窗</button>
    </div>

    <!-- loading 时显示骨架/提示 -->
    <p v-if="loading" style="color: var(--muted)">⏳ 加载中……</p>
    <p v-else>✅ 数据已就绪</p>

    <!-- 弹窗：v-if 控制显隐，点击遮罩关闭 -->
    <div v-if="dialogOpen" class="overlay" @click.self="dialogOpen = false">
      <div class="dialog">
        <h3>这是一个弹窗</h3>
        <p>用 v-if 控制它的创建与销毁。点击空白遮罩可以关闭。</p>
        <button class="primary" @click="dialogOpen = false">知道了</button>
      </div>
    </div>

    <p class="note">
      <code>@click.self</code> 表示「只有点在自己身上才触发」，子元素冒泡上来的点击不算。
      这样点内容区不会误关闭弹窗。
    </p>
  </DemoCard>
</template>

<style scoped>
.overlay {
  position: fixed;
  inset: 0;
  background: rgba(15, 23, 42, 0.5);
  display: grid;
  place-items: center;
  z-index: 50;
}
.dialog {
  background: #fff;
  border-radius: 12px;
  padding: 22px;
  max-width: 360px;
  box-shadow: 0 20px 50px rgba(0, 0, 0, 0.25);
}
</style>
