// ==========================================================================
// 15.4 具有成员函数的类模板
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十五章 class第二部分
// 原文: https://www.studycpp.cn/basic/chapter15/class-tmplate-with-member-func/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "15.04-class-tmplate-with-member-func.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 在成员函数中键入模板参数
//   · 如何在类模板外部定义成员函数
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 前面我们学习了函数模版：

// [代码 1]
// template <typename T> // 模版参数声明
// T max(T x, T y) // 函数模版 max<T> 定义
// {
//     return (x < y) ? y : x;
// }

// 使用函数模板时，可以定义类型模板参数（例如类型名T），然后将它们用作函数参数
// (T x, T y) 的类型。
//
// 同时，我们也介绍了类模板。类模板允许类类型（结构体、类和联合）的数据成员使
// 用类型模板参数：

// [代码 2]
// #include <iostream>
//
// template <typename T>
// struct Pair
// {
//     T first{};
//     T second{};
// };
//
// // 这里是我们自定义的 Pair 推导指引 (需要在 C++17 以上版本使用)
// // Pair 以两个 T 类型的参数初始化时，会被推导为 Pair<T>
// template <typename T>
// Pair(T, T) -> Pair<T>;
//
// int main()
// {
//     Pair<int> p1{ 5, 6 };        // 实例化 Pair<int> 并创建对象 p1
//     std::cout << p1.first << ' ' << p1.second << '\n';
//
//     Pair<double> p2{ 1.2, 3.4 }; // 实例化 Pair<double> 并创建对象 p2
//     std::cout << p2.first << ' ' << p2.second << '\n';
//
//     Pair<double> p3{ 7.8, 9.0 }; // 创建对象 p3，使用之前实例化的 Pair<double>
//     std::cout << p3.first << ' ' << p3.second << '\n';
//
//     return 0;
// }

// 本课将结合函数模板和类模板的相关内容，更仔细地讨论具有成员函数的类模板。
//

// ―――― 在成员函数中键入模板参数 ――――

// 模版参数既可以作为成员变量的类型，也可以作为成员函数参数的类型。
//
// 在下面的示例中，我们重写上面的Pair类模板，并将其从结构体转换为类：

// [代码 3]
// #include <ios>       // for std::boolalpha
// #include <iostream>
//
// template <typename T>
// class Pair
// {
// private:
//     T m_first{};
//     T m_second{};
//
// public:
//     // 在类中定义成员函数
//     // 模版参数来自类声明时的模版参数
//     Pair(const T& first, const T& second)
//         : m_first{ first }
//         , m_second{ second }
//     {
//     }
//
//     bool isEqual(const Pair<T>& pair);
// };
//
// // 在类外部定义成员函数
// // 需要重新提供模版参数声明
// template <typename T>
// bool Pair<T>::isEqual(const Pair<T>& pair)
// {
//     return m_first == pair.m_first && m_second == pair.m_second;
// }
//
// int main()
// {
//     Pair p1{ 5, 6 }; // 使用 CTAD 来推导 Pair<int>
//     std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
//     std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';
//
//     return 0;
// }

// 上面的内容应该比较直观，但有几点值得注意。
//
// 首先，因为类具有私有成员，所以它不是聚合，因此不能使用聚合初始化。相反，必
// 须通过构造函数初始化类对象。
//
// 由于类数据成员的类型为T，因此构造函数参数也设置为const T&，这样用户可以提供
// 相同类型的初始化值。由于T的复制成本可能很高，通过常量引用传递通常比按值传递
// 更稳妥。
//
// 注意，当在类模板定义中定义成员函数时，不需要为成员函数提供模板参数声明。这
// 样的成员函数隐式使用类模板参数声明。
//
// 其次，可以使用CTAD。只要提供的初始值能匹配构造函数，编译器就可以自动推断模
// 板参数。
//
// 让我们更仔细地看一下在类模板定义之外为类模板定义成员函数的情况：

// [代码 4]
// template <typename T>
// bool Pair<T>::isEqual(const Pair<T>& pair)
// {
//     return m_first == pair.m_first && m_second == pair.m_second;
// }

// 由于该成员函数定义与类模板定义分开，因此需要重新提供模板参数声明（template
// <typename T>），以便编译器知道T是什么。
//
// 此外，在类之外定义成员函数时，需要用类模板的完整模板化名称（
// Pair<T>::isEqual，而不是Pair::isEqual）来限定成员函数名称。
//

// ―――― 如何在类模板外部定义成员函数 ――――

// 对于类模板的成员函数，编译器需要看到类定义（以确认成员函数模板被声明为类的
// 一部分）和模板成员函数定义（以了解如何实例化模板）。因此，通常希望在同一位
// 置定义类及其成员函数模板。
//
// 当在类内部定义成员函数模板时，模板成员函数定义就是类定义的一部分。因此，只
// 要能看到类定义，就能看到模板成员函数定义。这让事情变得简单，但代价是类定义
// 会更杂乱。
//
// 当成员函数模板在类之外定义时，通常应将它定义在类定义的正下方。这样，任何能
// 看到类定义的地方，也能看到类定义下面的成员函数模板定义。
//
// 在类定义位于头文件中的典型情况下，这意味着任何在类之外定义的成员函数模板，
// 也应该在同一个头文件中、类定义的下方进行定义。
//
// 关键点
//
// 前面我们知道，从模板隐式实例化的函数是隐式内联的。这包括非成员函数模板和成
// 员函数模板。因此，将头文件中定义的成员函数模板包含到多个代码文件中没有问题，
// 因为由这些模板实例化出的函数会隐式内联（并且链接器会消除重复项）。
//
// 最佳实践
//
// 在类定义之外定义的任何成员函数模板都应该在类定义的正下方定义（在同一文件中）
// 。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 编写一个名为Triad的类模板，它包含3个私有数据成员，且这3个数据成员使用各自独
// 立的类型模板形参。该类应当有一个构造函数、若干访问函数，以及一个定义在类外
// 部的`print()`成员函数。
//
// 下面这个程序应当能够编译并运行：

// [代码 5]
// #include <iostream>
// #include <string>
//
// int main()
// {
// 	Triad<int, int, int> t1{ 1, 2, 3 };
// 	t1.print();
// 	std::cout << '\n';
// 	std::cout << t1.first() << '\n';
//
// 	using namespace std::literals::string_literals;
// 	const Triad t2{ 1, 2.3, "Hello"s };
// 	t2.print();
// 	std::cout << '\n';
//
// 	return 0;
// }

// 并产生如下输出：

// [文本/输出]
// [1, 2, 3]
// 1
// [1, 2.3, Hello]


// 【答案 · 查看答案】

// [代码 6]
// #include <iostream>
// #include <string>
//
// template <typename T, typename U, typename V>
// class Triad
// {
// private:
// 	T m_first{};
// 	U m_second{};
// 	V m_third{};
//
// public:
// 	Triad(const T& first, const U& second, const V& third)
// 		: m_first{ first }
// 		, m_second{ second }
// 		, m_third{ third }
// 	{
// 	}
//
// 	const T& first() const { return m_first; }
// 	const U& second() const { return m_second; }
// 	const V& third() const { return m_third; }
//
// 	void print() const;
// };
//
// template <typename T, typename U, typename V>
// void Triad<T, U, V>::print() const
// {
// 	std::cout << '[' << m_first << ", " << m_second << ", " << m_third << ']' ;
// }
//
// int main()
// {
// 	Triad<int, int, int> t1{ 1, 2, 3 };
// 	t1.print();
// 	std::cout << '\n';
// 	std::cout << t1.first() << '\n';
//
// 	using namespace std::literals::string_literals;
// 	const Triad t2{ 1, 2.3, "Hello"s };
// 	t2.print();
// 	std::cout << '\n';
//
// 	return 0;
// }


// ▼ 问题 2
// 如果把`print()`函数的声明和定义中的`const`去掉，程序将无法通过编译。为什么？

// 【答案 · 查看答案】
// `t2`是一个const对象，因此只能对`t2`调用const成员函数。如果把`print()`改成非
// const成员函数，`t2`就不允许调用它。这是因为非const成员函数有可能修改隐式对
// 象，而这就违反了const对象（这里是`t2`）的常量性。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// 这里是我们自定义的 Pair 推导指引 (需要在 C++17 以上版本使用)
// Pair 以两个 T 类型的参数初始化时，会被推导为 Pair<T>
template <typename T>
Pair(T, T) -> Pair<T>;

int main()
{
    Pair<int> p1{ 5, 6 };        // 实例化 Pair<int> 并创建对象 p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double> p2{ 1.2, 3.4 }; // 实例化 Pair<double> 并创建对象 p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    Pair<double> p3{ 7.8, 9.0 }; // 创建对象 p3，使用之前实例化的 Pair<double>
    std::cout << p3.first << ' ' << p3.second << '\n';

    return 0;
}
