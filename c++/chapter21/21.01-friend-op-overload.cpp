// ==========================================================================
// 21.1 使用友元函数重载算术运算符
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十一章 操作符重载
// 原文: https://www.studycpp.cn/basic/chapter21/friend-op-overload/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "21.01-friend-op-overload.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 使用友元函数重载运算符
//   · 可以在类内定义友元函数
//   · 为不同类型的操作数重载运算符
//   · 另一个例子
//   · 重载运算符函数中，可以使用其他运算符
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// C++中最常用的一些运算符是算术运算符，也就是加号运算符（+）、减号运算符（-）、
// 乘法运算符（*）和除法运算符（/）。注意，所有算术运算符都是二元运算符，这意
// 味着它们需要两个操作数，分别位于运算符两侧。这四个运算符的重载方式完全相同。
//
// 重载运算符有三种方式：成员函数、友元函数和普通函数。在本课中，我们将介绍友
// 元函数方式（因为它对于大多数二元运算符来说更直观）。下一课，我们将讨论普通
// 函数方式。最后，在本章后面的课程中，我们将介绍成员函数方式。当然，我们也会
// 更详细地总结应该在什么场景下使用哪一种。
//

// ―――― 使用友元函数重载运算符 ――――

// 考虑以下class：

// [代码 1]
// class Cents
// {
// private:
// 	int m_cents {};
//
// public:
// 	Cents(int cents) : m_cents{ cents } { }
// 	int getCents() const { return m_cents; }
// };

// 下面的示例展示了如何重载加号运算符（+），以便将两个“Cents”对象相加：

// [代码 2]
// #include <iostream>
//
// class Cents
// {
// private:
// 	int m_cents {};
//
// public:
// 	Cents(int cents) : m_cents{ cents } { }
//
// 	// 声明一个友元函数
// 	friend Cents operator+(const Cents& c1, const Cents& c2);
//
// 	int getCents() const { return m_cents; }
// };
//
// // 注: 这个函数不是成员函数
// Cents operator+(const Cents& c1, const Cents& c2)
// {
// 	// 可以直接访问m_cents，因为本函数是 Cents 的友元函数
// 	// 返回 int，触发Cents的构造函数
// 	return c1.m_cents + c2.m_cents;
// }
//
// int main()
// {
// 	Cents cents1{ 6 };
// 	Cents cents2{ 8 };
// 	Cents centsSum{ cents1 + cents2 };
// 	std::cout << "I have " << centsSum.getCents() << " cents.\n";
//
// 	return 0;
// }

// 这将产生以下结果：

// [文本/输出]
// I have 14 cents.

// 重载加号运算符（+）就像声明一个名为operator+的函数一样简单：给它两个表示待
// 相加操作数的参数，选择合适的返回类型，然后编写函数体。
//
// 对于Cents对象，operator+()函数的实现非常简单。首先看参数类型：这个版本的
// operator+会把两个Cents对象相加，因此函数接收两个Cents类型的对象作为输入。其
// 次看返回类型：我们的operator+会返回一个Cents类型的结果，因此返回类型就是
// Cents。
//
// 最后看实现：要将两个Cents对象相加，需要使用每个Cents对象中的m_cents成员。因
// 为重载的operator+()函数是类的友元，所以可以直接访问参数的m_cents成员。此外，
// m_cents是整数，而C++知道如何使用内置加号运算符将整数相加，因此我们可以直接
// 使用+运算符来完成加法。
//
// 重载减法运算符（-）也很简单：

// [代码 3]
// #include <iostream>
//
// class Cents
// {
// private:
// 	int m_cents {};
//
// public:
// 	explicit Cents(int cents) : m_cents{ cents } { }
//
// 	// Cents + Cents 实现为友元函数
// 	friend Cents operator+(const Cents& c1, const Cents& c2);
//
// 	// Cents - Cents 实现为友元函数
// 	friend Cents operator-(const Cents& c1, const Cents& c2);
//
// 	int getCents() const { return m_cents; }
// };
//
// // 注: 这个函数不是成员函数
// Cents operator+(const Cents& c1, const Cents& c2)
// {
// 	// 可以直接访问m_cents，因为本函数是 Cents 的友元函数
// 	// 返回 int，触发Cents的构造函数
// 	return Cents { c1.m_cents + c2.m_cents };
// }
//
// // 注: 这个函数不是成员函数
// Cents operator-(const Cents& c1, const Cents& c2)
// {
// 	// 可以直接访问m_cents，因为本函数是 Cents 的友元函数
// 	// 返回 int，触发Cents的构造函数
// 	return Cents { c1.m_cents - c2.m_cents };
// }
//
// int main()
// {
// 	Cents cents1{ 6 };
// 	Cents cents2{ 2 };
// 	Cents centsSum{ cents1 - cents2 };
// 	std::cout << "I have " << centsSum.getCents() << " cents.\n";
//
// 	return 0;
// }

// 重载乘法运算符（*）和除法运算符（/）也同样简单，只需要分别定义operator*和
// operator/函数。
//

// ―――― 可以在类内定义友元函数 ――――

// 友元函数不是类的成员，但如果需要，它们仍然可以在类中定义：

// [代码 4]
// #include <iostream>
//
// class Cents
// {
// private:
// 	int m_cents {};
//
// public:
// 	explicit Cents(int cents) : m_cents{ cents } { }
//
// 	// Cents + Cents 实现为友元函数
//     // 这个函数实现，放在类中，但它不是类的成员函数
// 	friend Cents operator+(const Cents& c1, const Cents& c2)
// 	{
// 		// 可以直接访问m_cents，因为本函数是 Cents 的友元函数
// 		// 返回 int，触发Cents的构造函数
// 		return Cents { c1.m_cents + c2.m_cents };
// 	}
//
// 	int getCents() const { return m_cents; }
// };
//
// int main()
// {
// 	Cents cents1{ 6 };
// 	Cents cents2{ 8 };
// 	Cents centsSum{ cents1 + cents2 };
// 	std::cout << "I have " << centsSum.getCents() << " cents.\n";
//
// 	return 0;
// }

// 对于实现很简单的重载运算符，这种写法很方便。
//

// ―――― 为不同类型的操作数重载运算符 ――――

// 通常，我们希望重载运算符可以处理不同类型的操作数。例如，如果我们有Cents（4）
// ，可能希望将整数6加到这个值上，得到Cents（10）。
//
// 当C++计算表达式x+y时，x会成为第一个参数，y会成为第二个参数。当x和y类型相同
// 时，计算x+y或y+x并不重要，因为无论哪种写法都会调用同一个operator+版本。然而，
// 当操作数类型不同时，x+y和y+x调用的就不是同一个函数。
//
// 例如，Cents（4）+6将调用operator+（Cents，int），而6+Cents（4）将调用
// operator+（int，Cents）。因此，每当我们为不同类型的操作数重载二元运算符时，
// 通常需要编写两个函数，每种参数顺序各一个。下面是一个例子：

// [代码 5]
// #include <iostream>
//
// class Cents
// {
// private:
// 	int m_cents {};
//
// public:
// 	explicit Cents(int cents) : m_cents{ cents } { }
//
// 	// Cents + int 实现为友元函数
// 	friend Cents operator+(const Cents& c1, int value);
//
// 	// int + Cents 实现为友元函数
// 	friend Cents operator+(int value, const Cents& c1);
//
// 	int getCents() const { return m_cents; }
// };
//
// // 注: 这个函数不是成员函数
// Cents operator+(const Cents& c1, int value)
// {
// 	// 可以直接访问m_cents，因为本函数是 Cents 的友元函数
// 	return Cents { c1.m_cents + value };
// }
//
// // 注: 这个函数不是成员函数
// Cents operator+(int value, const Cents& c1)
// {
// 	// 可以直接访问m_cents，因为本函数是 Cents 的友元函数
// 	return Cents { c1.m_cents + value };
// }
//
// int main()
// {
// 	Cents c1{ Cents{ 4 } + 6 };
// 	Cents c2{ 6 + Cents{ 4 } };
//
// 	std::cout << "I have " << c1.getCents() << " cents.\n";
// 	std::cout << "I have " << c2.getCents() << " cents.\n";
//
// 	return 0;
// }

// 注意，这两个重载函数的实现相同，因为它们做的是同一件事，只是参数顺序不同。
//

// ―――― 另一个例子 ――――

// 让我们来看另一个例子：

// [代码 6]
// #include <iostream>
//
// class MinMax
// {
// private:
// 	int m_min {}; // 遇到的最小值
// 	int m_max {}; // 遇到的最大值
//
// public:
// 	MinMax(int min, int max)
// 		: m_min { min }, m_max { max }
// 	{ }
//
// 	int getMin() const { return m_min; }
// 	int getMax() const { return m_max; }
//
// 	friend MinMax operator+(const MinMax& m1, const MinMax& m2);
// 	friend MinMax operator+(const MinMax& m, int value);
// 	friend MinMax operator+(int value, const MinMax& m);
// };
//
// MinMax operator+(const MinMax& m1, const MinMax& m2)
// {
// 	// 获取m1和m2的最小值
// 	int min{ m1.m_min < m2.m_min ? m1.m_min : m2.m_min };
//
// 	// 获取m1和m2的最大值
// 	int max{ m1.m_max > m2.m_max ? m1.m_max : m2.m_max };
//
// 	return MinMax { min, max };
// }
//
// MinMax operator+(const MinMax& m, int value)
// {
// 	// 获取m和value的最小值
// 	int min{ m.m_min < value ? m.m_min : value };
//
// 	// 获取m和value的最大值
// 	int max{ m.m_max > value ? m.m_max : value };
//
// 	return MinMax { min, max };
// }
//
// MinMax operator+(int value, const MinMax& m)
// {
// 	// 调用 operator+(MinMax, int)
// 	return m + value;
// }
//
// int main()
// {
// 	MinMax m1{ 10, 15 };
// 	MinMax m2{ 8, 11 };
// 	MinMax m3{ 3, 12 };
//
// 	MinMax mFinal{ m1 + m2 + 5 + 8 + m3 + 16 };
//
// 	std::cout << "Result: (" << mFinal.getMin() << ", " <<
// 		mFinal.getMax() << ")\n";
//
// 	return 0;
// }

// MinMax类会跟踪目前为止看到的最小值和最大值。我们将+运算符重载了3次，因此既
// 可以将两个MinMax对象相加，也可以将整数加入MinMax对象。
//
// 此示例生成结果：

// [文本/输出]
// Result: (3, 16)

// 让我们再多谈一点“MinMax mFinal{m1+m2+5+8+m3+16}”的计算过程。请记住，运算符+
// 从左到右求值，因此m1+m2首先求值。这会调用operator+(m1，m2)，并产生返回值
// MinMax（8，15）。然后计算MinMax（8，15）+5，这会调用operator+(MinMax（8,15）
// ，5)，并产生返回值MinMax（5,15）。接着，MinMax（5，15）+8以相同方式求值，生
// 成MinMax（5,15）。然后计算MinMax（5，15）+m3，产生MinMax（3，15）。最后，
// MinMax（3，15）+16计算为MinMax（3,16）。随后，这个最终结果用于初始化mFinal。
//
// 换句话说，该表达式等价于“MinMax mFinal=（（（（（m1+m2）+5）+8）+m3）+16）”。
// 每一步运算都会返回一个MinMax对象，而这个对象又成为下一次运算的左操作数。
//

// ―――― 重载运算符函数中，可以使用其他运算符 ――――

// 在上面的示例中，请注意，operator+（int，MinMax）是通过调用operator+（MinMax，
// int）来定义的，并且会产生相同结果。这让operator+（int，MinMax）的实现缩减到
// 一行，既减少了冗余，也让函数更容易理解和维护。
//
// 通常可以通过调用其他重载运算符来定义某个重载运算符。如果这样能让代码更简单，
// 就应该优先这样做。
//

// ―――― 习题 ――――


// ▼ 问题 1
// a) 编写一个名为`Fraction`的类，包含一个整数分子成员和一个整数分母成员。编写
// 一个`print()`函数打印这个分数。
//
// 下面这段代码应当能够通过编译：

// [代码 7]
// #include <iostream>
//
// int main()
// {
//     Fraction f1{ 1, 4 };
//     f1.print();
//
//     Fraction f2{ 1, 2 };
//     f2.print();
//
//     return 0;
// }

// 它应当打印：

// [文本/输出]
// 1/4
// 1/2


// 【答案 · 查看答案】

// [代码 8]
// #include <iostream>
//
// class Fraction
// {
// private:
// 	int m_numerator { 0 };
// 	int m_denominator { 1 };
//
// public:
// 	explicit Fraction(int numerator, int denominator=1)
// 		: m_numerator{numerator}, m_denominator{denominator}
// 	{
// 	}
//
// 	void print() const
// 	{
// 		std::cout << m_numerator << '/' << m_denominator << '\n';
// 	}
// };
//
// int main()
// {
// 	Fraction f1 {1, 4};
// 	f1.print();
//
// 	Fraction f2 {1, 2};
// 	f2.print();
//
// 	return 0;
// }

// b) 添加重载的乘法运算符，以支持「分数与整数相乘」以及「两个分数相乘」。请使
// 用友元函数的方式。
//
// 提示：两个分数相乘时，先把两个分子相乘，再把两个分母相乘。分数与整数相乘时，
// 用分数的分子乘以该整数，分母保持不变。
//
// 下面这段代码应当能够通过编译：

// [代码 9]
// #include <iostream>
//
// int main()
// {
//     Fraction f1{2, 5};
//     f1.print();
//
//     Fraction f2{3, 8};
//     f2.print();
//
//     Fraction f3{ f1 * f2 };
//     f3.print();
//
//     Fraction f4{ f1 * 2 };
//     f4.print();
//
//     Fraction f5{ 2 * f2 };
//     f5.print();
//
//     Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
//     f6.print();
//
//     return 0;
// }

// 它应当打印：

// [文本/输出]
// 2/5
// 3/8
// 6/40
// 4/5
// 6/8
// 6/24


// 【答案 · 查看答案】

// [代码 10]
// #include <iostream>
//
// class Fraction
// {
// private:
// 	int m_numerator { 0 };
// 	int m_denominator { 1 };
//
// public:
// 	explicit Fraction(int numerator, int denominator=1)
// 		: m_numerator{numerator}, m_denominator{denominator}
// 	{
// 	}
//
// 	// 我们不想按值传递，因为拷贝很慢。
// 	// 我们不能也不应该按非 const 引用传递，因为那样
// 	// 我们的函数就无法用于右值。
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
// 	return Fraction { f1 * value };
// }
//
// int main()
// {
// 	Fraction f1{2, 5};
// 	f1.print();
//
// 	Fraction f2{3, 8};
// 	f2.print();
//
// 	Fraction f3{ f1 * f2 };
// 	f3.print();
//
// 	Fraction f4{ f1 * 2 };
// 	f4.print();
//
// 	Fraction f5{ 2 * f2 };
// 	f5.print();
//
// 	Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
// 	f6.print();
//
// 	return 0;
// }

// c) 如果我们把构造函数改为非explicit，并去掉上一题解答中用于「整数乘法」的运
// 算符，程序为什么仍然能正确工作？

// [代码 11]
// // 去掉构造函数上的 explicit
// 	Fraction(int numerator, int denominator=1)
// 		: m_numerator{numerator}, m_denominator{denominator}
// 	{
// 	}
//
// // 去掉这些运算符后，程序仍然能正常工作
// Fraction operator*(const Fraction& f1, int value);
// Fraction operator*(int value, const Fraction& f1);


// 【答案 · 查看答案】
// 因为我们仍然有

// [文本/输出]
// Fraction operator*(const Fraction& f1, const Fraction& f2)

// 当分数与整数相乘时，例如

// [代码 12]
// Fraction f5{ 2 * f2 };

// 非explicit的`Fraction(int, int)`构造函数会被用来由2构造一个新的`Fraction`，
// 然后用`Fraction * Fraction`运算符把这个新`Fraction`与`f2`相乘。
//
// 由于这需要把`2`转换成`Fraction`，它比使用「整数乘法」重载运算符的版本稍慢一
// 些。
//
// d) 如果把`operator*(Fraction, Fraction)`的引用形参改为非const，`main`函数中
// 下面这一行就无法再工作。为什么？

// [代码 13]
// // 非 const 的乘法运算符是这样写的
// Fraction operator*(Fraction& f1, Fraction& f2)
//
// // 这样就不再可行了
// Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };


// 【答案 · 查看答案】
// 我们在这里相乘的是临时的`Fraction`对象，而非const引用无法绑定到临时对象。
//
// e) 附加题：分数2/4与1/2相等，但2/4没有化成最简分数。我们可以通过求出分子与
// 分母的最大公约数（GCD），再把分子和分母同时除以GCD，把任意分数化为最简。
//
// C++17在标准库中加入了`std::gcd()`（位于头文件中）。
//
// 如果你的编译器较旧，可以使用下面这个函数求GCD：

// [代码 14]
// #include <cmath> // 用于 std::abs
//
// int gcd(int a, int b) {
//     return (b == 0) ? std::abs(a) : gcd(b, a % b);
// }

// 编写一个名为`reduce()`的成员函数来约分你的分数。请确保所有分数都被正确约分。
//
// 下面这段代码应当能够通过编译：

// [代码 15]
// #include <iostream>
//
// int main()
// {
//     Fraction f1{2, 5};
//     f1.print();
//
//     Fraction f2{3, 8};
//     f2.print();
//
//     Fraction f3{ f1 * f2 };
//     f3.print();
//
//     Fraction f4{ f1 * 2 };
//     f4.print();
//
//     Fraction f5{ 2 * f2 };
//     f5.print();
//
//     Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
//     f6.print();
//
//     Fraction f7{0, 6};
//     f7.print();
//
//     return 0;
// }

// 并产生如下结果：

// [文本/输出]
// 2/5
// 3/8
// 3/20
// 4/5
// 3/4
// 1/4
// 0/1


// 【答案 · 查看答案】

// [代码 16]
// #include <iostream>
// #include <numeric> // 用于 std::gcd
//
// // 这个版本的 Fraction 类会自动约分
// class Fraction
// {
// private:
// 	int m_numerator{ 0 };
// 	int m_denominator{ 1 };
//
// public:
// 	explicit Fraction(int numerator, int denominator = 1)
// 		: m_numerator{ numerator }, m_denominator{ denominator }
// 	{
// 		// 我们把 reduce() 放在构造函数中，确保产生的分数都会被约分！
// 		// 由于所有重载运算符都会创建新的 Fraction，可以保证这里一定会被调用
// 		reduce();
// 	}
//
// 	void reduce()
// 	{
// 		int gcd{ std::gcd(m_numerator, m_denominator) };
// 		if (gcd) // 确保不会尝试除以 0
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
// 	return Fraction { f1 * value };
// }
//
// int main()
// {
// 	Fraction f1{ 2, 5 };
// 	f1.print();
//
// 	Fraction f2{ 3, 8 };
// 	f2.print();
//
// 	Fraction f3{ f1 * f2 };
// 	f3.print();
//
// 	Fraction f4{ f1 * 2 };
// 	f4.print();
//
// 	Fraction f5{ 2 * f2 };
// 	f5.print();
//
// 	Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
// 	f6.print();
//
// 	Fraction f7{ 0, 6 };
// 	f7.print();
//
// 	return 0;
// }

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
	Cents(int cents) : m_cents{ cents } { }

	// 声明一个友元函数
	friend Cents operator+(const Cents& c1, const Cents& c2);

	int getCents() const { return m_cents; }
};

// 注: 这个函数不是成员函数
Cents operator+(const Cents& c1, const Cents& c2)
{
	// 可以直接访问m_cents，因为本函数是 Cents 的友元函数
	// 返回 int，触发Cents的构造函数
	return c1.m_cents + c2.m_cents;
}

int main()
{
	Cents cents1{ 6 };
	Cents cents2{ 8 };
	Cents centsSum{ cents1 + cents2 };
	std::cout << "I have " << centsSum.getCents() << " cents.\n";

	return 0;
}
