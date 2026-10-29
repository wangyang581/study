// ==========================================================================
// 27.10 第27章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十七章 异常
// 原文: https://www.studycpp.cn/basic/chapter27/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "27.10-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 异常处理提供了一种机制，可以将错误或其他异常情况的处理与代码的常规控制流解
// 耦。这允许我们在更合适的时间、以更合适的方式处理错误，减轻了返回码导致的许
// 多混乱。
//
// throw语句用于引发异常。try块会查找其中编写或调用的代码所引发的异常。这些异
// 常会被路由到catch块，catch块捕获特定类型的异常（如果匹配）并处理它们。默认
// 情况下，被捕获的异常会被视为已处理。
//
// 异常会被立即处理。如果引发异常，控制流会跳到最近的外围try块，查找可以处理该
// 异常的catch处理程序。如果找到匹配的try/catch，则调用栈会展开到对应catch块的
// 起点，并从匹配catch块的开头恢复执行。如果找不到try块或没有匹配的catch块，程
// 序将调用std::terminate，并以未处理异常错误结束执行。
//
// 可以抛出任何数据类型的异常，包括类。
//
// catch块可以配置为捕获特定数据类型的异常，也可以使用省略号（…）设置为捕获所
// 有异常。捕获基类引用的catch块也会捕获派生类异常。标准库抛出的所有异常都派生
// 自std::exception类（位于exception头文件中），因此通过引用捕获std::exception
// 将捕获所有标准库异常。what()成员函数可用于确定引发了哪种类型的
// std::exception。
//
// 在catch块内部，可以抛出新的异常。只使用关键字throw，就可以从catch块重新抛出
// 当前捕获的异常。不要使用捕获到的异常变量重新抛出异常，否则可能导致对象切片。
//
// 函数try块提供了一种捕获函数体或关联成员初始化列表中任何异常的方法。它通常只
// 与派生类构造函数一起使用。
//
// 永远不要从析构函数中抛出异常。
//
// noexcept异常说明符可用于表示函数不会抛出异常或不会失败。
//
// 如果对象具有noexcept移动构造函数，则std::move_if_noexcept会返回可移动的右值，
// 否则会返回可复制的左值。我们可以将noexcept说明符与std::move_if_noexcept结合
// 使用，在具备强异常保证时使用移动语义（否则使用复制语义）。
//
// 最后，异常处理确实有成本。在大多数情况下，使用异常的代码会运行得稍慢一些，
// 而且处理异常的成本非常高。您应该只使用异常来处理异常情况，而不是用于正常的
// 错误处理场景（例如，判定用户的无效输入）。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 编写一个Fraction类，其构造函数接受一个分子和一个分母。如果用户传入的分母为0，
// 就抛出一个std::runtime_error类型的异常（该类型包含在stdexcept头文件中）。在
// 你的main程序中，要求用户输入两个整数。如果Fraction是有效的，就打印这个分数；
// 如果Fraction无效，就捕获std::exception，并告诉用户输入的分数无效。
//
// 下面是程序某次运行时的输出：

// [文本/输出]
// Enter the numerator: 5
// Enter the denominator: 0
// Invalid denominator


// 【答案 · 查看答案】

// [代码 1]
// #include <iostream>
// #include <stdexcept> // 用于 std::runtime_error
// #include <exception> // 用于 std::exception
//
// class Fraction
// {
// private:
// 	int m_numerator = 0;
// 	int m_denominator = 1;
//
// public:
// 	Fraction(int numerator = 0, int denominator = 1)
// 		: m_numerator{ numerator }
// 		, m_denominator{ denominator }
// 	{
// 		if (m_denominator == 0)
// 			throw std::runtime_error("Invalid denominator");
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
//
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
// 	std::cout << "Enter the numerator: ";
// 	int numerator{};
// 	std::cin >> numerator;
//
// 	std::cout << "Enter the denominator: ";
// 	int denominator{};
// 	std::cin >> denominator;
//
// 	try
// 	{
// 		Fraction f{ numerator, denominator };
// 		std::cout << "Your fraction is: " << f << '\n';
// 	}
// 	catch (const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}
//
// 	return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <stdexcept> // 用于 std::runtime_error
#include <exception> // 用于 std::exception

class Fraction
{
private:
	int m_numerator = 0;
	int m_denominator = 1;

public:
	Fraction(int numerator = 0, int denominator = 1)
		: m_numerator{ numerator }
		, m_denominator{ denominator }
	{
		if (m_denominator == 0)
			throw std::runtime_error("Invalid denominator");
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);

};

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
}

int main()
{
	std::cout << "Enter the numerator: ";
	int numerator{};
	std::cin >> numerator;

	std::cout << "Enter the denominator: ";
	int denominator{};
	std::cin >> denominator;

	try
	{
		Fraction f{ numerator, denominator };
		std::cout << "Your fraction is: " << f << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
