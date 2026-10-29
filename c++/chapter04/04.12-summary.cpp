// ==========================================================================
// 4.12 第4章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第四章 基本数据类型
// 原文: https://www.studycpp.cn/basic/chapter4/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "04.12-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 章节回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 章节回顾 ――――

// 存储器的最小单位是二进制数字，也称为比特。可以直接寻址（访问）的最小内存单
// 位是字节。现代标准规定一个字节等于8位。
//
// 数据类型告诉编译器如何以某种有意义的方式解释内存的内容。
//
// C++支持许多基本数据类型，包括浮点数、整数、布尔值、字符、空指针和void。
//
// void用于表示没有类型。它主要用于指示函数不返回值。
//
// 不同的类型占用不同大小的内存，且使用的内存量可能因机器而异。
//
// sizeof运算符可用于返回类型的大小（以字节为单位）。
//
// 有符号整数用于保存正整数、负整数以及0。特定数据类型可以保存的值的集合称为其
// 范围。使用整数时，请注意溢出和整数除法的问题。
//
// 无符号整数只能保存正数（和0），通常应避免使用，除非您需要进行位操作。
//
// 固定宽度整数是具有确定大小的整数，但它们可能并非在所有体系结构上都存在。快
// 速整数和至小整数分别是至少具有某种大小的最快和最小的整数类型。通常应避免使
// 用std::int8_t和std::uint8_t，因为它们的行为更倾向于像字符而非整数。
//
// size_t是一种无符号整数类型，用于表示对象的大小或长度。
//
// 科学记数法是一种书写冗长数字的简写方式。C++支持科学记数法和浮点数。有效位中
// 的数字（e之前的部分）称为有效数字。
//
// 浮点数是一组用于保存实数（包括带有小数部分的实数）的类型。数字的精度定义了
// 它可以表示多少个有效数字而不丢失信息。当浮点数中存储的有效数字超出了其精度
// 所能保持的范围时，就可能发生舍入错误。舍入错误始终可能发生，即使是像0.1这样
// 简单的数字也不例外。因此，不应该直接比较浮点数。
//
// 布尔类型用于存储true或false值。
//
// if语句允许我们在某些条件为真时执行一行或多行代码。if语句的条件表达式会被解
// 释为布尔值。当if语句条件的求值结果为false时，可以使用else语句来执行替代语句。
//
// char用于存储以ASCII字符形式解释的值。使用字符时，请注意不要混淆ASCII码值和
// 数字。将字符作为整数值打印需要使用static_cast。
//
// 尖括号 <> 在C++中通常用于表示需要参数化类型的场合。它与static_cast配合使用，
// 用于指定参数应转换为哪种数据类型（例如，static_cast<int>(x) 将x的值作为int
// 返回）。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 为下列各种情形中的变量挑选合适的数据类型。尽量选得具体一些。如果答案是整数，
// 在大小不重要时选`int`，在需要根据取值范围选择时选具体的定宽整数类型（例如
// `std::int16_t`）。
//
// a) 用户的年龄（以年为单位）（假设类型的大小不重要）

// 【答案 · 查看答案】
// int
//
// b) 用户是否希望程序检查更新

// 【答案 · 查看答案】
// bool
//
// c) 圆周率（3.14159265）

// 【答案 · 查看答案】
// double
//
// d) 一本教科书的页数（假设大小不重要）

// 【答案 · 查看答案】
// 书一般不会超过32767页，所以用`int`就可以了。
//
// e) 沙发长度的英尺数，保留2位小数（假设大小重要）

// 【答案 · 查看答案】
// float
//
// f) 从出生到现在你一共眨眼多少次（注意：答案以百万计）

// 【答案 · 查看答案】
// std::int32_t
//
// g) 用户通过字母从菜单中挑选一个选项

// 【答案 · 查看答案】
// char
//
// h) 某人的出生年份（假设大小重要）

// 【答案 · 查看答案】
// std::int16_t。可以用正数表示公元后的出生年份，用负数表示公元前。

// ▼ 问题 2
// 作者提示
//
// 从这里开始，习题会变得更有挑战性。这些要求编写程序的习题，目的是检验你能否
// 把各节课中介绍的多个概念综合起来。请做好在这些题目上花些时间的准备。如果你
// 是编程新手，不必期望自己能立刻写出答案。
//
// 请记住，这里的目的是帮你找出自己掌握了什么，以及哪些概念可能还需要多花些时
// 间。如果你觉得有点吃力，这很正常。
//
// 这里有一些建议：
// - 不要试图一次写出完整答案。先写一个函数，测试它是否按预期工作，然后再继续。
// - 用调试器帮你找出问题出在哪里。
// - 回头复习本章前面各节课的习题答案，它们往往包含类似的概念。
//
// 如果确实卡住了，可以去看答案，但务必花时间弄懂每一行代码的含义再继续。只要
// 能理解这些概念，是自己做出来的还是看了答案，其实没那么重要。
//
// 请编写下面这个程序：要求用户输入2个浮点数（使用double）。然后要求用户输入下
// 列数学符号之一：+、-、* 或 /。程序对用户输入的两个数进行计算并打印结果。如
// 果用户输入了无效的符号，程序应当什么都不打印。
//
// 程序的运行示例：

// [文本/输出]
// Enter a double value: 6.2
// Enter a double value: 5
// Enter +, -, *, or /: *
// 6.2 * 5 is 31


// 【答案 · 显示提示】
// 编写三个函数：一个用于获取double值，一个用于获取运算符符号，一个用于计算并
// 打印结果。

// 【答案 · 显示提示】
// 使用if语句和`operator==`，把用户输入与想要比较的运算符符号进行比较。

// 【答案 · 显示提示】
// 如果用户输入的不是受支持的运算，可以考虑使用提前返回（见「4.9 if语句简介」）
// 。

// 【答案 · 查看答案】

// [代码 1]
// #include <iostream>
//
// double getDouble()
// {
//     std::cout << "Enter a double value: ";
//     double x{};
//     std::cin >> x;
//     return x;
// }
//
// char getOperator()
// {
//     std::cout << "Enter +, -, *, or /: ";
//     char operation{};
//     std::cin >> operation;
//     return operation;
// }
//
// void printResult(double x, char operation, double y)
// {
//     double result{};
//
//     if (operation == '+')
//         result = x + y;
//     else if (operation == '-')
//         result = x - y;
//     else if (operation == '*')
//         result = x * y;
//     else if (operation == '/')
//         result = x / y;
//     else        // 如果用户输入的不是受支持的运算
//         return; // 提前返回
//
//     std::cout << x << ' ' << operation << ' ' << y << " is " << result << '\n';
// }
//
// int main()
// {
//     double x { getDouble() };
//     double y { getDouble() };
//
//     char operation { getOperator() };
//
//     printResult(x, operation, y);
//
//     return 0;
// }


// ▼ 问题 3
// 附加题：这道题稍微难一些。
//
// 编写一个短程序，模拟小球从塔顶落下的过程。首先要求用户输入塔的高度（以米为
// 单位）。假设重力正常（9.8 m/s²），且小球的初速度为0（开始时小球是静止的）。
// 让程序输出第0、1、2、3、4、5秒时小球离地面的高度。小球不应该落到地面以下（
// 高度0）。
//
// 用一个函数计算小球在x秒后的高度。该函数可以用下面的公式计算小球在x秒后下落
// 了多少距离：下落距离 = 重力常数 * x秒² / 2
//
// 预期的输出：

// [文本/输出]
// Enter the height of the tower in meters: 100
// At 0 seconds, the ball is at height: 100 meters
// At 1 seconds, the ball is at height: 95.1 meters
// At 2 seconds, the ball is at height: 80.4 meters
// At 3 seconds, the ball is at height: 55.9 meters
// At 4 seconds, the ball is at height: 21.6 meters
// At 5 seconds, the ball is on the ground.

// 注意：取决于塔的高度，小球可能不会在5秒内落到地面——这没关系。等学完循环后，
// 我们会改进这个程序。 注意：在C++中`^`符号并不表示乘方。请用乘法而不是乘方来
// 实现这个公式。 注意：记得对double使用double字面值，例如写`2.0`而不是`2`。

// 【答案 · 查看答案】

// [代码 2]
// #include <iostream>
//
// // 从用户处获取塔的高度并返回
// double getTowerHeight()
// {
// 	std::cout << "Enter the height of the tower in meters: ";
// 	double towerHeight{};
// 	std::cin >> towerHeight;
// 	return towerHeight;
// }
//
// // 返回小球在"seconds"秒后的高度
// double calculateBallHeight(double towerHeight, int seconds)
// {
// 	double gravity { 9.8 };
//
// 	// 使用公式：s = (u * t) + (a * t^2) / 2
// 	// 这里 u（初速度）= 0，因此 (u * t) = 0
// 	double fallDistance { gravity * (seconds * seconds) / 2.0 };
// 	double ballHeight { towerHeight - fallDistance };
//
// 	// 如果小球会落到地面以下，就把它放在地面上
// 	if (ballHeight < 0.0)
// 		return 0.0;
//
// 	return ballHeight;
// }
//
// // 打印小球离地面的高度
// void printBallHeight(double ballHeight, int seconds)
// {
// 	if (ballHeight > 0.0)
// 		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
// 	else
// 		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
// }
//
// // 计算小球当前的高度并打印出来
// // 这是一个辅助函数，让调用更方便
// void calculateAndPrintBallHeight(double towerHeight, int seconds)
// {
// 	double ballHeight{ calculateBallHeight(towerHeight, seconds) };
// 	printBallHeight(ballHeight, seconds);
// }
//
// int main()
// {
// 	double towerHeight{ getTowerHeight() };
//
// 	calculateAndPrintBallHeight(towerHeight, 0);
// 	calculateAndPrintBallHeight(towerHeight, 1);
// 	calculateAndPrintBallHeight(towerHeight, 2);
// 	calculateAndPrintBallHeight(towerHeight, 3);
// 	calculateAndPrintBallHeight(towerHeight, 4);
// 	calculateAndPrintBallHeight(towerHeight, 5);
//
// 	return 0;
// }

// 这个程序有3项任务：获取塔的初始高度、计算小球当前的高度、打印小球当前的高度。
// 按照「函数只做一件事」的最佳实践，我们为每项任务各写一个函数。
// `calculateAndPrintBallHeight()`是一个辅助函数，使得在`main()`中调用时，计算
// 和打印高度的代码更易读。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

double getDouble()
{
    std::cout << "Enter a double value: ";
    double x{};
    std::cin >> x;
    return x;
}

char getOperator()
{
    std::cout << "Enter +, -, *, or /: ";
    char operation{};
    std::cin >> operation;
    return operation;
}

void printResult(double x, char operation, double y)
{
    double result{};

    if (operation == '+')
        result = x + y;
    else if (operation == '-')
        result = x - y;
    else if (operation == '*')
        result = x * y;
    else if (operation == '/')
        result = x / y;
    else        // 如果用户输入的不是受支持的运算
        return; // 提前返回

    std::cout << x << ' ' << operation << ' ' << y << " is " << result << '\n';
}

int main()
{
    double x { getDouble() };
    double y { getDouble() };

    char operation { getOperator() };

    printResult(x, operation, y);

    return 0;
}
