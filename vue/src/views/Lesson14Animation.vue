<script setup>
// ===================================================================
// 第 14 课：过渡与动画
// <Transition>      → 单个元素的进入/离开
// <TransitionGroup> → 列表的增删/移动
// CSS 类名遵循固定规则：v-enter-from / v-enter-active / v-enter-to 等
// ===================================================================
import { ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'

const show1 = ref(true)
const show2 = ref(true)
const show3 = ref(true)

const animList = ref([1, 2, 3])
let uid = 4
function addItem() {
  animList.value.push(uid++)
}
function removeItem() {
  animList.value.pop()
}
function shuffle() {
  animList.value = [...animList.value].sort(() => Math.random() - 0.5)
}
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. 淡入淡出" hint="Transition 组件会自动给内部元素加上 6 个固定的 CSS 类。">
    <button @click="show1 = !show1">切换显示（淡入淡出）</button>

    <Transition name="fade">
      <p v-if="show1" class="box">我淡入淡出</p>
    </Transition>

    <pre class="code">/* 进入：opacity 0 → 1 */
.fade-enter-from { opacity: 0 }
.fade-enter-active { transition: opacity .4s ease }
.fade-enter-to { opacity: 1 }

/* 离开：opacity 1 → 0 */
.fade-leave-from { opacity: 1 }
.fade-leave-active { transition: opacity .4s ease }
.fade-leave-to { opacity: 0 }</pre>
  </DemoCard>

  <DemoCard title="2. 滑动 + 缩放" hint="组合 transform 就能做出常见的抽屉、下拉、卡片效果。">
    <button @click="show2 = !show2">切换显示（滑入 + 缩放）</button>

    <Transition name="slide">
      <p v-if="show2" class="box">我滑入并放大</p>
    </Transition>

    <pre class="code">.slide-enter-from { opacity: 0; transform: translateY(-16px) scale(.96) }
.slide-enter-active { transition: all .35s cubic-bezier(.34,1.56,.64,1) }
.slide-leave-to { opacity: 0; transform: translateY(-16px) scale(.96) }</pre>
  </DemoCard>

  <DemoCard title="3. 弹窗遮罩 + 内容分别过渡" hint="多个元素要过渡时，用外层 Transition 包裹，只对根节点生效；或用 mode='out-in' 做序列过渡。">
    <button class="primary" @click="show3 = !show3">{{ show3 ? '关闭' : '打开' }}弹窗</button>

    <Transition name="fade">
      <div v-if="show3" class="overlay" @click.self="show3 = false">
        <Transition name="pop" appear>
          <div v-if="show3" class="modal">
            <h3>弹窗标题</h3>
            <p>遮罩淡入、内容弹出，是两个不同的过渡。</p>
            <button class="primary" @click="show3 = false">关闭</button>
          </div>
        </Transition>
      </div>
    </Transition>

    <p class="note">
      <code>appear</code> 表示「初次渲染时也播放进入动画」。
      <code>mode="out-in"</code> 用于两个元素互斥切换时，等旧的先走完再进新的。
    </p>
  </DemoCard>

  <DemoCard title="4. 列表过渡 TransitionGroup" hint="给增删的每一项做动画，并让其他项平滑地「让位」。">
    <div class="demo-row">
      <button class="primary" @click="addItem">添加一项</button>
      <button class="danger" :disabled="!animList.length" @click="removeItem">移除末项</button>
      <button @click="shuffle">打乱顺序（看 .move 生效）</button>
      <button @click="animList = []">清空</button>
    </div>

    <!-- tag="ul" 表示渲染成 ul，否则默认是 fragment -->
    <TransitionGroup name="list" tag="ul" class="anim-list">
      <li v-for="n in animList" :key="n">第 {{ n }} 项</li>
    </TransitionGroup>

    <pre class="code">.list-enter-from { opacity: 0; transform: translateX(-24px) }
.list-leave-to   { opacity: 0; transform: translateX(24px) }
/* 关键：离开的元素要脱离文档流，其他项才能平滑移动 */
.list-leave-active { position: absolute }
/* 位置变化的元素会加上这个类 */
.list-move { transition: transform .4s ease }</pre>
  </DemoCard>

  <DemoCard title="5. JS 钩子与第三方动画库" hint="CSS 不够用时，Transition 也支持 JS 钩子（配合 GSAP、anime.js 等）。">
    <pre class="code">&lt;Transition
  @before-enter="onBeforeEnter"
  @enter="onEnter"
  @after-enter="onAfterEnter"
  :css="false"&gt;      &lt;!-- 声明不用 CSS 过渡 --&gt;

// 在 onEnter(el, done) 里调用动画库，结束时手动 done()
function onEnter(el, done) {
  gsap.to(el, { y: 0, opacity: 1, onComplete: done })
}</pre>

    <p class="note">
      什么时候需要动画库？时间线编排、物理弹性、SVG 路径、滚动驱动。
      只用简单的入场/列表动画，纯 CSS 就足够了 —— 优先 CSS，性能更好。
    </p>
  </DemoCard>
</template>

<style scoped>
.box {
  margin-top: 14px;
  padding: 14px 18px;
  background: var(--primary);
  color: #fff;
  border-radius: 8px;
  display: inline-block;
}

/* --- 淡入淡出 --- */
.fade-enter-active, .fade-leave-active { transition: opacity .4s ease; }
.fade-enter-from, .fade-leave-to { opacity: 0; }

/* --- 滑入 + 缩放 --- */
.slide-enter-active { transition: all .35s cubic-bezier(.34, 1.56, .64, 1); }
.slide-leave-active { transition: all .25s ease; }
.slide-enter-from { opacity: 0; transform: translateY(-16px) scale(.96); }
.slide-leave-to { opacity: 0; transform: translateY(-16px) scale(.96); }

/* --- 弹窗 --- */
.overlay {
  position: fixed; inset: 0; z-index: 60;
  background: rgba(15, 23, 42, .55);
  display: grid; place-items: center;
}
.modal {
  background: #fff; border-radius: 14px; padding: 24px;
  max-width: 380px; box-shadow: 0 24px 60px rgba(0,0,0,.3);
}
.pop-enter-active { transition: all .3s cubic-bezier(.34, 1.56, .64, 1); }
.pop-leave-active { transition: all .2s ease; }
.pop-enter-from, .pop-leave-to { opacity: 0; transform: scale(.9) translateY(10px); }

/* --- 列表 --- */
.anim-list { list-style: none; padding: 0; margin: 16px 0 0; position: relative; }
.anim-list li {
  padding: 10px 14px; margin-bottom: 8px;
  background: #fff; border: 1px solid var(--border); border-radius: 8px;
}
.list-enter-active, .list-leave-active { transition: all .4s ease; }
.list-enter-from { opacity: 0; transform: translateX(-24px); }
.list-leave-to { opacity: 0; transform: translateX(24px); }
.list-leave-active { position: absolute; width: 100%; }
.list-move { transition: transform .4s ease; }
</style>
