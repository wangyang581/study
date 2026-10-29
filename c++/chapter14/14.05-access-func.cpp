// ==========================================================================
// 14.5 访问函数
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十四章 class介绍
// 原文: https://www.studycpp.cn/basic/chapter14/access-func/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "14.05-access-func.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 访问函数
//   · 访问函数命名
//   · Getter应通过值或常量左值引用返回
//   · 访问函数的问题
//   · 如果要为数据提供public访问函数，为什么要将其私有化？

// ==========================================================================
// 教程正文
// ==========================================================================

// 在上一课中，我们讨论了public和private访问级别。作为提醒，类通常会将其数据成
// 员设置为私有，而私有成员不能被公共代码直接访问。
//
// 考虑以下Date类：

// [代码 1]
// #include <iostream>
//
// class Date
// {
// private:
//     int m_year{ 2020 };
//     int m_month{ 10 };
//     int m_day{ 14 };
//
// public:
//     void print() const
//     {
//         std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
//     }
// };
//
// int main()
// {
//     Date d{};  // 创建一个 Date 对象
//     d.print(); // 打印 date
//
//     return 0;
// }

// 虽然该类提供了一个 print() 成员函数来打印Date，但这可能不足以满足用户的需要。
// 例如，如果date对象的用户想要获取年份，该怎么办？或者想把年份更改为不同的值
// 呢？他们将无法这样做，因为m_year是私有的（因此不能被公共代码直接访问）。
//
// 对于某些类，在类所处的上下文中，合理地获取或设置私有成员变量的值是有必要的。
//

// ―――― 访问函数 ――――

// 访问函数是一个普通的公共成员函数，其任务是检索或更改私有成员变量的值。
//
// 访问函数有两种：getter和setter。Getter（有时也称为访问器）是返回私有成员变
// 量值的public成员函数。Setter（有时也称为mutator）是设置私有成员变量值的
// public成员函数。
//
// Getter通常被设置为const，因此可以在常量和非常量对象上调用它们。Setter应该是
// 非const，因此它们需要修改数据成员。
//
// 为了便于说明，下面更新Date类，使其拥有一整套getter和setter：

// [代码 2]
// #include <iostream>
//
// class Date
// {
// private:
//     int m_year { 2020 };
//     int m_month { 10 };
//     int m_day { 14 };
//
// public:
//     void print()
//     {
//         std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
//     }
//
//     int getYear() const { return m_year; }        // getter for year
//     void setYear(int year) { m_year = year; }     // setter for year
//
//     int getMonth() const  { return m_month; }     // getter for month
//     void setMonth(int month) { m_month = month; } // setter for month
//
//     int getDay() const { return m_day; }          // getter for day
//     void setDay(int day) { m_day = day; }         // setter for day
// };
//
// int main()
// {
//     Date d{};
//     d.setYear(2021);
//     std::cout << "The year is: " << d.getYear() << '\n';
//
//     return 0;
// }

// 这将打印：

// [文本/输出]
// The year is: 2021

//

// ―――― 访问函数命名 ――――

// 访问函数没有通用命名约定。当然，有一些命名约定比其他约定更受欢迎。
// - 前缀为“get”和“set”：

// [代码 3]
//     int getDay() const { return m_day; }  // getter
//     void setDay(int day) { m_day = day; } // setter

// 使用“get”和“set”前缀的优点是，它清楚地表明，这些是访问函数（并且调用成本应
// 该较低）。
// - 没有前缀：

// [代码 4]
//     int day() const { return m_day; }  // getter
//     void day(int day) { m_day = day; } // setter

// 这种风格更简洁，并且对getter和setter使用相同的名称（依赖于函数重载来区分两
// 者）。C++标准库使用此约定。
//
// 无前缀约定的缺点是，像下面这样设置day成员的值并不特别明显：

// [代码 5]
// d.day(5); // 这看起来并不太像将 day 成员变量设置成 5?

// - 仅限“set”前缀：

// [代码 6]
//     int day() const { return m_day; }     // getter
//     void setDay(int day) { m_day = day; } // setter

// 选择上面哪一种是个人偏好的问题。然而，强烈建议对setter使用“set”前缀。Getter
// 可以使用“get”前缀，也可以不使用前缀。
//
// 关键点
//
// 在私有数据成员前面加上“m_”的最好原因之一是避免数据成员和getter具有相同的名
// 称（C++不支持这一点，尽管Java等其他语言支持）。
//
// 提示
//
// 在setter上使用“set”前缀，可以让“它们会改变对象状态”这一语义更加明显。
//

// ―――― Getter应通过值或常量左值引用返回 ――――

// Getter应提供对数据的“只读”访问。因此，最佳实践是通过值返回（如果制作成员副
// 本的成本不高），或通过常量左值引用返回（如果制作该成员副本的成本很高）。
//
// 由于通过引用返回数据成员是一个非常重要的主题，因此将在后面更详细地讨论该主
// 题。
//

// ―――― 访问函数的问题 ――――

// 关于应该使用或避免访问函数的情况，有相当多的讨论。许多开发人员会认为，访问
// 函数的使用违反了良好的类设计（这是一个很容易填满整本书的主题）。
//
// 现在，我们将推荐一种务实的方法。创建类时，请考虑以下事项：
// - 如果您的类没有不变量约束，并且需要大量访问函数，请考虑使用结构体（其数据
//   成员是公共的），提供对成员的直接访问。
// - 优先实现行为或操作，而不是访问函数。例如，不是实现setAlive(bool)这样的
//   setter，而是实现kill() 和 revive() 函数。
// - 仅在公共接口中确实需要合理获取或设置单个成员值的情况下，才提供访问函数。
//

// ―――― 如果要为数据提供public访问函数，为什么要将其私有化？ ――――

// 这是一个很好的问题。我们将在后续讲解数据隐藏（封装）的好处时进行说明。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Date
{
private:
    int m_year{ 2020 };
    int m_month{ 10 };
    int m_day{ 14 };

public:
    void print() const
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }
};

int main()
{
    Date d{};  // 创建一个 Date 对象
    d.print(); // 打印 date

    return 0;
}
