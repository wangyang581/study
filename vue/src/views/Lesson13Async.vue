<script setup>
// ===================================================================
// 第 13 课：异步数据与网络请求
// 页面开发的日常：请求 → loading → 成功/失败 → 渲染/空状态。
// 本节用「模拟接口」+「真实 fetch」两种方式演示完整流程。
// ===================================================================
import { computed, onMounted, ref, watch } from 'vue'
import LessonHeader from '@/components/LessonHeader.vue'
import DemoCard from '@/components/DemoCard.vue'

// -------------------------------------------------------------------
// 1. 通用请求状态：用 status 一个变量覆盖所有分支，比多个布尔量更清晰
//    'idle' | 'loading' | 'success' | 'error'
// -------------------------------------------------------------------
const status = ref('idle')
const list = ref([])
const errorMsg = ref('')
const keyword = ref('')

// 模拟一个接口：延迟 + 随机失败
const MOCK_DB = [
  { id: 1, name: 'Vue.js', stars: 208000, lang: 'JavaScript' },
  { id: 2, name: 'React', stars: 230000, lang: 'JavaScript' },
  { id: 3, name: 'Svelte', stars: 79000, lang: 'JavaScript' },
  { id: 4, name: 'Vite', stars: 68000, lang: 'TypeScript' },
  { id: 5, name: 'Pinia', stars: 13000, lang: 'TypeScript' },
  { id: 6, name: 'Vue Router', stars: 5300, lang: 'TypeScript' },
]

function mockApi(keyword = '', { shouldFail = false, delay = 700 } = {}) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (shouldFail) return reject(new Error('网络异常：模拟请求失败'))
      const data = MOCK_DB.filter((r) => r.name.toLowerCase().includes(keyword.toLowerCase()))
      resolve(data)
    }, delay)
  })
}

// ---------- 基础版：一个函数搞定 loading / error ----------
async function load({ shouldFail = false } = {}) {
  status.value = 'loading'
  errorMsg.value = ''
  try {
    const data = await mockApi(keyword.value, { shouldFail })
    list.value = data
    status.value = 'success'
  } catch (err) {
    errorMsg.value = err.message
    status.value = 'error'
  }
}

// ---------- 并发请求：Promise.all ----------
const summary = ref(null)
async function loadSummary() {
  status.value = 'loading'
  try {
    // 多个独立请求一起发，总耗时 ≈ 最慢的那个
    const [repos, issues, commits] = await Promise.all([
      mockApi('', { delay: 500 }).then((r) => r.length),
      mockApi('', { delay: 800 }).then((r) => r.length * 3),
      mockApi('', { delay: 300 }).then((r) => r.length * 12),
    ])
    summary.value = { repos, issues, commits }
    status.value = 'success'
  } catch (e) {
    errorMsg.value = e.message
    status.value = 'error'
  }
}

// ---------- 竞态处理：只认最新一次请求的结果 ----------
let requestToken = 0
watch(keyword, async (kw) => {
  const myToken = ++requestToken
  status.value = 'loading'
  const data = await mockApi(kw, { delay: 600 }).catch(() => [])
  if (myToken !== requestToken) return // 已经过期，丢弃结果
  list.value = data
  status.value = 'success'
})

// -------------------------------------------------------------------
// 2. 真实网络请求：fetch + AbortController
// -------------------------------------------------------------------
const remote = ref([])
const remoteStatus = ref('idle')
const remoteError = ref('')
let controller = null

async function fetchRemote() {
  // 取消上一次未完成的请求，避免竞态
  controller?.abort()
  controller = new AbortController()

  remoteStatus.value = 'loading'
  remoteError.value = ''
  try {
    const res = await fetch('https://jsonplaceholder.typicode.com/users?_limit=5', {
      signal: controller.signal,
    })
    // fetch 不会因为 4xx/5xx 而 reject，必须手动检查
    if (!res.ok) throw new Error(`HTTP ${res.status} ${res.statusText}`)
    remote.value = await res.json()
    remoteStatus.value = 'success'
  } catch (err) {
    if (err.name === 'AbortError') return // 主动取消，不算错误
    remoteError.value = err.message
    remoteStatus.value = 'error'
  }
}

onMounted(() => {
  // 页面一进来就加载数据（最常见的使用场景）
  load()
})

const sorted = computed(() => [...list.value].sort((a, b) => b.stars - a.stars))
function formatStars(n) {
  return n >= 10000 ? (n / 1000).toFixed(0) + 'k' : n
}
</script>

<template>
  <LessonHeader />

  <DemoCard title="1. 标准请求流程：idle → loading → success / error" hint="用一个 status 字段管理全部状态，模板里用 v-if 分别渲染。">
    <div class="demo-row">
      <input v-model="keyword" placeholder="搜索框架 / 库名（输入即请求）" />
      <button class="primary" @click="load({ shouldFail: false })">重新加载</button>
      <button class="danger" @click="load({ shouldFail: true })">模拟失败</button>
      <span class="tag">status = {{ status }}</span>
    </div>

    <!-- loading 状态：用骨架屏而不是一句「加载中」体验更好 -->
    <div v-if="status === 'loading'" class="skeleton-wrap">
      <div v-for="i in 3" :key="i" class="skeleton" />
    </div>

    <!-- error 状态：给用户「重试」的出口 -->
    <div v-else-if="status === 'error'" class="error-box">
      <p>❌ {{ errorMsg }}</p>
      <button class="primary" @click="load()">重试</button>
    </div>

    <!-- success：数据渲染 -->
    <ul v-else-if="sorted.length" class="repo-list">
      <li v-for="r in sorted" :key="r.id">
        <strong>{{ r.name }}</strong>
        <span class="tag">{{ r.lang }}</span>
        <span style="margin-left: auto">⭐ {{ formatStars(r.stars) }}</span>
      </li>
    </ul>

    <!-- 空状态：这个分支最容易被忘记 -->
    <p v-else class="empty">🔍 没有匹配「{{ keyword }}」的结果</p>

    <pre class="code">const status = ref('idle')   // idle | loading | success | error

async function load() {
  status.value = 'loading'
  try {
    list.value = await api()
    status.value = 'success'
  } catch (e) {
    errorMsg.value = e.message
    status.value = 'error'
  }
}</pre>

    <p class="note">
      四个状态都要考虑：<strong>加载中 / 成功 / 空数据 / 失败</strong>。
      新手常见的 bug 是「请求失败了页面一片空白，用户不知道发生了什么」。
    </p>
  </DemoCard>

  <DemoCard title="2. 并发请求 Promise.all" hint="互不依赖的请求应该并发发出，而不是一个个 await（串行）。">
    <div class="demo-row">
      <button class="primary" @click="loadSummary">并发加载汇总数据</button>
      <span v-if="summary" class="tag">
        ✓ 仓库 {{ summary.repos }} · 议题 {{ summary.issues }} · 提交 {{ summary.commits }}
      </span>
    </div>

    <pre class="code">// ❌ 串行：总耗时 500 + 800 + 300 = 1600ms
const a = await apiA()
const b = await apiB()

// ✅ 并发：总耗时 ≈ max(500, 800, 300) = 800ms
const [a, b] = await Promise.all([apiA(), apiB()])

// 想「谁成功用谁、失败也不影响」用 Promise.allSettled
// 想「谁先回来用谁」用 Promise.race</pre>
  </DemoCard>

  <DemoCard title="3. 真实请求：fetch + AbortController" hint="需要联网。注意 fetch 对 4xx/5xx 不会自动抛错。" >
    <div class="demo-row">
      <button class="primary" @click="fetchRemote">请求 jsonplaceholder</button>
      <button class="danger" @click="controller?.abort()">取消请求</button>
      <span class="tag">status = {{ remoteStatus }}</span>
    </div>

    <p v-if="remoteStatus === 'loading'">⏳ 请求中……</p>
    <p v-else-if="remoteStatus === 'error'">❌ {{ remoteError }}</p>
    <ul v-else-if="remote.length" class="repo-list">
      <li v-for="u in remote" :key="u.id">
        <strong>{{ u.name }}</strong>
        <span style="margin-left: auto; color: var(--muted)">{{ u.email }}</span>
      </li>
    </ul>

    <pre class="code">const controller = new AbortController()
const res = await fetch(url, { signal: controller.signal })
if (!res.ok) throw new Error('HTTP ' + res.status)   // 必须手动判断
const data = await res.json()
// 取消：controller.abort() → fetch 抛出 AbortError</pre>
  </DemoCard>

  <DemoCard title="4. 生产环境建议" hint="真实项目里通常会把请求逻辑封装起来。">
    <pre class="code">// 1) 封装一个 request 工具（统一 baseURL、token、错误提示）
//    大多数项目会用 axios：拦截器、超时、自动 JSON 很好用
//    const api = axios.create({ baseURL: '/api', timeout: 10000 })

// 2) 把「请求 + 状态」抽成 composable，组件只关心数据
export function useRequest(fetcher, { immediate = true } = {}) {
  const data = ref(null), status = ref('idle'), error = ref(null)
  async function run(...args) {
    status.value = 'loading'
    try { data.value = await fetcher(...args); status.value = 'success' }
    catch (e) { error.value = e; status.value = 'error' }
  }
  if (immediate) run()
  return { data, status, error, run }
}

// 3) 组件里
const { data: users, status, run } = useRequest(() => api.get('/users'))

// 4) 列表接口记得做：分页、去重、防抖、缓存、取消
// 5) 敏感信息不要放在前端；token 过期要统一处理 401 跳转登录</pre>

    <p class="note warn">
      生产项目建议：<code>axios</code> 或 <code>ofetch</code> 做封装；
      数据请求也可交给 <code>@tanstack/vue-query</code> 这类库来管理缓存与重试。
    </p>
  </DemoCard>
</template>

<style scoped>
.repo-list { list-style: none; padding: 0; margin: 14px 0 0; }
.repo-list li {
  display: flex; align-items: center; gap: 10px;
  padding: 10px 12px; border-bottom: 1px solid var(--border); font-size: 14px;
}
.skeleton-wrap { display: grid; gap: 10px; margin-top: 14px; }
.skeleton {
  height: 42px; border-radius: 8px;
  background: linear-gradient(90deg, #eef2f6 25%, #e3e8ef 37%, #eef2f6 63%);
  background-size: 400% 100%;
  animation: shimmer 1.3s ease infinite;
}
@keyframes shimmer { 0% { background-position: 100% 0 } 100% { background-position: -100% 0 } }
.error-box {
  margin-top: 14px; padding: 14px; border-radius: 8px;
  background: rgba(217, 45, 32, .07); border: 1px solid rgba(217, 45, 32, .3);
}
.empty { margin-top: 14px; color: var(--muted); }
</style>
