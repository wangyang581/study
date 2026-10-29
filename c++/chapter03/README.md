# 第三章 程序调试

共 11 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 3.0 语法和语义错误 | [`03.00-syntax-semantic-errors.cpp`](./03.00-syntax-semantic-errors.cpp) | 2KB |
| 3.1 程序调试过程 | [`03.01-debug-process.cpp`](./03.01-debug-process.cpp) | 2KB |
| 3.2 调试策略 | [`03.02-debug-strategy.cpp`](./03.02-debug-strategy.cpp) | 3KB |
| 3.3 基本调试策略 | [`03.03-debug-tatics.cpp`](./03.03-debug-tatics.cpp) | 11KB |
| 3.4 更多调试策略 | [`03.04-more-tatics.cpp`](./03.04-more-tatics.cpp) | 4KB |
| 3.5 使用集成调试器：单步执行 | [`03.05-step.cpp`](./03.05-step.cpp) | 7KB |
| 3.6 断点 | [`03.06-breakpoint.cpp`](./03.06-breakpoint.cpp) | 3KB |
| 3.7 监视变量 | [`03.07-watch-var.cpp`](./03.07-watch-var.cpp) | 4KB |
| 3.8 调用堆栈 | [`03.08-call-stack.cpp`](./03.08-call-stack.cpp) | 2KB |
| 3.9 在问题变成问题前进行避免 | [`03.09-avoid-problem.cpp`](./03.09-avoid-problem.cpp) | 4KB |
| 3.10 第3章总结 | [`03.10-summary.cpp`](./03.10-summary.cpp) | 5KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "03.00-syntax-semantic-errors.cpp" -o /tmp/a.out && /tmp/a.out
```
