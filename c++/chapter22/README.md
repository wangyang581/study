# 第二十二章 移动语义与智能指针

共 8 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 22.0 智能指针和移动语义简介 | [`22.00-move-smart-pointer-intro.cpp`](./22.00-move-smart-pointer-intro.cpp) | 10KB |
| 22.1 右值引用 | [`22.01-r-value-ref.cpp`](./22.01-r-value-ref.cpp) | 5KB |
| 22.2 移动构造函数和移动赋值函数 | [`22.02-move-construct-assign.cpp`](./22.02-move-construct-assign.cpp) | 18KB |
| 22.3 std::move | [`22.03-std-move.cpp`](./22.03-std-move.cpp) | 5KB |
| 22.4 std::unique_ptr | [`22.04-unique-ptr.cpp`](./22.04-unique-ptr.cpp) | 12KB |
| 22.5 std::shared_ptr | [`22.05-shared-ptr.cpp`](./22.05-shared-ptr.cpp) | 6KB |
| 22.6 std::shared_ptr的循环依赖性问题和std::weak_ptr | [`22.06-circle-ref.cpp`](./22.06-circle-ref.cpp) | 11KB |
| 22.7 第22章总结 | [`22.07-summary.cpp`](./22.07-summary.cpp) | 3KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "22.00-move-smart-pointer-intro.cpp" -o /tmp/a.out && /tmp/a.out
```
