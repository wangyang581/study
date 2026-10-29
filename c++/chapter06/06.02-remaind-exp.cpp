// ==========================================================================
// 6.2 余数和指数
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第六章 运算符
// 原文: https://www.studycpp.cn/basic/chapter6/remaind-exp/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "06.02-remaind-exp.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 余数运算符（operator%）
//   · 带负数的余数
//   · 指数运算符
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 余数运算符（operator%） ――――

// 余数运算符（通常也称为模运算符）是在进行整数除法后返回余数的运算符。例如，
// 7/4=1余数3。因此，7%4=3。另一个例子是，25/7=3余数4，因此25%7=4。余数运算符
// 仅适用于整数操作数。
//
// 这对于测试一个数能否被另一个数整除（即除法之后没有余数）非常有用：如果 x %
// y的计算结果为0，则我们知道x可以被y整除。

// [代码 1]
// #include <iostream>
//
// int main()
// {
// 	std::cout << "Enter an integer: ";
// 	int x{};
// 	std::cin >> x;
//
// 	std::cout << "Enter another integer: ";
// 	int y{};
// 	std::cin >> y;
//
// 	std::cout << "The remainder is: " << x % y << '\n';
//
// 	if ((x % y) == 0)
// 		std::cout << x << " is evenly divisible by " << y << '\n';
// 	else
// 		std::cout << x << " is not evenly divisible by " << y << '\n';
//
// 	return 0;
// }

// 下面是该程序的几个运行结果：

// [文本/输出]
// Enter an integer: 6
// Enter another integer: 3
// The remainder is: 0
// 6 is evenly divisible by 3


// [文本/输出]
// Enter an integer: 6
// Enter another integer: 4
// The remainder is: 2
// 6 is not evenly divisible by 4

// 现在，让我们尝试一个第二个数字大于第一个数字的示例：

// [文本/输出]
// Enter an integer: 2
// Enter another integer: 4
// The remainder is: 2
// 2 is not evenly divisible by 4

// 当第二个数字大于第一个数字时，第一个数字本身就是余数。
//

// ―――― 带负数的余数 ――――

// 余数运算符也可以处理负操作数。 x % y总是返回带x符号的结果。
//
// 运行上述程序：

// [文本/输出]
// Enter an integer: -6
// Enter another integer: 4
// The remainder is: -2
// -6 is not evenly divisible by 4


// [文本/输出]
// Enter an integer: 6
// Enter another integer: -4
// The remainder is: 2
// 6 is not evenly divisible by -4

// 在这两种情况下，可以看到余数取第一个操作数的符号。
//
// 当第一个操作数可能为负时，必须注意余数也可能为负。例如，您可能会这样编写一
// 个判断数字是否为奇数的函数：

// [代码 2]
// bool isOdd(int x)
// {
//     return (x % 2) == 1; // 当x是 -5 时判断错误
// }

// 然而，当x是负奇数时，这将判断错误，例如-5，因为-5%2是-1，而-1!=1
//
// 因此，如果要比较余数运算的结果，最好与0进行比较，因为0没有正数/负数问题：

// [代码 3]
// bool isOdd(int x)
// {
//     return (x % 2) != 0; // 或者可以写成 return (x % 2)
// }

// 术语
//
// 尽管运算符%通常被称为”模”或”取模”运算符，但这可能会令人困惑，因为数学中的取
// 模运算，在一个（且仅一个）操作数为负数时，产生的结果与C++中的运算符%不同。
//
// 例如，在数学中： -21模4 = 3 -21余数4 = -1
//
// 因此，我们认为“余数”这个名称比“模”更准确地表示运算符%。
//
// 最佳实践
//
// 如果可能，最好将余数运算符（operator%）的结果与0进行比较。
//

// ―――― 指数运算符 ――――

// 您会注意到^运算符（在数学中通常用于表示指数）是C++中的按位异或运算。C++不包
// 含指数运算符。
//
// 要在C++中执行指数，请 #include 标头，并使用 pow() 函数：

// [代码 4]
// #include <cmath>
//
// double x{ std::pow(3.0, 4.0) }; // 3的4次方

// 注意，函数pow() 的参数（和返回值）是double类型。由于浮点数的舍入误差，pow()
// 的结果可能不精确（即使传递的是整数）。
//
// 如果要进行整数求幂，最好使用自己的函数来完成。以下函数实现整数求幂（使用非
// 直观的“平方求幂”算法以提高效率）：

// [代码 5]
// #include <cassert> // for assert
// #include <cstdint> // for std::int64_t
// #include <iostream>
//
// // note: exp 必须是非负整数
// // note: 不执行越界检查
// constexpr std::int64_t powint(std::int64_t base, int exp)
// {
// 	assert(exp >= 0 && "powint: exp parameter has negative value");
//
// 	// 处理 base 为 0 的情况
// 	if (base == 0)
// 		return (exp == 0) ? 1 : 0;
//
// 	std::int64_t result{ 1 };
// 	while (exp > 0)
// 	{
// 		if (exp & 1)  // 如果exp 为奇数
// 			result *= base;
// 		exp /= 2;
// 		base *= base;
// 	}
//
// 	return result;
// }
//
// int main()
// {
// 	std::cout << powint(7, 12) << '\n'; // 7 的 12 次方
//
// 	return 0;
// }

// 结果：
//
// 如果您不理解该函数的工作原理，请不要担心——您不需要理解它才能调用它。
// constexpr标记允许编译器在编译时计算该函数。
//
// 下面是上面检查溢出的指数函数的更安全版本：

// [代码 6]
// #include <cassert> // for assert
// #include <cstdint> // for std::int64_t
// #include <iostream>
// #include <limits> // for std::numeric_limits
//
// // 一个更安全(但是稍慢) 的检查溢出的版本
// // note: exp 必须是非负整数
// // 如果发生越界，返回 std::numeric_limits<std::int64_t>::max()
// constexpr std::int64_t powint_safe(std::int64_t base, int exp)
// {
//     assert(exp >= 0 && "powint_safe: exp parameter has negative value");
//
//     // 处理 base 为 0 的情况
//     if (base == 0)
//         return (exp == 0) ? 1 : 0;
//
//     std::int64_t result { 1 };
//
//     // 为了确保越界更简单，将base调转为正数
//     // 在返回结果时，再补上符号
//     bool negativeResult{ false };
//
//     if (base < 0)
//     {
//         base = -base;
//         negativeResult = (exp & 1);
//     }
//
//     while (exp > 0)
//     {
//         if (exp & 1) // 如果exp 为奇数
//         {
//             // 检查结果是否会溢出
//             if (result > std::numeric_limits<std::int64_t>::max() / base)
//             {
//                 std::cerr << "powint_safe(): result overflowed\n";
//                 return std::numeric_limits<std::int64_t>::max();
//             }
//
//             result *= base;
//         }
//
//         exp /= 2;
//
//         // 处理完成
//         if (exp <= 0)
//             break;
//
//         // 需要继续迭代，则继续执行检查
//
//         // 检查结果是否会溢出
//         if (base > std::numeric_limits<std::int64_t>::max() / base)
//         {
//             std::cerr << "powint_safe(): base overflowed\n";
//             return std::numeric_limits<std::int64_t>::max();
//         }
//
//         base *= base;
//     }
//
//     if (negativeResult)
//         return -result;
//
//     return result;
// }

// 警告
//
// 在绝大多数情况下，整数求幂将溢出整数类型。这可能就是为什么这样的函数最初没
// 有包含在标准库中。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 下面这个表达式的求值结果是什么？`6 + 5 * 4 % 3`

// 【答案 · 查看答案】
// 因为`*`和`%`的优先级高于`+`，所以`+`最后求值。我们可以把表达式改写成6 + (5
// * 4 % 3)。运算符`*`和`%`的优先级相同，因此需要看结合性来决定求值顺序。`*`和
// `%`都是左结合的，所以先计算左边的运算符。表达式可以进一步改写成：6 + ((5 *
// 4) % 3)。
//
// 6 + ((5 * 4) % 3) = 6 + (20 % 3) = 6 + 2 = 8

// ▼ 问题 2
// 编写一个程序，要求用户输入一个整数，然后告诉用户这个数字是偶数还是奇数。编
// 写一个名为`isEven()`的constexpr函数：传入的整数是偶数时返回true，否则返回
// false。使用取余运算符判断整数形参是否为偶数。请确保`isEven()`对正数和负数都
// 能正确工作。

// 【答案 · 显示提示】
// 这个程序可能需要用到if语句和比较运算符（==）。如果需要复习做法，请回看「4.8
// 布尔值（Boolean）」。
//
// 程序的输出应与下面一致：

// [文本/输出]
// Enter an integer: 5
// 5 is odd


// 【答案 · 查看答案】

// [代码 7]
// #include <iostream>
//
// constexpr bool isEven(int x)
// {
//     // 如果 x % 2 == 0，说明2能整除这个数，也就是它一定是偶数
//     return (x % 2) == 0;
// }
//
// int main()
// {
//     std::cout << "Enter an integer: ";
//     int x{};
//     std::cin >> x;
//
//     if (isEven(x))
//         std::cout << x << " is even\n";
//     else
//         std::cout << x << " is odd\n";
//
//     return 0;
// }

// 注意：你可能会想把`isEven()`写成这样：

// [代码 8]
// constexpr bool isEven(int x)
// {
//     if ((x % 2) == 0)
//         return true;
//     else
//         return false;
// }

// 这样写虽然能工作，但比需要的复杂。我们来看看如何简化它。首先，把if语句的条
// 件单独取出来，赋给一个布尔变量：

// [代码 9]
// constexpr bool isEven(int x)
// {
//     bool isEven = (x % 2) == 0;
//     if (isEven) // isEven 为 true
//         return true;
//     else // isEven 为 false
//         return false;
// }

// 现在注意到，上面这个if语句本质上是在说「如果isEven为true就返回true，否则如
// 果isEven为false就返回false」。既然如此，直接返回isEven就可以了：

// [代码 10]
// constexpr bool isEven(int x)
// {
//     bool isEven = (x % 2) == 0;
//     return isEven;
// }

// 而在当前情况下，变量isEven只用了一次，所以干脆把这个变量去掉：

// [代码 11]
// constexpr bool isEven(int x)
// {
//     return (x % 2) == 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
	std::cout << "Enter an integer: ";
	int x{};
	std::cin >> x;

	std::cout << "Enter another integer: ";
	int y{};
	std::cin >> y;

	std::cout << "The remainder is: " << x % y << '\n';

	if ((x % y) == 0)
		std::cout << x << " is evenly divisible by " << y << '\n';
	else
		std::cout << x << " is not evenly divisible by " << y << '\n';

	return 0;
}
