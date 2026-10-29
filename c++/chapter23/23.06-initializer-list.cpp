// ==========================================================================
// 23.6 std::initializer_list
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十三章 对象关系
// 原文: https://www.studycpp.cn/basic/chapter23/initializer-list/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "23.06-initializer-list.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 使用std::initializer_list进行类初始化
//   · 访问std::initializer_list中的元素
//   · 列表初始化优先匹配列表构造函数
//   · 向现有类中添加列表构造函数是危险的
//   · 使用std::initializer_list进行类赋值
//   · 总结
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 考虑C++中的固定长度整数数组：

// [文本/输出]
// int array[5]；

// 如果我们想用一组值初始化这个数组，可以直接使用初始化列表语法：

// [代码 1]
// #include <iostream>
//
// int main()
// {
// 	int array[] { 5, 4, 3, 2, 1 }; // 初始化列表
// 	for (auto i : array)
// 		std::cout << i << ' ';
//
// 	return 0;
// }

// 这会打印出：

// [文本/输出]
// 5 4 3 2 1

// 这也适用于动态分配的数组：

// [代码 2]
// #include <iostream>
//
// int main()
// {
// 	auto* array{ new int[5]{ 5, 4, 3, 2, 1 } }; // 初始化列表
// 	for (int count{ 0 }; count < 5; ++count)
// 		std::cout << array[count] << ' ';
// 	delete[] array;
//
// 	return 0;
// }

// 在上一课中，我们介绍了容器类的概念，并展示了保存整数数组的IntArray类的示例：

// [代码 3]
// #include <cassert> // for assert()
// #include <iostream>
//
// class IntArray
// {
// private:
//     int m_length{};
//     int* m_data{};
//
// public:
//     IntArray() = default;
//
//     IntArray(int length)
//         : m_length{ length }
// 	, m_data{ new int[static_cast<std::size_t>(length)] {} }
//     {
//     }
//
//     ~IntArray()
//     {
//         delete[] m_data;
//         // 这里没有将 m_data 设为 null，m_length 设置为 0，因为对象被销毁，没有任何人可以使用
//     }
//
//     int& operator[](int index)
//     {
//         assert(index >= 0 && index < m_length);
//         return m_data[index];
//     }
//
//     int getLength() const { return m_length; }
// };
//
// int main()
// {
// 	// 如果使用初始化列表，来初始化 IntArray，会发生什么？
// 	IntArray array { 5, 4, 3, 2, 1 }; // 这一行无法编译
// 	for (int count{ 0 }; count < 5; ++count)
// 		std::cout << array[count] << ' ';
//
// 	return 0;
// }

// 这段代码无法通过编译，因为IntArray类的构造函数不知道如何处理初始化列表。因
// 此，需要逐个初始化数组元素：

// [代码 4]
// int main()
// {
// 	IntArray array(5);
// 	array[0] = 5;
// 	array[1] = 4;
// 	array[2] = 3;
// 	array[3] = 2;
// 	array[4] = 1;
//
// 	for (int count{ 0 }; count < 5; ++count)
// 		std::cout << array[count] << ' ';
//
// 	return 0;
// }

// 这显得有些笨拙。
//

// ―――― 使用std::initializer_list进行类初始化 ――――

// 当编译器看到初始值设定项列表时，它会自动将其转换为类型为
// std::initializer_list的对象。
//
// 因此，如果我们创建一个接受std::initializer_list参数的构造函数，就可以使用初
// 始化列表作为输入来创建对象。
//
// 关于std::initializer_list，有几点需要了解。
//
// 与std::array或std::vector类似，您必须使用尖括号告诉std::initializer_list列
// 表中保存的数据类型。因此，您几乎不会看到单独使用的std::initializer_list。相
// 反，您会看到类似于std::initializer_list<int>或
// std::initializer_list<std::string>的写法。
//
// 其次，std::initializer_list有一个size()函数，用于返回列表中的元素个数。当我
// 们需要知道传入列表的长度时，这很有用。
//
// 第三，std::initializer_list通常通过值传递。与std::string_view很相似，
// std::initializer_list是一个视图。复制std::initializer_list不会复制其中的元
// 素。
//
// 让我们看看IntArray类如何使用接收std::initializer_list的构造函数：

// [代码 5]
// #include <algorithm> // for std::copy
// #include <cassert> // for assert()
// #include <initializer_list> // for std::initializer_list
// #include <iostream>
//
// class IntArray
// {
// private:
// 	int m_length {};
// 	int* m_data{};
//
// public:
// 	IntArray() = default;
//
// 	IntArray(int length)
// 		: m_length{ length }
// 		, m_data{ new int[static_cast<std::size_t>(length)] {} }
// 	{
//
// 	}
//
// 	IntArray(std::initializer_list<int> list) // 允许IntArray使用初始化列表作为输入
// 		: IntArray(static_cast<int>(list.size())) // 使用代理构造函数进行初始化
// 	{
// 		// 现在从初始化列表中拷贝数据
// 		std::copy(list.begin(), list.end(), m_data);
// 	}
//
// 	~IntArray()
// 	{
// 		delete[] m_data;
// 		// 这里没有将 m_data 设为 null，m_length 设置为 0，因为对象被销毁，没有任何人可以使用
// 	}
//
// 	IntArray(const IntArray&) = delete; // 避免浅拷贝
// 	IntArray& operator=(const IntArray& list) = delete; // 避免浅拷贝
//
// 	int& operator[](int index)
// 	{
// 		assert(index >= 0 && index < m_length);
// 		return m_data[index];
// 	}
//
// 	int getLength() const { return m_length; }
// };
//
// int main()
// {
// 	IntArray array{ 5, 4, 3, 2, 1 }; // 初始化列表
// 	for (int count{ 0 }; count < array.getLength(); ++count)
// 		std::cout << array[count] << ' ';
//
// 	return 0;
// }

// 这产生了预期的结果：

// [文本/输出]
// 5 4 3 2 1

// 运行正常！
//
// 现在，让我们更详细地看看其中的细节。
//
// 这是我们的IntArray构造函数，它接受std::initializer_list<int>。

// [代码 6]
// IntArray(std::initializer_list<int> list) // 允许IntArray使用初始化列表作为输入
//     : IntArray(static_cast<int>(list.size())) // 使用代理构造函数进行初始化
// {
//     // 现在从初始化列表中拷贝数据
//     std::copy(list.begin(), list.end(), m_data);
// }

// 在第1行：如上所述，必须使用尖括号来表示列表中预期的元素类型。在这种情况下，
// 因为这是一个IntArray，所以我们希望用int填充列表。请注意，我们不会通过常量引
// 用传递列表。与std::string_view非常相似，std::initializer_list非常轻量级。
//
// 第2行：我们通过委托构造函数将IntArray的内存分配委托给另一个构造函数（以减少
// 冗余代码）。另一个构造函数需要知道数组的长度，因此我们将list.size()传递给它，
// 用来表示列表中的元素数量。请注意，list.size() 返回一个size_t（无符号），因
// 此这里需要转换为有符号的int。
//
// 构造函数的主体用于将元素从列表复制到IntArray类中。最简单的方法是使用
// std::copy()，它位于<algorithm>头文件中。
//

// ―――― 访问std::initializer_list中的元素 ――――

// 在某些情况下，您可能希望在将std::initializer_list的每个元素复制到内部数组之
// 前先访问该元素（例如，检查值是否合法，或以某种方式修改这些值）。
//
// 由于一些难以解释的原因，std::initializer_list不支持通过下标（operator[]）访
// 问列表元素。这个遗漏已经多次向标准委员会提出，但一直没有得到解决。
//
// 然而，有许多简单的解决方法：
// - 可以使用基于范围的for循环来迭代列表的元素。
// - 另一种方法是使用begin()成员函数获取std::initializer_list的迭代器。由于此
//   迭代器是随机访问迭代器，因此可以对迭代器进行索引。

// [代码 7]
// IntArray(std::initializer_list<int> list) // 允许IntArray使用初始化列表作为输入
// 	: IntArray(static_cast<int>(list.size())) // 使用代理构造函数进行初始化
// {
// 	// 现在从列表中初始化我们的数组
// 	for (std::size_t count{}; count < list.size(); ++count)
// 	{
// 		m_data[count] = list.begin()[count];
// 	}
// }

//

// ―――― 列表初始化优先匹配列表构造函数 ――――

// 非空初始值设定项列表始终会优先匹配initializer_list构造函数，而不是其他可能
// 匹配的构造函数。考虑：

// [代码 8]
// IntArray a1(5);   // 匹配 IntArray(int), 分配长度为 5 的数组
// IntArray a2{ 5 }; // 匹配 IntArray<std::initializer_list<int>, 分配数组长度为 1

// a1使用直接初始化（不匹配列表构造函数），因此该定义将调用IntArray(int)，分配
// 大小为5的数组。
//
// a2使用列表初始化（优先匹配列表构造函数）。在这里，IntArray(int)和
// IntArray(std::initializer_list<int>)都是可能的匹配，但由于列表构造函数优先
// 级更高，因此将调用IntArray(std::initializer_list<int>)，分配大小为1的数组（
// 该元素的值为5）。
//
// 这就是为什么我们上面的委托构造函数在委托时使用直接初始化：

// [文本/输出]
// IntArray(std::initializer_list<int> list)
// 	: IntArray(static_cast<int>(list.size())) // 使用直接初始化

// 如果使用列表初始化进行委托，构造函数将尝试委托给自己，这将导致编译错误。
//
// 同样的情况也会发生在std::vector和其他容器类上，这些容器类同时具有列表构造函
// 数，以及参数类型相近的其它构造函数。

// [代码 9]
// std::vector<int> array(5); // 调用 std::vector::vector(std::vector::size_type), 5 个值初始化的元素: 0 0 0 0 0
// std::vector<int> array{ 5 }; // 调用 std::vector::vector(std::initializer_list<int>), 1 个元素: 5

// 关键点
//
// 列表初始化会优先匹配列表构造函数，而不是非列表构造函数。
//
// 最佳实践
//
// 当初始化具有列表构造函数的容器时：
// - 当打算调用列表构造函数时使用大括号初始化（例如，因为您的初始值设定项是元
//   素值）
// - 当打算调用非列表构造函数时，使用直接初始化（例如，因为您的初始值设定项不
//   是元素值）。
//

// ―――― 向现有类中添加列表构造函数是危险的 ――――

// 因为列表初始化会优先匹配列表构造函数，所以向现有类中添加列表构造函数可能会
// 导致现有程序在没有报错的情况下改变行为。考虑以下程序：

// [代码 10]
// #include <initializer_list> // for std::initializer_list
// #include <iostream>
//
// class Foo
// {
// public:
// 	Foo(int, int)
// 	{
// 		std::cout << "Foo(int, int)" << '\n';
// 	}
// };
//
// int main()
// {
// 	Foo f1{ 1, 2 }; // 调用 Foo(int, int)
//
// 	return 0;
// }

// 这会打印：

// [文本/输出]
// Foo(int, int)

// 现在，让我们向该类添加一个列表构造函数：

// [代码 11]
// #include <initializer_list> // for std::initializer_list
// #include <iostream>
//
// class Foo
// {
// public:
// 	Foo(int, int)
// 	{
// 		std::cout << "Foo(int, int)" << '\n';
// 	}
//
// 	// 添加一个列表构造函数
// 	Foo(std::initializer_list<int>)
// 	{
// 		std::cout << "Foo(std::initializer_list<int>)" << '\n';
// 	}
//
// };
//
// int main()
// {
// 	// 注意下面的程序未改动
// 	Foo f1{ 1, 2 }; // 现在调用 Foo(std::initializer_list<int>)
//
// 	return 0;
// }

// 尽管我们没有对main函数进行其他更改，但该程序现在打印：

// [文本/输出]
// Foo(std::initializer_list<int>)

// 向没有列表构造函数的现有类中添加列表构造函数，可能会破坏现有程序。
//

// ―――― 使用std::initializer_list进行类赋值 ――――

// 您还可以通过重载赋值运算符，使用std::initializer_list参数为类分配新值。这与
// 上面的机制类似。下面进行演示。
//
// 请注意，如果实现了接收std::initializer_list的构造函数，则应确保至少执行以下
// 操作之一：
// - 提供重载的列表赋值运算符
// - 提供适当的深拷贝语义的拷贝赋值运算符
// - 删除拷贝赋值运算符
//
// 原因如下：考虑以下类（它没有上面提到的三点逻辑），以及列表赋值语句：

// [代码 12]
// #include <algorithm> // for std::copy()
// #include <cassert>   // for assert()
// #include <initializer_list> // for std::initializer_list
// #include <iostream>
//
// class IntArray
// {
// private:
// 	int m_length{};
// 	int* m_data{};
//
// public:
// 	IntArray() = default;
//
// 	IntArray(int length)
// 		: m_length{ length }
// 		, m_data{ new int[static_cast<std::size_t>(length)] {} }
// 	{
//
// 	}
//
// 	IntArray(std::initializer_list<int> list) // 允许IntArray使用列表初始化
// 		: IntArray(static_cast<int>(list.size())) // 使用代理构造函数进行初始化
// 	{
// 		// 现在从列表中初始化我们的数组
// 		std::copy(list.begin(), list.end(), m_data);
// 	}
//
// 	~IntArray()
// 	{
// 		delete[] m_data;
// 	}
//
// //	IntArray(const IntArray&) = delete; // 避免浅拷贝
// //	IntArray& operator=(const IntArray& list) = delete; // 避免浅拷贝
//
// 	int& operator[](int index)
// 	{
// 		assert(index >= 0 && index < m_length);
// 		return m_data[index];
// 	}
//
// 	int getLength() const { return m_length; }
// };
//
// int main()
// {
// 	IntArray array{};
// 	array = { 1, 3, 5, 7, 9, 11 }; // 列表赋值语句
//
// 	for (int count{ 0 }; count < array.getLength(); ++count)
// 		std::cout << array[count] << ' '; // 未定义的行为
//
// 	return 0;
// }

// 首先，编译器会注意到接收std::initializer_list的赋值函数不存在。接下来，它会
// 查找其它可用的赋值函数，并发现隐式提供的拷贝赋值运算符。然而，只有当它可以
// 将初始值设定项列表转换为IntArray时，才能使用此函数。由于{1,3,5,7,9,11}是
// std::initializer_list，编译器会使用列表构造函数将该初始值设定项列表转换为临
// 时IntArray。然后，它会调用隐式赋值操作符，将临时IntArray浅拷贝到array对象中。
//
// 此时，临时IntArray的m_data和array->m_data都指向同一个地址（由于浅拷贝）。
//
// 在赋值语句结束时，临时IntArray会被销毁。它会调用析构函数，而析构函数会删除
// 临时IntArray的m_data。这会使array->m_data成为悬空指针。当您尝试以任何方式使
// 用array->m_data时（包括在析构函数中删除m_data），都会产生未定义行为。
//
// 最佳实践
//
// 如果提供了列表构造函数，最好也提供列表赋值函数。
//

// ―――― 总结 ――――

// 实现接受std::initializer_list参数的构造函数允许我们对自定义类使用列表初始化。
// 还可以使用std::initializer_list实现需要使用初始值设定项列表的其他函数，如赋
// 值运算符。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 使用上面介绍的IntArray类，实现一个接受初始化列表的重载赋值运算符。
//
// 下面这段代码应当能够运行：

// [代码 13]
// int main()
// {
// 	IntArray array { 5, 4, 3, 2, 1 }; // 初始化列表
// 	for (int count{ 0 }; count < array.getLength(); ++count)
// 		std::cout << array[count] << ' ';
//
// 	std::cout << '\n';
//
// 	array = { 1, 3, 5, 7, 9, 11 };
//
// 	for (int count{ 0 }; count < array.getLength(); ++count)
// 		std::cout << array[count] << ' ';
//
// 	std::cout << '\n';
//
// 	return 0;
// }

// 它应当打印：

// [文本/输出]
// 5 4 3 2 1
// 1 3 5 7 9 11


// 【答案 · 查看答案】

// [代码 14]
// #include <algorithm> // 用于 std::copy()
// #include <cassert>   // 用于 assert()
// #include <initializer_list> // 用于 std::initializer_list
// #include <iostream>
//
// class IntArray
// {
// private:
// 	int m_length {};
// 	int* m_data {};
//
// public:
// 	IntArray() = default;
//
// 	IntArray(int length)
// 		: m_length{ length }
// 		, m_data{ new int[static_cast<std::size_t>(length)] {} }
// 	{
//
// 	}
//
// 	IntArray(std::initializer_list<int> list) : // 允许通过列表初始化来初始化 IntArray
// 		IntArray(static_cast<int>(list.size())) // 使用委托构造函数来建立初始数组
// 	{
// 		// 现在用这个列表初始化数组
// 		std::copy(list.begin(), list.end(), m_data);
// 	}
//
// 	~IntArray()
// 	{
// 		delete[] m_data;
// 		// 这里不需要把 m_data 置空、把 m_length 置 0，因为对象在本函数结束后马上就会被销毁
// 	}
//
// 	IntArray(const IntArray&) = delete; // 以避免浅拷贝
// 	IntArray& operator=(const IntArray& list) = delete; // 以避免浅拷贝
//
// 	IntArray& operator=(std::initializer_list<int> list)
// 	{
// 		// 如果新列表的大小不同，就重新分配
// 		int length { static_cast<int>(list.size()) };
// 		if (length != m_length)
// 		{
// 			delete[] m_data;
// 			m_length = length;
// 			m_data = new int[list.size()]{};
// 		}
//
// 		// 现在用这个列表初始化数组
// 		std::copy(list.begin(), list.end(), m_data);
//
// 		return *this;
// 	}
//
// 	int& operator[](int index)
// 	{
// 		assert(index >= 0 && index < m_length);
// 		return m_data[index];
// 	}
//
// 	int getLength() const { return m_length; }
// };
//
// int main()
// {
// 	IntArray array { 5, 4, 3, 2, 1 }; // 初始化列表
// 	for (int count{ 0 }; count < array.getLength(); ++count)
// 		std::cout << array[count] << ' ';
//
// 	std::cout << '\n';
//
// 	array = { 1, 3, 5, 7, 9, 11 };
//
// 	for (int count{ 0 }; count < array.getLength(); ++count)
// 		std::cout << array[count] << ' ';
//
// 	std::cout << '\n';
//
// 	return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
	int array[] { 5, 4, 3, 2, 1 }; // 初始化列表
	for (auto i : array)
		std::cout << i << ' ';

	return 0;
}
