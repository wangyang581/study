// ==========================================================================
// 22.4 std::unique_ptr
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十二章 移动语义与智能指针
// 原文: https://www.studycpp.cn/basic/chapter22/unique-ptr/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "22.04-unique-ptr.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · std::unique_ptr
//   · 访问托管对象
//   · std::unique_ptr和数组
//   · std::make_unique
//   · 异常安全问题
//   · 从函数返回std::unique_ptr
//   · 将std::unique_ptr传递给函数
//   · std::unique_ptr和类
//   · 误用std::unique_ptr
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 在本章的开头，我们讨论了在某些情况下，指针的使用会导致错误和内存泄漏。例如，
// 当函数提前返回或抛出异常，而指针没有正确delete时，就会发生这种情况。

// [代码 1]
// #include <iostream>
//
// void someFunction()
// {
//     auto* ptr{ new Resource() };
//
//     int x{};
//     std::cout << "Enter an integer: ";
//     std::cin >> x;
//
//     if (x == 0)
//         throw 0; // 函数提前返回，ptr不会被删除!
//
//     // 这里对 ptr 做一些操作
//
//     delete ptr;
// }

// 现在，我们已经讨论了移动语义的基础知识，可以回到智能指针类这个主题。尽管智
// 能指针可以提供其他功能，但它的核心特点是：管理用户提供的动态分配资源，并确
// 保在适当时间（通常是智能指针超出作用域时）正确清理动态分配的对象。
//
// 因此，不应动态分配智能指针（否则，智能指针本身也可能无法被正确释放）。应尽
// 量始终在栈上分配智能指针（作为局部变量或类成员），这样可以保证包含智能指针
// 的函数或对象结束时，智能指针会正确超出作用域，从而确保它拥有的对象被正确释
// 放。
//
// C++11标准库提供了4个智能指针类：std::auto_ptr（在C++17中删除）、
// std::unique_ptr、std::shared_ptr和std::weak_ptr。unique_ptr是使用最多的智能
// 指针类，因此我们先介绍它。
//

// ―――― std::unique_ptr ――――

// std::unique_ptr是C++11对std::auto_ptr的替代。它应该用于管理不由多个对象共享
// 的动态分配对象。也就是说，std::unique_ptr应该完全拥有它管理的对象，而不是与
// 其他对象共享所有权。std::unique_ptr位于<memory>头文件中。
//
// 让我们看一个简单的智能指针示例：

// [代码 2]
// #include <iostream>
// #include <memory> // for std::unique_ptr
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// int main()
// {
// 	// 分配一个 Resource 对象，并把所有权交给 std::unique_ptr
// 	std::unique_ptr<Resource> res{ new Resource() };
//
// 	return 0;
// } // res 超出作用域, 动态分配的 Resource 被释放

// 因为这里的std::unique_ptr是在栈上分配的，所以可以保证它最终会超出作用域。当
// 它超出作用域时，会删除它所管理的Resource。
//
// 与std::auto_ptr不同，std::unique_ptr正确地实现移动语义。

// [代码 3]
// #include <iostream>
// #include <memory> // for std::unique_ptr
// #include <utility> // for std::move
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// int main()
// {
// 	std::unique_ptr<Resource> res1{ new Resource{} }; // Resource 这里创建
// 	std::unique_ptr<Resource> res2{}; // 默认是 nullptr
//
// 	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
// 	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");
//
// 	// res2 = res1; // 编译失败: 拷贝赋值被禁用
// 	res2 = std::move(res1); // res2 获得所有权, res1 被设置为 null
//
// 	std::cout << "Ownership transferred\n";
//
// 	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
// 	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");
//
// 	return 0;
// } // Resource 被销毁，因为 res2 超出作用域

// 这将打印：

// [文本/输出]
// Resource acquired
// res1 is not null
// res2 is null
// Ownership transferred
// res1 is null
// res2 is not null
// Resource destroyed

// 由于std::unique_ptr在设计时就考虑了移动语义，因此禁用了拷贝初始化和拷贝赋值。
// 如果要转移由std::unique_ptr管理的内容，则必须使用移动语义。在上面的程序中，
// 这一点通过std::move实现（它将res1转换为右值，从而触发移动赋值，而不是拷贝赋
// 值）。
//

// ―――― 访问托管对象 ――――

// std::unique_ptr重载了operator*和operator->，可用于访问被管理的资源。
// operator*返回对托管资源的引用，operator->返回指针。
//
// 请记住，std::unique_ptr并不总是在管理对象，因为它可能为空（使用默认构造函数
// 或传入nullptr），也可能因为正在管理的资源已被移动到另一个std::unique_ptr。
// 因此，在使用这些运算符之前，应该检查std::unique_ptr是否实际拥有资源。幸运的
// 是，这很容易：std::unique_ptr提供到bool的转换，如果它正在管理资源，则返回
// true。
//
// 下面是一个例子：

// [代码 4]
// #include <iostream>
// #include <memory> // for std::unique_ptr
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// std::ostream& operator<<(std::ostream& out, const Resource&)
// {
// 	out << "I am a resource";
// 	return out;
// }
//
// int main()
// {
// 	std::unique_ptr<Resource> res{ new Resource{} };
//
// 	if (res) // 隐式转换为 bool，检查是否拥有资源
// 		std::cout << *res << '\n'; // 打印拥有的资源
//
// 	return 0;
// }

// 这将打印：

// [文本/输出]
// Resource acquired
// I am a resource
// Resource destroyed

// 在上面的程序中，我们使用重载的operator*获取std::unique_ptr res拥有的
// Resource对象，然后将其发送到std::cout进行打印。
//

// ―――― std::unique_ptr和数组 ――――

// 与std::auto_ptr不同，std::unique_ptr足够智能，能够判断应该使用普通delete还
// 是数组delete，因此std::unique_ptr可以与普通对象和数组一起使用。
//
// 然而，与其将std::unique_ptr用于固定数组、动态数组或C样式字符串，std::array
// 或std::vector（或std::string）几乎总是更好的选择。
//

// ―――― std::make_unique ――――

// C++14提供了一个名为std::make_unique()的辅助函数。这个函数模板会构造符合模板
// 类型的对象，并使用传递给函数的参数对其进行初始化。

// [代码 5]
// #include <memory> // for std::unique_ptr and std::make_unique
// #include <iostream>
//
// class Fraction
// {
// private:
// 	int m_numerator{ 0 };
// 	int m_denominator{ 1 };
//
// public:
// 	Fraction(int numerator = 0, int denominator = 1) :
// 		m_numerator{ numerator }, m_denominator{ denominator }
// 	{
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
// 	{
// 		out << f1.m_numerator << '/' << f1.m_denominator;
// 		return out;
// 	}
// };
//
// int main()
// {
// 	// 使用 numerator 3 和 denominator 5 创建动态分配的对象
// 	auto f1{ std::make_unique<Fraction>(3, 5) };
// 	std::cout << *f1 << '\n';
//
// 	// 创建长度为 4 的动态分配的数组
// 	auto f2{ std::make_unique<Fraction[]>(4) };
// 	std::cout << f2[0] << '\n';
//
// 	return 0;
// }

// 上面的代码打印：

// [文本/输出]
// 3/5
// 0/1

// 使用std::make_unique()并非强制，但建议不要手动创建std::unique_ptr。这是因为
// 使用std::make_unique的代码更简单，并且需要更少的类型说明（与自动类型推断一
// 起使用时）。此外，在C++14中，它还解决了由于C++未指定函数参数求值顺序而导致
// 的异常安全问题。
//
// 最佳实践
//
// 使用std::make_unique()，而不是手动创建std::unique_ptr。
//

// ―――― 异常安全问题 ――――

// 如果您想知道上面提到的“异常安全问题”是什么，下面是对该问题的描述。
//
// 考虑这样的表达式：

// [代码 6]
// some_function(std::unique_ptr<T>(new T), function_that_can_throw_exception());

// 编译器在如何处理该函数调用方面有很大的灵活性。它可以先创建一个新的T，然后调
// 用function_that_can_throw_exception()，最后再创建管理动态分配T的
// std::unique_ptr。如果function_that_can_throw_exception()抛出异常，则分配的T
// 不会被释放，因为智能指针尚未创建。这会导致T泄漏。
//
// std::make_unique()不会遇到这个问题，因为对象T的创建和std::unique_ptr的创建
// 都发生在std::make_unique()函数中，对执行顺序没有歧义。
//
// 这个问题在C++17中得到了修复，因为函数参数的求值不能再交错。
//

// ―――― 从函数返回std::unique_ptr ――――

// std::unique_ptr可以按值从函数中安全返回：

// [代码 7]
// #include <memory> // for std::unique_ptr
//
// std::unique_ptr<Resource> createResource()
// {
//      return std::make_unique<Resource>();
// }
//
// int main()
// {
//     auto ptr{ createResource() };
//
//     // 做其他操作
//
//     return 0;
// }

// 在上面的代码中，createResource()按值返回std::unique_ptr。如果未将该值分配给
// 任何对象，则临时返回值会超出作用域，资源也会被清理。如果在C++14或更早版本中
// 使用它（如main()所示），则会使用移动语义将资源从返回值转移到接收对象（上例
// 中为ptr）；在C++17或更高版本中，返回语句会被优化掉。这使得通过
// std::unique_ptr返回资源比返回原始指针安全得多！
//
// 通常，不应通过指针或引用返回std::unique_ptr（除非您有非常明确且充分的理由）。
//

// ―――― 将std::unique_ptr传递给函数 ――――

// 如果希望函数获得指针内容的所有权，请按值传递std::unique_ptr。注意，由于复制
// 语义已被禁用，因此实际传递变量时需要使用std::move。

// [代码 8]
// #include <iostream>
// #include <memory> // for std::unique_ptr
// #include <utility> // for std::move
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// std::ostream& operator<<(std::ostream& out, const Resource&)
// {
// 	out << "I am a resource";
// 	return out;
// }
//
// // 函数会获得 Resource 的所有权, 不一定会是我们想要的行为
// void takeOwnership(std::unique_ptr<Resource> res)
// {
//      if (res)
//           std::cout << *res << '\n';
// } // Resource 这里被销毁
//
// int main()
// {
//     auto ptr{ std::make_unique<Resource>() };
//
// //    takeOwnership(ptr); // 无法编译, 需要使用移动语义
//     takeOwnership(std::move(ptr)); // ok: 使用移动语义
//
//     std::cout << "Ending program\n";
//
//     return 0;
// }

// 上述程序打印：

// [文本/输出]
// Resource acquired
// I am a resource
// Resource destroyed
// Ending program

// 请注意，在这种情况下，资源所有权被转移给takeOwnership()，因此资源会在
// takeOwnership()结尾被销毁，而不是在main()结尾被销毁。
//
// 然而，在大多数情况下，您不会希望函数获得资源的所有权。
//
// 尽管可以通过const引用传递std::unique_ptr（这允许函数在不获取所有权的情况下
// 使用对象），但更好的做法通常是传递资源本身（通过指针或引用，取决于是否可能
// 为nullptr）。
//
// 要从std::unique_ptr获取原始指针，可以使用get()成员函数：

// [代码 9]
// #include <memory> // for std::unique_ptr
// #include <iostream>
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// std::ostream& operator<<(std::ostream& out, const Resource&)
// {
// 	out << "I am a resource";
// 	return out;
// }
//
// // 这个函数只使用资源, 所以传递指向资源的原始指针
// void useResource(const Resource* res)
// {
// 	if (res)
// 		std::cout << *res << '\n';
// 	else
// 		std::cout << "No resource\n";
// }
//
// int main()
// {
// 	auto ptr{ std::make_unique<Resource>() };
//
// 	useResource(ptr.get()); // 注: get() 获取到指向 Resource 的原始指针
//
// 	std::cout << "Ending program\n";
//
// 	return 0;
// } // Resource 这里被销毁

// 上述程序打印：

// [文本/输出]
// Resource acquired
// I am a resource
// Ending program
// Resource destroyed

//

// ―――― std::unique_ptr和类 ――――

// 当然，您可以使用std::unique_ptr作为类成员。这样，您就不必担心需要在类析构函
// 数中删除动态分配的内存，因为当类对象被销毁时，std::unique_ptr会自动销毁。
//
// 然而，如果类对象没有被正确销毁（例如它是动态分配的，但没有被正确释放），则
// std::unique_ptr成员也不会被销毁，由std::unique_ptr管理的对象也不会被释放。
//

// ―――― 误用std::unique_ptr ――――

// 有两种容易误用std::unique_ptr的方式，而这两种方式都很容易避免。首先，不要让
// 多个对象管理同一资源。例如：

// [代码 10]
// Resource* res{ new Resource() };
// std::unique_ptr<Resource> res1{ res };
// std::unique_ptr<Resource> res2{ res };

// 虽然这在语法上是合法的，但最终结果是res1和res2都会尝试删除同一资源，这将导
// 致未定义行为。
//
// 其次，不要从std::unique_ptr中手动删除资源。

// [代码 11]
// Resource* res{ new Resource() };
// std::unique_ptr<Resource> res1{ res };
// delete res;

// 如果这样做，std::unique_ptr将尝试删除已经被删除的资源，这同样会导致未定义行
// 为。
//
// 请注意，std::make_unique()有助于防止上述两种情况意外发生。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 把下面这个程序由使用普通指针改写为在合适的地方使用std::unique_ptr：

// [代码 12]
// #include <iostream>
//
// class Fraction
// {
// private:
// 	int m_numerator{ 0 };
// 	int m_denominator{ 1 };
//
// public:
// 	Fraction(int numerator = 0, int denominator = 1) :
// 		m_numerator{ numerator }, m_denominator{ denominator }
// 	{
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
// 	{
// 		out << f1.m_numerator << '/' << f1.m_denominator;
// 		return out;
// 	}
// };
//
// void printFraction(const Fraction* ptr)
// {
// 	if (ptr)
// 		std::cout << *ptr << '\n';
// 	else
// 		std::cout << "No fraction\n";
// }
//
// int main()
// {
// 	auto* ptr{ new Fraction{ 3, 5 } };
//
// 	printFraction(ptr);
//
// 	delete ptr;
//
// 	return 0;
// }


// 【答案 · 查看答案】

// [代码 13]
// #include <memory> // 用于 std::unique_ptr
// #include <iostream>
//
// class Fraction
// {
// private:
// 	int m_numerator{ 0 };
// 	int m_denominator{ 1 };
//
// public:
// 	Fraction(int numerator = 0, int denominator = 1) :
// 		m_numerator{ numerator }, m_denominator{ denominator }
// 	{
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
// 	{
// 		out << f1.m_numerator << '/' << f1.m_denominator;
// 		return out;
// 	}
// };
//
// // 这个函数使用 Fraction 对象，因此直接传入 Fraction 本身即可
// // 这样我们就不必关心调用者用的是什么智能指针（或者没有用）
// void printFraction(const Fraction* ptr)
// {
// 	if (ptr)
// 		std::cout << *ptr << '\n';
// 	else
// 		std::cout << "No fraction\n";
// }
//
// int main()
// {
// 	auto ptr{ std::make_unique<Fraction>(3, 5) };
//
// 	printFraction(ptr.get());
//
// 	return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <memory> // for std::unique_ptr

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
	// 分配一个 Resource 对象，并把所有权交给 std::unique_ptr
	std::unique_ptr<Resource> res{ new Resource() };

	return 0;
} // res 超出作用域, 动态分配的 Resource 被释放
