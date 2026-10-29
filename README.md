# study

个人学习仓库，按主题分目录，每个目录都是一个可独立运行的练习工程。

## 目录

| 目录 | 主题 | 说明 |
| --- | --- | --- |
| [`vue/`](./vue) | **Vue 3 前端开发** | 17 节渐进式课程 + 10 篇配套文档，从模板语法到路由/状态管理/综合实战 Todo |
| [`c++/`](./c++) | **C++ 系统学习** | 29 章 313 节，按 [C++学习网](https://www.studycpp.cn/) 整理，每节一个带教程正文注释、可直接运行的单文件程序 |
| [`dsh/`](./dsh) | **DeepSeek Harness（dsh）Agent 开发** | 10 课教程 + 可运行插件/组合包示例 + 社区插件指南 |

## 快速开始

```bash
cd vue
npm install
npm run dev      # http://localhost:5173
```

详见 [`vue/README.md`](./vue/README.md)。

## C++ 教程

```bash
cd c++
./tools/run.sh chapter04/04.09-if.cpp   # 编译并运行某一节
```

从 [`c++/README.md`](./c++/README.md) 开始：章节导航 + 313 节学习进度清单。

## DeepSeek Harness 教程

```sh
# 直接体验
npx @deepseek-ai/dsh web      # http://127.0.0.1:3080
```

从 [`dsh/README.md`](./dsh/README.md) 开始：项目概览 → 安装运行 → 配置模型 → 插件开发 → 社区插件。
