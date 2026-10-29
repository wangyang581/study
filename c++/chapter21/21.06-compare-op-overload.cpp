// ==========================================================================
// 21.6 重载比较运算符
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十一章 操作符重载
// 原文: https://www.studycpp.cn/basic/chapter21/compare-op-overload/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "21.06-compare-op-overload.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 最大限度地减少相对冗余
//   · 太空船 运算符<=> （C++20）
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 比较运算符一共有六个。重载这些比较运算符相对简单，因为它们遵循与其他运算符
// 重载相同的模式。
//
// 由于比较运算符都是不修改左操作数的二元运算符，因此我们通常将它们重载为友元
// 函数。
//
// 下面是一个Car类示例，它重载了运算符==和运算符!=。

// [代码 1]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Car
// {
// private:
//     std::string m_make;
//     std::string m_model;
//
// public:
//     Car(std::string_view make, std::string_view model)
//         : m_make{ make }, m_model{ model }
//     {
//     }
//
//     friend bool operator== (const Car& c1, const Car& c2);
//     friend bool operator!= (const Car& c1, const Car& c2);
// };
//
// bool operator== (const Car& c1, const Car& c2)
// {
//     return (c1.m_make == c2.m_make &&
//             c1.m_model == c2.m_model);
// }
//
// bool operator!= (const Car& c1, const Car& c2)
// {
//     return (c1.m_make != c2.m_make ||
//             c1.m_model != c2.m_model);
// }
//
// int main()
// {
//     Car corolla{ "Toyota", "Corolla" };
//     Car camry{ "Toyota", "Camry" };
//
//     if (corolla == camry)
//         std::cout << "a Corolla and Camry are the same.\n";
//
//     if (corolla != camry)
//         std::cout << "a Corolla and Camry are not the same.\n";
//
//     return 0;
// }

// 这里的代码应该很简单。
//
// operator<和operator>呢？一辆车比另一辆车“大”或“小”意味着什么？通常并没有这
// 样的关系。由于运算符<和运算符>的结果并不直观，因此这里最好不要定义这些运算
// 符。
//
// 然而，上述建议也有例外。如果我们想对汽车列表进行排序，该怎么办？在这种情况
// 下，我们可能希望重载比较运算符，使其按照最符合预期的方式排序。例如，重载运
// 算符<后，汽车可以根据品牌和型号按字母顺序排序。
//
// 标准库中的一些容器类（保存其他对象的类）需要元素重载运算符<，以便对元素进行
// 排序。
//
// 下面是另一个重载所有6个逻辑比较运算符的示例：

// [代码 2]
// #include <iostream>
//
// class Cents
// {
// private:
//     int m_cents;
//
// public:
//     Cents(int cents)
// 	: m_cents{ cents }
// 	{}
//
//     friend bool operator== (const Cents& c1, const Cents& c2);
//     friend bool operator!= (const Cents& c1, const Cents& c2);
//
//     friend bool operator< (const Cents& c1, const Cents& c2);
//     friend bool operator> (const Cents& c1, const Cents& c2);
//
//     friend bool operator<= (const Cents& c1, const Cents& c2);
//     friend bool operator>= (const Cents& c1, const Cents& c2);
// };
//
// bool operator== (const Cents& c1, const Cents& c2)
// {
//     return c1.m_cents == c2.m_cents;
// }
//
// bool operator!= (const Cents& c1, const Cents& c2)
// {
//     return c1.m_cents != c2.m_cents;
// }
//
// bool operator> (const Cents& c1, const Cents& c2)
// {
//     return c1.m_cents > c2.m_cents;
// }
//
// bool operator< (const Cents& c1, const Cents& c2)
// {
//     return c1.m_cents < c2.m_cents;
// }
//
// bool operator<= (const Cents& c1, const Cents& c2)
// {
//     return c1.m_cents <= c2.m_cents;
// }
//
// bool operator>= (const Cents& c1, const Cents& c2)
// {
//     return c1.m_cents >= c2.m_cents;
// }
//
// int main()
// {
//     Cents dime{ 10 };
//     Cents nickel{ 5 };
//
//     if (nickel > dime)
//         std::cout << "a nickel is greater than a dime.\n";
//     if (nickel >= dime)
//         std::cout << "a nickel is greater than or equal to a dime.\n";
//     if (nickel < dime)
//         std::cout << "a dime is greater than a nickel.\n";
//     if (nickel <= dime)
//         std::cout << "a dime is greater than or equal to a nickel.\n";
//     if (nickel == dime)
//         std::cout << "a dime is equal to a nickel.\n";
//     if (nickel != dime)
//         std::cout << "a dime is not equal to a nickel.\n";
//
//     return 0;
// }

// 这也相当简单。
//
// 最佳实践
//
// 只定义对类有直观意义的重载运算符。
//

// ―――― 最大限度地减少相对冗余 ――――

// 在上面的示例中，请注意每个重载比较运算符的实现有多相似。重载比较运算符往往
// 高度冗余，实现越复杂，冗余就越多。
//
// 幸运的是，许多比较运算符可以使用其他比较运算符来实现：
// - 运算符!= 可以实现为 !（运算符==）
// - 运算符> 可以实现为 运算符<，只要参数的顺序翻转
// - 运算符>= 可以实现为 !（运算符<）
// - 运算符<= 可以实现为 !（运算符>）
//
// 这意味着我们只需要实现运算符==和运算符<的逻辑，然后就可以根据这两个运算符定
// 义其他四个比较运算符！下面是更新后的Cents示例，说明了这一点：

// [代码 3]
// #include <iostream>
//
// class Cents
// {
// private:
//     int m_cents;
//
// public:
//     Cents(int cents)
//         : m_cents{ cents }
//     {}
//
//     friend bool operator== (const Cents& c1, const Cents& c2) { return c1.m_cents == c2.m_cents; }
//     friend bool operator!= (const Cents& c1, const Cents& c2) { return !(operator==(c1, c2)); }
//
//     friend bool operator< (const Cents& c1, const Cents& c2) { return c1.m_cents < c2.m_cents; }
//     friend bool operator> (const Cents& c1, const Cents& c2) { return operator<(c2, c1); }
//
//     friend bool operator<= (const Cents& c1, const Cents& c2) { return !(operator>(c1, c2)); }
//     friend bool operator>= (const Cents& c1, const Cents& c2) { return !(operator<(c1, c2)); }
//
// };
//
// int main()
// {
//     Cents dime{ 10 };
//     Cents nickel{ 5 };
//
//     if (nickel > dime)
//         std::cout << "a nickel is greater than a dime.\n";
//     if (nickel >= dime)
//         std::cout << "a nickel is greater than or equal to a dime.\n";
//     if (nickel < dime)
//         std::cout << "a dime is greater than a nickel.\n";
//     if (nickel <= dime)
//         std::cout << "a dime is greater than or equal to a nickel.\n";
//     if (nickel == dime)
//         std::cout << "a dime is equal to a nickel.\n";
//     if (nickel != dime)
//         std::cout << "a dime is not equal to a nickel.\n";
//
//     return 0;
// }

// 这样，如果以后需要更改比较逻辑，只需要更新operator==和operator<，而不必修改
// 所有六个比较运算符！
//

// ―――― 太空船 运算符<=> （C++20） ――――

// C++20引入了太空船运算符（operator<=>），它可以将需要编写的比较函数数量减少
// 到最多2个，有时甚至只需要1个。我们会在后续某一课中讨论它！
//

// ―――― 习题 ――――


// ▼ 问题 1
// 为Fraction类添加6个比较运算符，使下面这个程序能够通过编译：

// [代码 4]
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
// 	Fraction(int numerator = 0, int denominator = 1) :
// 		m_numerator{ numerator }, m_denominator{ denominator }
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
// 	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
// };
//
// std::ostream& operator<<(std::ostream& out, const Fraction& f1)
// {
// 	out << f1.m_numerator << '/' << f1.m_denominator;
// 	return out;
// }
//
// int main()
// {
// 	Fraction f1{ 3, 2 };
// 	Fraction f2{ 5, 8 };
//
// 	std::cout << f1 << ((f1 == f2) ? " == " : " not == ") << f2 << '\n';
// 	std::cout << f1 << ((f1 != f2) ? " != " : " not != ") << f2 << '\n';
// 	std::cout << f1 << ((f1 < f2) ? " < " : " not < ") << f2 << '\n';
// 	std::cout << f1 << ((f1 > f2) ? " > " : " not > ") << f2 << '\n';
// 	std::cout << f1 << ((f1 <= f2) ? " <= " : " not <= ") << f2 << '\n';
// 	std::cout << f1 << ((f1 >= f2) ? " >= " : " not >= ") << f2 << '\n';
// 	return 0;
// }

// 如果你的编译器早于C++17，可以把std::gcd替换成下面这个函数：

// [代码 5]
// #include <cmath>
//
// int gcd(int a, int b) {
//     return (b == 0) ? std::abs(a) : gcd(b, a % b);
// }


// 【答案 · 查看答案】

// [代码 6]
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
// 	Fraction(int numerator = 0, int denominator = 1) :
// 		m_numerator{ numerator }, m_denominator{ denominator }
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
// 	friend bool operator== (const Fraction& f1, const Fraction& f2);
// 	friend bool operator!= (const Fraction& f1, const Fraction& f2);
//
// 	friend bool operator< (const Fraction& f1, const Fraction& f2);
// 	friend bool operator> (const Fraction& f1, const Fraction& f2);
//
// 	friend bool operator<= (const Fraction& f1, const Fraction& f2);
// 	friend bool operator>= (const Fraction& f1, const Fraction& f2);
//
// 	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
// };
//
// std::ostream& operator<<(std::ostream& out, const Fraction& f1)
// {
// 	out << f1.m_numerator << '/' << f1.m_denominator;
// 	return out;
// }
//
// bool operator== (const Fraction& f1, const Fraction& f2)
// {
// 	return (f1.m_numerator == f2.m_numerator) && (f1.m_denominator == f2.m_denominator);
// }
//
// bool operator!= (const Fraction& f1, const Fraction& f2)
// {
// 	return !(operator==(f1, f2));
// }
//
// bool operator< (const Fraction& f1, const Fraction& f2)
// {
// 	return (f1.m_numerator * f2.m_denominator < f2.m_numerator * f1.m_denominator);
// }
//
// bool operator> (const Fraction& f1, const Fraction& f2)
// {
// 	return operator<(f2, f1);
// }
//
// bool operator<= (const Fraction& f1, const Fraction& f2)
// {
// 	return !(operator>(f1, f2));
// }
//
// bool operator>= (const Fraction& f1, const Fraction& f2)
// {
// 	return !(operator<(f1, f2));
// }
//
// int main()
// {
// 	Fraction f1{ 3, 2 };
// 	Fraction f2{ 5, 8 };
//
// 	std::cout << f1 << ((f1 == f2) ? " == " : " not == ") << f2 << '\n';
// 	std::cout << f1 << ((f1 != f2) ? " != " : " not != ") << f2 << '\n';
// 	std::cout << f1 << ((f1 < f2) ? " < " : " not < ") << f2 << '\n';
// 	std::cout << f1 << ((f1 > f2) ? " > " : " not > ") << f2 << '\n';
// 	std::cout << f1 << ((f1 <= f2) ? " <= " : " not <= ") << f2 << '\n';
// 	std::cout << f1 << ((f1 >= f2) ? " >= " : " not >= ") << f2 << '\n';
//
// 	return 0;
// }


// ▼ 问题 2
// 为本课开头出现的Car类添加重载的`operator<<`和`operator<`，使下面这个程序能
// 够通过编译：

// [代码 7]
// #include <algorithm>
// #include <iostream>
// #include <string>
// #include <vector>
//
// int main()
// {
//   std::vector<Car> cars{
//     { "Toyota", "Corolla" },
//     { "Honda", "Accord" },
//     { "Toyota", "Camry" },
//     { "Honda", "Civic" }
//   };
//
//   std::sort(cars.begin(), cars.end()); // 需要重载 operator<
//
//   for (const auto& car : cars)
//     std::cout << car << '\n'; // 需要重载 operator<<
//
//   return 0;
// }

// 这个程序应当产生如下输出：

// [文本/输出]
// (Honda, Accord)
// (Honda, Civic)
// (Toyota, Camry)
// (Toyota, Corolla)

// 如果需要复习std::sort，可以看「18.0 对数组进行排序」。

// 【答案 · 查看答案】

// [代码 8]
// #include <algorithm>
// #include <iostream>
// #include <string>
// #include <string_view>
// #include <vector>
//
// class Car
// {
// private:
//     std::string m_make;
//     std::string m_model;
//
// public:
//     Car(std::string_view make, std::string_view model)
//         : m_make{ make }, m_model{ model }
//     {
//     }
//
//     friend bool operator==(const Car& c1, const Car& c2);
//     friend bool operator!=(const Car& c1, const Car& c2);
//
//     friend std::ostream& operator<<(std::ostream& out, const Car& c)
//     {
//         out << '(' << c.m_make << ", " << c.m_model << ')';
//         return out;
//     }
//
//     // 感谢读者 Olivier 提供这个函数的初版
//     friend bool operator<(const Car& c1, const Car& c2)
//     {
//         if (c1.m_make != c2.m_make) // 如果两辆车的厂商不同……
//             return c1.m_make < c2.m_make; // ……然后比较厂商
//
//         return c1.m_model < c2.m_model; // 否则比较型号
//     }
// };
//
// bool operator==(const Car& c1, const Car& c2)
// {
//     return c1.m_make == c2.m_make && c1.m_model == c2.m_model;
// }
//
// bool operator!= (const Car& c1, const Car& c2)
// {
//     return !operator==(c1, c2);
// }
//
// int main()
// {
//     std::vector<Car> cars{
//       { "Toyota", "Corolla" },
//       { "Honda", "Accord" },
//       { "Toyota", "Camry" },
//       { "Honda", "Civic" }
//     };
//
//     std::sort(cars.begin(), cars.end()); // 需要重载 Car::operator<
//
//     for (const auto& car : cars)
//         std::cout << car << '\n'; // 需要重载 Car::operator<<
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <string>
#include <string_view>

class Car
{
private:
    std::string m_make;
    std::string m_model;

public:
    Car(std::string_view make, std::string_view model)
        : m_make{ make }, m_model{ model }
    {
    }

    friend bool operator== (const Car& c1, const Car& c2);
    friend bool operator!= (const Car& c1, const Car& c2);
};

bool operator== (const Car& c1, const Car& c2)
{
    return (c1.m_make == c2.m_make &&
            c1.m_model == c2.m_model);
}

bool operator!= (const Car& c1, const Car& c2)
{
    return (c1.m_make != c2.m_make ||
            c1.m_model != c2.m_model);
}

int main()
{
    Car corolla{ "Toyota", "Corolla" };
    Car camry{ "Toyota", "Camry" };

    if (corolla == camry)
        std::cout << "a Corolla and Camry are the same.\n";

    if (corolla != camry)
        std::cout << "a Corolla and Camry are not the same.\n";

    return 0;
}
