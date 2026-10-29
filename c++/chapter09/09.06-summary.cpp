// ==========================================================================
// 9.6 第9章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第九章 错误检查与处理
// 原文: https://www.studycpp.cn/basic/chapter9/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       本节示例为片段或多文件程序，文末仅有占位 main()。
// 编译: g++ -std=c++20 -Wall -Wextra "09.06-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 章节回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 章节回顾 ――――

// 项目进程中新增或变更的需求，导致项目范围超出最初的计划和预算，这又称需求蔓
// 延（Scope creep）。
//
// 软件验证是测试软件在各种情况下是否按预期工作的过程。单元测试是一种测试，旨
// 在单独测试代码的一小部分（通常是函数或类），以确保特定行为按预期发生。单元
// 测试框架可以帮助您组织单元测试。集成测试用于测试一组单元的集成，以确保它们
// 能够正常协作。
//
// 代码覆盖率是指测试时执行了多少源代码。语句覆盖率是指程序中已由测试例程执行
// 的语句所占的百分比。分支覆盖率是指测试例程已执行的分支所占的百分比。循环覆
// 盖率（也称为0、1、2测试）意味着，如果代码中有一个循环，则应该确保它在迭代0
// 次、1次和2次时都能正常工作。
//
// 快乐路径（happy path）是在没有遇到错误时发生的执行路径。故障路径（sad path）
// 是发生错误或故障状态时的执行路径。不可恢复错误（也称为致命错误）是一种严重
// 到程序无法继续运行的错误。能够良好处理错误情况的程序是健壮的。
//
// 缓冲区是为在数据从一个位置移动到另一个位置时临时存储数据而预留的内存。
//
// 检查用户输入是否符合程序期望的过程称为输入验证。
//
// std::cerr是一个输出流（类似std::cout），旨在用于输出错误消息。
//
// 前置条件是在执行某些代码段之前必须始终为true的条件。不变量是在执行某个组件
// 时必须为true的条件。后置条件是在执行某些代码后必须始终为true的条件。
//
// 断言是一个表达式，除非程序中存在错误，否则该表达式应为真。在C++中，运行时断
// 言通常使用断言预处理器宏实现。断言通常会在非调试代码中关闭。static_assert是
// 在编译时计算的断言。
//
// 断言应该用于记录逻辑上不可能的情况。错误处理应该用于处理可能发生问题的情况。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 在「8.15 第八章总结」的习题中，我们实现了一个猜数字游戏（Hi-Lo）。
//
// 请更新你之前的解法，使其能够处理无效的猜测（例如「x」）、超出范围的猜测（例
// 如`0`或`101`），以及带有额外字符的合法猜测（例如`43x`）。同时还要处理用户在
// 被问到是否再玩一次时输入了多余字符的情况。
//
// 提示：单独写一个函数来处理用户输入猜测（以及相关的错误处理）。

// 【答案 · 查看答案】

// [代码 1]
// #include <iostream>
// #include <limits>   // std::numeric_limits
// #include "Random.h" // https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/
//
// int getGuess(int count, int min, int max)
// {
// 	while (true) // 循环直到用户输入合法的内容
// 	{
// 		std::cout << "Guess #" << count << ": ";
//
// 		int guess {};
// 		std::cin >> guess;
//
// 		bool success { std::cin };
// 		std::cin.clear(); // 让流回到「正常」工作模式（如果需要的话）
// 		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除多余输入
//
// 		// 如果没有提取到任何内容，或者提取到的猜测超出范围，就重新输入
// 		if (!success || guess < min || guess > max)
// 			continue;
//
// 		return guess;
// 	}
// }
//
// // 用户获胜返回 true，失败返回 false
// bool playHiLo(int guesses, int min, int max)
// {
// 	std::cout << "Let's play a game. I'm thinking of a number between " << min << " and " << max << ". You have " << guesses << " tries to guess what it is.\n";
// 	int number{ Random::get(min, max) }; // 这是用户需要猜的数字
//
// 	// 遍历所有猜测次数
// 	for (int count{ 1 }; count <= guesses; ++count)
// 	{
// 		int guess{ getGuess(count, min, max) };
//
// 		if (guess > number)
// 			std::cout << "Your guess is too high.\n";
// 		else if (guess < number)
// 			std::cout << "Your guess is too low.\n";
// 		else // guess == number，用户猜对了
// 		{
// 			std::cout << "Correct! You win!\n";
// 			return true;
// 		}
// 	}
//
// 	// 用户失败
// 	std::cout << "Sorry, you lose. The correct number was " << number << '\n';
// 	return false; // 如果用户失败
// }
//
// bool playAgain()
// {
// 	// 不断询问用户是否想再玩一次，直到用户选择 y 或 n
// 	while (true)
// 	{
// 		char ch{};
// 		std::cout << "Would you like to play again (y/n)? ";
// 		std::cin >> ch;
//
// 		// 清除多余的输入
// 		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
// 		switch (ch)
// 		{
// 		case 'y': return true;
// 		case 'n': return false;
// 		}
// 	}
// }
//
// int main()
// {
// 	constexpr int guesses { 7 }; // 用户拥有这么多次猜测机会
// 	constexpr int min     { 1 };
// 	constexpr int max     { 100 };
//
// 	do
// 	{
// 		playHiLo(guesses, min, max);
// 	} while (playAgain());
//
// 	std::cout << "Thank you for playing.\n";
//
// 	return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
    // 本节教程的代码是多文件示例、片段或概念性内容，没有可直接编译的完整程序。
    // 请对照上面的注释和代码块，自己动手补全并运行验证。
    std::cout << "本节无独立可运行示例, 请阅读文件中的教程正文。\n";
    return 0;
}
