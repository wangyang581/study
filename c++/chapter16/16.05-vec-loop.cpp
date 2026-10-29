// ==========================================================================
// 16.5 数组和循环
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十六章 动态数组：std::vector
// 原文: https://www.studycpp.cn/basic/chapter16/vec-loop/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "16.05-vec-loop.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 可变与可扩展性挑战
//   · 循环
//   · 模板、数组和循环释放了可扩展性
//   · 可以对数组和循环做什么
//   · 数组和off-by-one错误
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 在本章第一节中，我们介绍了当存在许多相关的单个变量时会出现的可扩展性挑战。
// 本课将重新回顾该问题，然后讨论数组如何帮助我们优雅地解决此类问题。
//

// ―――― 可变与可扩展性挑战 ――――

// 考虑这样一种情况：想要计算一个班级学生的平均考试成绩。为了让示例简洁，假设
// 这个班只有5个学生。
//
// 下面是可以使用单个变量解决此问题的方法：

// [代码 1]
// #include <iostream>
//
// int main()
// {
//     // 分配 5 个整型变量 (每一个名字不同)
//     int testScore1{ 84 };
//     int testScore2{ 92 };
//     int testScore3{ 76 };
//     int testScore4{ 81 };
//     int testScore5{ 56 };
//
//     int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5) / 5 };
//
//     std::cout << "The class average is: " << average << '\n';
//
//     return 0;
// }

// 这需要大量变量和大量输入。想象一下，如果要为30名学生或600名学生做同样的事情，
// 会有多少工作。此外，如果添加了新的成绩，就必须声明并初始化新变量，并将其添
// 加到平均值计算中。还记得更新除数吗？如果忘记了，就会产生语义错误。每当必须
// 修改现有代码时，都有引入错误的风险。
//
// 现在，您已经知道，当有一组相关变量时，应该使用数组。因此，可以用std::vector
// 替换这些单独变量：

// [代码 2]
// #include <iostream>
// #include <vector>
//
// int main()
// {
//     std::vector testScore { 84, 92, 76, 81, 56 };
//     std::size_t length { testScore.size() };
//
//     int average { (testScore[0] + testScore[1] + testScore[2] + testScore[3] + testScore[4])
//         / static_cast<int>(length) };
//
//     std::cout << "The class average is: " << average << '\n';
//
//     return 0;
// }

// 这要好得多，定义的变量数量显著减少，平均值计算中的除数现在也直接由数组长度
// 确定。
//
// 但平均值计算仍然有问题，因为必须手动逐个列出每个元素。由于必须显式列出每个
// 元素，这段代码只适用于固定长度的数组。如果还希望计算其他长度数组的平均值，
// 就需要为每种不同的数组长度编写新的平均值计算代码。
//
// 真正需要的是一种能访问每个数组元素、但不必显式列出每个元素的方法。
//

// ―――― 循环 ――――

// 在前面的课程中，我们注意到数组下标不需要是常量表达式，它们也可以是运行时表
// 达式。这意味着可以使用变量的值作为索引。
//
// 还请注意，前一示例的平均值计算中使用的数组索引是升序：0、1、2、3、4。因此，
// 如果有某种方法能让变量依次取值0、1、2、3和4，就可以直接使用该变量作为数组索
// 引。我们已经知道如何做到这一点：使用for循环。
//
// 下面使用for循环重写上面的示例，其中循环变量用作数组索引：

// [代码 3]
// #include <iostream>
// #include <vector>
//
// int main()
// {
//     std::vector testScore { 84, 92, 76, 81, 56 };
//     std::size_t length { testScore.size() };
//
//     int average { 0 };
//     for (std::size_t index{ 0 }; index < length; ++index) // index 从 0 增长到 length-1
//         average += testScore[index];                      // 将 `index` 位置对应的值进行累加
//     average /= static_cast<int>(length);                  // 计算平均值
//
//     std::cout << "The class average is: " << average << '\n';
//
//     return 0;
// }

// 这应该相当直观。索引从0开始，testScore[0]被加到average中，然后索引增加到1。
// testScore[1]被加到average中，索引增加到2。最终，当索引增加到5时，index <
// length为false，循环终止。
//
// 此时，循环已经将testScore[0]、testScore[1]、testScore[2]、testScore[3]和
// testScore[4]的值添加到average中。
//
// 最后，通过将累积值除以数组长度来计算平均值。
//
// 这个解决方案在可维护性方面比较理想。循环迭代次数由数组长度确定，循环变量用
// 于完成所有数组索引操作。不再需要手动列出每个数组元素。
//
// 如果想添加或删除测试分数，只需要修改数组初始值设定项的数量，其余代码仍然可
// 以工作，无需进一步更改！
//
// 按某种顺序访问容器的每个元素称为遍历容器。遍历通常也称为迭代，或者称为在容
// 器上迭代、在容器中迭代。
//
// 注
//
// 由于容器类使用类型size_t作为长度和索引，因此本课也会采用相同做法。后面会讨
// 论如何使用有符号长度和索引。
//

// ―――― 模板、数组和循环释放了可扩展性 ――――

// 数组提供了一种存储多个对象的方法，而不必命名每个元素。
//
// 循环提供了一种遍历数组的方法，而不必显式列出每个元素。
//
// 模板提供了一种参数化元素类型的方法。
//
// 模板、数组和循环结合在一起，使我们能够编写可操作元素容器的代码，而不必关心
// 容器中的元素类型或元素数量！
//
// 为了进一步说明这一点，下面重写上面的示例，将平均值计算重构为函数模板：

// [代码 4]
// #include <iostream>
// #include <vector>
//
// // 计算 std::vector 中平均值的函数模板
// template <typename T>
// T calculateAverage(const std::vector<T>& arr)
// {
//     std::size_t length { arr.size() };
//
//     T average { 0 };                                      // 如果数组里的值类型为 T, 那么其平均值类型也应该为 T
//     for (std::size_t index{ 0 }; index < length; ++index) // 遍历所有的元素
//         average += arr[index];                            // 进行相加
//     average /= static_cast<int>(length);
//
//     return average;
// }
//
// int main()
// {
//     std::vector class1 { 84, 92, 76, 81, 56 };
//     std::cout << "The class 1 average is: " << calculateAverage(class1) << '\n'; // 计算 5 个 int 的平均值
//
//     std::vector class2 { 93.2, 88.6, 64.2, 81.0 };
//     std::cout << "The class 2 average is: " << calculateAverage(class2) << '\n'; // 计算 4 个 double 的平均值
//
//     return 0;
// }

// 在上面的示例中，我们创建了函数模板calculateAverage()，它接受任意元素类型和
// 任意长度的std::vector，并返回平均值。在main()中，我们演示了当使用5个int元素
// 的数组或4个double元素的数组调用该函数时，它都能很好地工作！
//
// calculateAverage() 适用于任何支持函数内所用运算符（operator+=(T)，
// operator/=(int)）的类型T。如果尝试使用不支持这些运算符的T，编译器会在尝试编
// 译实例化函数模板时报错。
//

// ―――― 可以对数组和循环做什么 ――――

// 既然已经知道如何使用循环遍历元素容器，接下来看看容器遍历最常用于哪些事情。
// 我们通常通过遍历容器来执行以下四类操作之一：
// - 根据现有值计算一个新值（平均值、求和等）
// - 查询存在的元素（例如是否存在精确匹配、匹配的个数、最大值等）
// - 对每个元素进行操作（例如打印每个元素、将每个元素乘2等）
// - 对容器重新排序
//
// 前三项相当简单。可以使用单个循环遍历数组，并根据需要检查或修改每个元素。
//
// 重新排序容器元素要复杂得多，因为这通常涉及在一个循环中使用另一个循环。虽然
// 可以手动完成此操作，但通常最好使用标准库中的现有算法。未来讨论算法时会更详
// 细地介绍这一点。
//

// ―――― 数组和off-by-one错误 ――――

// 当使用索引遍历容器时，必须注意确保循环执行正确的次数。Off-by-one错误（循环
// 体多执行或少执行一次）很容易发生。
//
// 通常，当使用索引遍历容器时，索引会从0开始，并循环直到索引<长度。
//
// 新程序员有时会不小心将索引<=长度用作循环条件。这会导致在索引==长度时仍执行
// 循环，从而造成越界下标和未定义行为。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 编写一个短程序，用循环把下面这个vector的元素打印到屏幕上：

// [代码 5]
// #include <iostream>
// #include <vector>
//
// int main()
// {
//     std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
//
//     // 在这里补充你的代码
//
//     return 0;
// }

// 输出应当像这样：

// [文本/输出]
// 4 6 7 3 8 2 1 9


// 【答案 · 查看答案】

// [代码 6]
// #include <iostream>
// #include <vector>
//
// int main()
// {
//     std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
//
//     for (std::size_t index{ 0 }; index < arr.size(); ++index)
//     {
//         std::cout << arr[index] << ' ';
//     }
//
//     if (arr.size() > 0)
//         std::cout << '\n';
//
//     return 0;
// }


// ▼ 问题 2
// 修改你在上一题中编写的代码，使下面这个程序能够编译并且输出相同的结果：

// [代码 7]
// #include <iostream>
// #include <vector>
//
// // 在这里实现 printArray()
//
// int main()
// {
//     std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
//
//     printArray(arr); // 使用函数模板打印数组
//
//     return 0;
// }


// 【答案 · 查看答案】

// [代码 8]
// #include <iostream>
// #include <vector>
//
// template <typename T>
// void printArray(const std::vector<T>& arr)
// {
//     for (std::size_t index{ 0 }; index < arr.size(); ++index)
//     {
//         std::cout << arr[index] << ' ';
//     }
//
//     if (arr.size() > 0)
//         std::cout << '\n';
// }
//
// int main()
// {
//     std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
//
//     printArray(arr);
//
//     return 0;
// }


// ▼ 问题 3
// 在第2题答案的基础上完成下列任务：
// - 要求用户输入一个1到9之间的值。如果用户输入的不是1到9之间的值，就反复要求
//   输入一个整数，直到符合要求为止。如果用户输入的数字后面还跟着多余的输入，
//   忽略这些多余的内容。
// - 打印数组。
// - 编写一个函数模板，在数组中查找用户输入的值。如果该值在数组中，返回它的下
//   标；如果不在，返回一个合适值。
// - 如果找到了该值，打印该值及其下标；如果没找到，打印该值并说明未找到。
//
// 我们会在「9.4 std::cin和处理无效输入」中介绍如何处理无效输入。
//
// 下面是这个程序两次运行的示例：

// [文本/输出]
// Enter a number between 1 and 9: d
// Enter a number between 1 and 9: 6
// 4 6 7 3 8 2 1 9
// The number 6 has index 1


// [文本/输出]
// Enter a number between 1 and 9: 5
// 4 6 7 3 8 2 1 9
// The number 5 was not found


// 【答案 · 查看答案】

// [代码 9]
// #include <iostream>
// #include <limits>
// #include <vector>
//
// template <typename T>
// void printArray(const std::vector<T>& arr)
// {
//     for (std::size_t index{ 0 }; index < arr.size(); ++index)
//     {
//         std::cout << arr[index] << ' ';
//     }
//
//     if (arr.size() > 0)
//         std::cout << '\n';
// }
//
// template <typename T>
// int findIndex(const std::vector<T>& arr, T val)
// {
//     for (std::size_t index{ 0 }; index < arr.size(); ++index)
//     {
//         if (arr[index] == val)
//             return static_cast<int>(index);
//     }
//
//     return -1; // -1 不是有效下标，因此可以用它作为表示错误的返回值
// }
//
// int getValidNumber()
// {
//     // 首先读入用户的合法输入
//     int num {};
//     do
//     {
//         std::cout << "Enter a number between 1 and 9: ";
//         std::cin >> num;
//
//         // 如果用户输入了无效字符
//         if (!std::cin)
//             std::cin.clear(); // 重置所有错误标志
//
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略输入缓冲区中多余的字符（无论是否出错）
//
//     } while (num < 1 || num > 9);
//
//     return num;
// }
//
// int main()
// {
//     std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
//
//     int num { getValidNumber() };
//
//     printArray(arr);
//
//     int index { findIndex(arr, num) };
//
//     if (index != -1)
//         std::cout << "The number " << num << " has index " << index << '\n';
//     else
//         std::cout << "The number " << num << " was not found\n";
//
//     return 0;
// }


// ▼ 问题 4
// 附加题：修改上一题的程序，使其能够处理包含非int数值的`std::vector`，例如
// `std::vector arr{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };`。

// 【答案 · 查看答案】

// [代码 10]
// #include <iostream>
// #include <limits>
// #include <vector>
//
// template <typename T>
// void printArray(const std::vector<T>& arr)
// {
//     for (std::size_t index{ 0 }; index < arr.size(); ++index)
//     {
//         std::cout << arr[index] << ' ';
//     }
//
//     if (arr.size() > 0)
//         std::cout << '\n';
// }
//
// template <typename T>
// int findIndex(const std::vector<T>& arr, T val)
// {
//     for (std::size_t index{ 0 }; index < arr.size(); ++index)
//     {
//         if (arr[index] == val)
//             return static_cast<int>(index);
//     }
//
//     return -1; // -1 不是有效下标，因此可以用它作为表示错误的返回值
// }
//
// // 传入 low 和 high 可以让编译器推导出我们想要的输入类型
// template <typename T>
// T getValidNumber(std::string_view prompt, T low, T high)
// {
//     // 首先读入用户的合法输入
//     T val {};
//     do
//     {
//         std::cout << prompt;
//         std::cin >> val;
//
//         // 如果用户输入了无效字符
//         if (!std::cin)
//             std::cin.clear(); // 重置所有错误标志
//
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略输入缓冲区中多余的字符（无论是否出错）
//
//     } while (val < low || val > high);
//
//     return val;
// }
//
// int main()
// {
//     std::vector arr{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };
//
//     auto num { getValidNumber("Enter a number between 1 and 9: ", 1.0, 9.0) };
//
//     printArray(arr);
//
//     int index { findIndex(arr, num) };
//
//     if (index != -1)
//         std::cout << "The number " << num << " has index " << index << '\n';
//     else
//         std::cout << "The number " << num << " was not found\n";
//
//     return 0;
// }


// ▼ 问题 5
// 编写一个函数模板，查找`std::vector`中的最大值。如果vector为空，则返回该元素
// 类型的默认值。
//
// 下面这段代码应当能够运行：

// [代码 11]
// int main()
// {
//     std::vector data1 { 84, 92, 76, 81, 56 };
//     std::cout << findMax(data1) << '\n';
//
//     std::vector data2 { -13.0, -26.7, -105.5, -14.8 };
//     std::cout << findMax(data2) << '\n';
//
//     std::vector<int> data3 { };
//     std::cout << findMax(data3) << '\n';
//
//     return 0;
// }

// 并打印如下结果：

// [文本/输出]
// 92
// -13
// 0


// 【答案 · 显示提示】
// 使用一个非循环变量来记录目前为止见过的最大值。

// 【答案 · 查看答案】

// [代码 12]
// #include <iostream>
// #include <vector>
//
// template <typename T>
// T findMax(const std::vector<T>& arr)
// {
//     std::size_t length { arr.size() };
//
//     if (length==0)
//         return T{};
//
//     T max { arr[0] }; // 把最大值设为第一个元素
//
//     // 遍历其余元素，寻找更大的值
//     for (std::size_t index{ 1 }; index < length; ++index)
//     {
//         if (arr[index] > max)
//             max = arr[index];
//     }
//
//     return max;
// }
//
// int main()
// {
//     std::vector data1 { 84, 92, 76, 81, 56 };
//     std::cout << findMax(data1) << '\n';
//
//     std::vector data2 { -13.0, -26.7, -105.5, -14.8 };
//     std::cout << findMax(data2) << '\n';
//
//     std::vector<int> data3 { };
//     std::cout << findMax(data3) << '\n';
//
//     return 0;
// }

// 在这个例子中，我们使用一个非循环变量`max`来记录目前为止见过的最高分。我们把
// `max`初始化为第一个元素的值，这样它一开始就有一个合理的值。用值初始化看起来
// 也许很诱人，但如果数组中的元素全是负数，就会导致函数返回错误的值。
//
// 接着我们遍历数组的每一个元素，如果发现某个分数比之前见过的都高，就把`max`设
// 为该值。这样`max`始终代表目前搜索过的所有元素中的最高分。遍历到数组末尾时，
// `max`保存的就是整个数组中的最高分，可以返回给调用者。

// ▼ 问题 6
// 在「8.9 for语句」的习题中，我们实现了一个针对3、5、7的FizzBuzz游戏。
//
// 本次习题要求按下列规则实现这个游戏：
// - 只能被3整除的数字打印「fizz」。
// - 只能被5整除的数字打印「buzz」。
// - 只能被7整除的数字打印「pop」。
// - 只能被11整除的数字打印「bang」。
// - 只能被13整除的数字打印「jazz」。
// - 只能被17整除的数字打印「pow」。
// - 只能被19整除的数字打印「boom」。
// - 能被上述多个数字整除的，按顺序打印与之对应的每个单词。
// - 不能被上述任何数字整除的，直接打印该数字。
//
// 使用一个`std::vector`保存这些除数，再用一个`std::vector`保存对应的单词（类
// 型为`std::string_view`）。如果两个数组的长度不同，程序应当触发assert。输出
// 150个数字的结果。

// 【答案 · 显示提示】
// 使用`sv`字面值后缀把单词构造成`std::string_view`类型，这样就可以用CTAD推导
// 数组的类型。

// 【答案 · 显示提示】
// 使用嵌套for循环，把当前数字与各个除数逐一比较。嵌套for循环在「8.9 for语句」
// 中讨论过。
//
// 前21次迭代的预期输出如下：

// [文本/输出]
// 1
// 2
// fizz
// 4
// buzz
// fizz
// pop
// 8
// fizz
// buzz
// bang
// fizz
// jazz
// pop
// fizzbuzz
// 16
// pow
// fizz
// boom
// buzz
// fizzpop


// 【答案 · 查看答案】

// [代码 13]
// // 感谢读者 Waldo 建议了这道题
// #include <cassert>
// #include <iostream>
// #include <string_view>
// #include <vector>
//
// void fizzbuzz(int count)
// {
// 	// 把这些设为 static，这样只需要初始化一次
// 	static const std::vector divisors                { 3, 5, 7, 11, 13, 17, 19 };
// 	static const std::vector<std::string_view> words { "fizz", "buzz", "pop", "bang", "jazz", "pow", "boom" };
// 	assert(std::size(divisors) == std::size(words) && "fizzbuzz: array sizes don't match");
//
// 	// 遍历 1 到 count（含）之间的每个数字
// 	for (int i{ 1 }; i <= count; ++i)
// 	{
// 		bool printed{ false };
//
// 		// 把当前数字与每个可能的除数比较
// 		for (std::size_t j{ 0 }; j < divisors.size(); ++j)
// 		{
// 			if (i % divisors[j] == 0)
// 			{
// 				std::cout << words[j];
// 				printed = true;
// 			}
// 		}
//
// 		// 如果没有找到任何除数
// 		if (!printed)
// 			std::cout << i;
//
// 		std::cout << '\n';
// 	}
// }
//
// int main()
// {
// 	fizzbuzz(150);
//
// 	return 0;
// }

// 提示：由于`divisors`和`words`都是常量数组，把它们声明为`constexpr`会更好——
// 但是`std::vector`做不到这一点。这里更适合使用`constexpr std::array`。我们会
// 在「17.0 std::array简介」中介绍`std::array`。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
    // 分配 5 个整型变量 (每一个名字不同)
    int testScore1{ 84 };
    int testScore2{ 92 };
    int testScore3{ 76 };
    int testScore4{ 81 };
    int testScore5{ 56 };

    int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5) / 5 };

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
