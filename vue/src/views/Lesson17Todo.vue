<script setup>
// ===================================================================
// 第 17 课：综合实战 —— 待办清单
// 把前面所有知识串起来：
//   ref / computed / watch、v-model、v-for + :key、事件、条件渲染、
//   组件、TransitionGroup 动画、组合式函数、localStorage 持久化。
// ===================================================================
import { computed, nextTick, ref } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'
import { useLocalStorage } from '@/composables/useLocalStorage'

// ---------- 数据：自动持久化到 localStorage ----------
const todos = useLocalStorage('vue-lab-todos', [
  { id: 1, text: '看完 17 节课', done: true },
  { id: 2, text: '动手改一遍代码', done: false },
  { id: 3, text: '做一个自己的小项目', done: false },
])

// ---------- 界面状态 ----------
const draft = ref('')
const filter = ref('all')       // all | active | done
const editingId = ref(null)     // 正在编辑哪一条
const editingText = ref('')
const editInput = ref(null)
const keyword = ref('')

let nextId = Math.max(0, ...todos.value.map((t) => t.id)) + 1

// ---------- 派生数据（computed）----------
const filtered = computed(() => {
  let list = todos.value
  if (filter.value === 'active') list = list.filter((t) => !t.done)
  if (filter.value === 'done') list = list.filter((t) => t.done)
  if (keyword.value.trim()) {
    const kw = keyword.value.trim().toLowerCase()
    list = list.filter((t) => t.text.toLowerCase().includes(kw))
  }
  return list
})

const stats = computed(() => {
  const total = todos.value.length
  const done = todos.value.filter((t) => t.done).length
  return { total, done, active: total - done, percent: total ? Math.round((done / total) * 100) : 0 }
})

const allDone = computed({
  get: () => stats.value.total > 0 && stats.value.active === 0,
  set: (v) => todos.value.forEach((t) => (t.done = v)),
})

// ---------- 操作（actions）----------
function addTodo() {
  const text = draft.value.trim()
  if (!text) return
  todos.value.unshift({ id: nextId++, text, done: false }) // 新任务放最上面
  draft.value = ''
}

function removeTodo(id) {
  todos.value = todos.value.filter((t) => t.id !== id)
}

function clearCompleted() {
  todos.value = todos.value.filter((t) => !t.done)
}

async function startEdit(todo) {
  editingId.value = todo.id
  editingText.value = todo.text
  // 等 DOM 渲染出输入框后再聚焦
  await nextTick()
  // 注意：ref 写在 v-for 里时，Vue 会收集成「数组」
  const el = Array.isArray(editInput.value)
    ? editInput.value.find(Boolean)
    : editInput.value
  el?.focus()
}

function commitEdit(todo) {
  const text = editingText.value.trim()
  if (text) todo.text = text
  else removeTodo(todo.id) // 清空内容 = 删除
  editingId.value = null
}

function cancelEdit() {
  editingId.value = null
}

function resetAll() {
  todos.value = [
    { id: 1, text: '看完 17 节课', done: true },
    { id: 2, text: '动手改一遍代码', done: false },
    { id: 3, text: '做一个自己的小项目', done: false },
  ]
  nextId = 4
  keyword.value = ''
  filter.value = 'all'
}
</script>

<template>
  <LessonHeader />

  <DemoCard title="最终成果：一个能用的待办清单" hint="刷新页面数据不会丢（存在 localStorage）。试着把它拆成组件，作为你的练习。">
    <!-- 顶部：全选 + 输入 -->
    <div class="top">
      <label class="all-toggle" title="全选/取消全选">
        <input v-model="allDone" type="checkbox" :disabled="!stats.total" />
      </label>
      <input
        v-model="draft"
        class="add-input"
        placeholder="今天要做点什么？回车添加"
        @keyup.enter="addTodo"
      />
      <button class="primary" @click="addTodo">添加</button>
    </div>

    <!-- 进度条 -->
    <div class="progress-row">
      <div class="bar"><div class="bar-inner" :style="{ width: stats.percent + '%' }" /></div>
      <span class="tag">{{ stats.done }}/{{ stats.total }} · {{ stats.percent }}%</span>
    </div>

    <!-- 筛选 + 搜索 -->
    <div class="toolbar">
      <div class="demo-row">
        <button
          v-for="f in [
            { key: 'all', label: '全部' },
            { key: 'active', label: '未完成' },
            { key: 'done', label: '已完成' },
          ]"
          :key="f.key"
          :class="{ primary: filter === f.key }"
          @click="filter = f.key"
        >
          {{ f.label }}
        </button>
      </div>

      <input v-model="keyword" placeholder="搜索…" style="margin-left: auto" />
      <button class="danger" :disabled="!stats.done" @click="clearCompleted">
        清除已完成 ({{ stats.done }})
      </button>
    </div>

    <!-- 列表：TransitionGroup 让增删有动画 -->
    <TransitionGroup name="todo" tag="ul" class="todo-list">
      <li v-for="todo in filtered" :key="todo.id" :class="{ done: todo.done }">
        <input
          v-if="editingId !== todo.id"
          type="checkbox"
          :checked="todo.done"
          @change="todo.done = !todo.done"
        />

        <!-- 展示态 -->
        <span
          v-if="editingId !== todo.id"
          class="txt"
          title="双击编辑"
          @dblclick="startEdit(todo)"
        >
          {{ todo.text }}
        </span>

        <!-- 编辑态：v-if/v-else 成对切换 -->
        <template v-else>
          <input
            ref="editInput"
            v-model="editingText"
            class="edit-input"
            @keyup.enter="commitEdit(todo)"
            @keyup.esc="cancelEdit"
            @blur="commitEdit(todo)"
          />
          <button class="primary" @mousedown.prevent @click="commitEdit(todo)">保存</button>
          <button @mousedown.prevent @click="cancelEdit">取消</button>
        </template>

        <button
          v-if="editingId !== todo.id"
          class="danger remove"
          title="删除"
          @click="removeTodo(todo.id)"
        >
          ✕
        </button>
      </li>
    </TransitionGroup>

    <!-- 空状态 -->
    <p v-if="!filtered.length" class="empty">
      <template v-if="!stats.total">📝 还没有任务，在上面输入框里加一个吧</template>
      <template v-else-if="keyword">🔍 没有匹配「{{ keyword }}」的任务</template>
      <template v-else>🎉 没有符合当前筛选的任务</template>
    </p>

    <!-- 底部 -->
    <div class="footer">
      <span>剩余 <strong>{{ stats.active }}</strong> 项未完成</span>
      <button @click="resetAll">重置演示数据</button>
    </div>
  </DemoCard>

  <DemoCard title="这个例子用到了哪些知识点？" hint="回头对照前面的课程，把每个知识点都能指出来，就说明你真的掌握了。">
    <pre class="code">ref / computed / watch        → 状态与派生状态（第 6 课）
v-model                       → 输入框、复选框双向绑定（第 5 课）
v-for + :key                  → 列表渲染（第 3 课）
v-if / v-else / v-show        → 展示态与编辑态切换、空状态（第 2 课）
@keyup.enter / @dblclick / .self → 事件处理（第 4 课）
:class / :style               → 完成态样式、进度条宽度（第 7 课）
组件 + 插槽 + props/emit       → DemoCard / LessonHeader（第 8、9 课）
nextTick + 模板引用           → 编辑时自动聚焦（第 10 课）
useLocalStorage（组合式函数）  → 逻辑复用 + 持久化（第 12 课）
TransitionGroup               → 列表增删动画（第 14 课）</pre>
  </DemoCard>

  <DemoCard title="留给你的练习" hint="下面每个练习都能显著提升你的页面开发能力。">
    <ul class="plain">
      <li>把 <code>&lt;li&gt;</code> 抽成单独组件 <code>TodoItem.vue</code>，用 props + emit 通信</li>
      <li>加上「截止日期」字段和「逾期标红」的样式</li>
      <li>加上拖拽排序（可用 <code>vuedraggable</code> 或原生 drag 事件）</li>
      <li>把数据迁到 Pinia store（第 16 课），并在另一个页面显示统计</li>
      <li>接入一个真实后端接口，把「读/写」换成网络请求</li>
      <li>写单元测试（Vitest + @vue/test-utils）覆盖 addTodo / removeTodo</li>
    </ul>
    <p class="note">
      把练习做出来，你会比「看完这 17 课」强得多。前端是手艺活，
      必须自己写一遍。
    </p>
  </DemoCard>
</template>

<style scoped>
.top { display: flex; align-items: center; gap: 10px; }
.all-toggle { display: flex; align-items: center; }
.add-input { flex: 1; }

.progress-row { display: flex; align-items: center; gap: 10px; margin-top: 14px; }
.bar { flex: 1; height: 8px; background: var(--code-bg); border-radius: 999px; overflow: hidden; }
.bar-inner { height: 100%; background: var(--primary); border-radius: 999px; transition: width .3s ease; }

.toolbar {
  display: flex; align-items: center; gap: 10px;
  margin: 16px 0 4px; flex-wrap: wrap;
}

.todo-list { list-style: none; padding: 0; margin: 12px 0 0; position: relative; }
.todo-list li {
  display: flex; align-items: center; gap: 10px;
  padding: 10px 12px; margin-bottom: 6px;
  background: #fff; border: 1px solid var(--border); border-radius: 8px;
}
.todo-list li.done .txt { text-decoration: line-through; color: var(--muted); }
.txt { flex: 1; cursor: text; }
.edit-input { flex: 1; }
.remove { padding: 2px 8px; }

.empty { color: var(--muted); margin-top: 16px; }
.footer {
  display: flex; align-items: center; justify-content: space-between;
  margin-top: 16px; padding-top: 14px; border-top: 1px solid var(--border);
  font-size: 13px; color: var(--muted);
}

/* 列表动画 */
.todo-enter-active, .todo-leave-active { transition: all .3s ease; }
.todo-enter-from { opacity: 0; transform: translateX(-20px); }
.todo-leave-to { opacity: 0; transform: translateX(20px); }
.todo-leave-active { position: absolute; width: 100%; }
.todo-move { transition: transform .3s ease; }
</style>
