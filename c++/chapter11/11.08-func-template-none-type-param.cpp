// ==========================================================================
// 11.8 非类型模板参数
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十一章 函数重载与函数模版
// 原文: https://www.studycpp.cn/basic/chapter11/func-template-none-type-param/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "11.08-func-template-none-type-param.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 非类型模板参数
//   · 定义我们自己的非类型模板参数
//   · 非类型模板参数有哪些用途？
//   · 非类型模板参数的隐式转换可选
//   · 使用auto (C++17)对非类型模板参数进行类型推导
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 在前面的课程中，我们讨论了如何创建使用模板类型参数的函数模板。模板类型参数
// 是作为模板参数传入的实际类型的占位符。
//
// 虽然模板类型参数是迄今为止使用的最常见的模板参数类型，但还有另一种模板参数
// 值得了解：非类型模板参数。
//

// ―――― 非类型模板参数 ――――

// 非类型模板参数是具有固定类型的模板参数，它是作为模板参数传入的constexpr值的
// 占位符。
//
// 非类型模板参数可以是以下任何类型：
// - 整型
// - 枚举类型
// - std::nullptr_t
// - 浮点类型（自C++20）
// - 指向对象的指针或引用
// - 指向函数的指针或引用
// - 指向成员函数的指针或引用
// - 字面值类类型（自C++20）
//

// ―――― 定义我们自己的非类型模板参数 ――――

// 下面是使用int非类型模板参数的函数的简单示例：

// [代码 1]
// #include <iostream>
//
// template <int N> // 声明一个非类型模板参数，类型是 int，名称是 N
// void print()
// {
//     std::cout << N << '\n'; // 在这里使用N
// }
//
// int main()
// {
//     print<5>(); // 5 是传入的非类型模板参数
//
//     return 0;
// }

// 此示例打印：
//
// 在第3行，我们有模板参数声明。在尖括号内，我们定义了一个名为N的非类型模板参
// 数，该参数将作为int类型值的占位符。在print()函数内，我们使用N的值。
//
// 在第11行，我们调用了函数print()，该函数使用int值5作为非类型模板参数。当编译
// 器看到此调用时，它将实例化如下所示的函数：

// [代码 2]
// template <>
// void print<5>()
// {
//     std::cout << 5 << '\n';
// }

// 在运行时，当从main()调用该函数时，它打印5。
//
// 然后程序结束。很简单，对吧？
//
// 与T通常用作第一个模板类型参数的名称很相似，N通常用作int非类型模板参数名称。
//

// ―――― 非类型模板参数有哪些用途？ ――――

// 从C++20开始，函数参数不能声明是constexpr的。对于普通函数、constexpr函数（必
// 须能够在运行时运行），甚至是consteval函数，这都是正确的。
//
// 假设我们有这样的函数：

// [代码 3]
// #include <cassert>
// #include <cmath> // for std::sqrt
// #include <iostream>
//
// double getSqrt(double d)
// {
//     assert(d >= 0.0 && "getSqrt(): d must be non-negative");
//
//     // 上面的assert在非debug环境可能不会编译进来
//     if (d >= 0)
//         return std::sqrt(d);
//
//     return 0.0;
// }
//
// int main()
// {
//     std::cout << getSqrt(5.0) << '\n';
//     std::cout << getSqrt(-5.0) << '\n';
//
//     return 0;
// }

// 对getSqrt(-5.0)的调用将在运行时assert失败，虽然这总比什么都没有要好。因为
// -5.0是一个字面值（并且隐式地是constexpr），如果我们可以使用static_assert在
// 编译时捕获这样的错误，会更好。然而，static_assert需要常量表达式，而函数参数
// 不能是constexpr…
//
// 然而，如果我们改为将函数参数更改为非类型模板参数，则可以完全按照我们的要求
// 执行：

// [代码 4]
// #include <cmath> // for std::sqrt
// #include <iostream>
//
// template <double D> // 需要 C++20 才能使用浮点非类型模板参数
// double getSqrt()
// {
//     static_assert(D >= 0.0, "getSqrt(): D must be non-negative");
//
//     if constexpr (D >= 0) // 忽略这里的 constexpr
//         return std::sqrt(D);
//
//     return 0.0;
// }
//
// int main()
// {
//     std::cout << getSqrt<5.0>() << '\n';
//     std::cout << getSqrt<-5.0>() << '\n';
//
//     return 0;
// }

// 此版本会编译失败。当编译器遇到getSqrt<-5.0>()时，它将实例化并调用如下所示的
// 函数：

// [代码 5]
// template <>
// double getSqrt<-5.0>()
// {
//     static_assert(-5.0 >= 0.0, "getSqrt(): D must be non-negative");
//
//     if constexpr (-5.0 >= 0) // 忽略这里的 constexpr
//         return std::sqrt(-5.0);
//
//     return 0.0;
// }

// static_assert条件为false，因此编译器将报错。
//
// 关键点
//
// 非类型模板参数主要在需要将constexpr值传递给函数（或类类型）时使用，以便它们
// 可以在需要常量表达式的上下文中使用。
//
// 类类型std::bitset使用非类型模板参数来定义要存储的位数，因为位数必须是
// constexpr值。
//
// 注
//
// 必须使用非类型模板参数来绕过函数参数不能是constexpr的限制，这并不理想。目前
// 有不少相关提案正在评估中，以帮助解决这种情况。希望在未来的C++语言标准中看到
// 更好的解决方案。
//

// ―――― 非类型模板参数的隐式转换可选 ――――

// 可以隐式转换某些非类型模板参数，以匹配不同类型的非类型模板形参。例如：

// [代码 6]
// #include <iostream>
//
// template <int N> // int 非类型模板参数
// void print()
// {
//     std::cout << N << '\n';
// }
//
// int main()
// {
//     print<5>();   // 无需转换
//     print<'c'>(); // 'c' 被转为 int, 打印 99
//
//     return 0;
// }

// 这将打印：
//
// 在上面的示例中，‘c’被转换为int，以匹配函数模板print的非类型模板参数，然后该
// 函数将值打印为int。
//
// 在此上下文中，仅允许某些类型的constexpr转换。最常见的允许转换类型包括：
// - 整型提升（例如从char到int）
// - 整型转换（例如，char到long或int到char）
// - 用户自定义的转换（例如，自定义的类到int）
// - 左值到右值的转换（例如，变量x转换为变量x的值）
//
// 请注意，与列表初始化所允许的隐式转换类型相比，该列表的权限更小。例如，可以
// 使用constexpr int列表初始化类型为double的变量，但constexpr int非类型模板参
// 数不会转换为double非类型模板参数。
//
// 与普通函数不同，用于将函数模板调用匹配到函数模板定义的算法并不复杂，并且根
// 据所需的转换类型，某些匹配不会优先于其他匹配。这意味着，如果为不同类型的非
// 类型模板参数重载函数模板，则很容易导致不明确的匹配：

// [代码 7]
// #include <iostream>
//
// template <int N> // int 非类型模板参数
// void print()
// {
//     std::cout << N << '\n';
// }
//
// template <char N> // char 非类型模板参数
// void print()
// {
//     std::cout << N << '\n';
// }
//
// int main()
// {
//     print<5>();   // 不明确的匹配 int N = 5 与 char N = 5
//     print<'c'>(); // 不明确的匹配 int N = 99 与 char N = 'c'
//
//     return 0;
// }

// 令人惊讶的是，这两个对print()的调用都会导致不明确的匹配。
//

// ―――― 使用auto (C++17)对非类型模板参数进行类型推导 ――――

// 从C++17开始，可以使用auto让编译器从实际调用中推导非类型模板参数的类型：

// [代码 8]
// #include <iostream>
//
// template <auto N> // 针对模板参数的类型，让编译器从调用自动推导
// void print()
// {
//     std::cout << N << '\n';
// }
//
// int main()
// {
//     print<5>();   // N 被推导为 int `5`
//     print<'c'>(); // N 被推导为 char `c`
//
//     return 0;
// }

// 这将编译并产生预期结果：

// [文本/输出]
// 5
// c

// 对于高级读者
//
// 您可能会想知道，为什么这个示例不会像前一节中的示例那样产生不明确的匹配。编
// 译器首先查找不明确的匹配，然后在不存在不明确匹配的情况下实例化函数模板。在
// 这种情况下，只有一个函数模板，因此没有可能的歧义。
//
// 在实例化上述示例的函数模板后，程序如下所示：

// [代码 9]
// #include <iostream>
//
// template <auto N>
// void print()
// {
//     std::cout << N << '\n';
// }
//
// template <>
// void print<5>() // 注意这是 print<5> 而不是 print<int>
// {
//     std::cout << 5 << '\n';
// }
//
// template <>
// void print<'c'>() // 注意这是 print<`c`> 而不是 print<char>
// {
//     std::cout << 'c' << '\n';
// }
//
// int main()
// {
//     print<5>();   // 调用 print<5>
//     print<'c'>(); // 调用 print<'c'>
//
//     return 0;
// }

//

// ―――― 习题 ――――


// ▼ 问题 1
// 编写一个带非类型模板形参的constexpr函数模板，返回以模板实参为参数的阶乘。下
// 面这个程序在运行到`factorial<-3>()`时应当编译失败。

// [代码 10]
// // 在这里定义你的 factorial() 函数模板
//
// int main()
// {
//     static_assert(factorial<0>() == 1);
//     static_assert(factorial<3>() == 6);
//     static_assert(factorial<5>() == 120);
//
//     factorial<-3>(); // 应当编译失败
//
//     return 0;
// }


// 【答案 · 查看答案】

// [代码 11]
// template <int N>
// constexpr int factorial()
// {
//     static_assert(N >= 0);
//
//     int product { 1 };
//     for (int i { 2 }; i <= N; ++i)
//         product *= i;
//
//     return product;
// }
//
// int main()
// {
//     static_assert(factorial<0>() == 1);
//     static_assert(factorial<3>() == 6);
//     static_assert(factorial<5>() == 120);
//
//     factorial<-3>(); // 应当编译失败
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

template <int N> // 声明一个非类型模板参数，类型是 int，名称是 N
void print()
{
    std::cout << N << '\n'; // 在这里使用N
}

int main()
{
    print<5>(); // 5 是传入的非类型模板参数

    return 0;
}
