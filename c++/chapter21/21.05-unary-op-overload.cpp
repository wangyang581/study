// ==========================================================================
// 21.5 重载一元运算符+、-和！
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十一章 操作符重载
// 原文: https://www.studycpp.cn/basic/chapter21/unary-op-overload/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "21.05-unary-op-overload.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 与迄今为止看到的运算符不同，正号（+）、负号（-）和逻辑not（！）运算符都是一
// 元运算符，这意味着它们只作用于一个操作数。因为它们只作用于应用它们的对象，
// 所以一元运算符重载通常实现为成员函数。这三个运算符的实现方式都相同。
//
// 让我们看看如何在前面示例使用的Cents类上实现运算符：

// [代码 1]
// #include <iostream>
//
// class Cents
// {
// private:
//     int m_cents {};
//
// public:
//     Cents(int cents): m_cents{cents} {}
//
//     // 重载 -Cents 作为成员函数
//     Cents operator-() const;
//
//     int getCents() const { return m_cents; }
// };
//
// // 注: 这个函数是成员函数!
// Cents Cents::operator-() const
// {
//     return -m_cents; // 因为返回类型是Cents，这里有个int到Cents的隐式转换
// }
//
// int main()
// {
//     const Cents nickle{ 5 };
//     std::cout << "A nickle of debt is worth " << (-nickle).getCents() << " cents\n";
//
//     return 0;
// }

// 这应该很直接。我们的重载负号运算符（-）是一个作为成员函数实现的一元运算符，
// 因此它不带参数（它作用于*this对象）。它返回一个Cents对象，该对象表示原始
// Cents值的负数。因为operator-不会修改Cents对象，所以我们可以（并且应该）将其
// 设置为const函数（这样就可以在const Cents对象上调用它）。
//
// 注意，负号运算符和减法运算符不会混淆，因为它们的参数数量不同。
//
// 这是另一个例子。“operator！”是逻辑求反运算符。如果表达式的计算结果为“true”，
// 则“operator！”会返回false，反之亦然。我们通常将它应用于布尔变量，以测试它们
// 是否为真：

// [代码 2]
// if (!isHappy)
//     std::cout << "I am not happy!\n";
// else
//     std::cout << "I am so happy!\n";

// 对于整数，0会计算为false，其他任何值都会计算为true。因此，当“operator！”应
// 用于整数时，如果整数值为0，则返回true，否则返回false。
//
// 扩展这个概念，我们可以说：如果对象的状态表示“false”、“zero”或默认初始化状态，
// 那么“operator！”应计算为true。
//
// 下面的示例展示了如何为用户定义的Point类重载“operator！”：

// [代码 3]
// #include <iostream>
//
// class Point
// {
// private:
//     double m_x {};
//     double m_y {};
//     double m_z {};
//
// public:
//     Point(double x=0.0, double y=0.0, double z=0.0):
//         m_x{x}, m_y{y}, m_z{z}
//     {
//     }
//
//     // 转换成一个负的对应的量
//     Point operator- () const;
//
//     // 如果为原点，则返回true
//     bool operator! () const;
//
//     double getX() const { return m_x; }
//     double getY() const { return m_y; }
//     double getZ() const { return m_z; }
// };
//
// // 转换成一个负的对应的量
// Point Point::operator- () const
// {
//     return { -m_x, -m_y, -m_z };
// }
//
// // 如果为原点，则返回true
// bool Point::operator! () const
// {
//     return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0);
// }
//
// int main()
// {
//     Point point{}; // 默认构造函数会初始化为 (0.0, 0.0, 0.0)
//
//     if (!point)
//         std::cout << "point is set at the origin.\n";
//     else
//         std::cout << "point is not set at the origin.\n";
//
//     return 0;
// }

// 对于Point重载的“operator！”，如果对应对象位于坐标（0.0、0.0、0.0），就返回
// 布尔值“true”。因此，上述代码会生成如下结果：

// [文本/输出]
// point is set at the origin.

//

// ―――― 习题 ――――


// ▼ 问题 1
// 为Point类实现重载的一元`operator+`。一元`operator+`只是返回它的操作数（它不
// 会把负数变成正数）。

// 【答案 · 查看答案】
// 最直观的解法是：

// [代码 4]
// Point Point::operator+ () const
// {
//     return { m_x, m_y, m_z };
// }

// 但由于我们返回的Point与正在操作的那个对象完全相同，下面这种写法也可以：

// [代码 5]
// Point Point::operator+ () const
// {
//     return *this;
// }

// 注意，这里按值返回了副本，而不是返回const引用。这是因为该函数的使用者多半会
// 期望返回的对象是可以修改的。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Cents
{
private:
    int m_cents {};

public:
    Cents(int cents): m_cents{cents} {}

    // 重载 -Cents 作为成员函数
    Cents operator-() const;

    int getCents() const { return m_cents; }
};

// 注: 这个函数是成员函数!
Cents Cents::operator-() const
{
    return -m_cents; // 因为返回类型是Cents，这里有个int到Cents的隐式转换
}

int main()
{
    const Cents nickle{ 5 };
    std::cout << "A nickle of debt is worth " << (-nickle).getCents() << " cents\n";

    return 0;
}
