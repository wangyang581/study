# 第二十七章 异常

共 11 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 27.0 为什么需要异常机制 | [`27.00-exception-need.cpp`](./27.00-exception-need.cpp) | 4KB |
| 27.1 基本异常处理 | [`27.01-exception-basic.cpp`](./27.01-exception-basic.cpp) | 7KB |
| 27.2 异常、函数和堆栈展开 | [`27.02-exception-func-stack-unwind.cpp`](./27.02-exception-func-stack-unwind.cpp) | 7KB |
| 27.3 未捕获的异常和捕获所有异常 | [`27.03-uncatch-catchall.cpp`](./27.03-uncatch-catchall.cpp) | 5KB |
| 27.4 异常、类和继承 | [`27.04-exception-and-class.cpp`](./27.04-exception-and-class.cpp) | 14KB |
| 27.5 重新抛出异常 | [`27.05-exception-rethrow.cpp`](./27.05-exception-rethrow.cpp) | 6KB |
| 27.6 函数try块 | [`27.06-function-try.cpp`](./27.06-function-try.cpp) | 4KB |
| 27.7 异常的风险和缺点 | [`27.07-exception-downside.cpp`](./27.07-exception-downside.cpp) | 4KB |
| 27.8 异常规格和noexcept | [`27.08-exception-spec-noexcept.cpp`](./27.08-exception-spec-noexcept.cpp) | 8KB |
| 27.9 std::move_if_noexcept | [`27.09-move-if-noexcept.cpp`](./27.09-move-if-noexcept.cpp) | 8KB |
| 27.10 第27章总结 | [`27.10-summary.cpp`](./27.10-summary.cpp) | 4KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "27.00-exception-need.cpp" -o /tmp/a.out && /tmp/a.out
```
