// ==========================================================================
// 14.16 第14章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十四章 class介绍
// 原文: https://www.studycpp.cn/basic/chapter14/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "14.16-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 章节回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 在本章中，我们探索了C++的核心——类！这是教程系列中最重要的一章，它为后面的大
// 部分内容奠定了基础。
//

// ―――― 章节回顾 ――――

// 在面向过程编程中，重点是创建实现程序逻辑的“过程”（在C++中称为函数）。将数据
// 对象传递给这些函数，这些函数对数据执行操作，然后可能返回一个结果供调用方使
// 用。
//
// 在面向对象编程（通常缩写为OOP）中，重点是创建包含属性和一组定义良好行为的程
// 序定义数据类型。
//
// 类不变量是一种必须在对象整个生存期内为真的条件，以便对象保持有效状态。违反
// 类不变量的对象被称为处于无效状态，并且进一步使用该对象可能会导致意外或未定
// 义行为。
//
// 类是程序定义的复合类型，它捆绑了数据和处理该数据的函数。
//
// 属于类类型的函数称为成员函数。调用成员函数的对象通常称为隐式对象。不是成员
// 函数的函数称为非成员函数，以将它们与成员函数区分开来。如果类类型没有数据成
// 员，则更推荐使用命名空间。
//
// const成员函数是一个成员函数，它保证不会修改对象或调用任何非const成员函数（
// 因为它们可能会修改对象）。不（并且永远不会）修改对象状态的成员函数应成为
// const，以便可以在非常量对象和常量对象上调用它。
//
// 类类型的每个成员都有一个称为访问级别的属性，该属性确定谁可以访问该成员。访
// 问级别系统有时非正式地称为访问控制。访问级别是基于每个类而不是基于每个对象
// 定义的。
//
// public成员是类类型的成员，对如何访问它们没有任何限制。任何人都可以访问公共
// 成员。这包括同一类的其他成员。公共成员也可以被公共代码访问，这指的是存在于
// 给定类类型成员之外的代码，包括非成员函数以及其他类类型的成员。
//
// 默认情况下，结构体的所有成员都是公共成员。
//
// 私有成员是只能由同一类的其他成员访问的类类型的成员。
//
// 默认情况下，类的成员是私有的。具有私有成员的类不再是聚合，因此不能再使用聚
// 合初始化。考虑以“m_”前缀开头命名私有成员，以帮助将它们与局部变量、函数参数
// 和成员函数的名称区分开来。
//
// 可以通过使用访问说明符来显式设置成员的访问级别。结构体通常应避免使用访问说
// 明符，以便所有成员都默认为public。
//
// 访问函数是一个普通的public成员函数，其任务是检索或更改私有成员变量的值。访
// 问函数有两种风格：getter和setter。Getter（有时也称为访问器）是返回私有成员
// 变量值的公共成员函数。Setter（有时也称为mutator）是设置私有成员变量值的公共
// 成员函数。
//
// 类类型的接口定义了类类型的用户将如何与类类型的对象交互。由于只能从类类型外
// 部访问公共成员，因此类类型的公共成员形成其接口。由公共成员组成的接口有时称
// 为公共接口。
//
// 类类型的实现由实际使类按预期行为运行的代码组成。这包括存储数据的成员变量，
// 以及包含程序逻辑并操作成员变量的成员函数体。
//
// 在编程中，数据隐藏（也称为信息隐藏或数据抽象）是一种通过对用户隐藏程序定义
// 的数据类型的实现来强制实现接口和实现分离的技术。
//
// 术语封装有时也用于指代数据隐藏。然而，该术语也用于指将数据和功能捆绑在一起
// （不考虑访问控制）。
//
// 定义类时，最好先声明公共成员，然后声明私有成员。这突出了公共接口，并淡化了
// 实现细节。
//
// 构造函数是一个特殊的成员函数，用于初始化类类型对象。必须找到匹配的构造函数
// 才能创建非聚合类类型对象。
//
// 成员初始值设定项列表允许您从构造函数中初始化成员变量。应按在类中定义成员变
// 量的顺序列出它们。与在构造函数主体中分配值相比，优先使用成员初始值设定项列
// 表来初始化成员。
//
// 不带参数（或具有所有默认参数）的构造函数称为默认构造函数。如果用户没有提供
// 初始化值，则使用默认构造函数。如果非聚合类类型对象没有用户声明的构造函数，
// 编译器将生成默认构造函数（以便类可以被值初始化或默认初始化）。此构造函数称
// 为隐式默认构造函数。
//
// 允许构造函数将初始化委托给同一类类型的另一个构造函数。这个过程有时被称为构
// 造函数委托，这样的构造函数被称为委托构造函数。构造函数可以委托或初始化，但
// 不能同时委托和初始化。
//
// 临时对象（有时称为匿名对象或未命名对象）是没有名称且仅在单个表达式期间存在
// 的对象。
//
// 拷贝构造函数是用于使用相同类型的现有对象初始化对象的构造函数。如果不为类提
// 供拷贝构造函数，C++将为您创建一个执行成员级初始化的public隐式拷贝构造函数。
//
// 仿佛规则说，编译器可以随意修改程序，以产生更优化的代码，只要这些修改不影响
// 程序的“可观察行为”。“仿佛”规则的一个例外是拷贝省略。拷贝省略是一种编译器优
// 化技术，允许编译器删除不必要的对象复制。当编译器优化掉对拷贝构造函数的调用
// 时，可以说构造函数已被省略。
//
// 编写的将值转换为程序定义类型或从程序定义类型转换为值的函数称为用户定义转换。
// 可以用于执行隐式转换的构造函数称为转换构造函数。默认情况下，所有构造函数都
// 是转换构造函数。
//
// 可以使用explicit关键字来告诉编译器，构造函数不应用作转换构造函数。这样的构
// 造函数不能用于执行拷贝初始化或拷贝列表初始化，也不能用于执行隐式转换。
//
// 默认情况下，使任何接受单个参数的构造函数explicit。如果类型之间的隐式转换在
// 语义上是等效的，并且是性能更好的转换（例如从std::string到std::string_view的
// 转换），则可以考虑使构造函数成为非explicit的。不要使拷贝或移动构造函数
// explicit，因为它们不执行转换。
//

// ―――― 习题 ――――

// 作者提示
//
// 原先作为本课一部分的21点（blackjack）习题已移至「17.13 第17章总结」。

// ▼ 问题 1
// a) 编写一个名为`Point2d`的类。`Point2d`应当包含两个`double`类型的成员变量：
// `m_x`和`m_y`，两者都默认初始化为`0.0`。
//
// 提供一个构造函数和一个`print()`函数。
//
// 下面这个程序应当能够运行：

// [代码 1]
// #include <iostream>
//
// int main()
// {
//     Point2d first{};
//     Point2d second{ 3.0, 4.0 };
//
//     // Point2d third{ 4.0 }; // 取消注释后应当报错
//
//     first.print();
//     second.print();
//
//     return 0;
// }

// 它应当打印：

// [文本/输出]
// Point2d(0, 0)
// Point2d(3, 4)


// 【答案 · 查看答案】

// [代码 2]
// #include <iostream>
//
// class Point2d
// {
// private:
// 	double m_x{ 0.0 };
// 	double m_y{ 0.0 };
//
// public:
// 	Point2d() = default;
//
// 	Point2d(double x, double y)
// 		: m_x{ x }, m_y{ y }
// 	{
// 	}
//
// 	void print() const
// 	{
// 		std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
// 	}
// };
//
// int main()
// {
//     Point2d first{};
//     Point2d second{ 3.0, 4.0 };
//
//     // Point2d third{ 4.0 }; // 取消注释后应当报错
//
//     first.print();
//     second.print();
//
//     return 0;
// }

// b) 现在添加一个名为`distanceTo()`的成员函数，它接受另一个`Point2d`作为形参，
// 并计算两点之间的距离。给定两个点(x1, y1)和(x2, y2)，它们之间的距离可以用公
// 式`std::sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2))`计算。`std::sqrt`函
// 数位于`cmath`头文件中。
//
// 下面这个程序应当能够运行：

// [代码 3]
// #include <cmath>
// #include <iostream>
//
// int main()
// {
//     Point2d first{};
//     Point2d second{ 3.0, 4.0 };
//
//     first.print();
//     second.print();
//
//     std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';
//
//     return 0;
// }

// 它应当打印：

// [文本/输出]
// Point2d(0, 0)
// Point2d(3, 4)
// Distance between two points: 5


// 【答案 · 查看答案】

// [代码 4]
// #include <cmath>
// #include <iostream>
//
// class Point2d
// {
// private:
// 	double m_x{ 0.0 };
// 	double m_y{ 0.0 };
//
// public:
// 	Point2d() = default;
//
// 	Point2d(double x, double y)
// 		: m_x{ x }, m_y{ y }
// 	{
// 	}
//
// 	void print() const
// 	{
// 		std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
// 	}
//
// 	double distanceTo(const Point2d& other) const
// 	{
// 		return std::sqrt(
//             (m_x - other.m_x)*(m_x - other.m_x) +
//             (m_y - other.m_y)*(m_y - other.m_y)
//             );
// 	}
// };
//
// int main()
// {
//     Point2d first{};
//     Point2d second{ 3.0, 4.0 };
//
//     first.print();
//     second.print();
//
//     std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';
//
//     return 0;
// }


// ▼ 问题 2
// 在「13.7 结构体作为函数的输入与输出」中，我们编写了一个使用`Fraction`结构体
// 的短程序。参考解法如下：

// [代码 5]
// #include <iostream>
//
// struct Fraction
// {
//     int numerator{ 0 };
//     int denominator{ 1 };
// };
//
// Fraction getFraction()
// {
//     Fraction temp{};
//     std::cout << "Enter a value for numerator: ";
//     std::cin >> temp.numerator;
//     std::cout << "Enter a value for denominator: ";
//     std::cin >> temp.denominator;
//     std::cout << '\n';
//
//     return temp;
// }
//
// Fraction multiply(const Fraction& f1, const Fraction& f2)
// {
//     return { f1.numerator * f2.numerator, f1.denominator * f2.denominator };
// }
//
// void printFraction(const Fraction& f)
// {
//     std::cout << f.numerator << '/' << f.denominator << '\n';
// }
//
// int main()
// {
//     Fraction f1{ getFraction() };
//     Fraction f2{ getFraction() };
//
//     std::cout << "Your fractions multiplied together: ";
//
//     printFraction(multiply(f1, f2));
//
//     return 0;
// }

// 请把`Fraction`从结构体改成类，并把所有函数改写成（非静态的）成员函数。
//
// 作者提示
//
// 注意：本题并不符合「何时应使用非成员函数或成员函数」的最佳实践。它的目的是
// 考查你是否理解如何把非成员函数改写成成员函数。

// 【答案 · 查看答案】

// [代码 6]
// #include <iostream>
//
// class Fraction
// {
// private:
//     int m_numerator{ 0 };
//     int m_denominator{ 1 };
//
// public:
//     explicit Fraction(int numerator=0, int denominator=1)
//         : m_numerator { numerator }, m_denominator { denominator}
//     {
//     }
//
//     void getFraction()
//     {
//         std::cout << "Enter a value for numerator: ";
//         std::cin >> m_numerator; // 这是成员函数，因此可以直接访问成员
//         std::cout << "Enter a value for denominator: ";
//         std::cin >> m_denominator;
//         std::cout << '\n';
//     }
//
//     Fraction multiply(const Fraction& f) const
//     {
//         return Fraction{ m_numerator * f.m_numerator, m_denominator * f.m_denominator };
//     }
//
//     void printFraction() const
//     {
//         std::cout << m_numerator << '/' << m_denominator << '\n';
//     }
// };
//
// int main()
// {
//     Fraction f1{};
//     f1.getFraction();
//
//     Fraction f2{};
//     f2.getFraction();
//
//     std::cout << "Your fractions multiplied together: ";
//
//     f1.multiply(f2).printFraction();
//
//     return 0;
// }


// ▼ 问题 3
// 在上一题的答案中，为什么把Fraction的构造函数声明为`explicit`？

// 【答案 · 查看答案】
// 把构造函数声明为explicit，可以防止通过单个值的隐式转换来创建`Fraction`。这
// 有助于避免出现`f1.multiply(true)`这类无意义的情况。
//
// `f1.multiply(true)`需要把`true`隐式转换为`Fraction`。正常情况下，编译器会使
// 用`Fraction(int numerator=0, int denominator=1)`来完成转换；但如果我们把这
// 个构造函数声明为explicit，它就不能用于隐式转换。由于此时编译器找不到把
// `true`转换为`Fraction`的方法，就会产生编译错误。

// ▼ 问题 4
// 在上一题中，为什么把`getFraction()`和`print()`保留为非成员函数可能更好？

// 【答案 · 查看答案】
// 使用非成员版本的`getFraction()`，我们可以在一步之内定义并初始化一个Fraction。
// 而成员版本需要两步：必须先创建对象，再对它调用成员函数。此外，成员版本还会
// 向用户打印应用程序特有的文本提示。
//
// 把`print()`改为非成员函数（并使用访问函数来访问成员），就从类的接口中去掉了
// 这个函数，使类的核心功能更加清晰。这也意味着，如果类的实现将来发生变化，只
// 要接口不变，我们就不必考虑`print()`是否需要更新（因为我们知道它无法直接访问
// 任何数据成员）。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Point2d
{
private:
	double m_x{ 0.0 };
	double m_y{ 0.0 };

public:
	Point2d() = default;

	Point2d(double x, double y)
		: m_x{ x }, m_y{ y }
	{
	}

	void print() const
	{
		std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
	}
};

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    // Point2d third{ 4.0 }; // 取消注释后应当报错

    first.print();
    second.print();

    return 0;
}
