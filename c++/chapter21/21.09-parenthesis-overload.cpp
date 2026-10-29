// ==========================================================================
// 21.9 重载括号运算符
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十一章 操作符重载
// 原文: https://www.studycpp.cn/basic/chapter21/parenthesis-overload/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "21.09-parenthesis-overload.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 一个例子
//   · 函子（函数对象）
//   · 结论
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 到目前为止，您看到的所有重载运算符都允许您定义参数类型，但不能定义参数数量
// （参数数量由运算符类型决定）。例如，operator==总是接收两个参数，而operator！
// 总是接收一个参数。括号运算符（operator()）是一个特别有趣的运算符，它允许您
// 改变所接收参数的类型和数量。
//
// 有两件事需要记住：首先，括号运算符必须实现为成员函数。其次，在非面向对象的
// C++中，「operator()」用于调用函数。在类中，「operator()」只是一个普通运算符，
// 它像其他重载运算符一样调用函数（只是函数名为「operator()」）。
//

// ―――― 一个例子 ――――

// 让我们看一个示例：

// [代码 1]
// class Matrix
// {
// private:
//     double data[4][4]{};
// };

// 矩阵是线性代数中的一个关键概念，通常用于几何建模和3D图形。在上面的示例中，
// Matrix类包含一个4×4的二维double数组。
//
// 我们可以重载「operator[]」来提供对私有一维数组的直接访问。然而，在上面的场
// 景中，我们希望访问的是private二维数组。由于「operator[]」只能接收单个参数，
// 因此无法满足需求。
//
// 然而，由于「operator()」可以接收任意数量的参数，因此我们可以声明一个接收两
// 个整数索引参数的「operator()」版本，并使用它访问二维数组。下面是一个例子：

// [代码 2]
// #include <cassert> // for assert()
//
// class Matrix
// {
// private:
//     double m_data[4][4]{};
//
// public:
//     double& operator()(int row, int col);
//     double operator()(int row, int col) const; // for const 对象
// };
//
// double& Matrix::operator()(int row, int col)
// {
//     assert(row >= 0 && row < 4);
//     assert(col >= 0 && col < 4);
//
//     return m_data[row][col];
// }
//
// double Matrix::operator()(int row, int col) const
// {
//     assert(row >= 0 && row < 4);
//     assert(col >= 0 && col < 4);
//
//     return m_data[row][col];
// }

// 现在，我们可以声明矩阵并像这样访问其元素：

// [代码 3]
// #include <iostream>
//
// int main()
// {
//     Matrix matrix;
//     matrix(1, 2) = 4.5;
//     std::cout << matrix(1, 2) << '\n';
//
//     return 0;
// }

// 产生结果：

// [文本/输出]
// 4.5

// 现在，让我们再次重载「operator()」，这一次新增一个不需要参数的重载函数：

// [代码 4]
// #include <cassert> // for assert()
// class Matrix
// {
// private:
//     double m_data[4][4]{};
//
// public:
//     double& operator()(int row, int col);
//     double operator()(int row, int col) const;
//     void operator()();
// };
//
// double& Matrix::operator()(int row, int col)
// {
//     assert(row >= 0 && row < 4);
//     assert(col >= 0 && col < 4);
//
//     return m_data[row][col];
// }
//
// double Matrix::operator()(int row, int col) const
// {
//     assert(row >= 0 && row < 4);
//     assert(col >= 0 && col < 4);
//
//     return m_data[row][col];
// }
//
// void Matrix::operator()()
// {
//     // 将所有的值重置为 0.0
//     for (int row{ 0 }; row < 4; ++row)
//     {
//         for (int col{ 0 }; col < 4; ++col)
//         {
//             m_data[row][col] = 0.0;
//         }
//     }
// }

// 下面是新示例：

// [代码 5]
// #include <iostream>
//
// int main()
// {
//     Matrix matrix{};
//     matrix(1, 2) = 4.5;
//     matrix(); // 清空matrix
//     std::cout << matrix(1, 2) << '\n';
//
//     return 0;
// }

// 产生结果：

// [文本/输出]
// 0.0

// 由于「operator()」非常灵活，因此很容易被用于许多不同目的。然而，强烈不建议
// 这样做，因为「（）」本身并不能说明运算符正在做什么。在上面的示例中，最好将
// 清空功能写成名为clear()或erase()的函数，因为matrix.erase()的行为比matrix()
// 更容易理解。
//

// ―――― 函子（函数对象） ――――

// 「operator()」也经常被重载以实现functor（函子，即函数对象），也就是行为像函
// 数的类对象。函子相比普通函数的优点是：函子可以将数据存储在成员变量中（因为
// 它们是类对象）。
//
// 这里有一个简单的函子：

// [代码 6]
// #include <iostream>
//
// class Accumulator
// {
// private:
//     int m_counter{ 0 };
//
// public:
//     int operator() (int i) { return (m_counter += i); }
//
//     void reset() { m_counter = 0; }
// };
//
// int main()
// {
//     Accumulator acc{};
//     std::cout << acc(1) << '\n'; // 打印 1
//     std::cout << acc(3) << '\n'; // 打印 4
//
//     Accumulator acc2{};
//     std::cout << acc2(10) << '\n'; // 打印 10
//     std::cout << acc2(20) << '\n'; // 打印 30
//
//     return 0;
// }

// 请注意，使用Accumulator看起来就像进行普通函数调用，但acc对象会存储累积后的
// 值。
//
// 函子的好处在于，可以根据需要实例化任意多个独立的函子对象，并同时使用它们。
// 函子也可以拥有其他成员函数（例如reset（）），以执行一些方便的操作。
//

// ―――― 结论 ――――

// 「operator()」有时会通过两个参数重载，用于索引多维数组。但除此之外，大多数
// 需求都更适合实现为带有清晰函数名的成员函数。
//
// 「operator()」也经常被重载来创建函子。尽管简单函子（如上面的示例）相当容易
// 理解，但函子通常用于更高级的编程主题，有需要时再学习即可。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 编写一个名为`MyString`的类，其中保存一个`std::string`。重载`operator<<`输出
// 该字符串。重载`operator()`，返回「从第一个形参指定的下标开始、长度为第二个
// 形参」的子串（以`MyString`形式返回）。
//
// 下面这段代码应当能够运行：

// [代码 7]
// int main()
// {
//     MyString s { "Hello, world!" };
//     std::cout << s(7, 5) << '\n'; // 从下标 7 开始返回 5 个字符
//
//     return 0;
// }

// 它应当打印

// [文本/输出]
// world

// 提示：可以使用`std::string::substr`获取std::string的子串。

// 【答案 · 查看答案】

// [代码 8]
// #include <cassert>
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class MyString
// {
// private:
// 	std::string m_string{};
//
// public:
// 	MyString(std::string_view string = {})
// 		:m_string{ string }
// 	{
// 	}
//
// 	MyString operator()(int start, int length)
// 	{
// 		assert(start >= 0);
// 		assert(start + length <= static_cast<int>(m_string.length()) && "MyString::operator(int, int): Substring is out of range");
//
// 		return MyString { m_string.substr(
// 			static_cast<std::string::size_type>(start),
// 			static_cast<std::string::size_type>(length)
// 			)};
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const MyString& s)
// 	{
// 		out << s.m_string;
//
// 		return out;
// 	}
// };
//
// int main()
// {
// 	MyString s{ "Hello, world!" };
// 	std::cout << s(7, 5) << '\n'; // 从下标 7 开始返回 5 个字符
//
// 	return 0;
// }


// ▼ 问题 2
// 这道题是附加题。
//
// 第1步
//
// 如果我们不需要修改返回的子串，上面这种写法为什么效率不高？

// 【答案 · 查看答案】
// 在我们的`operator()`中，`std::string::substr`返回一个`std::string`，这意味
// 着调用它时会拷贝源字符串的一部分。我们重载的`operator()`用它构造一个新的
// `MyString`，其中包含一个`std::string`成员，这又是一次拷贝。接着我们把这个
// `MyString`返回给调用者，这是第三次拷贝。编译器多半会优化掉其中一些拷贝，但
// 至少必须保留一个`std::string`（保存结果子串）。
//
// 只有当我们要修改子串，或者子串的生命周期会超过原字符串时，才需要子串的副本。
// 通常并不属于这两种情况，因此我们做了通常并不需要的昂贵拷贝。
//
// 第2步
//
// 那我们该怎么做？

// 【答案 · 查看答案】
// `std::string_view`能够在不拷贝的情况下观察已有字符串的子串。如果我们的
// `operator()`返回`std::string_view`，那么调用者可以在够用时直接使用这个
// `std::string_view`，在需要修改或需要比原字符串存续更久时，再把它转换成
// `std::string`或`MyString`。
//
// 第3步
//
// 请把上一题解答中的`operator()`改成返回`std::string_view`形式的子串。
//
// 提示：`std::string::substr()`返回`std::string`，而
// `std::string_view::substr()`返回`std::string_view`。务必小心不要返回悬空的
// `std::string_view`！

// 【答案 · 显示提示】
// 不要创建任何`std::string`临时对象，因为它们会在函数结束时被销毁，指向它们的
// `std::string_view`就会悬空。

// 【答案 · 显示提示】
// 创建`std::string_view`临时对象是可以的，只要它们观察的是`m_string`即可。

// 【答案 · 查看答案】

// [代码 9]
// #include <cassert>
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class MyString
// {
// private:
// 	std::string m_string{};
//
// public:
// 	MyString(std::string_view string = {})
// 		:m_string{ string }
// 	{
// 	}
//
// 	std::string_view operator()(int start, int length)
// 	{
// 		assert(start >= 0);
// 		assert(start + length <= static_cast<int>(m_string.length()) && "MyString::operator(int, int): Substring is out of range");
//
// 		// 为 m_string 创建一个 std::string_view，这样就可以使用 std::string_view::substr() 而不是 std::string::substr()
// 		return std::string_view{ m_string }.substr(
// 			static_cast<std::string_view::size_type>(start),
// 			static_cast<std::string_view::size_type>(length)
// 		);
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const MyString& s)
// 	{
// 		out << s.m_string;
//
// 		return out;
// 	}
// };
//
// int main()
// {
// 	MyString s{ "Hello, world!" };
// 	std::cout << s(7, 5) << '\n'; // 从下标 7 开始返回 5 个字符
//
// 	return 0;
// }

// 我们再深入分析一下`return std::string_view{ m_string }.substr();`。首先，我
// 们创建了一个指向`m_string`的临时`std::string_view`，这很廉价，并且让我们能
// 够使用`std::string_view`的成员函数。接着，我们在这个临时对象上调用
// `std::string_view::substr`，得到子串（作为`m_string`的一个不以空字符结尾的
// 视图），然后把它返回给调用者。由于返回给调用者的`std::string_view`仍然观察
// 着`m_string`（此时`m_string`仍在作用域内），因此我们返回的
// `std::string_view`不会悬空。
//
// 最终结果是，我们创建了3个`std::string_view`而不是3个`std::string`，效率更高。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Accumulator
{
private:
    int m_counter{ 0 };

public:
    int operator() (int i) { return (m_counter += i); }

    void reset() { m_counter = 0; }
};

int main()
{
    Accumulator acc{};
    std::cout << acc(1) << '\n'; // 打印 1
    std::cout << acc(3) << '\n'; // 打印 4

    Accumulator acc2{};
    std::cout << acc2(10) << '\n'; // 打印 10
    std::cout << acc2(20) << '\n'; // 打印 30

    return 0;
}
