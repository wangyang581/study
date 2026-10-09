<script setup>
// ===================================================================
// 第 8 课：组件基础 —— props 向下传，emit 向上报
// 组件化的意义：把复杂页面拆成一个个「自治的小块」，
// 每块只关心自己的职责，组合起来就成了页面。
// ===================================================================
import { ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'
import BaseButton from '@/components/BaseButton.vue'
import UserCard from '@/components/UserCard.vue'

// 父组件的数据
const clickLog = ref([])
const pressed = ref(0)

const users = ref([
  { id: 1, name: 'alice', role: '前端工程师', color: '#42b883' },
  { id: 2, name: 'bob', role: '后端工程师', color: '#8b5cf6' },
  { id: 3, name: 'carol', role: '设计师', color: '#f59e0b' },
])

// 谁被关注了
const following = ref(new Set())

function toggleFollow(name) {
  const next = new Set(following.value)
  next.has(name) ? next.delete(name) : next.add(name)
  following.value = next // 用新 Set 赋值，保证触发响应式更新
}

// 接收子组件 emit 出来的事件
// 事件名 'action'，负载是 BaseButton 抛出的 { label, at }
function onButtonAction(payload) {
  pressed.value++
  clickLog.value.unshift(`收到子组件事件：${payload.label} @ ${new Date(payload.at).toLocaleTimeString()}`)
  if (clickLog.value.length > 4) clickLog.value.pop()
}
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. 引入并使用子组件" hint="在 <script setup> 中 import 后，模板里就能直接用（PascalCase 或 kebab-case 都行）。">
    <!-- 这里 BaseButton 是父组件传给子组件的 props -->
    <div class="demo-row">
      <BaseButton label="默认按钮" @action="onButtonAction" />
      <BaseButton label="主要按钮" variant="primary" @action="onButtonAction" />
      <BaseButton label="危险按钮" variant="danger" @action="onButtonAction" />
      <BaseButton label="禁用按钮" disabled />
      <BaseButton label="带数字" variant="primary" :count="3" @action="onButtonAction" />
    </div>

    <p style="margin-top: 12px">
      父组件收到事件 <strong>{{ pressed }}</strong> 次
    </p>
    <div v-if="clickLog.length" class="code">
      <div v-for="(l, i) in clickLog" :key="i">{{ l }}</div>
    </div>

    <pre class="code">&lt;!-- 父组件：传 props 下去，监听事件上来 --&gt;
&lt;BaseButton label="主要按钮" variant="primary" @action="onButtonAction" /&gt;

&lt;!-- 子组件 BaseButton.vue --&gt;
const props = defineProps({ label: String, variant: String, disabled: Boolean })
const emit  = defineEmits(['action'])
emit('action', { label: props.label })   // 抛事件给父组件</pre>
  </DemoCard>

  <DemoCard
    title="2. 单向数据流：props 是只读的"
    hint="子组件不能直接修改 props。数据只从父流向子；想改，就 emit 一个事件，让父组件去改。"
  >
    <pre class="code">// ❌ 子组件里这样写会报警告：
props.user.name = 'hacked'

// ✅ 正确姿势：
// 1) 子组件只读地使用 props
// 2) 需要变更时 emit 事件：emit('update', newValue)
// 3) 父组件监听事件并更新自己的数据
&lt;UserCard :user="u" @toggle-follow="toggleFollow" /&gt;</pre>

    <p class="note">
      为什么这么设计？因为「修改来源唯一」才能让数据流清晰、可追踪。
      如果多个子组件都能改同一份数据，出了 bug 极难定位。
    </p>
  </DemoCard>

  <DemoCard title="3. 完整例子：用户列表" hint="父组件持有列表数据和「关注集合」，子组件只负责展示 + 报告点击。">
    <div class="grid-2">
      <UserCard
        v-for="u in users"
        :key="u.id"
        :user="u"
        :following="following.has(u.name)"
        @toggle-follow="toggleFollow"
      />
    </div>

    <p style="margin-top: 14px">
      已关注：<span class="tag">{{ following.size ? [...following].join('、') : '暂无' }}</span>
    </p>
  </DemoCard>

  <DemoCard title="4. props 的几种声明方式" hint="把 props 当成组件的「API 契约」，写清楚类型和默认值，团队协作会轻松很多。">
    <pre class="code">// 最简单：只写类型
defineProps(['title', 'count'])

// 推荐：对象写法，带类型 / 必填 / 默认值 / 校验
defineProps({
  title: { type: String, required: true },
  count: { type: Number, default: 0 },
  tags:  { type: Array,  default: () => [] },     // 对象/数组默认值要用工厂函数
  level: { type: String, validator: (v) => ['low', 'mid', 'high'].includes(v) },
})

// 需要默认值时也可以用 withDefaults
const props = withDefaults(defineProps({ title: String, count: Number }), {
  title: '未命名',
  count: 0,
})</pre>

    <p class="note warn">
      <code>defineProps</code> / <code>defineEmits</code> / <code>defineModel</code> /
      <code>defineExpose</code> 都是「编译器宏」，不需要 import，也不能在普通 JS 文件里使用。
    </p>
  </DemoCard>
</template>
