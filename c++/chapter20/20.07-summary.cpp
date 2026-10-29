// ==========================================================================
// 20.7 第20章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十章 函数
// 原文: https://www.studycpp.cn/basic/chapter20/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "20.07-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 章节回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 章节回顾 ――――

// 函数参数可以通过值、引用或地址传递。对基本数据类型和枚举类型使用按值传递。
// 对结构体、类，或需要函数修改参数的场景，使用按引用传递。传递指针或内置数组
// 时使用按地址传递。
//
// 值可以按值、引用或地址返回。大多数情况下，按值返回即可；但在处理动态分配的
// 数据、结构体或类时，按引用或地址返回可能很有用。如果通过引用或地址返回，请
// 记住不要返回已经超出作用域的内容。
//
// 函数指针允许我们将函数传递给另一个函数。这对于允许调用者自定义函数的行为很
// 有用，例如列表的排序方式。
//
// 动态内存分配在堆上。
//
// 调用栈跟踪从程序开始到当前执行点的所有活动函数（那些已被调用但尚未终止的函
// 数）。局部变量在栈上分配。栈的大小有限。vector可以用于实现类似栈的行为。
//
// 递归函数是调用自身的函数。所有递归函数都需要终止条件。
//
// 命令行参数允许用户或其他程序在启动时将数据传递到程序中。命令行参数始终是C样
// 式字符串，如果需要数值，则必须转换为数字。
//
// 省略号允许您向函数传递可变数量的参数。然而，省略号参数不进行类型检查，也不
// 知道传递了多少个参数。这些细节需要由程序员手动跟踪。
//
// Lambda函数是可以嵌套在其他函数中的函数对象。它们不需要名称，与算法库结合使
// 用非常有用。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 为下列各种情况编写函数原型。必要时应使用const。
//
// a) 一个名为`max()`的函数，接受两个double，返回其中较大的一个。

// 【答案 · 查看答案】

// [代码 1]
// double max(double x, double y);

// b) 一个名为`swap()`的函数，交换两个整数。

// 【答案 · 查看答案】

// [代码 2]
// void swap(int& x, int& y);

// c) 一个名为`getLargestElement()`的函数，接受一个动态分配的整数数组，并以「
// 调用者可以修改所返回元素的值」的方式返回其中最大的数字（不要忘记长度形参）。

// 【答案 · 查看答案】

// [代码 3]
// // 注意：本例中数组不能是 const 的，因为返回指向 const 元素的非 const 引用会违反 const 规则。
// int& getLargestElement(int* array, int length);


// ▼ 问题 2
// 下面这些程序有什么问题？
//
// a)

// [代码 4]
// int& doSomething()
// {
//     int array[]{ 1, 2, 3, 4, 5 };
//     return array[3];
// }


// 【答案 · 查看答案】
// `doSomething()`返回了局部变量的引用，而这个局部变量会在`doSomething`结束时
// 被销毁。
//
// b)

// [代码 5]
// int sumTo(int value)
// {
//     return value + sumTo(value - 1);
// }


// 【答案 · 查看答案】
// 函数`sumTo()`没有终止条件。变量value最终会变成负数，函数会无限递归下去，直
// 到栈溢出。
//
// c)

// [代码 6]
// float divide(float x, float y)
// {
//     return x / y;
// }
//
// double divide(float x, float y)
// {
//     return x / y;
// }


// 【答案 · 查看答案】
// 这两个divide函数不是不同的函数，因为它们的名字和形参都相同。另外还存在除以0
// 的隐患。
//
// d)

// [代码 7]
// #include <iostream>
//
// int main()
// {
//     int array[100000000]{};
//
//     for (auto x: array)
//         std::cout << x << ' ';
//
//     std::cout << '\n';
//
//     return 0;
// }


// 【答案 · 查看答案】
// 这个数组太大，无法在栈上分配，应当改为动态分配。
//
// e)

// [代码 8]
// #include <iostream>
//
// int main(int argc, char* argv[])
// {
//     int age{ argv[1] };
//     std::cout << "The user's age is " << age << '\n';
//
//     return 0;
// }


// 【答案 · 查看答案】
// `argv[1]`可能不存在。即使存在，`argv[1]`也是一个字符串实参，不能通过赋值转
// 换成整数。

// ▼ 问题 3
// 判断一个值是否存在于有序数组中的最佳算法叫做二分查找（binary search）。
//
// 二分查找的流程如下：
// - 查看数组的中间元素（如果数组元素个数为偶数，则向下取整）。
// - 如果中间元素大于目标元素，就丢弃数组较大的那一半（或者说在较小的一半中递
//   归查找）。
// - 如果中间元素小于目标元素，就丢弃数组较小的那一半（或者说在较大的一半中递
//   归查找）。
// - 如果中间元素等于目标元素，就返回中间元素的下标。
// - 如果在丢弃整个数组后仍未找到目标元素，就返回一个表示「未找到」的哨兵值（
//   这里我们用-1，因为它是无效的数组下标）。
//
// 由于每次迭代都能丢掉一半的数组，这个算法非常快。即使数组有一百万个元素，最
// 多也只需要20次迭代就能确定某个值是否存在！不过它只能用于有序数组。
//
// 修改数组（例如丢弃数组中的一半元素）开销很大，因此通常我们不修改数组，而是
// 用两个整数（min和max）保存我们当前关注的数组区间的最小和最大下标。
//
// 我们来看一个例子：给定数组`{ 3, 6, 7, 9, 12, 15, 18, 21, 24 }`，目标值为7。
// 起初min = 0、max = 8，因为我们要搜索整个数组（数组长度为9，因此最后一个元素
// 的下标是8）。
// - 第1趟）计算min(0)与max(8)的中点，为4。下标为4的元素值是12，大于目标值。
//   由于数组是有序的，我们知道下标大于等于中点(4)的所有元素都太大了。因此min
//   保持不变，把max设为3。
// - 第2趟）计算min(0)与max(3)的中点，为1。下标为1的元素值是6，小于目标值。由
//   于数组是有序的，我们知道下标小于等于中点(1)的所有元素都太小了。因此把min
//   设为2，max保持不变。
// - 第3趟）计算min(2)与max(3)的中点，为2。下标为2的元素值是7，正是目标值。因
//   此返回2。
//
// 在C++20中，可以用`std::midpoint`计算中点。在C++20之前，需要自己计算中点——此
// 时可以使用`min + ((max - min) / 2)`以避免溢出（当min和max都是正数时）。
//
// 给定下面这段代码：

// [代码 9]
// #include <iostream>
// #include <iterator>
//
// // array 是要搜索的数组。
// // target 是我们要判断是否存在的那个值。
// // min 是当前搜索区间的下界下标。
// // max 是当前搜索区间的上界下标。
// // 找到目标元素时 binarySearch() 返回其下标，否则返回 -1
// int binarySearch(const int* array, int target, int min, int max)
// {
//
// }
//
// int main()
// {
//     constexpr int array[]{ 3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48 };
//
//     // 我们要测试一批值，看看算法是否返回我们期望的结果
//
//     // 下面是测试值
//     constexpr int testValues[]{ 0, 3, 12, 13, 22, 26, 43, 44, 48, 49 };
//
//     // 下面是我们期望这些测试值得到的结果
//     int expectedResult[]{ -1, 0, 3, -1, -1, 8, -1, 13, 14, -1 };
//
//     // 确保测试值的个数与期望结果的个数一致
//     static_assert(std::size(testValues) == std::size(expectedResult));
//
//     int numTestValues { std::size(testValues) };
//     // 遍历所有测试值
//     for (int count{ 0 }; count < numTestValues; ++count)
//     {
//         // 看测试值是否在数组中
//         int index{ binarySearch(array, testValues[count], 0, static_cast<int>(std::size(array)) - 1) };
//         // 如果与期望值一致，那就太好了！
//         if (index == expectedResult[count])
//              std::cout << "test value " << testValues[count] << " passed!\n";
//         else // 否则就说明我们的 binarySearch() 函数有 bug
//              std::cout << "test value " << testValues[count] << " failed.  There's something wrong with your code!\n";
//     }
//
//     return 0;
// }

// a) 编写一个迭代版的binarySearch函数。
//
// 提示：当min下标大于max下标时，就可以确定目标元素不存在。

// 【答案 · 查看答案】

// [代码 10]
// #include <cassert>
// #include <iostream>
// #include <numeric> // 用于 std::midpoint
//
// // array 是要搜索的数组。
// // target 是我们要判断是否存在的那个值。
// // min 是当前搜索区间的下界下标。
// // max 是当前搜索区间的上界下标。
// // 找到目标元素时 binarySearch() 返回其下标，否则返回 -1
// int binarySearch(const int* array, int target, int min, int max)
// {
//     assert(array); // 确保数组存在
//
//     while (min <= max)
//     {
//         // 用迭代方式实现
//         int midpoint{ std::midpoint(min, max) };
//         // C++20 之前
//         // int midpoint{ min + ((max-min) / 2) }; // 这样计算中点可以避免溢出
//
//         if (array[midpoint] > target)
//         {
//             // 如果 array[midpoint] > target，那么目标一定在数组的前半部分
//             // 可以把 midpoint - 1 作为新的上界下标，因为下一次迭代不需要再测中点
//             max = midpoint - 1;
//         }
//         else if (array[midpoint] < target)
//         {
//             // 如果 array[midpoint] < target，那么目标一定在数组的后半部分
//             // 可以把 midpoint + 1 作为新的下界下标，因为下一次迭代不需要再测中点
//             min = midpoint + 1;
//         }
//         else
//         {
//             return midpoint;
//         }
//     }
//
//     return -1;
// }

// b) 编写一个递归版的binarySearch函数。

// 【答案 · 查看答案】

// [代码 11]
// #include <cassert>
// #include <numeric> // 用于 std::midpoint
//
// // array 是要搜索的数组。
// // target 是我们要判断是否存在的那个值。
// // min 是当前搜索区间的下界下标。
// // max 是当前搜索区间的上界下标。
// // 找到目标元素时 binarySearch() 返回其下标，否则返回 -1
// int binarySearch(const int* array, int target, int min, int max)
// {
//     assert(array); // 确保数组存在
//
//     // 用递归方式实现
//
//     if (min > max)
//         return -1;
//
//     int midpoint{ std::midpoint(min, max) };
//     // C++20 之前
//     // int midpoint{ min + ((max-min) / 2) }; // 这样计算中点可以避免溢出
//
//     if (array[midpoint] > target)
//     {
//         return binarySearch(array, target, min, midpoint - 1);
//     }
//     else if (array[midpoint] < target)
//     {
//         return binarySearch(array, target, midpoint + 1, max);
//     }
//
//     return midpoint;
// }

// 提示：
//
// `std::binary_search`在值存在于有序列表中时返回true。 `std::equal_range`返回
// 给定值第一个和最后一个元素的迭代器。
//
// 不要用这些函数来解本题，但将来如果需要二分查找，可以使用它们。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
    int array[100000000]{};

    for (auto x: array)
        std::cout << x << ' ';

    std::cout << '\n';

    return 0;
}
