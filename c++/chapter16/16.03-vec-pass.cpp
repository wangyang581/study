// ==========================================================================
// 16.3 传递std::vector
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十六章 动态数组：std::vector
// 原文: https://www.studycpp.cn/basic/chapter16/vec-pass/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "16.03-vec-pass.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 传递不同元素类型的std::vector
//   · 使用通用模板或缩写函数模板传递std::vector
//   · 断言数组长度
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 类型为std::vector的对象可以像其他对象一样传递给函数。这意味着，如果按值传递
// std::vector，就会生成一个昂贵的副本。因此，通常通过（const）引用传递
// std::vector，以避免这种复制。
//
// 对于std::vector，存储的元素类型是对象类型信息的一部分。因此，当使用
// std::vector作为函数参数时，必须显式指定元素类型：

// [代码 1]
// #include <iostream>
// #include <vector>
//
// void passByRef(const std::vector<int>& arr) // 这里必须显式指定 <int>
// {
//     std::cout << arr[0] << '\n';
// }
//
// int main()
// {
//     std::vector primes{ 2, 3, 5, 7, 11 };
//     passByRef(primes);
//
//     return 0;
// }

//

// ―――― 传递不同元素类型的std::vector ――――

// 由于passByRef()函数需要std::vector<int>，因此无法传递具有不同元素类型的
// vector：

// [代码 2]
// #include <iostream>
// #include <vector>
//
// void passByRef(const std::vector<int>& arr)
// {
//     std::cout << arr[0] << '\n';
// }
//
// int main()
// {
//     std::vector primes{ 2, 3, 5, 7, 11 };
//     passByRef(primes);  // ok: 这是 std::vector<int>
//
//     std::vector dbl{ 1.1, 2.2, 3.3 };
//     passByRef(dbl); // 编译失败: std::vector<double> 不能转换为 std::vector<int>
//
//     return 0;
// }

// 在C++17或更新版本中，或许您想尝试使用CTAD来解决此问题：

// [代码 3]
// #include <iostream>
// #include <vector>
//
// void passByRef(const std::vector& arr) // 编译失败: CTAD 不能被用来推导函数参数
// {
//     std::cout << arr[0] << '\n';
// }
//
// int main()
// {
//     std::vector primes{ 2, 3, 5, 7, 11 }; // okay: 使用 CTAD 推导为 std::vector<int>
//     passByRef(primes);
//
//     return 0;
// }

// 尽管在定义vector变量时，CTAD可以从初始值设定项中推断出元素类型，但CTAD（目
// 前）不能处理函数参数。
//
// 以前我们见过类似问题：只有参数类型不同的重载函数。这正是适合使用函数模板的
// 场景！可以创建一个以元素类型作为模版参数的函数模板，然后C++会使用该函数模板
// 来实例化具有实际类型的函数。
//
// 可以创建如下的函数模板：

// [代码 4]
// #include <iostream>
// #include <vector>
//
// template <typename T>
// void passByRef(const std::vector<T>& arr)
// {
//     std::cout << arr[0] << '\n';
// }
//
// int main()
// {
//     std::vector primes{ 2, 3, 5, 7, 11 };
//     passByRef(primes); // ok: 编译器会实例化 passByRef(const std::vector<int>&)
//
//     std::vector dbl{ 1.1, 2.2, 3.3 };
//     passByRef(dbl);    // ok: 编译器会实例化 passByRef(const std::vector<double>&)
//
//     return 0;
// }

// 在上面的示例中，创建了一个名为passByRef()的函数模板，该模板具有类型为"const
// std::vector<T>&“的参数。T在上一行的模板参数声明中定义：template <typename
// T>。T是一个标准类型模板参数，允许调用方指定元素类型。
//
// 因此，当从 main() 调用 passByRef(primes) 时（其中primes定义为
// std::vector<int>），编译器会实例化并调用void passByRef(const
// std::vector<int>& arr)。
//
// 当从 main() 调用 passByRef(dbl) 时（其中dbl定义为std::vector<double>），编
// 译器会实例化并调用void passByRef(const std::vector<double>& arr)。
//
// 因此，我们创建了一个函数模板，可以实例化出函数来处理任意元素类型和长度的
// std::vector参数！
//

// ―――― 使用通用模板或缩写函数模板传递std::vector ――――

// 我们还可以创建一个函数模板，该模板将接受任何类型的对象：

// [代码 5]
// #include <iostream>
// #include <vector>
//
// template <typename T>
// void passByRef(const T& arr) // 将会接收有任意 operator[] 方法的arr对象
// {
//     std::cout << arr[0] << '\n';
// }
//
// int main()
// {
//     std::vector primes{ 2, 3, 5, 7, 11 };
//     passByRef(primes); // ok: 编译器会实例化 passByRef(const std::vector<int>&)
//
//     std::vector dbl{ 1.1, 2.2, 3.3 };
//     passByRef(dbl);    // ok: 编译器会实例化 passByRef(const std::vector<double>&)
//
//     return 0;
// }

// 在C++20中，可以使用缩写的函数模板（通过auto参数）来执行相同的操作：

// [代码 6]
// #include <iostream>
// #include <vector>
//
// void passByRef(const auto& arr) // 缩写函数模板
// {
//     std::cout << arr[0] << '\n';
// }
//
// int main()
// {
//     std::vector primes{ 2, 3, 5, 7, 11 };
//     passByRef(primes); // ok: 编译器会实例化 passByRef(const std::vector<int>&)
//
//     std::vector dbl{ 1.1, 2.2, 3.3 };
//     passByRef(dbl);    // ok: 编译器会实例化 passByRef(const std::vector<double>&)
//
//     return 0;
// }

// 这两个模版都会接受任何能够通过编译的参数类型。在编写不只针对std::vector操作
// 的函数时，这是理想的。例如，上面的函数也可以用于std::array、std::string，甚
// 至用于我们尚未考虑过的其他类型。
//
// 该方法的潜在缺点是，如果函数收到一个能通过编译、但语义上没有意义的类型对象，
// 可能会导致错误。
//

// ―――― 断言数组长度 ――――

// 考虑以下模板函数，该函数类似于上面给出的函数：

// [代码 7]
// #include <iostream>
// #include <vector>
//
// template <typename T>
// void printElement3(const std::vector<T>& arr)
// {
//     std::cout << arr[3] << '\n';
// }
//
// int main()
// {
//     std::vector arr{ 9, 7, 5, 3, 1 };
//     printElement3(arr);
//
//     return 0;
// }

// 虽然printElement3(arr)在这种情况下工作良好，但该程序中有一个潜在错误，正等
// 着粗心的程序员触发。看到了吗？
//
// 上面的程序会打印索引为3的数组元素值。只要数组具有索引为3的有效元素，这就是
// 可以的。然而，编译器也会允许您传入一个索引3越界的数组。例如：

// [代码 8]
// #include <iostream>
// #include <vector>
//
// template <typename T>
// void printElement3(const std::vector<T>& arr)
// {
//     std::cout << arr[3] << '\n';
// }
//
// int main()
// {
//     std::vector arr{ 9, 7 }; // 只有2个元素的数组 (下标只有 0 和 1 有效)
//     printElement3(arr);
//
//     return 0;
// }

// 这会导致未定义的行为。
//
// 这里的一个选项是对arr.size()进行断言。这样在调试模式配置中运行时，它就能捕
// 获此类错误。由于 std::vector::size() 是一个非常量表达式函数，因此只能在运行
// 时断言。
//
// 最好的选择是避免对传入数组的长度做出假设。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 编写一个函数，接受两个形参：一个`std::vector`和一个下标。如果下标越界，就打
// 印一条错误信息；如果下标在范围内，就打印该元素的值。
//
// 下面这个示例程序应当能够通过编译：

// [代码 9]
// #include <iostream>
// #include <vector>
//
// // 在这里编写你的 printElement 函数
//
// int main()
// {
//     std::vector v1 { 0, 1, 2, 3, 4 };
//     printElement(v1, 2);
//     printElement(v1, 5);
//
//     std::vector v2 { 1.1, 2.2, 3.3 };
//     printElement(v2, 0);
//     printElement(v2, -1);
//
//     return 0;
// }

// 并产生如下结果：

// [文本/输出]
// The element has value 2
// Invalid index
// The element has value 1.1
// Invalid index


// 【答案 · 查看答案】

// [代码 10]
// #include <iostream>
// #include <vector>
//
// // 下标需要是 int 而不是 std::size_t，否则无法检测用户是否传入了负下标
// template <typename T>
// void printElement(const std::vector<T>& arr, int index)
// {
//     if (index < 0 || index >= static_cast<int>(arr.size())) // 在 C++20 中可以用 std::ssize(arr) 避免这次转换
//         std::cout << "Invalid index\n";
//     else
//         std::cout << "The element has value " << arr[static_cast<std::size_t>(index)] << '\n';
// }
//
// int main()
// {
//     std::vector v1 { 0, 1, 2, 3, 4 };
//     printElement(v1, 2);
//     printElement(v1, 5);
//
//     std::vector v2 { 1.1, 2.2, 3.3 };
//     printElement(v2, 0);
//     printElement(v2, -1);
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <vector>

void passByRef(const std::vector<int>& arr) // 这里必须显式指定 <int>
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes);

    return 0;
}
