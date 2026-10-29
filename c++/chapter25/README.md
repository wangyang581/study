# 第二十五章 虚函数

共 12 节。

| 节 | 文件 | 大小 |
| --- | --- | --- |
| 25.0 指向派生对象的基类指针和引用 | [`25.00-base-pointer-ref-to-derived.cpp`](./25.00-base-pointer-ref-to-derived.cpp) | 12KB |
| 25.1 虚函数和多态 | [`25.01-virtual-func.cpp`](./25.01-virtual-func.cpp) | 13KB |
| 25.2 override和final说明符 | [`25.02-override-final.cpp`](./25.02-override-final.cpp) | 9KB |
| 25.3 虚析构函数、虚赋值函数以及虚函数重写 | [`25.03-virtual-destructor-assign-override.cpp`](./25.03-virtual-destructor-assign-override.cpp) | 5KB |
| 25.4 静态绑定和动态绑定 | [`25.04-early-bind-late-bind.cpp`](./25.04-early-bind-late-bind.cpp) | 6KB |
| 25.5 虚函数表 | [`25.05-virtual-table.cpp`](./25.05-virtual-table.cpp) | 6KB |
| 25.6 纯虚函数、抽象基类和接口类 | [`25.06-abstract-class.cpp`](./25.06-abstract-class.cpp) | 11KB |
| 25.7 虚基类 | [`25.07-virtual-base-class.cpp`](./25.07-virtual-base-class.cpp) | 5KB |
| 25.8 对象切片（Object slicing） | [`25.08-object-slice.cpp`](./25.08-object-slice.cpp) | 8KB |
| 25.9 dynamic_cast | [`25.09-dynamic-cast.cpp`](./25.09-dynamic-cast.cpp) | 8KB |
| 25.10 使用运算符<<打印继承的类 | [`25.10-print-inherit-class.cpp`](./25.10-print-inherit-class.cpp) | 7KB |
| 25.11 第25章总结 | [`25.11-summary.cpp`](./25.11-summary.cpp) | 14KB |

```bash
# 编译并运行某一节 (以第 1 节为例)
g++ -std=c++20 -Wall -Wextra "25.00-base-pointer-ref-to-derived.cpp" -o /tmp/a.out && /tmp/a.out
```
