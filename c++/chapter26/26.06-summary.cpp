// ==========================================================================
// 26.6 第26章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十六章 模板
// 原文: https://www.studycpp.cn/basic/chapter26/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "26.06-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 模板允许我们使用类型作为占位符来编写函数或类，从而用不同的类型实例化同一份
// 函数或类代码。
//
// 所有模板函数或类都必须以template参数声明开头，该声明会告诉编译器后面的函数
// 或类是模板。在模板参数声明中，可以指定模板类型参数或非类型参数。模板类型参
// 数只是占位符类型，通常命名为T、T1、T2，或其他单字母名称（例如S、U）。非类型
// 参数通常是整型，也可以是指向函数、类对象或成员函数的指针或引用。
//
// 拆分模板类定义和成员函数定义不像普通类那样简单——不能简单地将类的成员函数定
// 义放在.cpp文件中。通常最好将它们全部保存在头文件中，并将成员函数定义放在类
// 定义的下方。
//
// 当我们想要覆盖模板化函数或类在特定类型下的默认行为时，可以使用模板特化。如
// 果覆盖所有模板参数，则称为完全特化。类还支持部分特化，即只特化其中一部分模
// 板参数。函数不能部分特化。
//
// C++标准库中的许多类都使用模板，包括std::array和std::vector。模板通常用于实
// 现容器类，因此容器只需编写一次，就可以与任何合适的类型一起使用。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 有时把数据成对定义会很有用。编写一个名为Pair1的模板类，让用户只定义一个模板
// 类型，并把这个类型同时用于这一对中的两个值。下面这个函数应当能够工作：

// [代码 1]
// int main()
// {
// 	Pair1<int> p1 { 5, 8 };
// 	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
//
// 	const Pair1<double> p2 { 2.3, 4.5 };
// 	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
//
// 	return 0;
// }

// 并打印：

// [文本/输出]
// Pair: 5 8
// Pair: 2.3 4.5


// 【答案 · 查看答案】

// [代码 2]
// #include <iostream>
//
// template <typename T>
// class Pair1
// {
// private:
// 	T m_x {};
// 	T m_y {};
//
// public:
// 	Pair1(const T& x, const T& y)
// 		: m_x{ x }, m_y{ y }
// 	{
// 	}
//
// 	T& first() { return m_x; }
// 	T& second() { return m_y; }
// 	const T& first() const { return m_x; }
// 	const T& second() const { return m_y; }
// };
//
// int main()
// {
// 	Pair1<int> p1 { 5, 8 };
// 	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
//
// 	const Pair1<double> p2 { 2.3, 4.5 };
// 	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
//
// 	return 0;
// }


// ▼ 问题 2
// 编写一个Pair类，允许为这一对中的两个值分别指定不同的类型。
//
// 注意：我们给这个类取的名字与上一个不同，因为C++目前不允许「重载」仅在模板形
// 参个数或类型上不同的类。
//
// 下面这个程序应当能够工作：

// [代码 3]
// int main()
// {
// 	Pair<int, double> p1 { 5, 6.7 };
// 	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
//
// 	const Pair<double, int> p2 { 2.3, 4 };
// 	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
//
// 	return 0;
// }

// 并打印：

// [文本/输出]
// Pair: 5 6.7
// Pair: 2.3 4

// 提示：要定义使用两个不同类型的模板，请用逗号分隔模板形参声明中的两个类型。
// 更多信息参见「11.7 具有多个模板类型的函数模板」。

// 【答案 · 查看答案】

// [代码 4]
// #include <iostream>
//
// template <typename T, typename S>
// class Pair
// {
// private:
// 	T m_x;
// 	S m_y;
//
// public:
// 	Pair(const T& x, const S& y)
// 		: m_x{x}, m_y{y}
// 	{
// 	}
//
// 	T& first() { return m_x; }
// 	S& second() { return m_y; }
// 	const T& first() const { return m_x; }
// 	const S& second() const { return m_y; }
// };
//
// int main()
// {
// 	Pair<int, double> p1 { 5, 6.7 };
// 	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
//
// 	const Pair<double, int> p2 { 2.3, 4 };
// 	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
//
// 	return 0;
// }


// ▼ 问题 3
// 字符串-值对（string-value pair）是一种特殊的pair，其中第一个值总是字符串类
// 型，第二个值可以是任意类型。编写一个名为StringValuePair的模板类，它继承自一
// 个（以`std::string`作为第一个类型，并允许用户指定第二个类型的）偏特化Pair类。
//
// 下面这个程序应当能够运行：

// [代码 5]
// int main()
// {
// 	StringValuePair<int> svp { "Hello", 5 };
// 	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
//
// 	return 0;
// }

// 并打印：

// [文本/输出]
// Pair: Hello 5

// 提示：在StringValuePair的构造函数中调用Pair的构造函数时，不要忘记把模板形参
// 作为Pair类名的一部分写出来。

// 【答案 · 查看答案】

// [代码 6]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// template <typename T, typename S>
// class Pair
// {
// private:
// 	T m_x{};
// 	S m_y{};
//
// public:
// 	Pair(const T& x, const S& y)
// 		: m_x{ x }, m_y{ y }
// 	{
// 	}
//
// 	T& first() { return m_x; }
// 	S& second() { return m_y; }
// 	const T& first() const { return m_x; }
// 	const S& second() const { return m_y; }
// };
//
// template <typename S>
// class StringValuePair : public Pair<std::string, S>
// {
// public:
// 	StringValuePair(std::string_view key, const S& value)
//                 // std::string_view 不会隐式转换为 std::string，必须显式转换
// 		: Pair<std::string, S>{ static_cast<std::string>(key), value }
// 	{
// 	}
// };
//
// int main()
// {
// 	StringValuePair<int> svp{ "Hello", 5 };
// 	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
//
// 	return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

template <typename T>
class Pair1
{
private:
	T m_x {};
	T m_y {};

public:
	Pair1(const T& x, const T& y)
		: m_x{ x }, m_y{ y }
	{
	}

	T& first() { return m_x; }
	T& second() { return m_y; }
	const T& first() const { return m_x; }
	const T& second() const { return m_y; }
};

int main()
{
	Pair1<int> p1 { 5, 8 };
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2 { 2.3, 4.5 };
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

	return 0;
}
