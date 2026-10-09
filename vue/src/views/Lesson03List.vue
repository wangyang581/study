<script setup>
// ===================================================================
// 第 3 课：列表渲染 v-for 与 :key
// 页面开发中 80% 的工作是「把一组数据渲染成一组 UI」。
// ===================================================================
import { computed, ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'

const fruits = ref(['苹果', '香蕉', '橙子', '葡萄'])
const newFruit = ref('')

const todos = ref([
  { id: 1, text: '学习 v-for', done: true },
  { id: 2, text: '理解 :key 的作用', done: false },
  { id: 3, text: '完成课后练习', done: false },
])

const user = ref({ name: '小明', age: 18, city: '杭州' })

// 「过滤 + 排序」不要直接改原数组，而是用 computed 生成派生列表。
// 这样原数据干净，搜索框清空后能立刻恢复。
const keyword = ref('')
const sortBy = ref('default')

const visibleTodos = computed(() => {
  const list = todos.value.filter((t) => t.text.includes(keyword.value))
  if (sortBy.value === 'done') return [...list].sort((a, b) => Number(a.done) - Number(b.done))
  if (sortBy.value === 'active') return [...list].sort((a, b) => Number(b.done) - Number(a.done))
  return list
})

const doneCount = computed(() => todos.value.filter((t) => t.done).length)

// 数组的「响应式」增删改：push / splice / 重新赋值都可以
function addFruit() {
  const name = newFruit.value.trim()
  if (!name) return
  fruits.value.push(name)
  newFruit.value = ''
}

function removeFruit(index) {
  fruits.value.splice(index, 1) // splice 会就地修改，Vue 能侦测到
}

function toggle(id) {
  const item = todos.value.find((t) => t.id === id)
  if (item) item.done = !item.done
}

function removeTodo(id) {
  todos.value = todos.value.filter((t) => t.id !== id)
}

// 生成稳定且唯一的 key
let nextId = 4
function addTodo() {
  todos.value.push({ id: nextId++, text: '新任务 ' + nextId, done: false })
}
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. 遍历数组" hint="v-for 的写法：item in items，也可以 (item, index) in items">
    <ul class="plain">
      <li v-for="(fruit, index) in fruits" :key="fruit">
        {{ index + 1 }}. {{ fruit }}
        <button class="danger" style="padding: 2px 8px; margin-left: 8px" @click="removeFruit(index)">
          删除
        </button>
      </li>
    </ul>

    <div class="demo-row">
      <input v-model="newFruit" placeholder="输入水果名，回车添加" @keyup.enter="addFruit" />
      <button class="primary" @click="addFruit">添加</button>
    </div>

    <p class="note">
      数据变了，页面自动变。你完全不用写「先找到 li，再 appendChild」这类代码 ——
      这是声明式渲染最大的好处。
    </p>
  </DemoCard>

  <DemoCard
    title="2. :key 为什么重要？"
    hint="key 是 Vue 用来「识别每个元素身份」的标记。没有它，Vue 只能用位置来复用 DOM，容易出错。"
  >
    <p>
      规则：<strong>key 必须唯一且稳定</strong>。推荐用数据的 <code>id</code>；
      <span style="color: #d92d20">不要用 index</span>（列表顺序变化时会张冠李戴）。
    </p>
    <pre class="code">// ✅ 好：用业务 id
&lt;li v-for="item in list" :key="item.id"&gt;

// ❌ 差：用下标。删掉第 0 项后，原来第 1 项的 key 变成 0，
//    Vue 会误以为它们还是同一批元素，导致输入框内容/动画错位。
&lt;li v-for="(item, index) in list" :key="index"&gt;</pre>
  </DemoCard>

  <DemoCard title="3. 过滤 + 排序：用 computed 派生列表" hint="搜索框和排序只改变「派生数据」，源数据不动。">
    <div class="demo-row">
      <input v-model="keyword" placeholder="搜索任务…" />
      <select v-model="sortBy">
        <option value="default">默认顺序</option>
        <option value="done">已完成的靠前</option>
        <option value="active">未完成的靠前</option>
      </select>
      <span class="tag">共 {{ visibleTodos.length }} 条 / 已完成 {{ doneCount }}</span>
      <button @click="addTodo">➕ 添加任务</button>
    </div>

    <ul class="todo-list">
      <li v-for="todo in visibleTodos" :key="todo.id" :class="{ done: todo.done }">
        <input type="checkbox" :checked="todo.done" @change="toggle(todo.id)" />
        <span class="txt">{{ todo.text }}</span>
        <span class="tag">#{{ todo.id }}</span>
        <button class="danger" @click="removeTodo(todo.id)">删除</button>
      </li>
    </ul>

    <p v-if="visibleTodos.length === 0" style="color: var(--muted)">
      🔍 没有匹配的任务
    </p>

    <p class="note">
      体验一下：给复选框打钩、删除中间某项，观察列表是否正确。
      想更直观地理解 <code>:key</code>，可以把上面的 <code>:key="todo.id"</code> 改成
      <code>:key="index"</code>，再配合输入框试试差异。
    </p>
  </DemoCard>

  <DemoCard title="4. 遍历对象、数字与嵌套结构" hint="v-for 不仅能遍历数组。">
    <div class="grid-2">
      <div>
        <strong>遍历对象 (value, key, index)</strong>
        <ul class="plain">
          <li v-for="(value, key, i) in user" :key="key">
            {{ i }}. {{ key }} = {{ value }}
          </li>
        </ul>
      </div>

      <div>
        <strong>遍历数字（从 1 开始）</strong>
        <div class="demo-row">
          <span v-for="n in 6" :key="n" class="tag">{{ n }}² = {{ n * n }}</span>
        </div>
      </div>
    </div>

    <hr />
    <strong>嵌套循环：一张简单的表格</strong>
    <table class="tbl">
      <thead>
        <tr><th>科目</th><th>成绩</th></tr>
      </thead>
      <tbody>
        <template v-for="subject in [{ name: '数学', scores: [90, 88] }, { name: '英语', scores: [76, 92] }]" :key="subject.name">
          <tr v-for="(s, i) in subject.scores" :key="subject.name + i">
            <td>{{ subject.name }}</td>
            <td>{{ s }}</td>
          </tr>
        </template>
      </tbody>
    </table>
  </DemoCard>
</template>

<style scoped>
.todo-list { list-style: none; padding: 0; margin: 14px 0 0; }
.todo-list li {
  display: flex;
  align-items: center;
  gap: 10px;
  padding: 8px 10px;
  border-bottom: 1px solid var(--border);
}
.todo-list li.done .txt { text-decoration: line-through; color: var(--muted); }
.todo-list .txt { margin-right: auto; }
.tbl { width: 100%; border-collapse: collapse; margin-top: 10px; font-size: 14px; }
.tbl th, .tbl td { border: 1px solid var(--border); padding: 6px 10px; text-align: left; }
.tbl th { background: var(--code-bg); }
</style>
