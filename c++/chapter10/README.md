# 第十章 类型转换，类型别名与类型推导

共 10 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 10.0 隐式类型转换 | [`10.00-implicit-type-convert.cpp`](./10.00-implicit-type-convert.cpp) | 3KB |
| 10.1 数值提升 | [`10.01-promotion.cpp`](./10.01-promotion.cpp) | 4KB |
| 10.2 数值转换 | [`10.02-num-convert.cpp`](./10.02-num-convert.cpp) | 6KB |
| 10.3 窄化转换、列表初始化和constexpr初始化 | [`10.03-narrow-convert-list-constexpr-init.cpp`](./10.03-narrow-convert-list-constexpr-init.cpp) | 5KB |
| 10.4 算术转换 | [`10.04-arithmetic-convert.cpp`](./10.04-arithmetic-convert.cpp) | 4KB |
| 10.5 显式类型转换和static_cast | [`10.05-explicit-type-convert-static-cast.cpp`](./10.05-explicit-type-convert-static-cast.cpp) | 4KB |
| 10.6 typedef和类型别名 | [`10.06-typedef.cpp`](./10.06-typedef.cpp) | 9KB |
| 10.7 使用auto关键字的对象类型自动推导 | [`10.07-auto-type-object.cpp`](./10.07-auto-type-object.cpp) | 5KB |
| 10.8 函数的类型推导 | [`10.08-auto-type-func.cpp`](./10.08-auto-type-func.cpp) | 3KB |
| 10.9 第10章总结 | [`10.09-summary.cpp`](./10.09-summary.cpp) | 4KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "10.00-implicit-type-convert.cpp" -o /tmp/a.out && /tmp/a.out
```
