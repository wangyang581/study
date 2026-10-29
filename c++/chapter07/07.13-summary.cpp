// ==========================================================================
// 7.13 第七章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第七章 作用域与编译链接
// 原文: https://www.studycpp.cn/basic/chapter7/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "07.13-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 快速审阅
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 快速审阅 ――――

// 我们在这一章中涵盖了许多内容。
//
// 复合语句或块是一组零个或多个语句，编译器将其视为单个语句。块以{符号开始，以}
// 符号结束，要执行的语句放在两者之间。块可以在允许单个语句的任何地方使用。块
// 的末尾不需要分号。块通常与if语句一起使用，以执行多个语句。
//
// 用户定义的命名空间是您为自己的声明定义的命名空间。C++（如全局命名空间）或库
// （如命名空间std）提供的命名空间不被视为用户定义的命名空间。
//
// 可以通过域解析操作符（::）访问命名空间中的声明。域解析操作符告诉编译器，应
// 该在左侧操作数的范围内查找右侧操作数指定的标识符。如果未提供左侧操作数，则
// 假定为全局命名空间。
//
// 局部变量是在函数中定义的变量（包括函数参数）。局部变量具有块作用域，这意味
// 着它们从定义点到定义它们的块的末尾都在作用域内。局部变量具有自动存储期，这
// 意味着它们在定义点创建，在定义它们的块末尾销毁。
//
// 在嵌套块中声明的名称可以隐藏外部块中同名的变量。应该避免这样做。
//
// 全局变量是在函数外部定义的变量。全局变量具有文件范围，这意味着它们从声明点
// 到声明它们的文件末尾都是可见的。全局变量具有静态存储期，这意味着它们在程序
// 启动时创建，在程序结束时销毁。
//
// 标识符的链接属性确定该名称的其他声明是否引用同一对象。局部变量没有链接。具
// 有内部链接的标识符可以在单个文件中看到和使用，但不能从其他文件访问。具有外
// 部链接的标识符既可以从定义它们的文件中看到，也可以从其他代码文件中使用（通
// 过前向声明）。
//
// 尽可能避免非常量的全局变量。Const 全局变量通常被认为是可以接受的。如果编译
// 器支持C++17，请将inline用于全局常量。
//
// 可以通过static关键字将局部变量指定为静态存储期。
//
// 限定名是包含关联作用域的名称（例如，std::string）。非限定名是不包括作用域限
// 定符的名称。
//
// using语句（包括using声明和using指令）可以用于避免必须用显式命名空间限定标识
// 符。using声明允许我们使用非限定名称（没有域名）作为限定名称的别名。using指
// 令将命名空间中的所有标识符导入using指令的范围。通常应避免这两种情况。
//
// 内联函数最初的设计目的是请求编译器用函数代码的内联扩展替换函数调用。现在不
// 需要为此目的使用inline关键字，因为编译器通常会自动完成。在现代C++中，inline
// 关键字用于将函数从单个定义规则中排除，从而允许将其定义导入到多个代码文件中。
// 内联函数通常在头文件中定义，它们可以被包含在任何需要它们的代码文件中。
//
// 最后，C++支持未命名的命名空间，它隐式地将命名空间的所有内容视为具有内部链接。
// C++还支持内联命名空间，这为命名空间提供了一些原始版本控制功能。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 修正下面这个程序：

// [代码 1]
// #include <iostream>
//
// int main()
// {
// 	std::cout << "Enter a positive number: ";
// 	int num{};
// 	std::cin >> num;
//
// 	if (num < 0)
// 		std::cout << "Negative number entered.  Making positive.\n";
// 		num = -num;
//
// 	std::cout << "You entered: " << num;
//
// 	return 0;
// }


// 【答案 · 查看答案】

// [代码 2]
// #include <iostream>
//
// int main()
// {
// 	std::cout << "Enter a positive number: ";
// 	int num{};
// 	std::cin >> num;
//
// 	if (num < 0)
// 	{ // 这里需要一对花括号，使得 num < 0 时两条语句都会执行
// 		std::cout << "Negative number entered.  Making positive.\n";
// 		num = -num;
// 	}
//
// 	std::cout << "You entered: " << num;
//
// 	return 0;
// }


// ▼ 问题 2
// 编写一个名为 constants.h 的文件，使下面这个程序能够运行。如果你的编译器支持
// C++17，请使用inline constexpr变量；否则使用普通的constexpr变量。
// `maxClassSize`的值应当为`35`。
//
// main.cpp：

// [代码 3]
// #include "constants.h"
// #include <iostream>
//
// int main()
// {
// 	std::cout << "How many students are in your class? ";
// 	int students{};
// 	std::cin >> students;
//
// 	if (students > Constants::maxClassSize)
// 		std::cout << "There are too many students in this class";
// 	else
// 		std::cout << "This class isn't too large";
//
// 	return 0;
// }


// 【答案 · 查看答案】
// constants.h：

// [代码 4]
// #ifndef CONSTANTS_H
// #define CONSTANTS_H
//
// namespace Constants
// {
// 	inline constexpr int maxClassSize{ 35 }; // 如果不支持 C++17，请去掉 inline 关键字
// }
// #endif

// main.cpp：

// [代码 5]
// #include "constants.h"
// #include <iostream>
//
// int main()
// {
// 	std::cout << "How many students are in your class? ";
// 	int students{};
// 	std::cin >> students;
//
// 	if (students > Constants::maxClassSize)
// 		std::cout << "There are too many students in this class";
// 	else
// 		std::cout << "This class isn't too large";
//
// 	return 0;
// }


// ▼ 问题 3
// 编写一个函数`int accumulate(int x)`。该函数应当返回迄今为止传入该函数的所有
// `x`值之和。

// 【答案 · 显示提示】
// 使用静态局部变量来保存累加和。
//
// 下面这个程序应当能够运行，并产生注释中给出的输出：

// [代码 6]
// #include <iostream>
//
// int main()
// {
//     std::cout << accumulate(4) << '\n'; // 打印 4
//     std::cout << accumulate(3) << '\n'; // 打印 7
//     std::cout << accumulate(2) << '\n'; // 打印 9
//     std::cout << accumulate(1) << '\n'; // 打印 10
//
//     return 0;
// }


// 【答案 · 查看答案】

// [代码 7]
// #include <iostream>
//
// int accumulate(int x)
// {
//     static int sum{ 0 }; // 在程序开始时把 sum 初始化为 0
//     sum += x;
//     return sum;
// }
//
// int main()
// {
//     std::cout << accumulate(4) << '\n'; // 打印 4
//     std::cout << accumulate(3) << '\n'; // 打印 7
//     std::cout << accumulate(2) << '\n'; // 打印 9
//     std::cout << accumulate(1) << '\n'; // 打印 10
//
//     return 0;
// }


// ▼ 问题 3b（附加题）
// 上面这个`accumulate()`函数有哪两个缺点？

// 【答案 · 查看答案】
// - 如果不重新启动程序，就没有常规的办法重置累加值。
// - 没有办法同时运行多个累加器。
//
// 对于高级读者
//
// 这两个缺点都可以通过使用函数对象（functors，见「21.9 重载括号运算符」）而不
// 是静态局部变量来解决。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
	std::cout << "Enter a positive number: ";
	int num{};
	std::cin >> num;

	if (num < 0)
		std::cout << "Negative number entered.  Making positive.\n";
		num = -num;

	std::cout << "You entered: " << num;

	return 0;
}
