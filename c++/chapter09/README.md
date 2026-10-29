# 第九章 错误检查与处理

共 7 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 9.0 代码测试简介 | [`09.00-intro.cpp`](./09.00-intro.cpp) | 8KB |
| 9.1 代码覆盖率 | [`09.01-code-coverage.cpp`](./09.01-code-coverage.cpp) | 4KB |
| 9.2 常见的语义错误 | [`09.02-common-semantic-errors.cpp`](./09.02-common-semantic-errors.cpp) | 6KB |
| 9.3 检测和处理错误 | [`09.03-detect-handle-error.cpp`](./09.03-detect-handle-error.cpp) | 5KB |
| 9.4 std::cin和处理无效输入 | [`09.04-cin-error-handle.cpp`](./09.04-cin-error-handle.cpp) | 15KB |
| 9.5 断言 | [`09.05-assert.cpp`](./09.05-assert.cpp) | 6KB |
| 9.6 第9章总结 | [`09.06-summary.cpp`](./09.06-summary.cpp) | 4KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "09.00-intro.cpp" -o /tmp/a.out && /tmp/a.out
```
