# 第十二章 复合类型：引用与指针

共 15 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 12.0 复合数据类型简介 | [`12.00-compound-data-intro.cpp`](./12.00-compound-data-intro.cpp) | 3KB |
| 12.1 值类别（左值 lvalue 和右值 rvalue） | [`12.01-value-category.cpp`](./12.01-value-category.cpp) | 6KB |
| 12.2 左值引用 | [`12.02-lvalue-ref.cpp`](./12.02-lvalue-ref.cpp) | 6KB |
| 12.3 const的左值引用 | [`12.03-const-lvalue-ref.cpp`](./12.03-const-lvalue-ref.cpp) | 4KB |
| 12.4 通过左值引用传递函数参数 | [`12.04-lvalue-ref-func-arg.cpp`](./12.04-lvalue-ref-func-arg.cpp) | 4KB |
| 12.5 通过常量左值引用传递函数参数 | [`12.05-const-lvalue-ref-func-arg.cpp`](./12.05-const-lvalue-ref-func-arg.cpp) | 7KB |
| 12.6 指针简介 | [`12.06-pointer-intro.cpp`](./12.06-pointer-intro.cpp) | 11KB |
| 12.7 空指针 | [`12.07-null-ptr.cpp`](./12.07-null-ptr.cpp) | 7KB |
| 12.8 指针与常量 | [`12.08-const-ptr.cpp`](./12.08-const-ptr.cpp) | 4KB |
| 12.9 通过指针传递函数参数 | [`12.09-pointer-func-arg.cpp`](./12.09-pointer-func-arg.cpp) | 7KB |
| 12.10 通过指针传递函数参数（第2部分） | [`12.10-pointer-func-arg-two.cpp`](./12.10-pointer-func-arg-two.cpp) | 6KB |
| 12.11 引用或指针作为函数返回值 | [`12.11-ret-ref-pointer.cpp`](./12.11-ret-ref-pointer.cpp) | 9KB |
| 12.12 输入和输出参数 | [`12.12-io-args.cpp`](./12.12-io-args.cpp) | 6KB |
| 12.13 指针、引用和常量的类型自动推导 | [`12.13-auto-type-deduct-ptr-ref-const.cpp`](./12.13-auto-type-deduct-ptr-ref-const.cpp) | 8KB |
| 12.14 第12章总结 | [`12.14-summary.cpp`](./12.14-summary.cpp) | 5KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "12.00-compound-data-intro.cpp" -o /tmp/a.out && /tmp/a.out
```
