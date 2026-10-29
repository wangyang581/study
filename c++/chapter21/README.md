# 第二十一章 操作符重载

共 15 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 21.0 操作符重载简介 | [`21.00-op-overload-intro.cpp`](./21.00-op-overload-intro.cpp) | 4KB |
| 21.1 使用友元函数重载算术运算符 | [`21.01-friend-op-overload.cpp`](./21.01-friend-op-overload.cpp) | 14KB |
| 21.2 使用普通函数重载运算符 | [`21.02-normal-op-overload.cpp`](./21.02-normal-op-overload.cpp) | 4KB |
| 21.3 重载I/O运算符 | [`21.03-overload-io.cpp`](./21.03-overload-io.cpp) | 12KB |
| 21.4 使用成员函数重载运算符 | [`21.04-member-op-overload.cpp`](./21.04-member-op-overload.cpp) | 5KB |
| 21.5 重载一元运算符+、-和！ | [`21.05-unary-op-overload.cpp`](./21.05-unary-op-overload.cpp) | 4KB |
| 21.6 重载比较运算符 | [`21.06-compare-op-overload.cpp`](./21.06-compare-op-overload.cpp) | 13KB |
| 21.7 重载递增和递减运算符 | [`21.07-incr-decre-overload.cpp`](./21.07-incr-decre-overload.cpp) | 5KB |
| 21.8 重载下标运算符 | [`21.08-subscript-overload.cpp`](./21.08-subscript-overload.cpp) | 14KB |
| 21.9 重载括号运算符 | [`21.09-parenthesis-overload.cpp`](./21.09-parenthesis-overload.cpp) | 8KB |
| 21.10 重载类型转换 | [`21.10-type-cast-overload.cpp`](./21.10-type-cast-overload.cpp) | 6KB |
| 21.11 重载赋值运算符 | [`21.11-assign-op-overload.cpp`](./21.11-assign-op-overload.cpp) | 9KB |
| 21.12 浅拷贝与深拷贝 | [`21.12-shadow-deep-copy.cpp`](./21.12-shadow-deep-copy.cpp) | 7KB |
| 21.13 重载运算符和函数模板 | [`21.13-op-overload-template.cpp`](./21.13-op-overload-template.cpp) | 8KB |
| 21.14 第21章总结 | [`21.14-summary.cpp`](./21.14-summary.cpp) | 22KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "21.00-op-overload-intro.cpp" -o /tmp/a.out && /tmp/a.out
```
