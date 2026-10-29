// ==========================================================================
// 16.7 基于范围的for循环（range for / for each）
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十六章 动态数组：std::vector
// 原文: https://www.studycpp.cn/basic/chapter16/range-for/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "16.07-range-for.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 基于范围的for循环
//   · 使用auto关键字进行类型自动推导
//   · 尽量避免使用拷贝
//   · 什么时候使用 auto，auto& 或 const auto&
//   · 其他标准容器类型
//   · 获取当前元素的索引
//   · 基于范围的反向循环（C++20）
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 前面展示了使用for循环迭代数组每个元素的示例，其中使用循环变量作为索引。下面
// 是一个这样的例子：

// [代码 1]
// #include <iostream>
// #include <vector>
//
// int main()
// {
//     std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
//
//     std::size_t length { fibonacci.size() };
//     for (std::size_t index { 0 }; index < length; ++index)
//        std::cout << fibonacci[index] << ' ';
//
//     std::cout << '\n';
//
//     return 0;
// }

// 尽管for循环提供了一种方便而灵活的数组迭代方法，但它们也很容易写错，容易出现
// 索引越界错误，也容易遇到数组索引变量的符号问题。
//
// 由于遍历数组非常常见，C++支持另一种类型的for循环，称为基于范围的for循环（有
// 时也称为for each循环）。该循环允许遍历容器，而不必显式使用索引。基于范围的
// for循环更简单、更安全，并且可以与C++中的所有常见数组类型（包括std::vector、
// std::array和C样式数组）一起使用。
//

// ―――― 基于范围的for循环 ――――

// 基于范围的for语句的语法如下所示：

// [代码 2]
// for (元素声明 : 数组对象)
//    语句;

// 遇到基于范围的for循环时，循环会迭代“数组对象”中的每个元素。每次迭代时，当前
// 数组元素的值会被赋给“元素声明”中声明的变量，然后执行语句。
//
// 为了获得最佳结果，“元素声明”应该与数组元素具有相同类型，否则将发生类型转换。
//
// 下面是一个简单示例，使用基于范围的for循环打印名为fibonacci的数组中的所有元
// 素：

// [代码 3]
// #include <iostream>
// #include <vector>
//
// int main()
// {
//     std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
//
//     for (int num : fibonacci) // 迭代 fibonacci 里的每个元素，将其拷贝到 `num`
//        std::cout << num << ' '; // 打印 `num` 的值
//
//     std::cout << '\n';
//
//     return 0;
// }

// 这将打印：

// [文本/输出]
// 0 1 1 2 3 5 8 13 21 34 55 89

// 注意，这个例子不需要使用数组长度，也不需要索引数组！
//
// 让我们仔细看看它是如何工作的。这个基于范围的for循环会遍历fibonacci中的所有
// 元素。第一次迭代时，变量num被赋为第一个元素（0）的值。然后，程序执行关联语
// 句，将num（0）的值打印到控制台。第二次迭代时，num被赋为第二个元素（1）的值。
// 关联语句再次执行，打印1。基于范围的for循环会继续依次迭代每个数组元素，并为
// 每个元素执行关联语句，直到数组中没有剩余元素可供迭代。此时，循环终止，程序
// 继续执行（打印换行，然后将0返回给操作系统）。
//
// 由于num被赋为数组元素的值，这意味着数组元素会被复制（对于某些类型，这可能很
// 昂贵）。
//
// 关键点
//
// 声明的元素（上例中的num）不是数组索引。相反，它会被赋为当前迭代到的数组元素
// 值。
//
// 最佳实践
//
// 遍历容器时，优先使用基于范围的for循环。
//

// ―――― 使用auto关键字进行类型自动推导 ――――

// 因为元素声明应该与数组元素具有相同类型（以防止发生类型转换），所以这里非常
// 适合使用auto关键字，让编译器为我们推断数组元素类型。这样，就不必冗余地指定
// 类型，也不会因为手动输入类型而出错。
//
// 下面是与上面相同的示例，但使用auto作为num的类型：

// [代码 4]
// #include <iostream>
// #include <vector>
//
// int main()
// {
//     std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
//
//     for (auto num : fibonacci) // 编译器将会自动推导 num 的类型是 `int`
//        std::cout << num << ' ';
//
//     std::cout << '\n';
//
//     return 0;
// }

// 由于std::vector fibonacci包含int类型的元素，因此num会被推断为int。
//
// 使用auto的另一个好处是，如果数组元素类型以后发生变化（例如从int改成long），
// auto会自动推断更新后的元素类型，确保它们保持同步（并防止发生类型转换）。
//
// 最佳实践
//
// 将类型演绎（auto）与基于范围的for循环一起使用，以使编译器推断数组元素的类型。
//

// ―――― 尽量避免使用拷贝 ――――

// 考虑以下基于范围的for循环，它会迭代std::string数组：

// [代码 5]
// #include <iostream>
// #include <string>
// #include <vector>
//
// int main()
// {
//     std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" };
//
//     for (auto word : words)
//         std::cout << word << ' ';
//
//     std::cout << '\n';
//
//     return 0;
// }

// 对于这个循环的每次迭代，words数组中的下一个std::string元素都会被赋值（复制）
// 到变量word中。复制std::string的开销很大，这就是为什么我们通常通过常量引用将
// std::string传递给函数。我们希望避免复制成本高昂的对象，除非确实需要副本。在
// 当前情况下，我们只是打印副本的值，然后副本就会被销毁。如果可以避免复制，而
// 只是引用实际的数组元素，那会更好。
//
// 幸运的是，可以通过将“元素声明”设置为（const）引用来做到这一点：

// [代码 6]
// #include <iostream>
// #include <string>
// #include <vector>
//
// int main()
// {
//     std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" };
//
//     for (const auto& word : words) // word 现在是常量引用
//         std::cout << word << ' ';
//
//     std::cout << '\n';
//
//     return 0;
// }

// 在上面的示例中，word现在是常量引用。在该循环的每次迭代中，word都会绑定到下
// 一个数组元素。这允许我们访问数组元素的值，而不必制作昂贵副本。
//
// 如果引用是非常量的，它也可以用于更改数组中的值（如果“元素声明”是值的副本，
// 则做不到这一点）。
//

// ―――― 什么时候使用 auto，auto& 或 const auto& ――――

// 通常，可廉价复制的类型使用auto，需要更改的对象使用 auto&，复制成本高的类型
// 使用 const auto&。但对于基于范围的for循环，许多开发人员认为最好始终使用
// const auto&，因为它更经得起未来变化。
//
// 例如，考虑以下示例：

// [代码 7]
// #include <iostream>
// #include <string_view>
// #include <vector>
//
// int main()
// {
//     std::vector<std::string_view> words{ "peter", "likes", "frozen", "yogurt" }; // 元素是 std::string_view
//
//     for (auto word : words) // string_view 通常按值传递，所以这里使用auto
//         std::cout << word << ' ';
//
//     std::cout << '\n';
//
//     return 0;
// }

// 在这个例子中，有一个包含std::string_view对象的std::vector。由于
// std::string_view通常按值传递，因此使用auto似乎是合适的。
//
// 但考虑一下，如果后来将words更新为std::string数组，会发生什么。

// [代码 8]
// #include <iostream>
// #include <string>
// #include <vector>
//
// int main()
// {
//     std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" }; // 这里修改了
//
//     for (auto word : words) // 可能这里也需要修改了
//         std::cout << word << ' ';
//
//     std::cout << '\n';
//
//     return 0;
// }

// 基于范围的for循环仍然可以很好地编译和执行，但word现在会被推断为std::string。
// 由于使用的是auto，循环会默默制作std::string元素的昂贵副本。性能会受到巨大影
// 响！
//
// 有两种合理方法可以确保不会发生这种情况：
// - 不要在基于范围的for循环中使用类型推导。如果显式将元素类型指定为
//   std::string_view，那么当数组稍后更新为std::string时，std::string元素会隐
//   式转换为std::string_view，这没有问题。如果数组被更新为其他不可转换的类型，
//   编译器会报错，我们也能据此判断此时应该怎么做。
// - 当不想处理副本时，如果在基于范围的for循环中使用类型推导，请始终使用
//   const auto& 而不是auto。通过引用而不是按值访问元素的性能损失通常很小；如
//   果元素类型后来被更改为复制成本高昂的类型，这可以避免潜在的重大性能损失。
//

// ―――― 其他标准容器类型 ――――

// 基于范围的循环适用于各种数组类型，包括C样式数组、std::array、std::vector、
// 链表、树和map。后面这些还没有讲到，因此如果您不知道它们是什么，也不用担心。
// 请记住，基于范围的for循环提供了一种灵活且通用的迭代方法，而不仅仅适用于
// std::vector：

// [代码 9]
// #include <array>
// #include <iostream>
//
// int main()
// {
//     std::array fibonacci{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 }; // 这里使用 std::array
//
//     for (auto number : fibonacci)
//     {
//         std::cout << number << ' ';
//     }
//
//     std::cout << '\n';
//
//     return 0;
// }

//

// ―――― 获取当前元素的索引 ――――

// 基于范围的for循环不提供直接获取当前元素数组索引的方法。这是因为基于范围的
// for循环可以迭代的许多结构（如std::list）并不支持索引。
//
// 然而，由于基于范围的for循环总是向前迭代，并且不会跳过元素，因此您始终可以声
// 明并维护自己的计数器。不过，如果需要这样做，应该考虑是否直接使用普通for循环
// 会更合适。
//

// ―――― 基于范围的反向循环（C++20） ――――

// 基于范围的循环只按正向顺序迭代。然而，在某些情况下，我们希望以相反顺序遍历
// 数组。在C++20之前，基于范围的for循环不能轻易用于这个目的，必须采用其他解决
// 方案。
//
// 不过，从C++20开始，可以使用Ranges库的std::views::reverse功能，创建可遍历元
// 素的反向视图：

// [代码 10]
// #include <iostream>
// #include <ranges> // C++20
// #include <string_view>
// #include <vector>
//
// int main()
// {
//     std::vector<std::string_view> words{ "Alex", "Bobby", "Chad", "Dave" }; // 按字母表排序
//
//     for (const auto& word : std::views::reverse(words)) // 创建一个反向的视图
//         std::cout << word << ' ';
//
//     std::cout << '\n';
//
//     return 0;
// }

// 这将打印：

// [文本/输出]
// Dave
// Chad
// Bobby
// Alex

// 我们还没有介绍range库，所以现在可以先把它看作一个有用的技巧。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 定义一个`std::vector`，包含下列名字：「Alex」「Betty」「Caroline」「Dave」
// 「Emily」「Fred」「Greg」「Holly」。要求用户输入一个名字，使用范围for循环检
// 查用户输入的名字是否在数组中。
//
// 输出示例：

// [文本/输出]
// Enter a name: Betty
// Betty was found.


// [文本/输出]
// Enter a name: Megatron
// Megatron was not found.

// 提示：使用`std::string`保存用户输入的字符串。 提示：`std::string_view`的拷
// 贝开销很小。

// 【答案 · 查看答案】

// [代码 11]
// #include <iostream>
// #include <string>
// #include <string_view>
// #include <vector>
//
// int main()
// {
//     std::vector<std::string_view> names{ "Alex", "Betty", "Caroline", "Dave",
//         "Emily", "Fred", "Greg", "Holly" };
//
//     std::cout << "Enter a name: ";
//     std::string username{};
//     std::cin >> username;
//
//     bool found{ false };
//
//     // 这里显式表明我们期望 `name` 是 std::string_view
//     // 这样即使以后把 `names` 改成拷贝开销很大的类型
//     // （例如 std::string），我们就不会产生昂贵的拷贝。
//     for (std::string_view name : names)
//     {
//         if (name == username)
//         {
//             found = true;
//             break;
//         }
//     }
//
//     if (found)
//         std::cout << username << " was found.\n";
//     else
//         std::cout << username << " was not found.\n";
//
//     return 0;
// }


// ▼ 问题 2
// 修改你在第1题中的解答。这一版要求创建一个名为`isValueInArray()`的函数模板（
// 而不是普通函数），它接受两个形参：一个`std::vector`和一个值。如果该值在数组
// 中，函数返回`true`，否则返回`false`。在`main()`中调用这个函数，把名字数组和
// 用户输入的名字传给它。
//
// 提醒：
// - 使用模板实参推导（没有显式指定模板类型实参）的函数模板，不会为匹配模板类
//   型形参而做类型转换。调用要么与模板匹配（且能推导出模板类型），要么不匹配。
// - 显式指定了模板类型实参的函数模板会把实参转换为匹配形参的类型（因为类型已
//   经确定）。

// 【答案 · 查看答案】

// [代码 12]
// #include <iostream>
// #include <string>
// #include <string_view>
// #include <vector>
//
// template <typename T>
// bool isValueInArray(const std::vector<T>& arr, const T& value )
// {
//     // 由于不知道 T 的拷贝开销是否很大，这里使用引用
//     for (const auto& a : arr)
//     {
//         if (a == value)
//             return true;
//     }
//
//     return false;
// }
//
// int main()
// {
//     std::vector<std::string_view> names{ "Alex", "Betty", "Caroline", "Dave",
//         "Emily", "Fred", "Greg", "Holly" };
//
//     std::cout << "Enter a name: ";
//     std::string username{};
//     std::cin >> username;
//
//     // 通过显式指定 std::string_view 作为函数模板实参，
//     // 编译器会隐式地把 username 转换成 `std::string_view` 以匹配形参类型。
//     bool found{ isValueInArray<std::string_view>(names, username) };
//
//     // 下面这种写法也可以。如果我们改为依赖模板实参推导，编译器
//     // 不会做隐式转换，因此我们需要确保 `username` 具有期望的类型。
//     // bool found{ isValueInArray(names, static_cast<std::string_view>(username)) };
//
//     if (found)
//         std::cout << username << " was found.\n";
//     else
//         std::cout << username << " was not found.\n";
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <vector>

int main()
{
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    std::size_t length { fibonacci.size() };
    for (std::size_t index { 0 }; index < length; ++index)
       std::cout << fibonacci[index] << ' ';

    std::cout << '\n';

    return 0;
}
