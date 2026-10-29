// ==========================================================================
// 21.3 重载I/O运算符
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十一章 操作符重载
// 原文: https://www.studycpp.cn/basic/chapter21/overload-io/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "21.03-overload-io.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 重载operator«
//   · 重载operator»
//   · 防止部分提取
//   · 结论
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 对于具有多个成员变量的类，逐个将成员变量打印到屏幕上很快就会变得繁琐。例如，
// 考虑以下类：

// [代码 1]
// class Point
// {
// private:
//     double m_x{};
//     double m_y{};
//     double m_z{};
//
// public:
//     Point(double x=0.0, double y=0.0, double z=0.0)
//       : m_x{x}, m_y{y}, m_z{z}
//     {
//     }
//
//     double getX() const { return m_x; }
//     double getY() const { return m_y; }
//     double getZ() const { return m_z; }
// };

// 如果要将这个类的实例打印到屏幕上，就必须这样写：

// [代码 2]
// Point point { 5.0, 6.0, 7.0 };
//
// std::cout << "Point(" << point.getX() << ", " <<
//     point.getY() << ", " <<
//     point.getZ() << ')';

// 当然，编写一个可复用的函数来完成这件事更合理。下面我们创建了print()函数，其
// 工作方式如下：

// [代码 3]
// class Point
// {
// private:
//     double m_x{};
//     double m_y{};
//     double m_z{};
//
// public:
//     Point(double x=0.0, double y=0.0, double z=0.0)
//       : m_x{x}, m_y{y}, m_z{z}
//     {
//     }
//
//     double getX() const { return m_x; }
//     double getY() const { return m_y; }
//     double getZ() const { return m_z; }
//
//     void print() const
//     {
//         std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ')';
//     }
// };

// 虽然这样好多了，但它仍然有一些缺点。因为print()返回void，所以不能在输出语句
// 中间调用它。您必须改成这样：

// [代码 4]
// int main()
// {
//     const Point point { 5.0, 6.0, 7.0 };
//
//     std::cout << "My point is: ";
//     point.print();
//     std::cout << " in Cartesian space.\n";
// }

// 如果可以简单地键入：

// [代码 5]
// Point point{5.0, 6.0, 7.0};
// cout << "My point is: " << point << " in Cartesian space.\n";

// 并得到相同结果，那就更理想了。这样既不用把输出拆成多个语句，也不必记住您给
// print函数起的名字。
//
// 幸运的是，通过重载«运算符，可以实现该功能！
//

// ―――― 重载operator« ――――

// 重载运算符«类似于重载运算符+（它们都是二元运算符），区别主要在于参数类型不
// 同。
//
// 考虑表达式"std::cout « point"。运算符«的操作数是什么？左操作数是std::cout对
// 象，右操作数是Point类对象。std::cout实际上是一个std::ostream类型的对象。因
// 此，我们的重载函数将如下所示：

// [代码 6]
// // std::ostream 是 std::cout 对象的类型
// friend std::ostream& operator<< (std::ostream& out, const Point& point);

// Point类的operator«实现相当简单。因为C++已经知道如何使用运算符«输出double，
// 并且我们的成员都是double，所以可以直接使用运算符«输出Point的成员变量。下面
// 是在上面的Point类中新增重载运算符«。

// [代码 7]
// #include <iostream>
//
// class Point
// {
// private:
//     double m_x{};
//     double m_y{};
//     double m_z{};
//
// public:
//     Point(double x=0.0, double y=0.0, double z=0.0)
//       : m_x{x}, m_y{y}, m_z{z}
//     {
//     }
//
//     friend std::ostream& operator<< (std::ostream& out, const Point& point);
// };
//
// std::ostream& operator<< (std::ostream& out, const Point& point)
// {
//     // 因为 operator<< 是 Point 类的友元, 所以可以直接访问私有成员变量
//     out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')'; // 这里做实际输出
//
//     return out; // 返回 std::ostream 以便可以链式调用 operator<<
// }
//
// int main()
// {
//     const Point point1 { 2.0, 3.0, 4.0 };
//
//     std::cout << point1 << '\n';
//
//     return 0;
// }

// 这非常简单。请注意，我们的输出行与前面编写的print()函数中的那一行非常相似。
// 最明显的区别是，std::cout变成了参数out（调用函数时，它将是对std::cout的引用）
// 。
//
// 这里最棘手的部分是返回类型。对于算术运算符，我们通常按值计算并返回一个结果。
// 然而，如果您试图按值返回std::ostream，就会得到编译错误，因为std::ostream明
// 确禁止复制。
//
// 在这种情况下，我们将左操作数作为引用返回。这不仅可以避免生成std::ostream的
// 副本，还允许我们把输出操作“链接”起来，例如"std::cout« point « std::endl；"。
//
// 考虑一下，如果运算符«返回void会发生什么。当编译器计算"std::cout « point «
// ‘\n’; “时，由于优先级和结合性规则，它会将该表达式视为”（std::cout « point）
// « ‘\n’；"。“std::cout « point"将调用我们返回void的重载operator«函数，因此这
// 个子表达式的结果是void。随后，剩余表达式就变成了：” void « ‘\n’；"，这毫无
// 意义！
//
// 相反，如果返回out参数，（std::cout « point）就会返回std::cout。于是，剩余表
// 达式就变成：" std::cout « ‘\n’；"！
//
// 每当我们希望重载的二元运算符能够以这种方式链接调用时，都应该（通过引用）返
// 回左操作数。在这种情况下，通过引用返回左操作数是可以的，因为左操作数由调用
// 方传入，当被调用函数返回时它仍然必须存在。因此，不必担心返回悬空引用。
//
// 为了证明它有效，请看下面这个将Point类与重载运算符«一起使用的示例：

// [代码 8]
// #include <iostream>
//
// class Point
// {
// private:
//     double m_x{};
//     double m_y{};
//     double m_z{};
//
// public:
//     Point(double x=0.0, double y=0.0, double z=0.0)
//       : m_x{x}, m_y{y}, m_z{z}
//     {
//     }
//
//     friend std::ostream& operator<< (std::ostream& out, const Point& point);
// };
//
// std::ostream& operator<< (std::ostream& out, const Point& point)
// {
//     //  因为 operator<< 是 Point 类的友元, 所以可以直接访问私有成员变量
//     out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';
//
//     return out;
// }
//
// int main()
// {
//     Point point1 { 2.0, 3.5, 4.0 };
//     Point point2 { 6.0, 7.5, 8.0 };
//
//     std::cout << point1 << ' ' << point2 << '\n';
//
//     return 0;
// }

// 这将产生以下结果：

// [文本/输出]
// Point(2, 3.5, 4) Point(6, 7.5, 8)

// 在上面的示例中，operator«是友元函数，因为它需要直接访问Point的私有成员。然
// 而，如果可以通过getter访问成员，那么operator«也可以实现为非友元函数。
//

// ―――― 重载operator» ――――

// 也可以重载输入运算符。它的实现方式与重载输出运算符类似。您需要知道的关键点
// 是，std::cin是一个std::istream类型的对象。下面是添加了重载运算符»的Point类：

// [代码 9]
// #include <iostream>
//
// class Point
// {
// private:
//     double m_x{};
//     double m_y{};
//     double m_z{};
//
// public:
//     Point(double x=0.0, double y=0.0, double z=0.0)
//       : m_x{x}, m_y{y}, m_z{z}
//     {
//     }
//
//     friend std::ostream& operator<< (std::ostream& out, const Point& point);
// };
//
// std::ostream& operator<< (std::ostream& out, const Point& point)
// {
//     //  因为 operator<< 是 Point 类的友元, 所以可以直接访问私有成员变量
//     out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';
//
//     return out;
// }
//
// // 注意 point 参数是非 const，因为我们需要修改它
// // 注 这里实现为非友元函数
// std::istream& operator>> (std::istream& in, Point& point)
// {
//     double x{};
//     double y{};
//     double z{};
//
//     in >> x >> y >> z;
//
//     if (in)                     // 如果所有的输入都ok
//         point = Point{x, y, z}; // 覆盖现有的point对象
//
//     return in;
// }
//
// int main()
// {
//     std::cout << "Enter a point: ";
//
//     Point point{};
//     std::cin >> point;
//
//     std::cout << "You entered: " << point << '\n';
//
//     return 0;
// }

// 假设用户输入3.0 4.5 7.26，程序将产生以下结果：

// [文本/输出]
// You entered: Point(3, 4.5, 7.26)

// 在这个实现中，我们使用operator=覆盖point中的值。因为operator=是public可用的，
// 所以operator»不需要成为友元函数。
//

// ―――― 防止部分提取 ――――

// 您可能会期待Point的重载operator»实现得更像这样：

// [代码 10]
// // 假设这个运算符是Point的友元函数，可以直接修改私有成员
// std::istream& operator>> (std::istream& in, Point& point)
// {
//     // 这版本的代码可能有部分提取的问题
//     in >> point.m_x >> point.m_y >> point.m_z;
//
//     return in;
// }

// 然而，这种实现可能导致部分提取。考虑一下，如果用户输入“3.0 a b”会发生什么。
// 3.0将被提取到m_x。对m_y和m_z的提取都会失败，这意味着m_y与m_z将被设置为0.0。
// 我们的point会被部分输入值覆盖，部分被零覆盖。
//
// 对于Point对象，这可能是一个可接受的结果。但假设我们输入的是分数。提取分母失
// 败会将分母设置为0.0，这可能会在以后导致除以零错误。
//
// 因此，最好先保存所有输入，等确认所有输入都成功后，再覆盖对象。
//

// ―――― 结论 ――――

// 重载operator«和operator»可以让类的屏幕输出和控制台输入变得非常方便。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 取出下面这个Fraction类，为它添加重载的`operator<<`和`operator>>`。你的
// `operator>>`应当避免「部分提取」，并在用户输入的分母为`0`时失败。失败时不应
// 把Fraction重置为默认值。
//
// 下面这个程序应当能够通过编译：

// [代码 11]
// int main()
// {
// 	Fraction f1{};
// 	std::cout << "Enter fraction 1: ";
// 	std::cin >> f1;
//
// 	Fraction f2{};
// 	std::cout << "Enter fraction 2: ";
// 	std::cin >> f2;
//
// 	std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n'; // 注意：f1 * f2 的结果是右值
//
// 	return 0;
// }

// 并产生如下结果：

// [文本/输出]
// Enter fraction 1: 2/3
// Enter fraction 2: 3/8
// 2/3 * 3/8 is 1/4

// Fraction类如下：

// [代码 12]
// #include <iostream>
// #include <numeric> // 用于 std::gcd
//
// class Fraction
// {
// private:
// 	int m_numerator{};
// 	int m_denominator{};
//
// public:
// 	Fraction(int numerator=0, int denominator=1):
// 		m_numerator{numerator}, m_denominator{denominator}
// 	{
// 		// 把 reduce() 放在构造函数中，确保新产生的分数都会被约分！
// 		// 被覆盖的分数需要重新约分
// 		reduce();
// 	}
//
// 	void reduce()
// 	{
// 		int gcd{ std::gcd(m_numerator, m_denominator) };
// 		if (gcd)
// 		{
// 			m_numerator /= gcd;
// 			m_denominator /= gcd;
// 		}
// 	}
//
// 	friend Fraction operator*(const Fraction& f1, const Fraction& f2);
// 	friend Fraction operator*(const Fraction& f1, int value);
// 	friend Fraction operator*(int value, const Fraction& f1);
//
// 	void print() const
// 	{
// 		std::cout << m_numerator << '/' << m_denominator << '\n';
// 	}
// };
//
// Fraction operator*(const Fraction& f1, const Fraction& f2)
// {
// 	return Fraction { f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator };
// }
//
// Fraction operator*(const Fraction& f1, int value)
// {
// 	return Fraction { f1.m_numerator * value, f1.m_denominator };
// }
//
// Fraction operator*(int value, const Fraction& f1)
// {
// 	return Fraction { f1.m_numerator * value, f1.m_denominator };
// }

// 如果你的编译器早于C++17，可以把std::gcd替换成下面这个函数：

// [代码 13]
// #include <cmath>
//
// int gcd(int a, int b) {
//     return (b == 0) ? std::abs(a) : gcd(b, a % b);
// }


// 【答案 · 查看答案】

// [代码 14]
// #include <iostream>
// #include <limits>
// #include <numeric> // 用于 std::gcd
//
// class Fraction
// {
// private:
//     int m_numerator{ 0 };
//     int m_denominator{ 1 };
//
// public:
//     Fraction(int numerator=0, int denominator = 1) :
//         m_numerator{ numerator }, m_denominator{ denominator }
//     {
//         // 把 reduce() 放在构造函数中，确保新产生的分数都会被约分！
//         // 被覆盖的分数需要重新约分
//         reduce();
//     }
//
//     void reduce()
//     {
//         int gcd{ std::gcd(m_numerator, m_denominator) };
//         if (gcd)
//         {
//             m_numerator /= gcd;
//             m_denominator /= gcd;
//         }
//     }
//
//     friend Fraction operator*(const Fraction& f1, const Fraction& f2);
//     friend Fraction operator*(const Fraction& f1, int value);
//     friend Fraction operator*(int value, const Fraction& f1);
//
//     friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
//
//     void print() const
//     {
//         std::cout << m_numerator << '/' << m_denominator << '\n';
//     }
// };
//
// Fraction operator*(const Fraction& f1, const Fraction& f2)
// {
//     return Fraction { f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator };
// }
//
// Fraction operator*(const Fraction& f1, int value)
// {
//     return Fraction { f1.m_numerator * value, f1.m_denominator };
// }
//
// Fraction operator*(int value, const Fraction& f1)
// {
//     return Fraction { f1.m_numerator * value, f1.m_denominator };
// }
//
// std::ostream& operator<<(std::ostream& out, const Fraction& f1)
// {
//     out << f1.m_numerator << '/' << f1.m_denominator;
//     return out;
// }
//
// std::istream& operator>>(std::istream& in, Fraction& f1)
// {
//     int numerator {};
//     char ignore {};
//     int denominator {};
//
//     in >> numerator >> ignore >> denominator;
//     if (denominator == 0)                       // 如果分母在语义上无效
//         in.setstate(std::ios_base::failbit);    // 手动设置失败状态
//     if (in)                                     // 如果我们没有处于失败状态
//         f1 = Fraction {numerator, denominator}; // 用提取出的值更新对象
//
//     return in;
// }
//
// int main()
// {
//     Fraction f1{};
//     std::cout << "Enter fraction 1: ";
//     std::cin >> f1;
//
//     Fraction f2{};
//     std::cout << "Enter fraction 2: ";
//     std::cin >> f2;
//
//     std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n'; // 注意：f1 * f2 的结果是右值
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0)
      : m_x{x}, m_y{y}, m_z{z}
    {
    }

    friend std::ostream& operator<< (std::ostream& out, const Point& point);
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    // 因为 operator<< 是 Point 类的友元, 所以可以直接访问私有成员变量
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')'; // 这里做实际输出

    return out; // 返回 std::ostream 以便可以链式调用 operator<<
}

int main()
{
    const Point point1 { 2.0, 3.0, 4.0 };

    std::cout << point1 << '\n';

    return 0;
}
