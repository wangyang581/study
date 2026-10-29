# 第八章 控制流与错误处理

共 16 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 8.0 控制流简介 | [`08.00-control-flow-intro.cpp`](./08.00-control-flow-intro.cpp) | 2KB |
| 8.1 If语句与代码块 | [`08.01-if-block.cpp`](./08.01-if-block.cpp) | 5KB |
| 8.2 常见的if语句问题 | [`08.02-if-problem.cpp`](./08.02-if-problem.cpp) | 5KB |
| 8.3 Constexpr if语句 | [`08.03-constexpr-if.cpp`](./08.03-constexpr-if.cpp) | 2KB |
| 8.4 Switch语句基础 | [`08.04-switch.cpp`](./08.04-switch.cpp) | 6KB |
| 8.5 switch fallthrough机制与作用域 | [`08.05-switch-fallthrough-scope.cpp`](./08.05-switch-fallthrough-scope.cpp) | 6KB |
| 8.6 goto语句 | [`08.06-goto.cpp`](./08.06-goto.cpp) | 3KB |
| 8.7 循环和while语句简介 | [`08.07-loop.cpp`](./08.07-loop.cpp) | 9KB |
| 8.8 Do while语句 | [`08.08-do-while.cpp`](./08.08-do-while.cpp) | 4KB |
| 8.9 for语句 | [`08.09-for.cpp`](./08.09-for.cpp) | 9KB |
| 8.10 break与continue | [`08.10-break-continue.cpp`](./08.10-break-continue.cpp) | 6KB |
| 8.11 提前退出程序 | [`08.11-halt.cpp`](./08.11-halt.cpp) | 5KB |
| 8.12 随机数生成简介 | [`08.12-random-intro.cpp`](./08.12-random-intro.cpp) | 9KB |
| 8.13 使用Mersenne Twister生成随机数 | [`08.13-random-ms.cpp`](./08.13-random-ms.cpp) | 11KB |
| 8.14 全局随机数 | [`08.14-random-global.cpp`](./08.14-random-global.cpp) | 3KB |
| 8.15 第八章总结 | [`08.15-summary.cpp`](./08.15-summary.cpp) | 14KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "08.00-control-flow-intro.cpp" -o /tmp/a.out && /tmp/a.out
```
