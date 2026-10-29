# 第十七章 固定长度数组：std::array与c样式数组

共 14 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 17.0 std::array简介 | [`17.00-arr-intro.cpp`](./17.00-arr-intro.cpp) | 8KB |
| 17.1 std::array长度和索引 | [`17.01-arr-len-index.cpp`](./17.01-arr-len-index.cpp) | 5KB |
| 17.2 std::array作为函数参数或返回值 | [`17.02-arr-pass-ret.cpp`](./17.02-arr-pass-ret.cpp) | 11KB |
| 17.3 std::array与类类型元素 | [`17.03-arr-of-class.cpp`](./17.03-arr-of-class.cpp) | 9KB |
| 17.4 通过std::reference_wrapper创建引用的数组 | [`17.04-arr-ref.cpp`](./17.04-arr-ref.cpp) | 3KB |
| 17.5 std::array和枚举 | [`17.05-arr-enum.cpp`](./17.05-arr-enum.cpp) | 12KB |
| 17.6 C样式数组简介 | [`17.06-c-arr.cpp`](./17.06-c-arr.cpp) | 9KB |
| 17.7 C样式数组退化 | [`17.07-c-arr-decay.cpp`](./17.07-c-arr-decay.cpp) | 11KB |
| 17.8 指针运算和下标 | [`17.08-pointer-arithmetic.cpp`](./17.08-pointer-arithmetic.cpp) | 8KB |
| 17.9 C样式字符串 | [`17.09-c-str.cpp`](./17.09-c-str.cpp) | 7KB |
| 17.10 常量C样式字符串 | [`17.10-c-const-str.cpp`](./17.10-c-const-str.cpp) | 3KB |
| 17.11 多维C样式数组 | [`17.11-c-multi-arr.cpp`](./17.11-c-multi-arr.cpp) | 7KB |
| 17.12 多维std::array | [`17.12-std-multi-arr.cpp`](./17.12-std-multi-arr.cpp) | 11KB |
| 17.13 第17章总结 | [`17.13-summary.cpp`](./17.13-summary.cpp) | 42KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "17.00-arr-intro.cpp" -o /tmp/a.out && /tmp/a.out
```
