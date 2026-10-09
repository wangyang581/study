<script setup>
// ===================================================================
// 第 7 课：Class 与 Style 的动态绑定
// 让界面的「样子」跟着数据走，是交互开发的核心技能。
// ===================================================================
import { computed, reactive, ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'

const isActive = ref(true)
const hasError = ref(false)
const size = ref('medium')

// 字符串写法
const staticClass = ref('box')

// 数组语法：可以混用字符串、变量、三元
const classList = computed(() => ['box', size.value, { active: isActive.value, error: hasError.value }])

// 对象语法：键是类名，值是布尔（true 才加）
const classObject = computed(() => ({
  'box': true,
  'box-lg': size.value === 'large',
  'box-sm': size.value === 'small',
  active: isActive.value,
  error: hasError.value,
}))

// ---------- 内联 style ----------
const baseStyle = reactive({ padding: '12px', borderRadius: '8px' })
const color = ref('#42b883')
const fontSize = ref(14)
const showBorder = ref(true)

const styleObject = computed(() => ({
  ...baseStyle,
  color: '#fff',
  backgroundColor: color.value,
  fontSize: fontSize.value + 'px',
  border: showBorder.value ? '3px solid #2c3e50' : 'none',
  width: '120px',
  textAlign: 'center',
}))

// 数组语法：后面覆盖前面
const styleArray = computed(() => [
  { padding: '12px', borderRadius: '8px', color: '#fff' },
  { backgroundColor: color.value, fontSize: fontSize.value + 'px' },
])

// 常用场景：进度条 / 主题色
const progress = ref(35)
const theme = ref('light')
const THEMES = {
  light: { bg: '#ffffff', text: '#24292f', accent: '#42b883' },
  dark: { bg: '#1e293b', text: '#f1f5f9', accent: '#38bdf8' },
  sepia: { bg: '#f7f0e3', text: '#5b4636', accent: '#b45309' },
}
const themeVars = computed(() => ({
  '--panel-bg': THEMES[theme.value].bg,
  '--panel-text': THEMES[theme.value].text,
  '--panel-accent': THEMES[theme.value].accent,
}))
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. Class 的三种写法" hint="对象语法用于「开关某个类」，数组语法用于「组合多个类」。">
    <div class="demo-row">
      <button :class="{ primary: isActive }" @click="isActive = !isActive">切换 active</button>
      <button :class="{ danger: hasError }" @click="hasError = !hasError">切换 error</button>
      <select v-model="size">
        <option value="small">small</option>
        <option value="medium">medium</option>
        <option value="large">large</option>
      </select>
    </div>

    <!-- 对象语法 -->
    <div :class="classObject" style="margin-top: 14px">对象语法</div>

    <!-- 数组语法 -->
    <div :class="classList" style="margin-top: 10px">数组语法</div>

    <!-- 内联 + 静态混用：最终会被合并 -->
    <div class="box" :class="{ active: isActive }" style="margin-top: 10px">
      静态 class + 动态 class
    </div>

    <pre class="code">:class="{ active: isActive, error: hasError }"       // 对象
:class="['box', size, { active: isActive }]"        // 数组
:class="['box', isActive ? 'active' : '']"          // 三元
class="box" :class="{ active }"                     // 静态+动态合并</pre>
  </DemoCard>

  <DemoCard title="2. 内联 Style 绑定" hint="属性名用 camelCase（fontSize）或 kebab-case 字符串（'font-size'），数值默认补 px。">
    <div class="demo-row">
      <label>颜色 <input v-model="color" type="color" style="padding: 0; width: 44px" /></label>
      <label>字号 <input v-model.number="fontSize" type="range" min="10" max="28" /></label>
      <label><input v-model="showBorder" type="checkbox" /> 显示边框</label>
    </div>

    <div class="demo-row" style="margin-top: 14px">
      <div :style="styleObject">对象语法</div>
      <div :style="styleArray">数组语法</div>
      <!-- 直接写死的内联样式也可以 -->
      <div :style="{ backgroundColor: color, color: '#fff', padding: '12px', borderRadius: '8px' }">
        直接写
      </div>
    </div>
  </DemoCard>

  <DemoCard title="3. CSS 自定义属性（CSS 变量）驱动主题" hint="把主题色写进 style 的 --var，CSS 里用 var() 读取。主题切换变得非常轻量。">
    <div class="demo-row">
      <button v-for="t in Object.keys(THEMES)" :key="t" :class="{ primary: theme === t }" @click="theme = t">
        {{ t }}
      </button>
    </div>

    <!-- :style 绑定一个包含 CSS 变量的对象 -->
    <div class="theme-panel" :style="themeVars" style="margin-top: 14px">
      <h3>主题面板：{{ theme }}</h3>
      <p>这段文字的配色来自 CSS 变量，而不是逐个改样式。</p>
      <button>强调色按钮</button>
    </div>

    <pre class="code">// JS：计算 CSS 变量
const themeVars = computed(() => ({ '--panel-accent': THEMES[theme.value].accent }))
// 模板
&lt;div :style="themeVars"&gt; ... &lt;/div&gt;
/* CSS */
.theme-panel button { background: var(--panel-accent); color: #fff; border: none; }</pre>
  </DemoCard>

  <DemoCard title="4. 实战：动态进度条" hint="宽度、颜色都由数据算出 —— 这就是「数据驱动视图」。">
    <div class="demo-row">
      <input v-model.number="progress" type="range" min="0" max="100" style="flex: 1" />
      <span class="tag">{{ progress }}%</span>
    </div>

    <div class="bar">
      <div
        class="bar-inner"
        :style="{
          width: progress + '%',
          backgroundColor: progress < 30 ? '#d92d20' : progress < 70 ? '#f79009' : '#42b883',
        }"
      />
    </div>

    <pre class="code">&lt;div class="bar-inner" :style="{ width: progress + '%', backgroundColor: color }" /&gt;</pre>
  </DemoCard>
</template>

<style scoped>
.box {
  padding: 10px 14px;
  border: 2px solid var(--border);
  border-radius: 8px;
  transition: .2s;
  display: inline-block;
}
.box.active { border-color: #42b883; background: rgba(66, 184, 131, .12); }
.box.error { border-color: #d92d20; background: rgba(217, 45, 32, .1); }
.box.small { font-size: 12px; padding: 6px 10px; }
.box.medium { font-size: 15px; }
.box.large { font-size: 19px; padding: 14px 18px; }

.theme-panel {
  padding: 18px;
  border-radius: 10px;
  background: var(--panel-bg);
  color: var(--panel-text);
  border: 1px solid var(--border);
  transition: .25s;
}
.theme-panel h3 { margin: 0 0 6px; }
.theme-panel button {
  background: var(--panel-accent);
  border: none;
  color: #fff;
}

.bar {
  height: 18px;
  background: var(--code-bg);
  border-radius: 999px;
  overflow: hidden;
  margin-top: 14px;
}
.bar-inner {
  height: 100%;
  border-radius: 999px;
  transition: width .3s ease, background-color .3s;
}
</style>
