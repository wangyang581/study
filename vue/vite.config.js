import { fileURLToPath, URL } from 'node:url'
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

// Vite 是构建工具（开发服务器 + 打包器）。
// 这里注册 Vue 插件，并配置一个 @ 别名指向 src 目录，
// 这样 import 时可以用 '@/components/Xxx.vue'，不用写一长串 '../'。
export default defineConfig({
  plugins: [vue()],
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url)),
    },
  },
  server: {
    port: 5173,
    open: true,
  },
})
