<script setup>
// 动态路由页面：/engineering/router/user/:id
// route.params.id 就是地址里的那一段
import { computed } from 'vue'
import { useRoute, useRouter } from 'vue-router'

const route = useRoute()
const router = useRouter()

const USERS = {
  1: { name: 'Alice', role: '前端工程师', city: '杭州' },
  2: { name: 'Bob', role: '后端工程师', city: '北京' },
  3: { name: 'Carol', role: '产品经理', city: '上海' },
}

// route.params 是响应式的：地址变了，用户信息自动跟着变
const user = computed(() => USERS[route.params.id])
</script>

<template>
  <h2>用户详情</h2>

  <div v-if="user" class="card">
    <p>路由参数 <code>id</code> = <span class="tag">{{ route.params.id }}</span></p>
    <h3>{{ user.name }}</h3>
    <p>{{ user.role }} · {{ user.city }}</p>
  </div>

  <div v-else class="card">
    <p>❌ 找不到 id 为 <code>{{ route.params.id }}</code> 的用户</p>
  </div>

  <div class="demo-row">
    <button @click="router.back()">← 返回上一页</button>
    <button class="primary" @click="router.push('/engineering/router')">回到路由课程</button>
  </div>

  <pre class="code">// 读取参数
const route = useRoute()
route.params.id          // 动态段 :id
route.query.page         // ?page=2
route.path               // /engineering/router/user/1
route.name               // 'user-detail'

// 编程式跳转
const router = useRouter()
router.push('/a')                 // 压入历史
router.replace('/a')              // 替换当前历史
router.back() / router.go(-1)     // 后退</pre>
</template>
