// ==========================================================================
// 15.6 静态成员函数
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十五章 class第二部分
// 原文: https://www.studycpp.cn/basic/chapter15/static-member-func/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "15.06-static-member-func.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 静态成员函数
//   · 静态成员函数没有this指针
//   · 在类定义外部定义的静态成员
//   · 关于具有所有静态成员的类的警告
//   · 纯静态类与命名空间
//   · C++不支持静态构造函数
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 上一课中，我们了解到静态成员变量属于类，而不属于类的某个对象。如果静态成员
// 变量是public的，则可以使用类名和域解析操作符直接访问它：

// [代码 1]
// #include <iostream>
//
// class Something
// {
// public:
//     static inline int s_value { 1 };
// };
//
// int main()
// {
//     std::cout << Something::s_value; // s_value 是 public, 可以直接访问
// }

// 但如果静态成员变量是私有的呢？考虑以下示例：

// [代码 2]
// #include <iostream>
//
// class Something
// {
// private: // 现在是 private
//     static inline int s_value { 1 };
// };
//
// int main()
// {
//     std::cout << Something::s_value; // error: s_value 是 private，无法在类的外部直接访问
// }

// 在这种情况下，不能直接从 main() 访问Something::s_value，因为它是私有的。通
// 常，我们通过公共成员函数访问私有成员。虽然可以创建一个普通的公共成员函数来
// 访问s_value，但必须先实例化类类型的对象，才能调用该函数！

// [代码 3]
// #include <iostream>
//
// class Something
// {
// private:
//     static inline int s_value { 1 };
//
// public:
//     int getValue() { return s_value; }
// };
//
// int main()
// {
//     Something s{};
//     std::cout << s.getValue(); // 可以, 但必须先实例化一个对象才能调用 getValue()
// }

// 可以做得更好。
//

// ―――― 静态成员函数 ――――

// 成员变量并不是唯一可以设为静态的成员类型。成员函数也可以设为静态。下面是一
// 个带有静态成员函数访问器的示例：

// [代码 4]
// #include <iostream>
//
// class Something
// {
// private:
//     static inline int s_value { 1 };
//
// public:
//     static int getValue() { return s_value; } // static 成员函数
// };
//
// int main()
// {
//     std::cout << Something::getValue() << '\n';
// }

// 由于静态成员函数不与特定对象关联，因此可以使用类名和域解析操作符（例如
// Something::getValue()）直接调用它们。与静态成员变量一样，它们也可以通过类类
// 型的对象调用，但不建议这样做。
//

// ―――― 静态成员函数没有this指针 ――――

// 静态成员函数有两个值得注意的特殊之处。首先，因为静态成员函数不附加到对象，
// 所以它们没有this指针！这是有意义的：this指针始终指向成员函数正在处理的对象。
// 静态成员函数不作用于对象，因此不需要this指针。
//
// 其次，静态成员函数可以直接访问其他静态成员（变量或函数），但不能访问非静态
// 成员。这是因为非静态成员必须属于类对象，并且静态成员函数没有可使用的类对象！
//

// ―――― 在类定义外部定义的静态成员 ――――

// 静态成员函数也可以在类声明之外定义。这与普通成员函数的写法相同。

// [代码 5]
// #include <iostream>
//
// class IDGenerator
// {
// private:
//     static inline int s_nextID { 1 };
//
// public:
//      static int getNextID(); // 这里是静态成员函数声明
// };
//
// // 这里是类外部的静态成员函数定义，注意这里没有加 static 关键字
// int IDGenerator::getNextID() { return s_nextID++; }
//
// int main()
// {
//     for (int count{ 0 }; count < 5; ++count)
//         std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';
//
//     return 0;
// }

// 该程序打印：

// [文本/输出]
// The next ID is: 1
// The next ID is: 2
// The next ID is: 3
// The next ID is: 4
// The next ID is: 5

// 注意，因为这个类中的所有数据和函数都是静态的，所以不需要实例化类对象就能使
// 用它的函数！该类使用静态成员变量保存要分配的下一个ID，并提供一个静态成员函
// 数返回该ID后再将其递增。
//
// 在类定义中定义的成员函数是隐式内联的。在类定义外部定义的成员函数不是隐式内
// 联的，但可以使用inline关键字将其设为内联。因此，在头文件中定义的静态成员函
// 数应该内联，以便该头文件被包含到多个翻译单元中时不会违反“单定义规则”（ODR）。
//

// ―――― 关于具有所有静态成员的类的警告 ――――

// 编写全是静态成员的类时要小心。尽管这种“纯静态类”可能有用，但也存在一些潜在
// 缺点。
//
// 首先，因为所有静态成员都只实例化一次，所以无法拥有纯静态类的多个副本（无法
// 拷贝类对象并将其重命名）。例如，如果您需要两个独立的IDGenerator，纯静态类就
// 无法做到。
//
// 其次，在关于全局变量的课程中，我们了解到全局变量是危险的，因为任何代码片段
// 都可以更改全局变量的值，并最终破坏另一段看似无关的代码。纯静态类也有同样的
// 问题。由于所有成员都属于类（而不是类对象），并且类声明通常具有全局范围，因
// 此纯静态类本质上相当于在全局可访问的命名空间中声明函数和全局变量，具有全局
// 变量的所有缺点。
//
// 与其编写全是静态成员的类，不如考虑编写一个普通类并实例化它的全局实例（全局
// 变量具有静态存储期）。这样，可以在适当的时候使用全局实例，同时仍然可以实例
// 化其他实例。
//

// ―――― 纯静态类与命名空间 ――――

// 纯静态类与命名空间有许多重叠。两者都允许您定义具有静态存储期的变量，并在其
// 作用域内定义函数。然而，一个显著区别是类具有访问控制，而命名空间没有。
//
// 通常，当您有静态数据成员和/或需要访问控制时，最好使用静态类。否则，首选命名
// 空间。
//

// ―――― C++不支持静态构造函数 ――――

// 如果可以通过构造函数初始化普通成员变量，那么看起来也应该能通过静态构造函数
// 初始化静态成员变量。虽然一些现代语言确实支持静态构造函数来实现这一目的，但
// 遗憾的是，C++并不支持。
//
// 如果可以直接初始化静态变量，就不需要构造函数：您可以在定义点初始化静态成员
// 变量（即使它是私有的）。上面的IDGenerator示例就是这样做的。下面是另一个示例：

// [代码 6]
// #include <iostream>
//
// struct Chars
// {
//     char first{};
//     char second{};
//     char third{};
//     char fourth{};
//     char fifth{};
// };
//
// struct MyClass
// {
// 	static inline Chars s_mychars { 'a', 'e', 'i', 'o', 'u' }; // 在定义点初始化静态成员变量
// };
//
// int main()
// {
//     std::cout << MyClass::s_mychars.third; // 打印 i
//
//     return 0;
// }

// 如果初始化静态成员变量需要执行代码（例如循环），那么有许多不同但稍显笨拙的
// 方法可以做到这一点。处理所有变量（静态或非静态）的一种方法是使用函数创建对
// 象，用数据填充它，并将其返回给调用方。该返回值可以拷贝到正在初始化的对象中。

// [代码 7]
// #include <iostream>
//
// struct Chars
// {
//     char first{};
//     char second{};
//     char third{};
//     char fourth{};
//     char fifth{};
// };
//
// class MyClass
// {
// private:
//     static Chars generate()
//     {
//         Chars c{}; // 创建一个对象
//         c.first = 'a'; // 填充值
//         c.second = 'e';
//         c.third = 'i';
//         c.fourth = 'o';
//         c.fifth = 'u';
//
//         return c; // 返回对象
//     }
//
// public:
// 	static inline Chars s_mychars { generate() }; // 将返回的对象填充到 s_mychars
// };
//
// int main()
// {
//     std::cout << MyClass::s_mychars.third; // 打印 i
//
//     return 0;
// }

// 前面讲解随机数时，我们展示过类似技巧（尽管当时使用命名空间而不是静态类来实
// 现，但工作方式相同）。
//
// 相关内容
//
// lambda也可以用于此。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 把下面例子中的`Random`命名空间改成一个带静态成员的类：

// [代码 8]
// #include <chrono>
// #include <random>
// #include <iostream>
//
// namespace Random
// {
// 	inline std::mt19937 generate()
// 	{
// 		std::random_device rd{};
//
// 		// 用高精度时钟和 std::random_device 生成的 7 个随机数来创建 seed_seq
// 		std::seed_seq ss{
// 			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
// 				rd(), rd(), rd(), rd(), rd(), rd(), rd() };
//
// 		return std::mt19937{ ss };
// 	}
//
// 	inline std::mt19937 mt{ generate() }; // 生成一个已播种的 std::mt19937 并拷贝到全局对象中
//
// 	// 生成 [min, max]（含两端）范围内的随机整数
// 	inline int get(int min, int max)
// 	{
// 		return std::uniform_int_distribution{min, max}(mt);
// 	}
// }
//
// int main()
// {
// 	// 打印一堆随机数
// 	for (int count{ 1 }; count <= 10; ++count)
// 		std::cout << Random::get(1, 6) << '\t';
//
// 	std::cout << '\n';
//
// 	return 0;
// }


// 【答案 · 查看答案】

// [代码 9]
// #include <chrono>
// #include <random>
// #include <iostream>
//
// class Random
// {
// private: // 如果希望这些成员可以被访问，也可以改为 public
// 	static std::mt19937 generate()
// 	{
// 		std::random_device rd{};
//
// 		// 用高精度时钟和 std::random_device 生成的 7 个随机数来创建 seed_seq
// 		std::seed_seq ss{
// 			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
// 				rd(), rd(), rd(), rd(), rd(), rd(), rd() };
//
// 		return std::mt19937{ ss };
// 	}
//
// 	static inline std::mt19937 mt{ generate() }; // 生成一个已播种的 std::mt19937 并拷贝到全局对象中
//
// public:
// 	// 生成 [min, max]（含两端）范围内的随机整数
// 	static int get(int min, int max)
// 	{
// 		return std::uniform_int_distribution{min, max}(mt);
// 	}
// };
//
// int main()
// {
// 	// 打印一堆随机数
// 	for (int count{ 1 }; count <= 10; ++count)
// 		std::cout << Random::get(1, 6) << '\t';
//
// 	std::cout << '\n';
//
// 	return 0;
// }

// 在命名空间中声明的任何对象都是全局变量。当我们在命名空间内部声明`inline
// std::mt19937 mt`时，就是把`mt`声明为inline全局变量。这样整个程序就可以共用
// 同一个`std::mt19937`实例（通过全局变量`mt`）。
//
// 相反，实例化一个类对象时，该对象会包含每个非静态数据成员的一份拷贝。我们不
// 希望每个类对象都有自己的`std::mt19937`拷贝。因此我们声明`static inline
// std::mt19937 mt`，它告诉编译器：整个程序中只应存在一个`std::mt19937`实例，
// 作为`Random`类的一部分。把`mt`定义为`static inline`使成为一个inline变量，从
// 而可以在类定义内部初始化它（这一点在「15.5 静态成员变量」中介绍）。
//
// 我们同时把成员函数声明为`static`，这样就可以在不实例化`Random`对象的情况下
// 访问它们。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Something
{
public:
    static inline int s_value { 1 };
};

int main()
{
    std::cout << Something::s_value; // s_value 是 public, 可以直接访问
}
