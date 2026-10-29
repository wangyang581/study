# 第七章 作用域与编译链接

共 14 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 7.0 代码块 | [`07.00-code-block.cpp`](./07.00-code-block.cpp) | 3KB |
| 7.1 自定义命名空间和作用域解析操作符 | [`07.01-user-def-namespace.cpp`](./07.01-user-def-namespace.cpp) | 10KB |
| 7.2 局部变量 | [`07.02-local-var.cpp`](./07.02-local-var.cpp) | 5KB |
| 7.3 全局变量 | [`07.03-global-var.cpp`](./07.03-global-var.cpp) | 4KB |
| 7.4 变量名称遮挡（Variable shadowing） | [`07.04-name-shadow.cpp`](./07.04-name-shadow.cpp) | 4KB |
| 7.5 内部链接 | [`07.05-internal-link.cpp`](./07.05-internal-link.cpp) | 3KB |
| 7.6 外部链接和变量前向声明 | [`07.06-external-link.cpp`](./07.06-external-link.cpp) | 4KB |
| 7.7 为什么（非常量）全局变量是邪恶的 | [`07.07-why-non-const-global-var-evil.cpp`](./07.07-why-non-const-global-var-evil.cpp) | 6KB |
| 7.8 在多个文件中共享全局常量（使用内联变量） | [`07.08-share-const-global.cpp`](./07.08-share-const-global.cpp) | 5KB |
| 7.9 静态局部变量 | [`07.09-static-local-var.cpp`](./07.09-static-local-var.cpp) | 5KB |
| 7.10 作用域、存储期和链接摘要 | [`07.10-scope-duration-linkage.cpp`](./07.10-scope-duration-linkage.cpp) | 3KB |
| 7.11 using声明和using指令 | [`07.11-using.cpp`](./07.11-using.cpp) | 8KB |
| 7.12 未命名与内联的命名空间 | [`07.12-unname-namespace.cpp`](./07.12-unname-namespace.cpp) | 5KB |
| 7.13 第七章总结 | [`07.13-summary.cpp`](./07.13-summary.cpp) | 5KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "07.00-code-block.cpp" -o /tmp/a.out && /tmp/a.out
```
