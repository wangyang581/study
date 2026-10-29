# 第十六章 动态数组：std::vector

共 13 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 16.0 容器和数组简介 | [`16.00-intro-container-array.cpp`](./16.00-intro-container-array.cpp) | 6KB |
| 16.1 std::vector和列表构造函数简介 | [`16.01-intro-vector-list-init.cpp`](./16.01-intro-vector-list-init.cpp) | 10KB |
| 16.2 vector与无符号长度和下标问题 | [`16.02-vec-len.cpp`](./16.02-vec-len.cpp) | 10KB |
| 16.3 传递std::vector | [`16.03-vec-pass.cpp`](./16.03-vec-pass.cpp) | 6KB |
| 16.4 返回std::vector，移动语义简介 | [`16.04-vec-ret-move.cpp`](./16.04-vec-ret-move.cpp) | 5KB |
| 16.5 数组和循环 | [`16.05-vec-loop.cpp`](./16.05-vec-loop.cpp) | 14KB |
| 16.6 数组、循环和有符号下标 | [`16.06-vec-loop-sign-index.cpp`](./16.06-vec-loop-sign-index.cpp) | 11KB |
| 16.7 基于范围的for循环（range for / for each） | [`16.07-range-for.cpp`](./16.07-range-for.cpp) | 10KB |
| 16.8 使用枚举值来作为数组索引 | [`16.08-enum-as-index.cpp`](./16.08-enum-as-index.cpp) | 8KB |
| 16.9 std::vector大小调整和容量 | [`16.09-vec-size-capacity.cpp`](./16.09-vec-size-capacity.cpp) | 7KB |
| 16.10 std::vector和栈行为 | [`16.10-vec-stack.cpp`](./16.10-vec-stack.cpp) | 11KB |
| 16.11 std::vector<bool> | [`16.11-vec-bool.cpp`](./16.11-vec-bool.cpp) | 3KB |
| 16.12 第16章总结 | [`16.12-summary.cpp`](./16.12-summary.cpp) | 27KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "16.00-intro-container-array.cpp" -o /tmp/a.out && /tmp/a.out
```
