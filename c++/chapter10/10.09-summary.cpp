// ==========================================================================
// 10.9 第10章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十章 类型转换，类型别名与类型推导
// 原文: https://www.studycpp.cn/basic/chapter10/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "10.09-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 章节回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 标准转换规则相当复杂 —— 如果您不理解每个细微差别，请不要担心，实际使用时再
// 详细研究即可。
//

// ―――― 章节回顾 ――――

// 将值从一种数据类型转换为另一种数据类型的过程称为类型转换。
//
// 只要需要一种数据类型，但却提供了不同的数据类型，就执行隐式类型转换（也称为
// 自动类型转换）。如果编译器能够找出如何在这两种类型之间进行转换，就可以编译
// 成功。如果它不知道如何操作，那么会出现编译错误。
//
// C++语言在其基本类型之间定义了许多内置转换（以及一些用于更高级类型的转换），
// 称为标准转换。这些包括数值提升、数值转换和算术转换。
//
// 数值提升是将某些较小的数值类型转换为某些较大的数值类型（通常为int或double），
// 以便CPU可以对与处理器自然数据大小匹配的数据进行操作。数值提升包括整型提升和
// 浮点提升。数值提升是保值的，这意味着不会损失数字或精度。并非所有扩大的转换
// 都是提升。
//
// 数值转换是基本类型之间不属于数值提升的类型转换。窄化转换可能会导致值或精度
// 丢失。
//
// 在C++中，某些二进制运算符要求其操作数具有相同的类型。如果提供了不同类型的操
// 作数，则使用一组称为常用算术转换的规则将其中一个或两个操作数隐式转换为匹配
// 类型。
//
// 当程序员通过强制转换显式请求转换时，会执行显式类型转换。C++支持5种类型的显
// 式转换：C样式转换、静态转换、常量转换、动态转换和重解释转换。通常，应避免C
// 样式转换、常量转换和重解释转换。static_cast用于将值从一种类型转换为另一种类
// 型的值，并且是迄今为止C++中使用最多的转换。
//
// typedef和类型别名允许程序员为数据类型创建别名。这些别名不是新类型，其行为与
// 被别名的类型相同。typedef和类型别名不提供任何类型安全，需要注意不要假设别名
// 与被别名的类型不同。
//
// auto关键字有许多用法。首先，auto可以用于进行类型推导，这会从变量的初始值设
// 定项中推导变量的类型。类型推导会删除常量和引用限定符，因此如果需要，请确保
// 将它们显式添加。
//
// auto也可以用作函数返回类型，以使编译器从函数的return语句推导函数的返回类型。
// 对于普通函数，应该避免这种情况。auto也可用作尾部返回语法的一部分。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 下列各种情况下会发生哪种类型的转换？可选答案有：不需要转换、数值提升、数值
// 转换、由于窄化转换而无法通过编译。假设`int`和`long`都是4字节。

// [代码 1]
// int main()
// {
//     int a { 5 }; // 1a
//     int b { 'a' }; // 1b
//     int c { 5.4 }; // 1c
//     int d { true }; // 1d
//     int e { static_cast<int>(5.4) }; // 1e
//
//     double f { 5.0f }; // 1f
//     double g { 5 }; // 1g
//
//     // 附加题部分
//     long h { 5 }; // 1h
//
//     float i { f }; // 1i（使用前面定义的变量 f）
//     float j { 5.0 }; // 1j
//
// }

// 1a)

// 【答案 · 查看答案】
// 不需要转换
//
// 1b)

// 【答案 · 查看答案】
// char「a」数值提升为int
//
// 1c)

// 【答案 · 查看答案】
// 由于窄化转换而无法通过编译
//
// 1d)

// 【答案 · 查看答案】
// bool值true数值提升为int
//
// 1e)

// 【答案 · 查看答案】
// double值5.4数值转换为int
//
// 1f)

// 【答案 · 查看答案】
// float数值提升为double
//
// 1g)

// 【答案 · 查看答案】
// int数值转换为double
//
// 1h)

// 【答案 · 查看答案】
// int数值转换为long（这个转换是平凡的，但仍然属于转换）
//
// 1i)

// 【答案 · 查看答案】
// 由于从double到float的窄化转换而无法通过编译
//
// 1j)

// 【答案 · 查看答案】
// double数值转换为float（这是允许的，因为5.0是constexpr，且落在float的取值范
// 围内）

// ▼ 问题 2
// 2a) 更新下面的程序，为角度值和弧度值使用类型别名：

// [代码 2]
// #include <iostream>
//
// namespace constants
// {
//     constexpr double pi { 3.14159 };
// }
//
// double convertToRadians(double degrees)
// {
//     return degrees * constants::pi / 180;
// }
//
// int main()
// {
//     std::cout << "Enter a number of degrees: ";
//     double degrees{};
//     std::cin >> degrees;
//
//     double radians { convertToRadians(degrees) };
//     std::cout << degrees << " degrees is " << radians << " radians.\n";
//
//     return 0;
// }


// 【答案 · 查看答案】

// [代码 3]
// #include <iostream>
//
// namespace constants
// {
//     constexpr double pi{ 3.14159 };
// }
//
// using Degrees = double;
// using Radians = double;
//
// Radians convertToRadians(Degrees degrees)
// {
//     return degrees * constants::pi / 180;
// }
//
// int main()
// {
//     std::cout << "Enter a number of degrees: ";
//     Degrees degrees{};
//     std::cin >> degrees;
//
//     Radians radians{ convertToRadians(degrees) };
//     std::cout << degrees << " degrees is " << radians << " radians.\n";
//
//     return 0;
// }

// 2b) 根据上一题答案中`degrees`和`radians`的定义，说明下面这条语句能否通过编
// 译，并解释原因：

// [代码 4]
// radians = degrees;


// 【答案 · 查看答案】
// 可以通过编译。`radians`的类型是`Radians`，它是`double`的类型别名；`degrees`
// 的类型是`Degrees`，它同样是`double`的类型别名。因此这不过是将一个`double`值
// 赋给一个`double`类型的变量而已。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

namespace constants
{
    constexpr double pi { 3.14159 };
}

double convertToRadians(double degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{
    std::cout << "Enter a number of degrees: ";
    double degrees{};
    std::cin >> degrees;

    double radians { convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";

    return 0;
}
