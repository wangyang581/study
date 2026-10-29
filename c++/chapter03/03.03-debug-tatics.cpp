// ==========================================================================
// 3.3 基本调试策略
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第三章 程序调试
// 原文: https://www.studycpp.cn/basic/chapter3/debug-tatics/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "03.03-debug-tatics.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 调试策略#1：注释代码
//   · 调试策略#2:验证代码流程
//   · 调试策略#3:打印值
//   · 再举一个例子
//   · 为什么使用打印语句进行调试不太好

// ==========================================================================
// 教程正文
// ==========================================================================

// 在上节课中，我们探索了查找问题的策略——运行程序并猜测问题位置。本节课将介绍
// 一些其他基本策略，用于实际进行猜测和收集信息，以帮助定位问题。
//

// ―――― 调试策略#1：注释代码 ――――

// 我们从一个简单的方法开始。如果程序表现出错误行为，减少搜索代码量的一种方法
// 是注释掉一些代码，然后查看问题是否仍然存在。如果问题保持不变，那么注释掉的
// 代码就可能不是问题的根因。
//
// 考虑以下代码：

// [代码 1]
// int main()
// {
//     getNames(); // 让用户输入一些名称
//     doMaintenance(); // 做一下其他事情
//     sortNames(); // 排序名称
//     printNames(); // 打印排序后的名称
//
//     return 0;
// }

// 假设这个程序应该按顺序打印用户输入的名称，但它却未按顺序打印。问题出在哪里？
// 是getNames输入的名称不正确？还是sortNames排序有误？又或者是printNames没有正
// 常打印？可能是任何一种原因。但doMaintenance()大概与该问题无关，所以我们先将
// 其注释掉。

// [代码 2]
// int main()
// {
//     getNames(); // 让用户输入一些名称
// //    doMaintenance(); // 做一下其他事情
//     sortNames(); // 排序名称
//     printNames(); // 打印排序后的名称
//
//     return 0;
// }

// 有三种可能的结果：
// - 如果问题消失了，那么doMaintenance一定是问题的根源。
// - 如果问题没有改变（这更可能），则可以假设doMaintenance没有错，并将整个函
//   数从排查范围中排除。这虽然不能确定实际问题是在调用doMaintenance之前还是
//   之后，但减少了后续需要检查的代码量。
// - 如果注释掉doMaintenance导致问题演变为其他相关问题（例如，程序停止打印名
//   称），则doMaintenance很可能在做一些其他代码所依赖的事情。在这种情况下，
//   我们无法判断问题是在doMaintenance中还是在其他地方，因此应取消注释
//   doMaintenance并尝试其他方法。
//
// 警告
//
// 不要忘记注释掉了哪些函数，以便以后可以取消注释它们！
//
// 在进行了许多与调试相关的更改之后，很容易忽略某一两处修改未被撤消。如果发生
// 这种情况，最终会引入其他错误！
//
// 拥有好的版本控制系统非常有用，你可以将代码与主分支进行比较，以查看所有与调
// 试相关的更改（确保在提交更改前还原它们）。
//

// ―――― 调试策略#2:验证代码流程 ――――

// 在更复杂的程序中，另一个常见问题是程序调用函数的次数太多或太少（包括根本不
// 调用）。
//
// 在这种情况下，在函数的顶部放置一条打印函数名称的语句会很有帮助。这样程序运
// 行时，你就可以看到调用了哪些函数。
//
// 请考虑以下无法正常工作的简单程序：

// [代码 3]
// #include <iostream>
//
// int getValue()
// {
// 	return 4;
// }
//
// int main()
// {
//     std::cout << getValue << '\n';
//
//     return 0;
// }

// 你需要禁用”将警告视为错误”选项，才能编译通过。
//
// 尽管我们希望程序打印值4，但它可能打印的是：
//
// 在Visual Studio（可能还有其他一些编译器）上，它可能会打印以下内容：
//
// 为函数添加调试语句：

// [代码 4]
// #include <iostream>
//
// int getValue()
// {
// std::cerr << "getValue() called\n";
// 	return 4;
// }
//
// int main()
// {
// std::cerr << "main() called\n";
//     std::cout << getValue << '\n';
//
//     return 0;
// }

// 当函数被执行时，输出的函数名称表示该函数被调用了：

// [文本/输出]
// main() called
// 1

// 可以看到函数getValue并未被调用。调用函数的那一行一定有问题。仔细看这行：

// [代码 5]
//     std::cout << getValue << '\n';

// 我们在函数调用中忘记了括号。应该是：

// [代码 6]
// #include <iostream>
//
// int getValue()
// {
// std::cerr << "getValue() called\n";
// 	return 4;
// }
//
// int main()
// {
// std::cerr << "main() called\n";
//     std::cout << getValue() << '\n'; // 添加括号
//
//     return 0;
// }

// 现在可以看到正确的输出了：

// [文本/输出]
// main() called
// getValue() called
// 4

// 最后删除临时调试语句即可。
//
// 提示
//
// 打印调试信息时，请使用std::cerr而不是std:∶cout。原因是，std::cout可能有缓冲
// 区，这意味着在请求std:∶cout输出信息和实际输出信息之间可能有停顿。如果使用
// std::cout输出后程序随即崩溃，则std::cout可能还未实际输出，这会误导你对问题
// 位置的判断。另一方面，std::cerr没有缓冲，发送的内容将立即输出。这有助于确保
// 所有调试输出尽快出现（虽然会牺牲一些性能，但在调试时我们并不关心性能）。
//
// 使用std::cerr还有助于明确输出的信息是用于错误情况，而不是正常输出。
//
// 在后续 检测和处理错误 章节中，会进一步讨论何时使用std::cout 或 std::cerr。
//
// 相关内容
//
// 在 函数指针 章节中，我们讨论了为什么某些编译器打印的是1而不是函数地址（以及
// 当编译器打印1而你希望它打印地址时该怎么办）。
//
// 提示
//
// 添加临时调试语句时，不缩进这些语句会有所帮助。这使得它们更容易被找到，以便
// 后续删除。
//
// 如果使用clang-format来格式化代码，它会自动缩进。你可以通过以下方式抑制自动
// 格式化：

// [代码 7]
// // clang-format off
// std::cerr << "main() called\n";
// // clang-format on

//

// ―――― 调试策略#3:打印值 ――――

// 对于某些类型的错误，程序可能会计算或传递错误的值。
//
// 我们还可以输出变量（包括参数）或表达式的值，以检查它们是否正确。
//
// 考虑以下程序，该程序将两个数字相加，但不能正常工作：

// [代码 8]
// #include <iostream>
//
// int add(int x, int y)
// {
// 	return x + y;
// }
//
// void printResult(int z)
// {
// 	std::cout << "The answer is: " << z << '\n';
// }
//
// int getUserInput()
// {
// 	std::cout << "Enter a number: ";
// 	int x{};
// 	std::cin >> x;
// 	return x;
// }
//
// int main()
// {
// 	int x{ getUserInput() };
// 	int y{ getUserInput() };
//
// 	std::cout << x << " + " << y << '\n';
//
// 	int z{ add(x, 5) };
// 	printResult(z);
//
// 	return 0;
// }

// 下面是该程序的一些输出：

// [文本/输出]
// Enter a number: 4
// Enter a number: 3
// 4 + 3
// The answer is: 9

// 你发现错误了吗？即使在这个简短的程序中，它也很难被发现。让我们添加一些代码
// 来调试变量的值：

// [代码 9]
// #include <iostream>
//
// int add(int x, int y)
// {
// 	return x + y;
// }
//
// void printResult(int z)
// {
// 	std::cout << "The answer is: " << z << '\n';
// }
//
// int getUserInput()
// {
// 	std::cout << "Enter a number: ";
// 	int x{};
// 	std::cin >> x;
// 	return x;
// }
//
// int main()
// {
// 	int x{ getUserInput() };
// std::cerr << "main::x = " << x << '\n';
// 	int y{ getUserInput() };
// std::cerr << "main::y = " << y << '\n';
//
// 	std::cout << x << " + " << y << '\n';
//
// 	int z{ add(x, 5) };
// std::cerr << "main::z = " << z << '\n';
// 	printResult(z);
//
// 	return 0;
// }

// 下面是对应的输出：

// [代码 10]
// Enter a number: 4
// main::x = 4
// Enter a number: 3
// main::y = 3
// 4 + 3
// main::z = 9
// The answer is: 9

// 变量x和y获得了正确的值，但变量z没有。问题必须在这两点之间，这使得函数add()
// 成为关键问题所在。
//
// 让我们修改函数add：

// [代码 11]
// #include <iostream>
//
// int add(int x, int y)
// {
// std::cerr << "add() called (x=" << x <<", y=" << y << ")\n";
// 	return x + y;
// }
//
// void printResult(int z)
// {
// 	std::cout << "The answer is: " << z << '\n';
// }
//
// int getUserInput()
// {
// 	std::cout << "Enter a number: ";
// 	int x{};
// 	std::cin >> x;
// 	return x;
// }
//
// int main()
// {
// 	int x{ getUserInput() };
// std::cerr << "main::x = " << x << '\n';
// 	int y{ getUserInput() };
// std::cerr << "main::y = " << y << '\n';
//
// 	std::cout << x << " + " << y << '\n';
//
// 	int z{ add(x, 5) };
// std::cerr << "main::z = " << z << '\n';
// 	printResult(z);
//
// 	return 0;
// }

// 现在，我们将获得输出：

// [代码 12]
// Enter a number: 4
// main::x = 4
// Enter a number: 3
// main::y = 3
// add() called (x=4, y=5)
// main::z = 9
// The answer is: 9

// 变量y的值为3，但我们的函数add不知何故获得了参数y的值5。我们一定传递了错误的
// 参数。果然：

// [代码 13]
// 	int z{ add(x, 5) };

// 就是这样。我们传递了字面值5，而不是变量y的值作为参数。这个问题很容易修复，
// 修复后我们就可以删除调试语句了。
//

// ―――― 再举一个例子 ――――

// 该程序与前一个程序非常相似，但也不能正常工作：

// [代码 14]
// #include <iostream>
//
// int add(int x, int y)
// {
// 	return x + y;
// }
//
// void printResult(int z)
// {
// 	std::cout << "The answer is: " << z << '\n';
// }
//
// int getUserInput()
// {
// 	std::cout << "Enter a number: ";
// 	int x{};
// 	std::cin >> x;
// 	return --x;
// }
//
// int main()
// {
// 	int x{ getUserInput() };
// 	int y{ getUserInput() };
//
// 	int z { add(x, y) };
// 	printResult(z);
//
// 	return 0;
// }

// 如果运行此代码并看到以下内容：

// [文本/输出]
// Enter a number: 4
// Enter a number: 3
// The answer is: 5

// 嗯，有点不对劲。但在哪里呢？
//
// 让我们对该代码进行一些调试：

// [代码 15]
// #include <iostream>
//
// int add(int x, int y)
// {
// std::cerr << "add() called (x=" << x << ", y=" << y << ")\n";
// 	return x + y;
// }
//
// void printResult(int z)
// {
// std::cerr << "printResult() called (z=" << z << ")\n";
// 	std::cout << "The answer is: " << z << '\n';
// }
//
// int getUserInput()
// {
// std::cerr << "getUserInput() called\n";
// 	std::cout << "Enter a number: ";
// 	int x{};
// 	std::cin >> x;
// 	return --x;
// }
//
// int main()
// {
// std::cerr << "main() called\n";
// 	int x{ getUserInput() };
// std::cerr << "main::x = " << x << '\n';
// 	int y{ getUserInput() };
// std::cerr << "main::y = " << y << '\n';
//
// 	int z{ add(x, y) };
// std::cerr << "main::z = " << z << '\n';
// 	printResult(z);
//
// 	return 0;
// }

// 现在，让我们使用相同的输入再次运行该程序：

// [代码 16]
// main() called
// getUserInput() called
// Enter a number: 4
// main::x = 3
// getUserInput() called
// Enter a number: 3
// main::y = 2
// add() called (x=3, y=2)
// main::z = 5
// printResult() called (z=5)
// The answer is: 5

// 现在，我们可以立即看到出现了问题：用户正在输入值4，但main的x得到的是值3。在
// 用户输入的位置和将该值分配给main的变量x的位置之间，肯定出现了问题。让我们通
// 过向函数getUserInput添加一些调试代码来确保程序从用户处获得正确的值：

// [代码 17]
// #include <iostream>
//
// int add(int x, int y)
// {
// std::cerr << "add() called (x=" << x << ", y=" << y << ")\n";
// 	return x + y;
// }
//
// void printResult(int z)
// {
// std::cerr << "printResult() called (z=" << z << ")\n";
// 	std::cout << "The answer is: " << z << '\n';
// }
//
// int getUserInput()
// {
// std::cerr << "getUserInput() called\n";
// 	std::cout << "Enter a number: ";
// 	int x{};
// 	std::cin >> x;
// std::cerr << "getUserInput::x = " << x << '\n'; // 添加额外的这一行来做调试
// 	return --x;
// }
//
// int main()
// {
// std::cerr << "main() called\n";
// 	int x{ getUserInput() };
// std::cerr << "main::x = " << x << '\n';
// 	int y{ getUserInput() };
// std::cerr << "main::y = " << y << '\n';
//
// 	int z{ add(x, y) };
// std::cerr << "main::z = " << z << '\n';
// 	printResult(z);
//
// 	return 0;
// }

// 输出：

// [代码 18]
// main() called
// getUserInput() called
// Enter a number: 4
// getUserInput::x = 4
// main::x = 3
// getUserInput() called
// Enter a number: 3
// getUserInput::x = 3
// main::y = 2
// add() called (x=3, y=2)
// main::z = 5
// printResult() called (z=5)
// The answer is: 5

// 通过这一额外的调试行，我们可以看到用户输入被正确地接收到getUserInput的变量x
// 中。然而，main的变量x得到了错误的值。问题一定在这两点之间。唯一的罪魁祸首是
// 函数getUserInput的返回值。让我们更仔细地看一下那一行。

// [代码 19]
// 	return --x;

// 嗯，这很奇怪。x前面的”–”是什么？我们还没有在这些教程中介绍这个知识点，所以
// 如果你不知道它的含义，请不要担心。但即使不知道它的含义，通过调试工作，你也
// 可以合理地确定这行代码有问题——因此，很可能就是这个”–”符号导致了问题。
//
// 由于我们确实希望getUserInput仅返回x的值，因此让我们删除”–”，看看会发生什么：

// [代码 20]
// #include <iostream>
//
// int add(int x, int y)
// {
// std::cerr << "add() called (x=" << x << ", y=" << y << ")\n";
// 	return x + y;
// }
//
// void printResult(int z)
// {
// std::cerr << "printResult() called (z=" << z << ")\n";
// 	std::cout << "The answer is: " << z << '\n';
// }
//
// int getUserInput()
// {
// std::cerr << "getUserInput() called\n";
// 	std::cout << "Enter a number: ";
// 	int x{};
// 	std::cin >> x;
// std::cerr << "getUserInput::x = " << x << '\n';
// 	return x; // 移除变量x前的“--”
// }
//
// int main()
// {
// std::cerr << "main() called\n";
// 	int x{ getUserInput() };
// std::cerr << "main::x = " << x << '\n';
// 	int y{ getUserInput() };
// std::cerr << "main::y = " << y << '\n';
//
// 	int z{ add(x, y) };
// std::cerr << "main::z = " << z << '\n';
// 	printResult(z);
//
// 	return 0;
// }

// 现在输出：

// [代码 21]
// main() called
// getUserInput() called
// Enter a number: 4
// getUserInput::x = 4
// main::x = 4
// getUserInput() called
// Enter a number: 3
// getUserInput::x = 3
// main::y = 3
// add() called (x=4, y=3)
// main::z = 7
// printResult() called (z=7)
// The answer is: 7

// 程序现在正常工作了。即使不了解”–”的含义，我们也能够找到导致问题的特定代码行，
// 并修复它。
//

// ―――― 为什么使用打印语句进行调试不太好 ――――

// 虽然为诊断目的向程序中添加调试语句是一种常见的基本技术，也是一种功能性技术
// （特别是当调试器由于某种原因不可用时），但由于以下几个原因，它并不是那么好：
// - 调试语句扰乱了代码
// - 调试语句扰乱了输出内容
// - 调试语句需要不断增加和移除代码，容易引入新的问题
// - 在解决问题之后需要移除调试代码，而这些代码完全不可重用
//
// 我们可以做得更好。我们将在后续的课程中探索更好的方法。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int getValue()
{
	return 4;
}

int main()
{
    std::cout << getValue << '\n';

    return 0;
}
