// ==========================================================================
// 17.4 通过std::reference_wrapper创建引用的数组
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十七章 固定长度数组：std::array与c样式数组
// 原文: https://www.studycpp.cn/basic/chapter17/arr-ref/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "17.04-arr-ref.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · std::reference_wrapper
//   · std::ref和std::cref

// ==========================================================================
// 教程正文
// ==========================================================================

// 在上一课中，我们提到了数组可以包含任何对象类型的元素。这包括基本类型（例如
// int）的对象和具有复合类型（例如指向int的指针）的对象。

// [代码 1]
// #include <array>
// #include <iostream>
// #include <vector>
//
// int main()
// {
//     int x { 1 };
//     int y { 2 };
//
//     [[maybe_unused]] std::array valarr { x, y };   // int 数组
//     [[maybe_unused]] std::vector ptrarr { &x, &y }; // 指针数组
//
//     return 0;
// }

// 然而，由于引用不是对象，因此不能创建引用数组。数组的元素也必须可以被赋值，
// 而引用一旦绑定后就不能重新绑定。

// [代码 2]
// #include <array>
// #include <iostream>
//
// int main()
// {
//     int x { 1 };
//     int y { 2 };
//
//     [[maybe_unused]] std::array<int&, 2> refarr { x, y }; // 编译失败: 不能创建引用的数组
//
//     int& ref1 { x };
//     int& ref2 { y };
//     [[maybe_unused]] std::array valarr { ref1, ref2 }; // ok: 这是一个 std::array<int, 2>, 而不是引用的数组
//
//     return 0;
// }

// 如果需要引用数组，有一个解决方法。
//
// 在本课中，将在示例中使用std::array，但这同样适用于所有数组类型。
//

// ―――― std::reference_wrapper ――――

// std::reference_wrapper是一个标准库类模板，位于<functional>头文件中。它接受
// 类型模板参数T，然后表现得像对T的可修改左值引用。
//
// 关于std::reference_wrapper，有几点值得注意:
// - Operator=将重置std::reference_wrapper（更改正在引用的对象）。
// - std::reference_wrapper<T>将隐式转换为T&。
// - get()成员函数可用于获取T&。当我们想要更新被引用对象的值时，这很有用。
//
// 下面是一个简单的例子:

// [代码 3]
// #include <array>
// #include <functional> // for std::reference_wrapper
// #include <iostream>
//
// int main()
// {
//     int x { 1 };
//     int y { 2 };
//     int z { 3 };
//
//     std::array<std::reference_wrapper<int>, 3> arr { x, y, z };
//
//     arr[1].get() = 5; // 修改下标 1 处的值
//
//     std::cout << arr[1] << y << '\n'; // 修改了 arr[1] 和 y, 打印 55
//
//     return 0;
// }

// 此示例打印以下内容:
//
// 请注意，我们必须使用arr[1].get()=5，而不是arr[1]=5。后者是不明确的，因为编
// 译器无法判断我们是打算将std::reference_wrapper<int>重置为值5（无论如何这都
// 是非法的），还是更改正在引用的值。使用get()可以消除这种歧义。
//
// 当打印arr[1]时，编译器将意识到它不能打印std::reference_wrapper<int>，因此它
// 将隐式地将其转换为int&，然后可以打印它。因此，不需要在这里使用get()。
//

// ―――― std::ref和std::cref ――――

// 在C++17之前，CTAD（类模板参数演绎）不存在，因此需要显式列出类类型的所有模板
// 参数。因此，要创建std::reference_wrapper<int>，可以执行以下任一操作:

// [代码 4]
//     int x { 5 };
//
//     std::reference_wrapper<int> ref1 { x };        // C++11
//     auto ref2 { std::reference_wrapper<int>{ x }}; // C++11

// 在长的名称和必须显式列出模板参数的方式之下，创建许多这样的引用包装器可能是
// 一件痛苦的事情。
//
// 为了简化操作，C++提供了std::ref()和std::cref()函数作为快捷方式，用来创建
// std::reference_wrapper和const std::reference_wrapper包装的对象。请注意，这
// 些函数可以与auto一起使用，从而避免显式指定模板参数。

// [代码 5]
//     int x { 5 };
//     auto ref { std::ref(x) };   // C++11, 推导为 std::reference_wrapper<int>
//     auto cref { std::cref(x) }; // C++11, 推导为 std::reference_wrapper<const int>

// 当然，既然我们在C++17中有了CTAD，我们也可以这样做:

// [代码 6]
//     std::reference_wrapper ref1 { x };        // C++17
//     auto ref2 { std::reference_wrapper{ x }}; // C++17

// 但由于std::ref()和std::cref()的拼写较短，因此它们仍然广泛用于创建
// std::reference_wrapper对象。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <array>
#include <iostream>
#include <vector>

int main()
{
    int x { 1 };
    int y { 2 };

    [[maybe_unused]] std::array valarr { x, y };   // int 数组
    [[maybe_unused]] std::vector ptrarr { &x, &y }; // 指针数组

    return 0;
}
