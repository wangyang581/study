// 应用的入口文件：创建 Vue 应用、挂载全局能力、渲染到页面。
import { createApp } from 'vue'
import { createPinia } from 'pinia'   // Pinia：Vue 官方推荐的状态管理库
import App from './App.vue'
import router from './router'
import './styles/main.css'

const app = createApp(App)

// app.use(...) 用来安装「插件」。
// 这里安装了路由（页面跳转）和 Pinia（跨组件共享状态）。
app.use(createPinia())
app.use(router)

// 把整个应用挂载到 index.html 里的 <div id="app"></div>
app.mount('#app')
