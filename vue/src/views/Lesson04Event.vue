<script setup>
// ===================================================================
// 第 4 课：事件处理 v-on（简写 @）与事件修饰符
// ===================================================================
import { ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'

const count = ref(0)
const events = ref([])

function add(n) {
  count.value += n
}

// 内联调用时可以传参，模板里能拿到 $event（原生事件对象）
function logStep(step, e) {
  events.value.unshift(`第 ${step} 步，事件类型：${e.type}`)
}

const text = ref('')
const blurTip = ref('还没失焦')

function onInput(e) {
  text.value = e.target.value
}

function onBlur(e) {
  blurTip.value = `失焦时内容为「${e.target.value}」`
}
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. v-on 绑定事件（简写 @）" hint="<button v-on:click> 等价于 <button @click>，后者更常用。">
    <div class="demo-row">
      <button @click="count++">点我 +1</button>
      <button @click="add(5)">+5</button>
      <button @click="add(-1)">-1</button>
      <button @click="count = 0">重置</button>
      <span class="tag">count = {{ count }}</span>
    </div>

    <div class="demo-row" style="margin-top: 12px">
      <button @click="add(2)">内联表达式</button>
      <button @click="(e) => logStep('内联', e)">传 $event（内联写法）</button>
      <button @click="count++">方法名写法</button>
    </div>

    <p class="note">
      <code>@click="add(5)"</code> 你传的是「调用表达式」；
      <code>@click="add"</code> 传的是「函数本身」，Vue 会把事件对象作为第一个参数传进去。
      想同时传参又要事件对象，就用 <code>@click="fn(5, $event)"</code>。
    </p>

    <div v-if="events.length" class="code" style="margin-top: 12px">
      <div v-for="(e, i) in events.slice(0, 4)" :key="i">{{ e }}</div>
    </div>
  </DemoCard>

  <DemoCard title="2. 事件修饰符" hint="修饰符写在事件名后面，用来处理常见的事件细节，省去写 e.preventDefault()。">
    <div class="demo-row">
      <a href="https://cn.vuejs.org" target="_blank" @click.prevent="events.unshift('@click.prevent：阻止了跳转')">
        我会拦截跳转（.prevent）
      </a>
      <a href="https://cn.vuejs.org" target="_blank">我不会（没有 .prevent）</a>
    </div>

    <hr />
    <p>点击下面方框，事件会从内往外「冒泡」：</p>
    <div class="outer" @click="events.unshift('外层被点击（冒泡到达）')">
      外层 div
      <div class="inner" @click.stop="events.unshift('内层被点击，并用 .stop 阻止冒泡')">
        内层 div（@click.stop）
      </div>
      <div class="inner" @click="events.unshift('内层被点击，未阻止冒泡')">
        内层 div（普通 @click）
      </div>
    </div>

    <hr />
    <input placeholder="试试按 Enter / Esc / 输入" @keyup.enter="events.unshift('按下 Enter')" @keyup.esc="events.unshift('按下 Esc')" />
    <div class="demo-row" style="margin-top: 8px">
      <button @click.once="events.unshift('这个只触发一次（.once）')">.once 按钮</button>
    </div>

    <pre class="code">.prevent  阻止默认行为（表单提交、链接跳转）
.stop     阻止事件冒泡
.self     只有事件目标是自身时才触发
.once     只触发一次
.capture  使用捕获模式
.passive  滚动性能优化（不监听 preventDefault）
按键修饰符 .enter / .esc / .tab / .delete / .space / .up ...
系统修饰符 .ctrl / .alt / .shift / .meta
鼠标修饰符 .left / .right / .middle</pre>
  </DemoCard>

  <DemoCard title="3. 常用原生事件：input / change / blur / submit" hint="表单场景必备。">
    <input :value="text" @input="onInput" @blur="onBlur" placeholder="输入后点别处试试" />
    <p>{{ blurTip }}</p>
    <p>实时值：<strong>{{ text }}</strong></p>

    <p class="note">
      其实这种「输入框 ↔ 状态」的联动，用下一课的 <code>v-model</code> 一行就够了。
      这里用 <code>@input</code> 是为了让你看清它的底层原理。
    </p>
  </DemoCard>

  <DemoCard title="4. 键盘事件与表单提交" hint="回车提交是搜索框的标配。">
    <form @submit.prevent="events.unshift('表单被提交（已阻止默认刷新）')">
      <div class="demo-row">
        <input name="q" placeholder="输入后按回车" />
        <button class="primary" type="submit">提交</button>
      </div>
    </form>
    <p class="note warn">
      表单提交默认会刷新整个页面，Vue 应用里几乎总是要加 <code>.prevent</code>。
    </p>
  </DemoCard>
</template>

<style scoped>
.outer { border: 2px dashed var(--primary); padding: 12px; border-radius: 8px; margin-top: 8px; }
.inner { border: 1px solid var(--border); background: #fff; padding: 10px; margin-top: 8px; border-radius: 6px; cursor: pointer; }
</style>
