// ==========================================================================
// 25.9 dynamic_cast
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十五章 虚函数
// 原文: https://www.studycpp.cn/basic/chapter25/dynamic-cast/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "25.09-dynamic-cast.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 为什么需要dynamic_cast
//   · dynamic_cast
//   · dynamic_cast失败的情况
//   · 使用static_cast进行向下转换
//   · dynamic_cast和引用
//   · dynamic_cast与static_cast
//   · 向下转换 vs 虚函数
//   · 关于dynamic_cast和RTTI

// ==========================================================================
// 教程正文
// ==========================================================================

// 在前面的显式类型转换中，我们研究了如何使用 static_cast 将变量从一种类型转换
// 为另一种类型。
//
// 在本课中，我们将继续研究另一种类型转换：dynamic_cast。
//

// ―――― 为什么需要dynamic_cast ――――

// 在处理多态时，您经常会遇到这样的情况：手里只有一个指向基类的指针，但希望访
// 问仅存在于派生类中的信息。
//
// 考虑下面的（稍微有点做作的）程序：

// [代码 1]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Base
// {
// protected:
// 	int m_value{};
//
// public:
// 	Base(int value)
// 		: m_value{value}
// 	{
// 	}
//
// 	virtual ~Base() = default;
// };
//
// class Derived : public Base
// {
// protected:
// 	std::string m_name{};
//
// public:
// 	Derived(int value, std::string_view name)
// 		: Base{value}, m_name{name}
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// };
//
// Base* getObject(bool returnDerived)
// {
// 	if (returnDerived)
// 		return new Derived{1, "Apple"};
// 	else
// 		return new Base{2};
// }
//
// int main()
// {
// 	Base* b{ getObject(true) };
//
// 	// 只有Base指针，如何获得Derived 对象的 m_name？
//
// 	delete b;
//
// 	return 0;
// }

// 在该程序中，函数 getObject() 始终返回 Base 指针，但该指针可以指向 Base 或
// Derived 对象。当 Base 指针实际指向 Derived 对象时，如何调用
// Derived::getName()？
//
// 一种方法是将名为 getName() 的虚函数添加到 Base 中（这样我们就可以使用 Base
// 指针或引用调用它，并将其动态解析为 Derived::getName()）。但如果用实际指向
// Base 对象的 Base 指针或引用调用它，该函数应该返回什么？没有真正有意义的结果。
// 而且，这会让只有派生类关心的内容污染基类。
//
// 我们知道 C++ 允许隐式地将 Derived 指针转换为 Base 指针（实际上，getObject()
// 就是这样做的）。这个过程有时称为向上转换。如果有一种方法可以将 Base 指针转
// 换回 Derived 指针，我们就可以使用该指针直接调用 Derived::getName()，完全不
// 需要通过虚函数解析。
//

// ―――― dynamic_cast ――――

// C++ 提供了一个名为 dynamic_cast 的转换运算符，可以用于这个目的。尽管
// dynamic_cast 还有其他功能，但目前最常见的用途是将基类指针转换为派生类指针。
// 这个过程称为向下转换。
//
// dynamic_cast 的使用方式与 static_cast 类似。下面是对应上面示例的代码：

// [代码 2]
// int main()
// {
// 	Base* b{ getObject(true) };
//
// 	Derived* d{ dynamic_cast<Derived*>(b) }; // 使用 dynamic cast 将 Base 指针转换为 Derived 指针
//
// 	std::cout << "The name of the Derived is: " << d->getName() << '\n';
//
// 	delete b;
//
// 	return 0;
// }

// 这会打印：

// [文本/输出]
// The name of the Derived is: Apple

//

// ―――― dynamic_cast失败的情况 ――――

// 上面的示例之所以有效，是因为 b 实际上指向 Derived 对象，因此可以将 b 转换为
// Derived 指针。然而，我们做了一个相当危险的假设：b 一定指向 Derived 对象。如
// 果 b 没有指向 Derived 对象怎么办？只需将参数从 true 改为 false 就能轻松测试。
// 在这种情况下，getObject() 将返回指向 Base 对象的指针。当我们试图将其
// dynamic_cast 为 Derived 时，转换会失败，因为无法进行这种转换。
//
// 如果 dynamic_cast 失败，转换结果将是空指针。
//
// 如果我们没有检查返回结果是否为空指针，而是直接访问 d->getName()，程序将尝试
// 解引用空指针，导致未定义行为（可能表现为崩溃）。
//
// 为了使程序安全，我们需要确保 dynamic_cast 实际成功：

// [代码 3]
// int main()
// {
// 	Base* b{ getObject(true) };
//
// 	Derived* d{ dynamic_cast<Derived*>(b) }; // 使用 dynamic cast 将 Base 指针转换为 Derived 指针
//
// 	if (d) // 确保 d 不是空指针
// 		std::cout << "The name of the Derived is: " << d->getName() << '\n';
//
// 	delete b;
//
// 	return 0;
// }

// 提示
//
// 通过检查空指针结果，确保 dynamic_cast 实际成功。
//
// 请注意，由于 dynamic_cast 会在运行时执行一些一致性检查（以确保可以进行转换）
// ，因此使用 dynamic_cast 会带来一些性能损失。
//
// 还要注意，在一些情况下，使用 dynamic_cast 进行向下转换不会起作用：
// - 使用 protected 或 private 继承。
// - 对于不声明或继承任何虚函数（因此没有虚函数表）的类。
// - 在涉及虚基类的某些情况下（请参阅本页中的部分示例，以及对应的解决方式）。
//

// ―――― 使用static_cast进行向下转换 ――――

// 向下转换也可以使用 static_cast 完成。主要区别是 static_cast 不进行运行时类
// 型检查。这使 static_cast 更快，但也更危险。它会将 Base* 强制转换为 Derived*，
// 即使 Base 指针并未指向 Derived 对象，转换也会“成功”。当您尝试访问生成的
// Derived 指针（它实际上指向 Base 对象）时，就会导致未定义行为。
//
// 如果您绝对确信正在向下转换的指针一定能成功转换，那么使用 static_cast 是可以
// 接受的。了解所指向对象类型的一种方法是使用虚函数，这里有一种（不太好的）做
// 法：

// [代码 4]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// // 类型定义
// enum class ClassID
// {
// 	base,
// 	derived
// 	// 其它以后会添加的类
// };
//
// class Base
// {
// protected:
// 	int m_value{};
//
// public:
// 	Base(int value)
// 		: m_value{value}
// 	{
// 	}
//
// 	virtual ~Base() = default;
// 	virtual ClassID getClassID() const { return ClassID::base; }
// };
//
// class Derived : public Base
// {
// protected:
// 	std::string m_name{};
//
// public:
// 	Derived(int value, std::string_view name)
// 		: Base{value}, m_name{name}
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// 	ClassID getClassID() const override { return ClassID::derived; }
//
// };
//
// Base* getObject(bool bReturnDerived)
// {
// 	if (bReturnDerived)
// 		return new Derived{1, "Apple"};
// 	else
// 		return new Base{2};
// }
//
// int main()
// {
// 	Base* b{ getObject(true) };
//
// 	if (b->getClassID() == ClassID::derived)
// 	{
// 		// 我们确信 b 指向 Derived 对象, 所以下面的转换是一定会成功的
// 		Derived* d{ static_cast<Derived*>(b) };
// 		std::cout << "The name of the Derived is: " << d->getName() << '\n';
// 	}
//
// 	delete b;
//
// 	return 0;
// }

// 但如果您要费这么大力气来实现这一点（并支付调用虚函数和处理结果的成本），那
// 么最好直接使用 dynamic_cast。
//
// 还要考虑一种情况：如果我们的对象实际上是从 Derived 继续派生出的某个类（称为
// D2），会发生什么？上面的检查 b->getClassID() == ClassID::derived 将失败，因
// 为 getClassID() 会返回 ClassID::D2，它不等于 ClassID::derived。然而，将 D2
// dynamic_cast 为 Derived 可以成功，因为 D2 是 Derived 的更底层派生类！
//

// ―――― dynamic_cast和引用 ――――

// 尽管上述所有示例都展示了指针上的 dynamic_cast（这更常见），但 dynamic_cast
// 也可以与引用一起使用。它与处理指针时类似：

// [代码 5]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Base
// {
// protected:
// 	int m_value;
//
// public:
// 	Base(int value)
// 		: m_value{value}
// 	{
// 	}
//
// 	virtual ~Base() = default;
// };
//
// class Derived : public Base
// {
// protected:
// 	std::string m_name;
//
// public:
// 	Derived(int value, std::string_view name)
// 		: Base{value}, m_name{name}
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// };
//
// int main()
// {
// 	Derived apple{1, "Apple"}; // 创建 Derived apple
// 	Base& b{ apple }; // 将 base 引用到 apple
// 	Derived& d{ dynamic_cast<Derived&>(b) }; // dynamic cast 引用，而不是指针
//
// 	std::cout << "The name of the Derived is: " << d.getName() << '\n'; // 可以通过 d 访问到 Derived::getName
//
// 	return 0;
// }

// 由于 C++ 没有“空引用”，因此 dynamic_cast 在失败时不能返回空引用。相反，如果
// 对引用执行的 dynamic_cast 失败，则会抛出类型为 std::bad_cast 的异常。在本教
// 程的后面部分中，我们将讨论异常。
//

// ―――― dynamic_cast与static_cast ――――

// 新程序员有时会对何时使用 static_cast、何时使用 dynamic_cast 感到困惑。答案
// 很简单：默认使用 static_cast，除非是在进行向下转换；在向下转换场景中，
// dynamic_cast 通常是更好的选择。不过，您还应该考虑完全避免强制转换，改用虚函
// 数。
//

// ―――― 向下转换 vs 虚函数 ――――

// 有些开发人员认为 dynamic_cast 不好，并且意味着类设计存在问题。这些程序员会
// 建议使用虚函数。
//
// 通常，应优先使用虚函数，而不是向下转换。然而，有时向下转换是更好的选择：
// - 当您不能修改基类以添加虚函数时（例如，因为基类是标准库的一部分）
// - 当您需要访问特定于派生类的内容（例如，仅存在于派生类中的访问函数）
// - 当将虚函数添加到基类中没有意义时（例如基类没有合适的返回值）。如果不需要
//   实例化基类，也可以考虑使用纯虚函数。
//

// ―――― 关于dynamic_cast和RTTI ――――

// 运行时类型信息（RTTI，run-time type information）是 C++ 的一项功能，它会在
// 运行时暴露有关对象数据类型的信息。dynamic_cast 利用了此功能。由于 RTTI 具有
// 相当大的空间和性能开销，因此一些编译器允许关闭 RTTI。当然，如果这样做，
// dynamic_cast 将无法正常工作。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <string>
#include <string_view>

class Base
{
protected:
	int m_value{};

public:
	Base(int value)
		: m_value{value}
	{
	}

	virtual ~Base() = default;
};

class Derived : public Base
{
protected:
	std::string m_name{};

public:
	Derived(int value, std::string_view name)
		: Base{value}, m_name{name}
	{
	}

	const std::string& getName() const { return m_name; }
};

Base* getObject(bool returnDerived)
{
	if (returnDerived)
		return new Derived{1, "Apple"};
	else
		return new Base{2};
}

int main()
{
	Base* b{ getObject(true) };

	// 只有Base指针，如何获得Derived 对象的 m_name？

	delete b;

	return 0;
}
