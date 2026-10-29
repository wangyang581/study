// ==========================================================================
// 8.3 Constexpr if语句
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第八章 控制流与错误处理
// 原文: https://www.studycpp.cn/basic/chapter8/constexpr-if/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "08.03-constexpr-if.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · Constexpr if语句（C++17）
//   · 现代编译器，与语句常量条件表达式的if语句（C++17）

// ==========================================================================
// 教程正文
// ==========================================================================

// 通常，if语句的条件在运行时求值。
//
// 然而，考虑条件是常量表达式的情况，例如在下面的示例中：

// [代码 1]
// #include <iostream>
//
// int main()
// {
// 	constexpr double gravity{ 9.8 };
//
// 	// 提醒: 低精度的浮点数常量可以直接比较是否相等
// 	if (gravity == 9.8) // 常量表达式，结果永远为true
// 		std::cout << "Gravity is normal.\n";   // 永远会执行
// 	else
// 		std::cout << "We are not on Earth.\n"; // 不会执行到
//
// 	return 0;
// }

// 由于gravity是constexpr，并用值9.8初始化，因此条件gravity==9.8的计算结果必须
// 为true。因此，else语句将永远不会执行。
//
// 在运行时计算constexpr条件表达式是浪费的（因为结果永远不会变化）。将代码编译
// 为永远无法执行的可执行文件也是浪费的。
//

// ―――― Constexpr if语句（C++17） ――――

// C++17引入了constexpr if语句，该语句要求条件必须是常量表达式。constexpr if语
// 句的条件表达式会在编译时求值。
//
// 如果constexpr条件的计算结果为true，则整个If-else将替换为true语句。如果
// constexpr条件的计算结果为false，则整个If-else将替换为false语句（如果存在
// else）或直接删除（如果没有else）。
//
// constexpr if语句的用法如下：

// [代码 2]
// #include <iostream>
//
// int main()
// {
// 	constexpr double gravity{ 9.8 };
//
// 	if constexpr (gravity == 9.8) // 现在使用 constexpr if
// 		std::cout << "Gravity is normal.\n";
// 	else
// 		std::cout << "We are not on Earth.\n";
//
// 	return 0;
// }

// 编译上述代码时，编译器将在编译时计算条件表达式，确认它始终为true，并仅保留
// 单个语句std::cout « “Gravity is normal.\n”;。
//
// 换句话说，它将编译以下内容：

// [代码 3]
// int main()
// {
// 	std::cout << "Gravity is normal.\n";
//
// 	return 0;
// }

// 最佳实践
//
// 当条件表达式是常量表达式时，优先使用constexpr if语句。
//

// ―――― 现代编译器，与语句常量条件表达式的if语句（C++17） ――――

// 出于优化目的，现代编译器通常会把具有常量条件的非constexpr-if语句当作
// constexpr-if语句处理。然而，这并不意味着编译器一定会这样做。
//
// 遇到具有常量条件的非constexpr-if语句时，编译器可能会发出警告，建议您改用
// constexpr-if语句。这样可以确保条件在编译时求值（即使禁用了编译优化）。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
	constexpr double gravity{ 9.8 };

	// 提醒: 低精度的浮点数常量可以直接比较是否相等
	if (gravity == 9.8) // 常量表达式，结果永远为true
		std::cout << "Gravity is normal.\n";   // 永远会执行
	else
		std::cout << "We are not on Earth.\n"; // 不会执行到

	return 0;
}
