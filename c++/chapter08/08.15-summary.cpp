// ==========================================================================
// 8.15 第八章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第八章 控制流与错误处理
// 原文: https://www.studycpp.cn/basic/chapter8/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "08.15-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 章节回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 章节回顾 ――――

// CPU在程序中执行的特定语句序列称为程序的执行路径。顺序执行的程序每次运行时都
// 会采用相同的路径。
//
// 控制流语句允许更改正常的执行路径。当控制流语句导致程序开始执行某个非顺序的
// 指令序列时，这称为分支。
//
// 条件语句用于指定是否应执行某些关联语句。
//
// if语句允许根据某个条件是否为真来执行关联语句。如果关联条件为false，则执行
// else语句。可以将多个if和else语句链接在一起。
//
// 当else语句应该连接到哪个if语句不明确时，就会出现悬空else。悬空else语句会与
// 同一代码块中最后一个尚未匹配else的if语句匹配。可以通过将嵌套的if语句放入代
// 码块中来避免悬空else。
//
// 空语句是仅由分号组成的语句。它什么也不做，通常用于语言标准要求此处必须存在
// 语句，但程序员不需要执行任何操作的场景。
//
// switch语句为在多个匹配项之间进行选择提供了一种更清晰、更快速的方法。switch
// 语句仅适用于整型等可支持的类型。case标签用于标识要匹配的条件值。如果找不到
// 匹配的case标签，则执行default标签下的语句。
//
// 当从标签下的语句延续到后续标签下的语句时，这称为fallthrough。break语句（或
// return语句）可用于防止fallthrough。[[fallthrough]]属性可用于标记有意的
// fallthrough。
//
// goto语句允许程序向前或向后跳转到代码中的其他位置。通常应该避免使用它，因为
// 这会产生意大利面条代码，意味着程序的执行路径类似于一碗纠缠在一起的意大利面
// 条。
//
// 只要给定条件计算为true，循环就允许程序重复执行某些语句。在循环执行之前，会
// 判断是否满足循环条件。
//
// 无限循环的循环条件始终为true。除非使用另一个控制流语句来停止它，否则它会永
// 远循环。
//
// 循环变量（也称为计数器）是一个整数变量，用于统计循环已执行的次数。循环的每
// 次执行都称为一次迭代。
//
// do-while循环类似于while循环，但条件是在循环执行之后判断的。
//
// for循环是最常用的循环。当需要循环特定次数时，它是理想选择。要注意，不要多迭
// 代或少迭代一次。
//
// break语句允许中断switch、while、do-while或for循环。continue语句允许立即进入
// 下一次循环迭代。
//
// 退出允许我们终止程序。正常终止是指程序以预期方式退出（状态码会指示它是否成
// 功）。在main的末尾会自动调用std::exit()。也可以显式调用它来终止程序。它会执
// 行一些清理，但不会清理任何局部变量，也不会清理调用堆栈。
//
// 当程序遇到某种意外错误并必须关闭时，会发生异常终止。异常终止会调用
// std::abort。
//
// 算法是一个有限的指令序列，可以按照它来解决某些问题或产生一些有用的结果。如
// 果算法在调用之间保留了一些信息，则认为该算法是有状态的。相反，无状态算法不
// 存储任何信息（调用它时必须提供所需的所有信息）。用于算法时，术语“状态”指的
// 是保存在有状态变量中的当前值。
//
// 如果对于给定输入（为启动提供的值），算法始终产生相同的输出序列，则该算法被
// 认为是确定性的。
//
// 伪随机数生成器（PRNG）是一种模拟随机数序列生成的算法。当实例化PRNG时，可以
// 提供称为随机种子（或简称种子）的初始值（或一组值）来初始化PRNG的状态。当用
// 种子初始化PRNG时，我们说它已经被播种。种子值的大小可以小于PRNG状态的大小。
// 当这种情况发生时，我们说PRNG的种子不足。PRNG输出结果开始自我重复之前的序列
// 长度称为其周期。
//
// 随机数分布会将PRNG的输出转换为其他数字分布。均匀分布是一种在两个数字X和Y（
// 包括X和Y）之间以相等概率产生输出的随机数分布。
//

// ―――― 习题 ――――

// 注意：从这里开始习题会变得更难，但你能做到的。让我们攻克这些习题！

// ▼ 问题 1
// 在「4.12 第4章总结」中，我们编写了一个模拟小球从塔顶落下的程序。由于当时还
// 没有学过循环，小球只能下落5秒。
//
// 请对下面这个程序进行修改，让小球下落足够长的时间，直到它落到地面为止。并按
// 已介绍的最佳实践（命名空间、constexpr等）更新程序。

// [代码 1]
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
// 	const double gravity { 9.8 };
//
// 	// 使用公式：s = (u * t) + (a * t^2) / 2
// 	// 这里 u（初速度）= 0，因此 (u * t) = 0
// 	const double fallDistance { gravity * (seconds * seconds) / 2.0 };
// 	const double ballHeight { towerHeight - fallDistance };
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
// 	const double ballHeight{ calculateBallHeight(towerHeight, seconds) };
// 	printBallHeight(ballHeight, seconds);
// }
//
// int main()
// {
// 	const double towerHeight{ getTowerHeight() };
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


// 【答案 · 查看答案】

// [代码 2]
// #include <iostream>
//
// namespace Constants
// {
// 	constexpr double gravity { 9.8 };
// }
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
// // 注意：这个函数可以写成 constexpr，但我们还没有介绍 constexpr 函数
// double calculateBallHeight(double towerHeight, int seconds)
// {
// 	// 使用公式：s = (u * t) + (a * t^2) / 2
// 	// 这里 u（初速度）= 0，因此 (u * t) = 0
// 	const double fallDistance { Constants::gravity * (seconds * seconds) / 2.0 };
// 	const double ballHeight { towerHeight - fallDistance };
//
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
// double calculateAndPrintBallHeight(double towerHeight, int seconds)
// {
// 	const double ballHeight{ calculateBallHeight(towerHeight, seconds) };
// 	printBallHeight(ballHeight, seconds);
//
// 	return ballHeight;
// }
//
// int main()
// {
// 	const double towerHeight{ getTowerHeight() };
//
// 	int seconds { 0 };
// 	while (calculateAndPrintBallHeight(towerHeight, seconds) > 0.0)
// 	{
// 		++seconds;
// 	}
//
// 	return 0;
// }


// ▼ 问题 2
// 质数是大于1的自然数，它只能被1和自身整除（没有余数）。
//
// 请使用for循环编写`isPrime()`函数，补全下面的程序。如果正确，程序会打印「
// Success!」。

// [代码 3]
// // 确保即使在 release 模式下编译，assert 也会触发
// #undef NDEBUG
//
// #include <cassert> // assert
// #include <iostream>
//
// bool isPrime(int x)
// {
//     return false;
//     // 用 for 循环实现这个函数
// }
//
// int main()
// {
//     assert(!isPrime(0)); // 如果 isPrime(0) 为真，则终止程序
//     assert(!isPrime(1));
//     assert(isPrime(2));  // 如果 isPrime(2) 为假，则终止程序
//     assert(isPrime(3));
//     assert(!isPrime(4));
//     assert(isPrime(5));
//     assert(isPrime(7));
//     assert(!isPrime(9));
//     assert(isPrime(11));
//     assert(isPrime(13));
//     assert(!isPrime(15));
//     assert(!isPrime(16));
//     assert(isPrime(17));
//     assert(isPrime(19));
//     assert(isPrime(97));
//     assert(!isPrime(99));
//     assert(isPrime(13417));
//
//     std::cout << "Success!\n";
//
//     return 0;
// }

// 相关内容：
//
// `assert`是一个预处理宏，当关联的实参求值为假时，它会终止程序。因此当我们写
// `assert(!isPrime(0))`时，意思就是「如果isPrime(0)为真，则终止程序」。我们会
// 在「9.5 断言」中更详细地介绍assert。

// 【答案 · 查看答案】

// [代码 4]
// // 确保即使在 release 模式下编译，assert 也会触发
// #undef NDEBUG
//
// #include <cassert> // assert
// #include <iostream>
//
// // 未优化的版本
// bool isPrime(int x)
// {
//     if (x <= 1) // 如果 x 为负数、0 或 1，则该数字不是质数
//         return false;
//
//     for (int test{ 2 }; test < x; ++test)
//     {
//         if (x % test == 0) // 如果 x 能被整除
//             return false;  // 那么这个数字不是质数
//     }
//
//     return true; // 如果没有找到任何约数，那么 x 一定是质数
// }
//
// int main()
// {
//     assert(!isPrime(0));
//     assert(!isPrime(1));
//     assert(isPrime(2));
//     assert(isPrime(3));
//     assert(!isPrime(4));
//     assert(isPrime(5));
//     assert(isPrime(7));
//     assert(!isPrime(9));
//     assert(isPrime(11));
//     assert(isPrime(13));
//     assert(!isPrime(15));
//     assert(!isPrime(16));
//     assert(isPrime(17));
//     assert(isPrime(19));
//     assert(isPrime(97));
//     assert(!isPrime(99));
//     assert(isPrime(13417));
//
//     std::cout << "Success!\n";
//
//     return 0;
// }


// ▼ 附加题
// 上面解法中的for循环在两个方面不够理想：
// - 它检查了偶数约数。除了2以外，我们不需要检查这些。
// - 它对直到`x`的每个数字都检查是否为约数。非质数（合数）必然有至少一个小于
//   等于其平方根的约数，因此检查超过`x`平方根的约数是没有必要的。
//   `std::sqrt(x)`（位于头文件中）返回`x`的平方根。
//
// 对于后一点，我们有两种选择：在循环之前先算出`std::sqrt(x)`，然后用循环变量
// 与该值比较；或者把比较式两边同时平方，从而把`std::sqrt(x)`从比较中彻底优化
// 掉（感谢读者JJag的建议）。后面的解法采用后一种做法。

// 【答案 · 显示提示】
// 给定两个变量`a >= 0`和`b >= 0`，可以把比较式`a <= sqrt(b)`的两边同时平方，
// 比较关系依然成立。这样就得到`a * a <= sqrt(b) * sqrt(b)`，它等价于`a * a <=
// b`。
//
// 请更新上面的解法，实现这两项优化。

// 【答案 · 查看答案】

// [代码 5]
// // 确保即使在 release 模式下编译，assert 也会触发
// #undef NDEBUG
//
// #include <cassert> // assert
// #include <iostream>
//
// // 优化版本
// bool isPrime(int x)
// {
//     if (x <= 1)     // 如果 x 为负数、0 或 1，则该数字不是质数
//         return false;
//     if (x == 2)     // 2 是唯一的偶质数
//         return true;
//     if (x % 2 == 0) // 其他任何偶数都不是质数
//         return false;
//
//     // 对于大于等于 3 的数字，检查 3 到 sqrt(x) 之间的奇数是否为约数
//     // （这就是每次加 2 的原因）
//     // 参见 https://stackoverflow.com/questions/5811151/why-do-we-check-up-to-the-square-root-of-a-number-to-determine-if-the-number-is
//     // 由于 test >= 0 且 x >= 0，可以把 test < std::sqrt(x) 优化为 test * test < x
//     for (int test{ 3 }; test * test <= x; test += 2)
//     {
//         if (x % test == 0) // 如果 x 能被整除
//             return false;  // 那么这个数字不是质数
//     }
//
//     return true; // 如果没有找到任何约数，那么 x 一定是质数
// }
//
// int main()
// {
//     assert(!isPrime(0));
//     assert(!isPrime(1));
//     assert(isPrime(2));
//     assert(isPrime(3));
//     assert(!isPrime(4));
//     assert(isPrime(5));
//     assert(isPrime(7));
//     assert(!isPrime(9));
//     assert(isPrime(11));
//     assert(isPrime(13));
//     assert(!isPrime(15));
//     assert(!isPrime(16));
//     assert(isPrime(17));
//     assert(isPrime(19));
//     assert(isPrime(97));
//     assert(!isPrime(99));
//     assert(isPrime(13417));
//
//     std::cout << "Success!\n";
//
//     return 0;
// }


// ▼ 问题 3
// 实现一个猜数字游戏（Hi-Lo）。首先，程序应当在1到100之间随机选择一个整数。用
// 户有7次机会来猜这个数字。
//
// 如果用户没有猜对，程序应当告诉他们猜得过大还是过小。如果用户猜对了，程序应
// 当告诉他们赢了。如果次数用完了，程序应当告诉他们输了，并告诉他们正确的数字
// 是多少。游戏结束时，应当询问用户是否想再玩一次。如果用户输入的不是「y」或「
// n」，就再问一次。
//
// 本题假设用户输入的都是合法数字。
//
// 使用「8.14 全局随机数」中的 Random.h 头文件。
//
// 程序的输出应当像下面这样：

// [代码 6]
// Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is.
// Guess #1: 64
// Your guess is too high.
// Guess #2: 32
// Your guess is too low.
// Guess #3: 54
// Your guess is too high.
// Guess #4: 51
// Correct! You win!
// Would you like to play again (y/n)? y
// Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is.
// Guess #1: 64
// Your guess is too high.
// Guess #2: 32
// Your guess is too low.
// Guess #3: 54
// Your guess is too high.
// Guess #4: 51
// Your guess is too high.
// Guess #5: 36
// Your guess is too low.
// Guess #6: 45
// Your guess is too low.
// Guess #7: 48
// Your guess is too low.
// Sorry, you lose. The correct number was 49.
// Would you like to play again (y/n)? q
// Would you like to play again (y/n)? n
// Thank you for playing.

// 附加题：把最小值、最大值和猜测次数做成可配置的形参。

// 【答案 · 查看答案】

// [代码 7]
// #include <iostream>
// #include "Random.h" // https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/
//
// // 用户获胜返回 true，失败返回 false
// // 本程序没有使用这个返回值，但保留它并不会增加复杂度，而且在将来（例如想把输赢信息移到函数外部，
// // 或者根据输赢做其他处理时）可能会用得上
// bool playHiLo(int guesses, int min, int max)
// {
// 	std::cout << "Let's play a game. I'm thinking of a number between " << min << " and " << max << ". You have " << guesses << " tries to guess what it is.\n";
// 	const int number { Random::get(min, max) }; // 这是用户需要猜的数字
//
// 	// 遍历所有猜测次数
// 	for (int count{ 1 }; count <= guesses; ++count)
// 	{
// 		std::cout << "Guess #" << count << ": ";
//
// 		int guess{};
// 		std::cin >> guess;
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
// 	return false;
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

// 我们会在「9.6 第9章总结」中为这个解法加上错误处理。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

// 从用户处获取塔的高度并返回
double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;
	return towerHeight;
}

// 返回小球在"seconds"秒后的高度
double calculateBallHeight(double towerHeight, int seconds)
{
	const double gravity { 9.8 };

	// 使用公式：s = (u * t) + (a * t^2) / 2
	// 这里 u（初速度）= 0，因此 (u * t) = 0
	const double fallDistance { gravity * (seconds * seconds) / 2.0 };
	const double ballHeight { towerHeight - fallDistance };

	// 如果小球会落到地面以下，就把它放在地面上
	if (ballHeight < 0.0)
		return 0.0;

	return ballHeight;
}

// 打印小球离地面的高度
void printBallHeight(double ballHeight, int seconds)
{
	if (ballHeight > 0.0)
		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
	else
		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

// 计算小球当前的高度并打印出来
// 这是一个辅助函数，让调用更方便
void calculateAndPrintBallHeight(double towerHeight, int seconds)
{
	const double ballHeight{ calculateBallHeight(towerHeight, seconds) };
	printBallHeight(ballHeight, seconds);
}

int main()
{
	const double towerHeight{ getTowerHeight() };

	calculateAndPrintBallHeight(towerHeight, 0);
	calculateAndPrintBallHeight(towerHeight, 1);
	calculateAndPrintBallHeight(towerHeight, 2);
	calculateAndPrintBallHeight(towerHeight, 3);
	calculateAndPrintBallHeight(towerHeight, 4);
	calculateAndPrintBallHeight(towerHeight, 5);

	return 0;
}
