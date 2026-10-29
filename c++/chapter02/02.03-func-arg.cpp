// ==========================================================================
// 2.3 函数参数简介
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二章 函数
// 原文: https://www.studycpp.cn/basic/chapter2/func-arg/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "02.03-func-arg.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 函数参数
//   · 参数如何工作
//   · 修复问题代码
//   · 使用函数的返回值作为参数
//   · 参数和返回值如何一起工作
//   · 更多示例
//   · 未使用的参数
//   · 结论
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 上一课中，我们学习了如何让函数将值返回给函数调用者。利用这个功能，我们在程
// 序中创建了模块化的getValueFromUser函数：

// [代码 1]
// #include <iostream>
//
// int getValueFromUser()
// {
//  	std::cout << "Enter an integer: ";
// 	int input{};
// 	std::cin >> input;
//
// 	return input;
// }
//
// int main()
// {
// 	int num { getValueFromUser() };
//
// 	std::cout << num << " doubled is: " << num * 2 << '\n';
//
// 	return 0;
// }

// 如何将输出的处理也封装到函数中？尝试如下操作：

// [代码 2]
// #include <iostream>
//
// int getValueFromUser()
// {
//  	std::cout << "Enter an integer: ";
// 	int input{};
// 	std::cin >> input;
//
// 	return input;
// }
//
// // 这个函数无法编译通过
// void printDouble()
// {
// 	std::cout << num << " doubled is: " << num * 2 << '\n';
// }
//
// int main()
// {
// 	int num { getValueFromUser() };
//
// 	printDouble();
//
// 	return 0;
// }

// 这无法编译通过，因为函数printDouble不认识标识符num。或者尝试在函数
// printDouble()中将num定义为变量：

// [代码 3]
// void printDouble()
// {
// 	int num{}; // 新增一行
// 	std::cout << num << " doubled is: " << num * 2 << '\n';
// }

// 虽然解决了编译器错误，但程序仍无法正常工作（始终打印”0 doubled is：0”）。问
// 题的核心是函数printDouble没有访问到用户输入的值。
//
// 我们需要将变量num的值传递给函数printDouble，以便printDouble在函数体中使用该
// 值。
//

// ―――― 函数参数 ――――

// 函数参数是函数头中定义的变量。函数参数的工作方式与函数内定义的变量几乎相同，
// 只有一点不同：它的初始值由函数调用方提供。
//
// 函数参数在函数头中定义，放在函数名后面的括号之间，多个参数用逗号分隔。
//
// 以下是具有不同数量参数的函数示例：

// [代码 4]
// // 本函数无参数
// // 不依赖调用函数的任何数据
// void doPrint()
// {
//     std::cout << "In doPrint()\n";
// }
//
// // 本函数有一个参数x
// // 调用函数需要提供一个值给x
// void printValue(int x)
// {
//     std::cout << x  << '\n';
// }
//
// // 本函数有两个参数，x与y
// // 调用函数需要提供两个值，分别给x与y
// int add(int x, int y)
// {
//     return x + y;
// }

// 参数是函数调用时从调用方传递给函数的值：

// [代码 5]
// doPrint(); // 没有参数
// printValue(6); // 参数是6
// add(2, 3); // 参数是2，3

// 注意，调用时多个参数由逗号分隔。
//

// ―――― 参数如何工作 ――――

// 调用函数时，所有参数被创建为变量，每个值都被复制到匹配的参数中。该过程称为
// 按值传递。
//
// 例如：

// [代码 6]
// #include <iostream>
//
// // 本函数有两个参数，x与y
// // 调用函数需要提供两个值，分别给x与y
// void printValues(int x, int y)
// {
//     std::cout << x << '\n';
//     std::cout << y << '\n';
// }
//
// int main()
// {
//     printValues(6, 7); // 函数调用，传递6，7，分别给x和y
//
//     return 0;
// }

// 用参数6和7调用函数printValues时，会创建printValues的参数x并初始化为值6，创
// 建printValues的参数y并初始化为值7。
//
// 运行结果输出：
//
// 注意，调用时传递的参数数量必须与函数参数的数量匹配，否则编译器将抛出错误。
// 传递给函数的参数可以是任何有效的表达式（因为参数传递的本质就是参数的初始化，
// 而初始值可以是任何合法表达式的计算结果）。
//

// ―――― 修复问题代码 ――――

// 现在来修复课程开始时演示的程序：

// [代码 7]
// #include <iostream>
//
// int getValueFromUser()
// {
//  	std::cout << "Enter an integer: ";
// 	int input{};
// 	std::cin >> input;
//
// 	return input;
// }
//
// void printDouble(int value) // 此函数有一个value参数
// {
// 	std::cout << value << " doubled is: " << value * 2 << '\n';
// }
//
// int main()
// {
// 	int num { getValueFromUser() };
//
// 	printDouble(num);
//
// 	return 0;
// }

// 该程序中，用户输入值初始化变量num。接着，调用函数printDouble，并将num的值复
// 制到函数printDouble的参数中。函数printDouble使用参数value的值。
//

// ―――― 使用函数的返回值作为参数 ――――

// 在上面的问题中，变量num仅使用了一次，只是将getValueFromUser的返回值传递给
// printDouble的调用参数。
//
// 将上述示例简化如下：

// [代码 8]
// #include <iostream>
//
// int getValueFromUser()
// {
//  	std::cout << "Enter an integer: ";
// 	int input{};
// 	std::cin >> input;
//
// 	return input;
// }
//
// void printDouble(int value)
// {
// 	std::cout << value << " doubled is: " << value * 2 << '\n';
// }
//
// int main()
// {
// 	printDouble(getValueFromUser());
//
// 	return 0;
// }

// 直接用函数getValueFromUser的返回值作为函数printDouble的参数！
//
// 尽管该程序更简洁（并且清楚地表明用户输入的值不会用于其他用途），但也会发现
// 这种”紧凑语法”较难阅读。使用上一个包含变量的版本也是完全可以的。
//

// ―――― 参数和返回值如何一起工作 ――――

// 利用参数和返回值，可以将数据作为输入传入函数，对其进行计算，并将结果值返回
// 给调用者。
//
// 以下是一个简单的函数示例，该函数将两个数字相加，并将结果返回给调用者：

// [代码 9]
// #include <iostream>
//
// // add() 使用2个整数作为输入，返回它们的和
// // x and y 的值由调用函数决定
// int add(int x, int y)
// {
//     return x + y;
// }
//
// // main 函数没有参数
// int main()
// {
//     std::cout << add(4, 5) << '\n'; // 4 和 5 被传递给add
//     return 0;
// }

// 执行从main顶部开始。当计算add(4，5)时，调用函数add，参数x用值4初始化，参数y
// 用值5初始化。
//
// 函数add中的return语句计算x+y以产生值9，将该值返回给main。并将值9发送到
// std::cout，在控制台打印。
//
// 输出：
// [图片] https://www.studycpp.cn/basic/chapter2/func-arg/ParametersReturn.webp
// 函数调用行为
//

// ―――― 更多示例 ――――

// 更多的函数调用：

// [代码 10]
// #include <iostream>
//
// int add(int x, int y)
// {
//     return x + y;
// }
//
// int multiply(int z, int w)
// {
//     return z * w;
// }
//
// int main()
// {
//     std::cout << add(4, 5) << '\n'; //  add() x=4, y=5, x+y=9
//     std::cout << add(1 + 2, 3 * 4) << '\n'; // add() x=3, y=12, x+y=15
//
//     int a{ 5 };
//     std::cout << add(a, a) << '\n'; // (5 + 5)
//
//     std::cout << add(1, multiply(2, 3)) << '\n'; // 1 + (2 * 3)
//     std::cout << add(1, add(2, 3)) << '\n'; // 1 + (2 + 3)
//
//     return 0;
// }

// 该程序生成输出：
//
// main函数中第一个语句很简单。
//
// 在第二条语句中，参数在传递之前会先进行求值。1+2的计算结果为3，因此3被复制到
// 参数x。3*4的结果是12，因此12被复制到参数y。add(3, 12)的结果为15。
//
// 下一对语句也相对简单：

// [代码 11]
//     int a{ 5 };
//     std::cout << add(a, a) << '\n'; // (5 + 5)

// 调用add()时，a的值被复制到参数x和y中。a的值为5，因此add(a, a)=add(5, 5)，结
// 果为10。
//
// 这组语句中有一个稍微棘手的：

// [代码 12]
//     std::cout << add(1, multiply(2, 3)) << '\n'; // 1 + (2 * 3)

// 执行函数add时，程序需要确定参数x和y的值。x很简单，将整数1传递给x。要获得参
// 数y的值，需要先计算multiply(2, 3)。程序调用multiply并初始化z=2和w=3，
// multiply(2, 3)返回整数值6。返回值6用于初始化add函数的y参数。add(1, 6)返回整
// 数7，将其传递给std::cout打印。
//
// 更明确地说：add(1, multiply(2, 3))求值为add(1, 6)，计算为7
//
// 下面的语句看起来棘手，add()的参数之一是另一个add()函数。

// [代码 13]
//     std::cout << add(1, add(2, 3)) << '\n'; // 1 + (2 + 3)

// 但这种情况与前面的情况完全相同。add(2,3) 首先解析，返回值为5。接着解析为
// add(1, 5)，计算结果为值6，该值被传递给std::cout打印。
//
// 更明确地说：add(1, add(2, 3)) 求值为add(1, 5) => 结果为6
//

// ―――― 未使用的参数 ――――

// 在某些情况下，会遇到参数未被使用的函数。
//
// 来看一个简单的例子：

// [代码 14]
// void doSomething(int count) // warning: 参数count未被使用
// {
//     // 函数体中没有用到 count
// }
//
// int main()
// {
//     doSomething(4);
// }

// 就像未使用的局部变量一样，编译器会警告已定义但未使用的参数。
//
// 在函数定义中，函数参数的名称是可选的。因此，在函数参数需要存在但未被使用的
// 情况下，可以简单地省略名称。没有名称的参数称为未命名参数：

// [代码 15]
// void doSomething(int) // ok: 未命名参数
// {
// }

// Google C++样式指南建议使用注释来记录未命名参数的名称：

// [代码 16]
// void doSomething(int /*count*/)
// {
// }

// 关键点
//
// 如果简单地删除未使用的函数参数，则对该函数的现有调用将编译失败（因为函数调
// 用提供的参数数量超过了函数可接受的数量）。
//

// ―――― 结论 ――――

// 函数参数和返回值是让函数可重用的关键机制，使得函数不必预先知道输入是什么，
// 就能给出对应的计算结果。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 下面这段程序有什么问题？

// [代码 17]
// #include <iostream>
//
// void multiply(int x, int y)
// {
//     return x * y;
// }
//
// int main()
// {
//     std::cout << multiply(4, 5) << '\n';
//
//     return 0;
// }


// 【答案 · 查看答案】
// `multiply()`的返回类型是`void`，也就是说它是一个不返回值的函数。由于该函数
// 试图通过return语句返回一个值，因此会产生编译错误。返回类型应当改为`int`。

// ▼ 问题 2
// 下面这段程序有哪两处错误？

// [代码 18]
// #include <iostream>
//
// int multiply(int x, int y)
// {
//     int product { x * y };
// }
//
// int main()
// {
//     std::cout << multiply(4) << '\n';
//
//     return 0;
// }


// 【答案 · 查看答案】
// 错误1：`main()`向`multiply()`传递了一个实参，但`multiply()`需要两个形参。
// 错误2：`multiply()`没有return语句。

// ▼ 问题 3
// 下列程序会打印出什么值？

// [代码 19]
// #include <iostream>
//
// int add(int x, int y, int z)
// {
//     return x + y + z;
// }
//
// int multiply(int x, int y)
// {
//     return x * y;
// }
//
// int main()
// {
//     std::cout << multiply(add(1, 2, 3), 4) << '\n';
//
//     return 0;
// }


// 【答案 · 查看答案】
// 调用`multiply`时x = add(1, 2, 3)，y = 4。CPU首先求出x = add(1, 2, 3)，即1 +
// 2 + 3，于是x = 6。再计算multiply(6, 4) = 24，这就是答案。

// ▼ 问题 4
// 编写一个名为`doubleNumber()`的函数，它接受一个整数形参，并返回该形参值的两
// 倍。

// 【答案 · 查看答案】

// [代码 20]
// int doubleNumber(int x)
// {
//     return 2 * x;
// }


// ▼ 问题 5
// 编写一个完整的程序：从用户处读取一个整数，用上一题中编写的`doubleNumber()`
// 函数把它翻倍，然后把翻倍后的值打印到控制台。

// 【答案 · 查看答案】

// [代码 21]
// #include <iostream>
//
// int doubleNumber(int x)
// {
//     return 2 * x;
// }
//
// int main()
// {
//     std::cout << "Enter an integer value: ";
//     int x{};
//     std::cin >> x;
//     std::cout << doubleNumber(x) << '\n';
//
//     return 0;
// }

// 注意：你可能会写出其他类似的解法。在C++中，同一件事往往有多种实现方式。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int getValueFromUser()
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input;
}

int main()
{
	int num { getValueFromUser() };

	std::cout << num << " doubled is: " << num * 2 << '\n';

	return 0;
}
