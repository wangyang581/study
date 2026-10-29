// ==========================================================================
// 19.2 再谈析构函数
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十九章 动态内存分配
// 原文: https://www.studycpp.cn/basic/chapter19/destructor/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "19.02-destructor.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 析构函数命名
//   · 析构函数示例
//   · 构造函数和析构函数的调用时机
//   · RAII
//   · 关于std::exit()函数的警告
//   · 总结

// ==========================================================================
// 教程正文
// ==========================================================================

// 析构函数是另一种特殊类型的类成员函数，会在该类对象被销毁时执行。构造函数用
// 于初始化类，而析构函数用于帮助清理类。
//
// 当对象正常超出作用域，或者使用delete关键字显式删除动态分配的对象时，类的析
// 构函数会自动调用（如果存在），以便在对象从内存中移除之前完成必要的清理。对
// 于简单的类（那些只初始化普通成员变量值的类），通常不需要析构函数，因为C++会
// 自动为您清理内存。
//
// 然而，如果类对象持有任何资源（例如动态内存、文件或数据库句柄），或者您需要
// 在销毁对象之前执行某种维护操作，那么析构函数就是完成这些工作的最佳位置，因
// 为它通常是对象销毁前发生的最后一件事。
//

// ―――― 析构函数命名 ――――

// 与构造函数一样，析构函数也有特定的命名规则：
// - 析构函数与类名一致，外加一个前导的 ~
// - 析构函数无任何参数
// - 析构函数无返回值
//
// 类只能有一个析构函数。
//
// 通常，您不应该显式调用析构函数（因为对象被销毁时它会自动调用），因为很少有
// 场景需要多次清理同一个对象。析构函数可以安全地调用其他成员函数，因为对象直
// 到析构函数执行完成后才会被销毁。
//

// ―――― 析构函数示例 ――――

// 让我们来看一个使用析构函数的简单类：

// [代码 1]
// #include <iostream>
// #include <cassert>
// #include <cstddef>
//
// class IntArray
// {
// private:
// 	int* m_array{};
// 	int m_length{};
//
// public:
// 	IntArray(int length) // 构造函数
// 	{
// 		assert(length > 0);
//
// 		m_array = new int[static_cast<std::size_t>(length)]{};
// 		m_length = length;
// 	}
//
// 	~IntArray() // 析构函数
// 	{
// 		// 删除初始化时动态分配的数组
// 		delete[] m_array;
// 	}
//
// 	void setValue(int index, int value) { m_array[index] = value; }
// 	int getValue(int index) { return m_array[index]; }
//
// 	int getLength() { return m_length; }
// };
//
// int main()
// {
// 	IntArray ar ( 10 ); // 分配 10 个int
// 	for (int count{ 0 }; count < ar.getLength(); ++count)
// 		ar.setValue(count, count+1);
//
// 	std::cout << "The value of element 5 is: " << ar.getValue(5) << '\n';
//
// 	return 0;
// } // ar 在这里销毁, 所以 ~IntArray() 析构函数在这里被调用

// 该程序生成以下结果：

// [文本/输出]
// The value of element 5 is: 6

// 在main()的第一行，我们实例化了一个名为ar的IntArray类对象，并传入长度为10的
// 值。这会调用构造函数，而该构造函数会为数组成员动态分配内存。这里必须使用动
// 态分配，因为我们在编译时不知道数组的长度是多少（长度由调用方决定）。
//
// 在main()的末尾，ar超出作用域。这会触发~IntArray()析构函数的调用，从而删除在
// 构造函数中分配的数组！
//
// 一个提醒
//
// 在介绍std::vector和列表构造函数时，我们注意到，在初始化具有长度（而不是元素
// 列表）的数组/容器/列表类时，应该使用基于圆括号的初始化。因此，我们使用
// “IntArray ar ( 10 );” 初始化IntArray。
//

// ―――― 构造函数和析构函数的调用时机 ――――

// 如前所述，创建对象时会调用构造函数，销毁对象时会调用析构函数。在下面的示例
// 中，我们在构造函数和析构函数中使用cout语句来展示这一点：

// [代码 2]
// #include <iostream>
//
// class Simple
// {
// private:
//     int m_nID{};
//
// public:
//     Simple(int nID)
//         : m_nID{ nID }
//     {
//         std::cout << "Constructing Simple " << nID << '\n';
//     }
//
//     ~Simple()
//     {
//         std::cout << "Destructing Simple" << m_nID << '\n';
//     }
//
//     int getID() { return m_nID; }
// };
//
// int main()
// {
//     // 在栈上分配了一个对象 simple
//     Simple simple{ 1 };
//     std::cout << simple.getID() << '\n';
//
//     // 动态分配了一个 Simple 对象
//     Simple* pSimple{ new Simple{ 2 } };
//
//     std::cout << pSimple->getID() << '\n';
//
//     // pSimple 是动态分配的, 所以这里手动delete它.
//     delete pSimple;
//
//     return 0;
// } // simple 超出作用域

// 该程序产生以下结果：

// [文本/输出]
// Constructing Simple 1
// 1
// Constructing Simple 2
// 2
// Destructing Simple 2
// Destructing Simple 1

// 注意，“Simple1”在“Simple2”之后被销毁，因为我们在函数结束之前delete了pSimple，
// 而simple直到main()结束才被销毁。
//
// 全局变量在main()之前构造，在main()之后销毁。
//

// ―――― RAII ――――

// RAII（Resource Acquisition Is Initialization，资源获取即初始化）是一种编程
// 技术，它将资源的使用与具有自动持续时间的对象（例如非动态分配的对象）的生命
// 周期关联起来。在C++中，RAII通过具有构造函数和析构函数的类来实现。资源（如内
// 存、文件或数据库句柄等）通常在对象的构造函数中获取（尽管也可以在创建对象后
// 获取）。然后，可以在对象处于活动状态时使用该资源。销毁对象时，资源会在析构
// 函数中释放。RAII的主要优势是有助于防止资源泄漏（例如，内存未被释放），因为
// 所有持有资源的对象都会自动清理。
//
// 本课开头的IntArray类就是实现RAII的示例：在构造函数中分配资源，在析构函数中
// 释放资源。string和std::vector是标准库中遵循RAII的类的示例：动态内存在初始化
// 时获得，在销毁时自动清理。
//

// ―――― 关于std::exit()函数的警告 ――――

// 注意，如果使用std::exit()函数，程序将会终止，并且不会调用析构函数。如果您依
// 赖析构函数来执行必要的清理工作（例如，在退出之前将某些内容写入日志文件或数
// 据库），请谨慎使用。
//

// ―――― 总结 ――――

// 正如您所看到的，当构造函数和析构函数配合使用时，类可以帮助完成初始化和清理，
// 而使用该类的程序员不必做任何特殊工作！这降低了出错概率，并使类更易于使用。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <cassert>
#include <cstddef>

class IntArray
{
private:
	int* m_array{};
	int m_length{};

public:
	IntArray(int length) // 构造函数
	{
		assert(length > 0);

		m_array = new int[static_cast<std::size_t>(length)]{};
		m_length = length;
	}

	~IntArray() // 析构函数
	{
		// 删除初始化时动态分配的数组
		delete[] m_array;
	}

	void setValue(int index, int value) { m_array[index] = value; }
	int getValue(int index) { return m_array[index]; }

	int getLength() { return m_length; }
};

int main()
{
	IntArray ar ( 10 ); // 分配 10 个int
	for (int count{ 0 }; count < ar.getLength(); ++count)
		ar.setValue(count, count+1);

	std::cout << "The value of element 5 is: " << ar.getValue(5) << '\n';

	return 0;
} // ar 在这里销毁, 所以 ~IntArray() 析构函数在这里被调用
