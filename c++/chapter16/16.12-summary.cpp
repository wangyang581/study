// ==========================================================================
// 16.12 第16章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十六章 动态数组：std::vector
// 原文: https://www.studycpp.cn/basic/chapter16/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "16.12-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 鼓励的话
//   · 章节回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 鼓励的话 ――――

// 这一章并不容易。我们讲解了许多内容，也看到了C++的一些缺点。恭喜你完成了这一
// 章！
//
// 数组是在C++程序中释放大量表达能力的关键之一。
//

// ―――― 章节回顾 ――――

// 容器是一种数据类型，为未命名对象（称为元素）的集合提供存储。当需要处理一组
// 相关的值时，我们通常使用容器。
//
// 容器中元素的数量通常称为它的长度（有时称为大小）。在C++中，术语“大小”也常用
// 于表示容器中的元素数。在大多数编程语言（包括C++）中，容器是同质的，这意味着
// 容器的元素需要具有相同类型。
//
// 容器库是C++标准库的一部分，它包含实现一些常见容器类型的各种类类型。实现容器
// 的类类型有时称为容器类。
//
// 数组是连续存储值序列的容器数据类型（意味着每个元素都放在相邻的内存位置，没
// 有间隙）。数组允许快速、直接访问任何元素。
//
// C++包含三种主要的数组类型：（C样式）数组、std::vector容器类和std::array容器
// 类。
//
// vector是C++标准容器库中实现数组的容器类之一。std::vector在<vector>头文件中
// 定义为类模板，具有用于定义元素类型的模板类型参数。因此，std::vector<int>声
// 明了一个元素类型为int的std::vector。
//
// 容器通常具有一个名为列表构造函数的特殊构造函数，它允许我们使用初始值设定项
// 列表构造容器实例（列表初始化）。
//
// 在C++中，访问数组元素最常见的方法是使用数组名称和下标运算符（运算符[]）。为
// 了选择特定元素，需要在下标运算符的方括号内提供一个整数值，用于标识要选择的
// 元素。该整数值称为下标（非正式地称为索引）。第一个元素使用索引0访问，第二个
// 元素使用索引1访问，以此类推。因为索引从0开始，而不是从1开始，所以我们说C++
// 中的数组是从零开始的。
//
// 运算符[]不执行任何边界检查，这意味着它不会检查索引是否位于0到N-1（包括0和
// N-1）的范围内。将无效索引传递给运算符[]会导致未定义行为。
//
// 数组是少数允许随机访问的容器类型之一，这意味着可以以相同的速度直接访问容器
// 中的每个元素，而不管容器中的元素数量如何。
//
// 构造类类型对象时，会优先选择匹配的列表构造函数，而不是其他匹配构造函数。使
// 用不是元素值的初始值设定项构造容器时，请使用直接初始化。

// [代码 1]
// std::vector v1 { 5 }; // 定义包含一个元素的vector `5`.
// std::vector v2 ( 5 ); // 定义包含五个元素的vector，元素被值初始化

// std::vector可以设置为const，但不能设置为constexpr。
//
// 每个标准库容器类都定义了一个名为size_type（有时写为T::size_type）的嵌套
// typedef成员，它是容器长度（以及索引，如果支持）的类型别名。size_type几乎总
// 是std::size_t的别名，但在极少数情况下可以重写为不同类型。可以合理地假设
// size_type是std::size_t的别名。
//
// 访问容器类的size_type成员时，必须使用容器类的完整模板化名称进行限定。例如，
// std::vector<int>::size_type。
//
// 可以使用size()成员函数查询容器类对象的长度，该函数会以无符号size_type返回长
// 度。在C++17中，还可以使用std::size()非成员函数。
//
// 在C++20中，std::ssize()非成员函数会以大型有符号整数类型（通常为
// std::ptrdiff_t，它通常用作std::size_t的有符号对应类型）返回长度。
//
// 使用at()成员函数访问数组元素会执行运行时边界检查（如果越界，则抛出类型为
// std::out_of_range的异常）。如果未捕获异常，则应用程序会被终止。
//
// 运算符[]和at()成员函数都支持使用非常数索引进行获取。然而，两者都希望索引的
// 类型为size_type，这是一个无符号整数类型。当索引为非constexpr时，这会导致符
// 号转换问题。
//
// 类型为std::vector的对象可以像其他对象一样传递给函数。这意味着，如果按值传递
// std::vector，就会生成一个昂贵的副本。因此，通常通过（const）引用传递
// std::vector，以避免这种复制。
//
// 我们可以使用函数模板将任何元素类型的std::vector传递到函数中。可以使用
// assert()来确保传入的vector具有正确的长度。
//
// 术语复制语义是指决定如何制作对象副本的规则。当我们说正在调用复制语义时，意
// 味着已经执行了某些操作来制作对象副本。
//
// 当数据所有权从一个对象转移到另一个对象时，我们说数据已经被移动。
//
// 移动语义是指决定如何将数据从一个对象移动到另一个对象的规则。当调用移动语义
// 时，会移动任何可以移动的数据成员，并复制任何无法移动的数据成员。移动数据而
// 不是复制数据的能力，可以让移动语义比复制语义更高效，特别是在可以用廉价移动
// 代替昂贵副本时。
//
// 通常，当用相同类型的对象初始化对象，或将相同类型的对象赋值给另一个对象时，
// 会使用复制语义（假设没有拷贝省略）。当对象类型支持移动语义，并且用于赋值或
// 初始化的对象是右值时，会自动使用移动语义。
//
// 可以按值返回支持移动的类型（如std::vector和std::string）。这样的类型会以较
// 低成本移动其值，而不是制作昂贵副本。
//
// 按某种顺序访问容器的每个元素称为遍历容器。
//
// 循环通常用于遍历数组，循环变量用作索引。请注意off-by-one错误，也就是循环体
// 少执行或多执行一次。
//
// 基于范围的for循环（有时也称为for-each循环）允许遍历容器，而不必显式使用索引。
// 遍历容器时，优先使用for-each。
//
// 在基于范围的for循环中使用类型演绎（auto），让编译器推断数组元素类型。每当您
// 通常会通过（const）引用传递该元素类型时，元素声明都应该使用（const）引用。
// 除非需要处理副本，否则可以考虑始终使用const auto&。这将确保即使后来更改了元
// 素类型，也不会发生复制。
//
// 非限定作用域枚举可以用作索引，并有助于提供有关索引含义的信息。
//
// 每当需要表示数组长度的枚举元素时，添加额外的“count”枚举元素是有用的。可以断
// 言或static_assert数组长度等于计数枚举元素，以确保数组使用了预期数量的初始值
// 设定项进行初始化。
//
// 长度必须在实例化点定义、之后不能更改的数组称为固定大小数组或固定长度数组。
// 动态数组（也称为可调整大小的数组）是大小可以在实例化后更改的数组。这种调整
// 大小的能力让std::vector变得特别。
//
// 实例化后，可以通过调用resize()成员函数并传入新的所需长度来调整std::vector大
// 小。
//
// 在std::vector的上下文中，容量表示std::vector为多少个元素分配了存储空间，长
// 度表示当前正在使用的元素数。可以通过capacity()成员函数查询std::vector的容量。
//
// 当std::vector更改其管理的存储量时，这个过程称为重新分配。由于重新分配通常需
// 要复制数组中的每个元素，因此它是一个昂贵过程。所以，我们希望尽可能避免重新
// 分配。
//
// 下标运算符（运算符[]）和at()成员函数的有效索引基于vector的长度，而不是容量。
//
// vector有一个名为shrink_to_fit()的成员函数，该函数请求vector收缩其容量以匹配
// 其长度。这个请求没有强制约束力。
//
// 元素添加到栈和从栈中删除的顺序可以描述为后进先出（LIFO）。添加到栈上的最后
// 一个元素会最先被移除。在编程中，栈是一种容器数据类型，其中元素的插入和删除
// 以后进先出的方式进行。这通常通过名为push和pop的两个操作实现。
//
// std::vector成员函数push_back()和emplace_back()会增加std::vector的长度，并在
// 容量不足以插入值时导致重新分配。当push触发重新分配时，std::vector通常会分配
// 一些额外容量，以便继续添加其他元素，而不会在下一次添加元素时立刻触发另一次
// 重新分配。
//
// resize()成员函数更改vector的长度和容量。reserve()成员函数仅更改容量。
//
// 要增加std::vector中的元素数，请执行以下操作：
// - 通过索引访问vector时使用resize()。这会更改vector长度，以便索引有效。
// - 使用栈操作访问vector时，请使用reserve()。这会在不更改vector长度的情况下
//   增加容量。
//
// push_back()和emplace_back()都会将元素推送到栈上。如果要推送的对象已经存在，
// 则push_back()和emplace_back()是等效的。然而，在创建临时对象并将其推送到
// vector上的情况下，emplace_back()可能更高效。在创建要添加到容器的新临时对象
// 时，或者在需要访问显式构造函数时，首选emplace_back()。否则，首选push_back()。
//
// std::vector<bool>有一个特殊实现，它会以类似将8个布尔值压缩到一个字节中的方
// 式，更有效地节省布尔值所需空间。
//
// std::vector<bool>并不是真正的vector（它在内存中不需要连续），也不包含bool值
// （而是包含一组bit），并且不满足C++对容器的定义。尽管在大多数情况下，
// std::vector<bool>的行为类似于vector，但它与标准库的其余部分并不完全兼容。能
// 与其他元素类型一起使用的代码，可能无法与std::vector<bool>一起使用。因此，通
// 常应避免使用std::vector<bool>。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 写出下列各项的定义。尽可能使用CTAD（见「13.11 类模板参数推导（CTAD）」）。
//
// a) 一个用前6个偶数初始化的`std::vector`。

// 【答案 · 查看答案】

// [代码 2]
// std::vector evens { 2, 4, 6, 8, 10, 12 };

// b) 一个用`1.2`、`3.4`、`5.6`和`7.8`初始化的常量`std::vector`。

// 【答案 · 查看答案】

// [代码 3]
// const std::vector d { 1.2, 3.4, 5.6, 7.8 }; // 提醒：std::vector 不能是 constexpr 的

// c) 一个由`std::string_view`构成的常量`std::vector`，用名字「Alex」「Brad」
// 「Charles」和「Dave」初始化。

// 【答案 · 查看答案】

// [代码 4]
// using namespace std::literals::string_view_literals; // 用于 sv 后缀
// const std::vector names { "Alex"sv, "Brad"sv, "Charles"sv, "Dave"sv }; // 需要 sv 后缀，CTAD 才能推导出 std::string_view

// d) 一个只含单个元素值`12`的`std::vector`。

// 【答案 · 查看答案】

// [代码 5]
// std::vector v { 12 };

// 使用元素值初始化`std::vector`时，应当使用列表初始化。
//
// e) 一个包含12个int元素的`std::vector`，初始化为默认值。

// 【答案 · 显示提示】
// 想一想这种情况能否使用CTAD。

// 【答案 · 查看答案】

// [代码 6]
// std::vector<int> v( 12 );

// 使用初始长度初始化`std::vector`时，必须使用直接初始化。同时必须显式指定类型
// 模板实参，因为没有初始化值可以用来推导元素类型。

// ▼ 问题 2
// 假设你在写一个游戏，玩家可以持有3种物品：治疗药水、火把和箭矢。
//
// 第1步
//
// 在一个命名空间中定义一个非限定作用域枚举，用于区分不同的物品类型。定义一个
// `std::vector`来保存玩家持有的每种物品的数量。玩家初始时应拥有1瓶治疗药水、5
// 个火把和10支箭矢。用assert确保数组的初始化值个数正确。
//
// 提示：定义一个表示数量的枚举元素，并在assert中使用它。
//
// 程序的输出应当如下：

// [文本/输出]
// You have 16 total items


// 【答案 · 查看答案】

// [代码 7]
// #include <cassert>
// #include <iostream>
// #include <vector>
//
// namespace Items
// {
//     enum Type
//     {
//         health_potion,
//         torch,
//         arrow,
//         max_items
//     };
// }
//
// // 背包中物品的数量都是整数，因此这里不需要函数模板
// int countTotalItems(const std::vector<int>& inventory)
// {
//     int sum { 0 };
//     for (auto e: inventory)
//         sum += e;
//     return sum;
// }
//
// int main()
// {
//     std::vector inventory { 1, 5, 10 };
//     assert(std::size(inventory) == Items::max_items); // 确保背包的初始化值个数正确
//
//     std::cout << "You have " << countTotalItems(inventory) << " total items\n";
//
//     return 0;
// }

// 第2步
//
// 修改上一步的程序，使其输出：

// [文本/输出]
// You have 1 health potion
// You have 5 torches
// You have 10 arrows
// You have 16 total items

// 使用循环打印每种物品的数量和名称。处理好名称的单复数。

// 【答案 · 查看答案】

// [代码 8]
// #include <cassert>
// #include <iostream>
// #include <string_view>
// #include <type_traits> // 用于 std::is_integral 和 std::is_enum
// #include <vector>
//
// namespace Items
// {
//     enum Type: int
//     {
//         health_potion,
//         torch,
//         arrow,
//         max_items
//     };
// }
//
// std::string_view getItemNamePlural(Items::Type type)
// {
//     switch (type)
//     {
//         case Items::health_potion:  return "health potions";
//         case Items::torch:          return "torches";
//         case Items::arrow:          return "arrows";
//
//         default:                    return "???";
//     }
// }
//
// std::string_view getItemNameSingular(Items::Type type)
// {
//     switch (type)
//     {
//         case Items::health_potion:  return "health potion";
//         case Items::torch:          return "torch";
//         case Items::arrow:          return "arrow";
//
//         default:                    return "???";
//     }
// }
//
// // 把 `value` 转换成 std::size_t 类型对象的辅助函数
// // UZ 是 std::size_t 类型字面值的后缀。
// template <typename T>
// constexpr std::size_t toUZ(T value)
// {
//     // 确保 T 是整型
//     static_assert(std::is_integral<T>() || std::is_enum<T>());
//
//     return static_cast<std::size_t>(value);
// }
//
// void printInventoryItem(const std::vector<int>& inventory, Items::Type type)
// {
//     bool plural { inventory[toUZ(type)] != 1 };
//     std::cout << "You have " << inventory[toUZ(type)] << ' ';
//     std::cout << (plural ? getItemNamePlural(type) : getItemNameSingular(type)) << '\n';
// }
//
// // 背包中物品的数量都是整数，因此这里不需要函数模板
// int countTotalItems(const std::vector<int>& inventory)
// {
//     int sum { 0 };
//     for (auto e: inventory)
//         sum += e;
//     return sum;
// }
//
// int main()
// {
//     std::vector inventory { 1, 5, 10 };
//     assert(std::size(inventory) == Items::max_items); // 确保背包的初始化值个数正确
//
//     // 由于无法用范围 for 遍历枚举类型，这里需要使用传统的 for 循环
//     for (int i=0; i < Items::max_items; ++i)
//     {
//         auto item { static_cast<Items::Type>(i) };
//         printInventoryItem(inventory, item);
//     }
//
//     std::cout << "You have " << countTotalItems(inventory) << " total items\n";
//
//     return 0;
// }


// ▼ 问题 3
// 编写一个函数，接受一个`std::vector`，返回一个`std::pair`，其中包含数组中最
// 小值元素和最大值元素的下标。`std::pair`的说明文档可以在这里找到。对下面两个
// vector调用该函数：

// [代码 9]
//     std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
//     std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };

// 程序应当输出如下内容：

// [文本/输出]
// With array ( 3, 8, 2, 5, 7, 8, 3 ):
// The min element has index 2 and value 2
// The max element has index 1 and value 8
//
// With array ( 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 ):
// The min element has index 4 and value 1.2
// The max element has index 5 and value 8.8


// 【答案 · 查看答案】

// [代码 10]
// #include <iostream>
// #include <vector>
//
// template <typename T>
// std::pair<std::size_t, std::size_t> findMinMaxIndices(const std::vector<T>& v)
// {
//     // 假设下标 0 的元素既是最小值也是最大值
//     std::size_t minIndex { 0 };
//     std::size_t maxIndex { 0 };
//
//     // 检查其余元素，看能否找到更小或更大的元素
//     for (std::size_t index { 1 }; index < v.size(); ++index)
//     {
//         if (v[index] < v[minIndex])
//             minIndex = index;
//         if (v[index] > v[maxIndex])
//             maxIndex = index;
//     }
//
//     return { minIndex, maxIndex };
// }
//
// template <typename T>
// void printArray(const std::vector<T>& v)
// {
//     bool comma { false };
//     std::cout << "With array ( ";
//     for (const auto& e: v)
//     {
//         if (comma)
//             std::cout << ", ";
//
//         std::cout << e;
//         comma = true;
//     }
//     std::cout << " ):\n";
// }
//
// int main()
// {
//     std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
//     printArray(v1);
//
//     auto m1 { findMinMaxIndices(v1) };
//     std::cout << "The min element has index " << m1.first << " and value " << v1[m1.first] << '\n';
//     std::cout << "The max element has index " << m1.second << " and value " << v1[m1.second] << '\n';
//
//     std::cout << '\n';
//
//     std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
//     printArray(v2);
//
//     auto m2 { findMinMaxIndices(v2) };
//     std::cout << "The min element has index " << m2.first << " and value " << v2[m2.first] << '\n';
//     std::cout << "The max element has index " << m2.second << " and value " << v2[m2.second] << '\n';
//
//     return 0;
// }


// ▼ 问题 4
// 修改上一题的程序，使用户可以输入任意多个整数。当用户输入`-1`时停止接受输入。
//
// 打印这个vector，并找出其中的最小值和最大值元素。
//
// 当输入为`3 8 5 2 3 7 -1`时，程序应当产生如下输出：

// [文本/输出]
// Enter numbers to add (use -1 to stop): 3 8 5 2 3 7 -1
// With array ( 3, 8, 5, 2, 3, 7 ):
// The min element has index 3 and value 2
// The max element has index 1 and value 8

// 如果用户第一个输入就是`-1`，请做合理的处理。

// 【答案 · 查看答案】

// [代码 11]
// #include <iostream>
// #include <limits>
// #include <vector>
//
// template <typename T>
// std::pair<std::size_t, std::size_t> findMinMaxIndices(const std::vector<T>& v)
// {
//     // 假设下标 0 的元素既是最小值也是最大值
//     std::size_t minIndex { 0 };
//     std::size_t maxIndex { 0 };
//
//     // 检查其余元素，看能否找到更小或更大的元素
//     for (std::size_t index { 1 }; index < v.size(); ++index)
//     {
//         if (v[index] < v[minIndex])
//             minIndex = index;
//         if (v[index] > v[maxIndex])
//             maxIndex = index;
//     }
//
//     return { minIndex, maxIndex };
// }
//
// template <typename T>
// void printArray(const std::vector<T>& v)
// {
//     bool comma { false };
//     std::cout << "With array ( ";
//     for (const auto& e: v)
//     {
//         if (comma)
//             std::cout << ", ";
//
//         std::cout << e;
//         comma = true;
//     }
//     std::cout << " ):\n";
// }
//
// int main()
// {
//     std::vector<int> v1 { };
//     std::cout << "Enter numbers to add (use -1 to stop): ";
//
//     while (true)
//     {
//         int input{};
//         std::cin >> input;
//         if (input == -1)
//             break;
//
//         if (!std::cin) // 如果上一次提取失败
//         {
//             std::cin.clear(); // 让流回到「正常」工作模式
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 并移除错误的输入
//             continue;
//         }
//
//         v1.push_back(input);
//     }
//
//     // 如果数组为空
//     if (v1.size() == 0)
//     {
//         std::cout << "The array has no elements\n";
//     }
//     else
//     {
//         printArray(v1);
//
//         auto m1 { findMinMaxIndices(v1) };
//         std::cout << "The min element has index " << m1.first << " and value " << v1[m1.first] << '\n';
//         std::cout << "The max element has index " << m1.second << " and value " << v1[m1.second] << '\n';
//     }
//
//     return 0;
// }


// ▼ 问题 5
// 我们来实现C++man这个游戏（它是经典儿童游戏「吊死鬼」（Hangman）的变体）。
//
// 如果你从没玩过，下面是简化的规则：
//
// 总体规则：
// - 计算机随机挑选一个单词，并为单词中的每个字母画一条下划线。
// - 如果玩家在猜错X次（X可配置）之前猜出了单词中的所有字母，就算获胜。
//
// 每一轮：
// - 玩家猜一个字母。
// - 如果玩家之前已经猜过这个字母，它不算数，游戏继续进行。
// - 如果某条下划线对应这个字母，就把这些下划线替换为该字母，游戏继续进行。
// - 如果没有任何下划线对应这个字母，玩家就用掉一次猜错机会。
//
// 状态显示：
// - 玩家应当知道自己还剩几次猜错机会。
// - 玩家应当知道自己猜错过的字母（按字母顺序排列）。
//
// 由于这是C++man，我们用`+`符号表示剩余的猜错机会。如果`+`用完了，你就输了。
//
// 下面是完成后的游戏输出示例：

// [文本/输出]
// Welcome to C++man (a variant of Hangman)
// To win: guess the word.  To lose: run out of pluses.
//
// The word: ________   Wrong guesses: ++++++
// Enter your next letter: a
// No, 'a' is not in the word!
//
// The word: ________   Wrong guesses: +++++a
// Enter your next letter: b
// Yes, 'b' is in the word!
//
// The word: b_______   Wrong guesses: +++++a
// Enter your next letter: c
// Yes, 'c' is in the word!
//
// The word: b__cc___   Wrong guesses: +++++a
// Enter your next letter: d
// No, 'd' is not in the word!
//
// The word: b__cc___   Wrong guesses: ++++ad
// Enter your next letter: %
// That wasn't a valid input.  Try again.
//
// The word: b__cc___   Wrong guesses: ++++ad
// Enter your next letter: d
// You already guessed that.  Try again.
//
// The word: b__cc___   Wrong guesses: ++++ad
// Enter your next letter: e
// No, 'e' is not in the word!
//
// The word: b__cc___   Wrong guesses: +++ade
// Enter your next letter: f
// No, 'f' is not in the word!
//
// The word: b__cc___   Wrong guesses: ++adef
// Enter your next letter: g
// No, 'g' is not in the word!
//
// The word: b__cc___   Wrong guesses: +adefg
// Enter your next letter: h
// No, 'h' is not in the word!
//
// The word: b__cc___   Wrong guesses: adefgh
// You lost!  The word was: broccoli

// 第1步
//
// 目标：
// - 先定义单词列表，并编写一个随机选词函数。可以借助「8.14 全局随机数」中的
//   Random.h。
//
// 任务：
// - 首先定义一个名为`WordList`的命名空间。初始的单词列表为：「mystery」「
//   broccoli」「account」「almost」「spaghetti」「opinion」「beautiful」「
//   distance」「luggage」。你也可以自行添加其他单词。
// - 编写一个函数，随机挑选一个单词并显示它。多次运行程序，确认选出的单词是随
//   机的。
//
// 这一步骤的输出示例如下：

// [文本/输出]
// Welcome to C++man (a variant of Hangman)
// To win: guess the word.  To lose: run out of pluses.
//
// The word is: broccoli


// 【答案 · 查看答案】

// [代码 12]
// #include <iostream>
// #include <vector>
// #include "Random.h"
//
// namespace WordList
// {
//     // 在这里定义你的单词列表
//     std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };
//
//     std::string_view getRandomWord()
//     {
//         return words[Random::get<std::size_t>(0, words.size()-1)];
//     }
// }
//
// int main()
// {
//     std::cout << "Welcome to C++man (a variant of Hangman)\n";
//     std::cout << "To win: guess the word.  To lose: run out of pluses.\n";
//
//     std::cout << "The word is: " << WordList::getRandomWord();
//
//     return 0;
// }

// 第2步
//
// 开发复杂程序时，我们希望增量式地推进：每次加一两样东西，然后确认它们能正常
// 工作。接下来加什么比较合理？
//
// 目标：
// - 能够画出游戏的基本状态，把单词显示为下划线。
// - 接收用户输入的一个字母，并做基本的错误校验。
//
// 这一步骤中，我们还不需要记录用户已经输入过哪些字母。
//
// 这一步骤的输出示例如下：

// [文本/输出]
// Welcome to C++man (a variant of Hangman)
// To win: guess the word.  To lose: run out of pluses.
//
// The word: ________
// Enter your next letter: %
// That wasn't a valid input.  Try again.
// Enter your next letter: a
// You entered: a

// 任务：
// - 创建一个名为`Session`的类，用来保存一局游戏中需要管理的所有数据。目前我
//   们只需要知道随机选出的单词。
// - 创建一个函数，显示游戏的基本状态，把单词显示为下划线。
// - 创建一个函数，接收用户输入的一个字母。做基本的输入校验，过滤掉非字母字符
//   和多余输入。

// 【答案 · 查看答案】

// [代码 13]
// #include <iostream>
// #include <string_view>
// #include <vector>
// #include "Random.h"
//
// namespace WordList
// {
//     // 在这里定义你的单词列表
//     std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };
//
//     std::string_view getRandomWord()
//     {
//         return words[Random::get<std::size_t>(0, words.size()-1)];
//     }
// }
//
// class Session
// {
// private:
//     // 游戏会话数据
//     std::string_view m_word { WordList::getRandomWord() };
//
// public:
//     std::string_view getWord() const { return m_word; }
// };
//
// void draw(const Session& s)
// {
//     std::cout << '\n';
//
//     std::cout << "The word: ";
//     for ([[maybe_unused]] auto c: s.getWord()) // 逐个字符遍历单词
//     {
//         std::cout << '_';
//     }
//
//     std::cout << '\n';
// }
//
// char getGuess()
// {
//     while (true)
//     {
//         std::cout << "Enter your next letter: ";
//
//         char c{};
//         std::cin >> c;
//
//         // 如果用户的输入有问题，就重新输入
//         if (!std::cin)
//         {
//             // 修正流的状态
//             std::cin.clear();
//             std::cout << "That wasn't a valid input.  Try again.\n";
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             continue;
//         }
//
//         // 清除多余的输入
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//         // 如果用户输入了无效字符，就重新输入
//         if (c < 'a' || c > 'z')
//         {
//             std::cout << "That wasn't a valid input.  Try again.\n";
//             continue;
//         }
//
//         return c;
//     }
// }
//
// int main()
// {
//     std::cout << "Welcome to C++man (a variant of Hangman)\n";
//     std::cout << "To win: guess the word.  To lose: run out of pluses.\n";
//
//     Session s{};
//
//     draw(s);
//     char c { getGuess() };
//     std::cout << "You guessed: " << c << '\n';
//
//     return 0;
// }

// 第3步
//
// 现在我们已经能够显示部分游戏状态并获取用户输入，接下来把用户输入整合到游戏
// 里。
//
// 目标：
// - 记录用户已经猜过哪些字母。
// - 正确显示已猜出的字母。
// - 实现一个基本的游戏循环。
//
// 任务：
// - 更新Session类，记录目前为止猜过哪些字母。
// - 修改显示游戏状态的函数，同时显示下划线和已经猜对的字母。
// - 更新输入处理函数，拒绝已经猜过的字母。
// - 编写一个执行6次后结束的循环（便于测试上面的内容）。
//
// 这一步骤中，我们还不需要告诉用户他们猜的字母是否在单词中（但会在游戏状态显
// 示中体现出来）。
//
// 这一步的难点在于决定如何保存「用户猜过哪些字母」的信息。有几种可行的做法。
// 提示：字母的数量是固定的，而且这件事你会做很多次。

// 【答案 · 显示提示】
// 为每个字母使用一个`bool`，比维护一个字母列表、每次都要在列表中查找是否存在
// 某个字母，更简单也更快。

// 【答案 · 显示提示】
// 这里可以使用`std::vector<bool>`，因为我们不会用到标准库的其他功能。

// 【答案 · 显示提示】
// 可以用`(letter % 32)-1`把字母转换成数组下标。大小写字母都适用。
//
// 这一步骤的输出示例如下：

// [文本/输出]
// Welcome to C++man (a variant of Hangman)
// To win: guess the word.  To lose: run out of pluses.
//
// The word: ________
// Enter your next letter: a
//
// The word: ____a___
// Enter your next letter: a
// You already guessed that.  Try again.
// Enter your next letter: b
//
// The word: ____a___
// Enter your next letter: c
//
// The word: ____a___
// Enter your next letter: d
//
// The word: d___a___
// Enter your next letter: e
//
// The word: d___a__e
// Enter your next letter: f
//
// The word: d___a__e
// Enter your next letter: g


// 【答案 · 查看答案】

// [代码 14]
// #include <iostream>
// #include <string_view>
// #include <vector>
// #include "Random.h"
//
// namespace WordList
// {
//     // 在这里定义你的单词列表
//     std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };
//
//     std::string_view getRandomWord()
//     {
//         return words[Random::get<std::size_t>(0, words.size()-1)];
//     }
// }
//
// class Session
// {
// private:
//     // 游戏会话数据
//     std::string_view m_word { WordList::getRandomWord() };
//     std::vector<bool> m_letterGuessed { std::vector<bool>(26) };
//
//     std::size_t toIndex(char c) const { return static_cast<std::size_t>((c % 32)-1); }
//
// public:
//     std::string_view getWord() const { return m_word; }
//
//     bool isLetterGuessed(char c) const { return m_letterGuessed[toIndex(c)]; }
//     void setLetterGuessed(char c) { m_letterGuessed[toIndex(c)] = true; }
// };
//
// void draw(const Session& s)
// {
//     std::cout << '\n';
//
//     std::cout << "The word: ";
//     for (auto c: s.getWord()) // 逐个字符遍历单词
//     {
//         if (s.isLetterGuessed(c))
//             std::cout << c;
//         else
//             std::cout << '_';
//     }
//
//     std::cout << '\n';
// }
//
// char getGuess(const Session& s)
// {
//     while (true)
//     {
//         std::cout << "Enter your next letter: ";
//
//         char c{};
//         std::cin >> c;
//
//         // 如果用户的输入有问题，就重新输入
//         if (!std::cin)
//         {
//             // 修正流的状态
//             std::cin.clear();
//             std::cout << "That wasn't a valid input.  Try again.\n";
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             continue;
//         }
//
//         // 清除多余的输入
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//         // 如果用户输入了无效字符，就重新输入
//         if (c < 'a' || c > 'z')
//         {
//             std::cout << "That wasn't a valid input.  Try again.\n";
//             continue;
//         }
//
//         // 如果这个字母已经猜过，就重新输入
//         if (s.isLetterGuessed(c))
//         {
//             std::cout << "You already guessed that.  Try again.\n";
//             continue;
//         }
//
//         // 能运行到这里，说明这次猜测一定合法
//         return c;
//     }
// }
//
// int main()
// {
//     std::cout << "Welcome to C++man (a variant of Hangman)\n";
//     std::cout << "To win: guess the word.  To lose: run out of pluses.\n";
//
//     Session s {};
//
//     int count { 6 };
//     while (count--)
//     {
//         draw(s);
//         char c { getGuess(s) };
//         s.setLetterGuessed(c);
//     }
//
//     // 绘制游戏的最终状态
//     draw(s);
//
//     return 0;
// }

// 第4步
//
// 目标：完成这个游戏。
//
// 任务：
// - 增加显示剩余猜错次数的功能。
// - 增加显示猜错的字母的功能。
// - 增加获胜/失败条件以及对应的提示文字。

// 【答案 · 查看答案】

// [代码 15]
// #include <iostream>
// #include <string_view>
// #include <vector>
// #include "Random.h"
//
// namespace Settings
// {
//     constexpr int wrongGuessesAllowed { 6 };
// }
//
// namespace WordList
// {
//     // 在这里定义你的单词列表
//     std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };
//
//     std::string_view getRandomWord()
//     {
//         return words[Random::get<std::size_t>(0, words.size()-1)];
//     }
// }
//
// class Session
// {
// private:
//     // 游戏会话数据
//     std::string_view m_word { WordList::getRandomWord() };
//     int m_wrongGuessesLeft { Settings::wrongGuessesAllowed };
//     std::vector<bool> m_letterGuessed { std::vector<bool>(26) };
//
//     std::size_t toIndex(char c) const { return static_cast<std::size_t>((c % 32)-1); }
//
// public:
//     std::string_view getWord() const { return m_word; }
//
//     int wrongGuessesLeft() const { return m_wrongGuessesLeft; }
//     void removeGuess() { --m_wrongGuessesLeft; }
//
//     bool isLetterGuessed(char c) const { return m_letterGuessed[toIndex(c)]; }
//     void setLetterGuessed(char c) { m_letterGuessed[toIndex(c)] = true; }
//
//     bool isLetterInWord(char c) const
//     {
//         for (auto ch: m_word) // 逐个字符遍历单词
//         {
//             if (ch == c)
//                 return true;
//         }
//
//         return false;
//     }
//
//     bool won()
//     {
//         for (auto c: m_word) // 逐个字符遍历单词
//         {
//             if (!isLetterGuessed(c))
//                 return false;
//         }
//
//         return true;
//     }
// };
//
// void draw(const Session& s)
// {
//     std::cout << '\n';
//
//     std::cout << "The word: ";
//     for (auto c: s.getWord()) // 逐个字符遍历单词
//     {
//         if (s.isLetterGuessed(c))
//             std::cout << c;
//         else
//             std::cout << '_';
//     }
//
//     std::cout << "   Wrong guesses: ";
//     for (int i=0; i < s.wrongGuessesLeft(); ++i)
//         std::cout << '+';
//
//     for (char c='a'; c <= 'z'; ++c)
//         if (s.isLetterGuessed(c) && !s.isLetterInWord(c))
//             std::cout << c;
//
//     std::cout << '\n';
// }
//
// char getGuess(const Session& s)
// {
//     while (true)
//     {
//         std::cout << "Enter your next letter: ";
//
//         char c{};
//         std::cin >> c;
//
//         // 如果用户的输入有问题，就重新输入
//         if (!std::cin)
//         {
//             // 修正流的状态
//             std::cin.clear();
//             std::cout << "That wasn't a valid input.  Try again.\n";
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             continue;
//         }
//
//         // 清除多余的输入
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//         // 如果用户输入了无效字符，就重新输入
//         if (c < 'a' || c > 'z')
//         {
//             std::cout << "That wasn't a valid input.  Try again.\n";
//             continue;
//         }
//
//         // 如果这个字母已经猜过，就重新输入
//         if (s.isLetterGuessed(c))
//         {
//             std::cout << "You already guessed that.  Try again.\n";
//             continue;
//         }
//
//         // 能运行到这里，说明这次猜测一定合法
//         return c;
//     }
// }
//
// void handleGuess(Session &s, char c)
// {
//     s.setLetterGuessed(c);
//
//     if (s.isLetterInWord(c))
//     {
//         std::cout << "Yes, '" << c << "' is in the word!\n";
//         return;
//     }
//
//     std::cout << "No, '" << c << "' is not in the word!\n";
//     s.removeGuess();
// }
//
// int main()
// {
//     std::cout << "Welcome to C++man (a variant of Hangman)\n";
//     std::cout << "To win: guess the word.  To lose: run out of pluses.\n";
//
//     Session s{};
//
//     while (s.wrongGuessesLeft() && !s.won())
//     {
//         draw(s);
//         char c { getGuess(s) };
//         handleGuess(s, c);
//     }
//
//     // 绘制游戏的最终状态
//     draw(s);
//
//     if (!s.wrongGuessesLeft())
//         std::cout << "You lost!  The word was: " << s.getWord() << '\n';
//     else
//         std::cout << "You won!\n";
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <cassert>
#include <iostream>
#include <vector>

namespace Items
{
    enum Type
    {
        health_potion,
        torch,
        arrow,
        max_items
    };
}

// 背包中物品的数量都是整数，因此这里不需要函数模板
int countTotalItems(const std::vector<int>& inventory)
{
    int sum { 0 };
    for (auto e: inventory)
        sum += e;
    return sum;
}

int main()
{
    std::vector inventory { 1, 5, 10 };
    assert(std::size(inventory) == Items::max_items); // 确保背包的初始化值个数正确

    std::cout << "You have " << countTotalItems(inventory) << " total items\n";

    return 0;
}
