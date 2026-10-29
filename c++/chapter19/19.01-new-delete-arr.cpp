// ==========================================================================
// 19.1 动态分配数组
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十九章 动态内存分配
// 原文: https://www.studycpp.cn/basic/chapter19/new-delete-arr/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "19.01-new-delete-arr.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 动态删除数组
//   · 动态数组使用几乎与固定数组相同
//   · 初始化动态分配的数组
//   · 调整数组大小
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 除了动态分配单个值外，我们还可以动态分配数组。与固定数组（数组大小必须在编
// 译时固定）不同，动态分配数组允许我们在运行时选择数组长度（这意味着长度不需
// 要是constexpr）。
//
// 要动态分配数组，我们使用数组形式的new和delete（通常称为new[]和delete[]）：

// [代码 1]
// #include <cstddef>
// #include <iostream>
//
// int main()
// {
//     std::cout << "Enter a positive integer: ";
//     std::size_t length{};
//     std::cin >> length;
//
//     int* array{ new int[length]{} }; // 使用数组 new。注意这里长度不再需要是常量了!
//
//     std::cout << "I just allocated an array of integers of length " << length << '\n';
//
//     array[0] = 5; // 将第 0 个元素设置为 5
//
//     delete[] array; // 使用数组 delete 进行回收
//
//     // 这里未将数组设置为nullptr，因为马上array变量要超出作用域了
//
//     return 0;
// }

// 因为我们分配的是数组，所以C++知道这里使用的是new的数组版本，而不是new的单个
// 值版本。
//
// 动态分配数组的长度类型为std::size_t。如果您使用的是非constexpr int，则需要
// 使用static_cast将长度转换为std::size_t。由于这被认为是一个窄化转换，编译器
// 会发出警告。
//
// 请注意，由于这块内存是从堆上分配的，因此数组大小可以相当大。您可以运行上面
// 的程序，并分配长度为1000000（甚至可能是100000000）的数组，通常不会出现问题。
// 试试看！因此，在C++中需要分配大量内存的程序通常会采用这种方式。
//
// 注
//
// 在这些课程中，我们将动态分配C样式的数组，这是最常见的动态分配数组类型。
//
// 虽然可以动态分配std::array，但在这种情况下，通常最好使用非动态分配的
// std::vector。
//

// ―――― 动态删除数组 ――――

// 删除动态分配的数组时，我们必须使用delete的数组版本，即delete[]。
//
// 这会告诉系统需要清理多个变量，而不是单个变量。新程序员最常见的错误之一，是
// 在删除动态分配的数组时使用delete而不是delete[]。在数组上使用非数组形式的
// delete将导致未定义的行为，例如数据损坏、内存泄漏、崩溃或其他问题。
//
// 关于数组delete[]，一个常见问题是：“delete[]如何知道要删除多少内存？”答案是，
// 数组new[]会跟踪分配给变量的内存量，因此数组delete[]可以删除适当的数量。不幸
// 的是，程序员无法访问这个大小/长度。
//

// ―――― 动态数组使用几乎与固定数组相同 ――――

// 在学习C样式数组退化时，我们知道固定数组保存第一个数组元素的内存地址。我们还
// 了解到，固定数组可以衰减为指向数组第一个元素的指针。在这种衰减形式中，固定
// 数组的长度不可用（因此，通过sizeof()也不能获得数组的大小），但在其他方面几
// 乎没有区别。
//
// 动态数组本质上也是指向数组第一个元素的指针。因此，它具有相同的限制，因为它
// 不知道自己的长度或大小。动态数组的功能与退化后的固定数组相同，但程序员需要
// 负责通过delete[]关键字释放动态数组。
//

// ―――― 初始化动态分配的数组 ――――

// 如果要将动态分配的数组初始化为0，语法非常简单：

// [代码 2]
// int* array{ new int[length]{} };

// 在C++11之前，没有简单的方法将动态数组初始化为非零值（初始化列表仅适用于固定
// 数组）。这意味着您必须循环遍历数组并显式分配元素值。

// [代码 3]
// int* array = new int[5];
// array[0] = 9;
// array[1] = 7;
// array[2] = 5;
// array[3] = 3;
// array[4] = 1;

// 这非常繁琐！
//
// 然而，从C++11开始，现在可以使用初始化列表初始化动态数组！

// [代码 4]
// int fixedArray[5] = { 9, 7, 5, 3, 1 }; // 初始化固定数组
// int* array{ new int[5]{ 9, 7, 5, 3, 1 } }; // C++11开始，初始化动态分配的数组
// // 使用auto，可以避免写两遍类型名
// auto* array{ new int[5]{ 9, 7, 5, 3, 1 } };

// 注意，该语法在数组长度和初始值列表之间没有运算符=。
//
// 为了一致性，还可以使用统一初始化来初始化固定数组：

// [代码 5]
// int fixedArray[]{ 9, 7, 5, 3, 1 }; // C++11 中初始化固定数组
// char fixedArray[]{ "Hello, world!" }; // C++11 中初始化固定数组

// 显式声明数组的长度是可选的。
//

// ―――― 调整数组大小 ――――

// 动态分配数组允许您在分配时设置数组长度。然而，C++并没有提供一种内置方法来调
// 整已经分配好的数组大小。可以通过动态分配新数组、复制元素并删除旧数组来绕过
// 此限制。然而，这很容易出错，特别是当元素类型是类时（这些类具有管理自身创建
// 方式的特殊规则）。
//
// 因此，我们建议避免自己这样做。请改用std::vector。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 编写一个程序，完成下列操作：
// - 询问用户想输入多少个名字。
// - 动态分配一个`std::string`数组。
// - 要求用户输入每一个名字。
// - 调用`std::sort`对这些名字排序（参见「18.0 对数组进行排序」和「17.8 指针
//   运算和下标」）。
// - 打印排序后的名字列表。
//
// `std::string`支持用比较运算符 < 和 > 比较字符串，不需要自己实现字符串比较。
//
// 程序的输出应与下面一致：

// [代码 6]
// How many names would you like to enter? 5
// Enter name #1: Jason
// Enter name #2: Mark
// Enter name #3: Alex
// Enter name #4: Chris
// Enter name #5: John
//
// Here is your sorted list:
// Name #1: Alex
// Name #2: Chris
// Name #3: Jason
// Name #4: John
// Name #5: Mark

// 提醒：
//
// 可以使用`std::getline()`读入包含空格的名字（见「5.8 std::string简介」）。
//
// 提醒：
//
// 要把`std::sort()`用于指向数组的指针，需要手工计算出起点和终点：

// [代码 7]
// std::sort(array, array + arrayLength);


// 【答案 · 查看答案】

// [代码 8]
// #include <algorithm> // std::sort
// #include <cstddef>
// #include <iostream>
// #include <string>
//
// std::size_t getNameCount()
// {
//     std::cout << "How many names would you like to enter? ";
//     std::size_t length{};
//     std::cin >> length;
//
//     return length;
// }
//
// // 要求用户输入所有名字
// void getNames(std::string* names, std::size_t length)
// {
//     for (std::size_t i{ 0 }; i < length; ++i)
//     {
//         std::cout << "Enter name #" << i + 1 << ": ";
//         std::getline(std::cin >> std::ws, names[i]);
//     }
// }
//
// // 打印排序后的名字
// void printNames(std::string* names, std::size_t length)
// {
//     std::cout << "\nHere is your sorted list:\n";
//
//     for (std::size_t i{ 0 }; i < length; ++i)
//         std::cout << "Name #" << i + 1 << ": " << names[i] << '\n';
// }
//
// int main()
// {
//     std::size_t length{ getNameCount() };
//
//     // 分配一个数组来保存这些名字
//     auto* names{ new std::string[length]{} };
//
//     getNames(names, length);
//
//     // 排序数组
//     std::sort(names, names + length);
//
//     printNames(names, length);
//
//     // 别忘了使用数组形式的 delete
//     delete[] names;
//     // 这里不需要把 names 置为 nullptr/0，因为它马上就要离开
//     // 反正它马上就会离开作用域。
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <cstddef>
#include <iostream>

int main()
{
    std::cout << "Enter a positive integer: ";
    std::size_t length{};
    std::cin >> length;

    int* array{ new int[length]{} }; // 使用数组 new。注意这里长度不再需要是常量了!

    std::cout << "I just allocated an array of integers of length " << length << '\n';

    array[0] = 5; // 将第 0 个元素设置为 5

    delete[] array; // 使用数组 delete 进行回收

    // 这里未将数组设置为nullptr，因为马上array变量要超出作用域了

    return 0;
}
