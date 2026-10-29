// ==========================================================================
// 6.7 第六章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第六章 运算符
// 原文: https://www.studycpp.cn/basic/chapter6/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "06.07-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 快速回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 快速回顾 ――――

// 如果有任何疑问或可能引起混淆的地方，请始终使用括号来消除运算符优先级的歧义。
//
// 算术运算符的工作方式都与它们在普通数学中的工作方式相同。余数（%）运算符返回
// 整数除法的余数。
//
// 递增和递减运算符可以用于轻松地递增或递减数字。尽可能避免这些运算符的后缀版
// 本。
//
// 注意副作用，特别是在函数参数的求值顺序方面。不要在同一条语句中多次使用带有
// 副作用的变量。
//
// 逗号运算符可以将多个语句压缩为一个。但单独编写语句通常更好。
//
// 条件运算符是if语句的简洁替代方式，但不要将其用作if语句的替代品。仅在需要使
// 用条件运算符的结果时才使用它。
//
// 关系运算符可以用于比较浮点数。注意浮点数的相等和不相等判断可能存在精度问题。
//
// 逻辑运算符允许我们编写复合条件语句。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 补全下面的程序：

// [代码 1]
// #include <iostream>
//
// // 在这里编写 getQuantityPhrase() 函数
//
// // 在这里编写 getApplesPluralized() 函数
//
// int main()
// {
//     constexpr int maryApples { 3 };
//     std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";
//
//     std::cout << "How many apples do you have? ";
//     int numApples{};
//     std::cin >> numApples;
//
//     std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";
//
//     return 0;
// }

// 输出示例：

// [文本/输出]
// Mary has a few apples.
// How many apples do you have? 1
// You have a single apple.

// `getQuantityPhrase()`应当接受一个表示某物数量的int形参，并返回下列描述词：
// - < 0 = 「negative」
// - 0 = 「no」
// - 1 = 「a single」
// - 2 = 「a couple of」
// - 3 = 「a few」
// - > 3 = 「many」
//
// `getApplesPluralized()`应当接受一个表示苹果数量的int形参，并返回：
// - 1 = 「apple」
// - 其他情况 = 「apples」
//
// 这个函数应当使用条件运算符。

// 【答案 · 显示提示】
// 以`std::string_view`的形式从函数中返回C样式字符串字面值是可以的。

// 【答案 · 查看答案】

// [代码 2]
// #include <iostream>
// #include <string_view>
//
// std::string_view getQuantityPhrase(int num)
// {
//     if (num < 0)
//         return "negative";
//     if (num == 0)
//         return "no";
//     if (num == 1)
//         return "a single";
//     if (num == 2)
//         return "a couple of";
//     if (num == 3)
//         return "a few";
//     return "many";
// }
//
// std::string_view getApplesPluralized(int num)
// {
//     return (num == 1) ? "apple" : "apples";
// }
//
// int main()
// {
//     constexpr int maryApples { 3 };
//     std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";
//
//     std::cout << "How many apples do you have? ";
//     int numApples{};
//     std::cin >> numApples;
//
//     std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <string_view>

std::string_view getQuantityPhrase(int num)
{
    if (num < 0)
        return "negative";
    if (num == 0)
        return "no";
    if (num == 1)
        return "a single";
    if (num == 2)
        return "a couple of";
    if (num == 3)
        return "a few";
    return "many";
}

std::string_view getApplesPluralized(int num)
{
    return (num == 1) ? "apple" : "apples";
}

int main()
{
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";

    return 0;
}
