// ==========================================================================
// 21.14 第21章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十一章 操作符重载
// 原文: https://www.studycpp.cn/basic/chapter21/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "21.14-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 总结
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 在本章中，我们探讨了运算符重载、重载类型转换，以及与拷贝构造函数相关的主题。
//

// ―――― 总结 ――――

// 运算符重载是函数重载的一种变体，它允许为类重载运算符。重载运算符时，其语义
// 应尽可能接近运算符的原始意图。如果某个运算符应用于自定义类时含义不够明确、
// 直观，请使用命名成员函数。
//
// 运算符可以重载为普通函数、友元函数或成员函数。以下经验法则可以帮助您确定哪
// 种形式最适合给定的情况：
// - 如果重载赋值（=）、下标（[]）、函数调用（（））或成员选择（->），请作为
//   成员函数进行重载。
// - 如果要重载一元运算符，请作为成员函数进行重载。
// - 如果重载修改其左操作数的二元运算符（例如，运算符+=），请尽可能作为成员函
//   数进行重载。
// - 如果要重载不修改其左操作数的二元运算符（例如，运算符+），请作为普通函数
//   或友元函数进行重载。
//
// 可以重载类型转换来提供转换函数，用于将类显式或隐式转换为另一种类型。
//
// 拷贝构造函数是一种特殊类型的构造函数，用于从同类型的另一个对象初始化对象。
// 拷贝构造函数会在从同类型对象进行直接/统一初始化、拷贝初始化（Fraction f =
// Fraction（5,3）），以及按值传递或返回对象时使用。
//
// 如果不提供拷贝构造函数，编译器将为您创建一个默认版本。编译器提供的拷贝构造
// 函数会使用成员级初始化，这意味着副本的每个成员都会从原始对象对应成员初始化。
// 出于优化目的，拷贝构造函数可能会被省略，即使它有副作用也一样，因此不要依赖
// 拷贝构造函数一定会实际执行。
//
// 默认情况下，构造函数会被视为转换构造函数，这意味着编译器可能使用它们将其他
// 类型的对象隐式转换为该类的对象。通过在构造函数前使用explicit关键字，可以避
// 免这种情况。您还可以删除类中的函数，包括拷贝构造函数和重载赋值运算符（如果
// 需要）。如果调用已删除的函数，将导致编译错误。
//
// 可以重载赋值运算符，以允许对类对象进行赋值。如果不提供重载赋值运算符，编译
// 器将为您创建一个默认版本。重载赋值运算符通常应该包含自赋值检查。
//
// 新程序员经常会混淆赋值运算符和拷贝构造函数的使用场景，但判断方式相当简单：
// - 如果在复制之前必须创建新对象，则使用拷贝构造函数（注意：这包括按值传递或
//   返回对象）。
// - 如果在复制之前不必创建新对象，则使用赋值运算符。
//
// 默认情况下，编译器提供的拷贝构造函数和赋值运算符会执行成员级初始化或赋值，
// 也就是浅拷贝。如果类会动态分配内存，这可能导致问题，因为多个对象最终会指向
// 同一块已分配内存。在这种情况下，您需要显式定义这些函数，以便执行深拷贝。更
// 好的做法是：如果可以，请避免自己进行内存管理，优先使用标准库中的类。
//

// ―――― 习题 ――――


// ▼ 问题 1
// - 假设`Point`是一个类，`point`是该类的实例，下列运算符应当使用普通/友元函
//   数重载，还是成员函数重载？
//
// a) `point + point`

// 【答案 · 查看答案】
// 二元`operator+`最好实现为普通函数或友元函数。
//
// b) `-point`

// 【答案 · 查看答案】
// 一元`operator-`最好实现为成员函数。
//
// c) `std::cout << point`

// 【答案 · 查看答案】
// `operator<<`必须实现为普通函数或友元函数。
//
// d) `point = 5;`

// 【答案 · 查看答案】
// `operator=`必须实现为成员函数。

// ▼ 问题 2
// 编写一个名为`Average`的类，用来记录传入它的所有整数的平均值。使用两个成员：
// 第一个成员类型为`std::int32_t`，用于记录目前为止见过的所有数字之和；第二个
// 成员记录目前为止见过的数字个数。用前者除以后者即可得到平均值。
//
// a) 编写让下面这个程序能够运行所需的全部函数：

// [代码 1]
// int main()
// {
// 	Average avg{};
// 	std::cout << avg << '\n';
//
// 	avg += 4;
// 	std::cout << avg << '\n'; // 4 / 1 = 4
//
// 	avg += 8;
// 	std::cout << avg << '\n'; // (4 + 8) / 2 = 6
//
// 	avg += 24;
// 	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12
//
// 	avg += -10;
// 	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5
//
// 	(avg += 6) += 10; // 两次调用链式相连
// 	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7
//
// 	Average copy{ avg };
// 	std::cout << copy << '\n';
//
// 	return 0;
// }

// 并产生如下结果：

// [文本/输出]
// 0
// 4
// 6
// 12
// 6.5
// 7
// 7


// 【答案 · 查看答案】

// [代码 2]
// #include <iostream>
// #include <cstdint> // 用于固定宽度的整数
//
// class Average
// {
// private:
// 	std::int32_t m_total{ 0 }; // 目前见过的所有数字之和
// 	int m_numbers{ 0 }; // 目前见过的数字个数
//
// public:
// 	Average()
// 	{
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const Average& average)
// 	{
//         // 处理还没有见过任何数字的情况
// 		if (average.m_numbers == 0)
// 		{
// 			out << 0;
// 			return out;
// 		}
//
// 		// 平均值等于已见过的数字之和除以已见过的数字个数
// 		// 注意这里要做浮点除法，而不是整数除法
// 		out << static_cast<double>(average.m_total) / average.m_numbers;
//
// 		return out;
// 	}
//
// 	// 由于 operator+= 会修改左操作数，我们把它实现为成员函数
// 	Average& operator+=(std::int32_t num)
// 	{
// 		// 用新数字累加总和
// 		m_total += num;
// 		// 并把计数加 1
// 		++m_numbers;
//
// 		// 返回 *this，以便有人想把多个 += 连起来写
// 		return *this;
// 	}
// };
//
// int main()
// {
// 	Average avg{};
// 	std::cout << avg << '\n';
//
// 	avg += 4;
// 	std::cout << avg << '\n';
//
// 	avg += 8;
// 	std::cout << avg << '\n';
//
// 	avg += 24;
// 	std::cout << avg << '\n';
//
// 	avg += -10;
// 	std::cout << avg << '\n';
//
// 	(avg += 6) += 10; // 两次调用链式相连
// 	std::cout << avg << '\n';
//
// 	Average copy{ avg };
// 	std::cout << copy << '\n';
//
// 	return 0;
// }

// b) 应该为这个类提供自定义的拷贝构造函数或赋值运算符吗？

// 【答案 · 查看答案】
// 不需要。因为这里采用逐成员初始化/拷贝是合适的，使用编译器提供的默认版本即可。
//
// c) 为什么使用`std::int32_t`而不是`int`？

// 【答案 · 查看答案】
// `int`在某些平台上可能是16位的，这意味着我们的`Average`对象最多只能保存32767
// 这样的分子值。使用`std::int32_t`可以保证得到32位整数值，可用范围大得多。

// ▼ 问题 3
// 从零开始编写你自己的整数数组类，名为`IntArray`（不要使用std::array或
// std::vector）。用户在创建时传入数组大小，数组应当动态分配。使用assert语句防
// 止错误的数据。创建让下面这个程序能够正确运行所需的所有构造函数或重载运算符：

// [代码 3]
// #include <iostream>
//
// IntArray fillArray()
// {
// 	IntArray a(5);
//
// 	a[0] = 5;
// 	a[1] = 8;
// 	a[2] = 2;
// 	a[3] = 3;
// 	a[4] = 6;
//
// 	return a;
// }
//
// int main()
// {
// 	IntArray a{ fillArray() };
//
// 	std::cout << a << '\n';
//
// 	auto& ref{ a }; // 这里使用引用是为了避免编译器对自赋值报错
// 	a = ref;
//
// 	IntArray b(1);
// 	b = a;
//
// 	a[4] = 7;
//
// 	std::cout << b << '\n';
//
// 	return 0;
// }

// 这个程序应当打印：

// [文本/输出]
// 5 8 2 3 6
// 5 8 2 3 6


// 【答案 · 查看答案】

// [代码 4]
// #include <iostream>
// #include <cassert> // 用于 assert
//
// class IntArray
// {
// private:
// 	int m_length{ 0 };
// 	int* m_array{ nullptr };
//
// public:
// 	explicit IntArray(int length)
// 		: m_length{ length }
// 	{
// 		assert(length > 0 && "IntArray length should be a positive integer");
//
// 		m_array = new int[static_cast<std::size_t>(m_length)] {};
// 	}
//
// 	// 进行深拷贝的拷贝构造函数
// 	IntArray(const IntArray& array)
// 		: m_length{ array.m_length }
// 	{
// 		// 分配一个新数组
// 		m_array = new int[static_cast<std::size_t>(m_length)] {};
//
// 		// 把元素从原数组拷贝到新数组
// 		for (int count{ 0 }; count < array.m_length; ++count)
// 			m_array[count] = array.m_array[count];
// 	}
//
// 	~IntArray()
// 	{
// 		delete[] m_array;
// 	}
//
// 	// 如果这里的值乱七八糟，很可能你在拷贝构造函数中忘了做深拷贝
// 	friend std::ostream& operator<<(std::ostream& out, const IntArray& array)
// 	{
// 		for (int count{ 0 }; count < array.m_length; ++count)
// 		{
// 			out << array.m_array[count] << ' ';
// 		}
// 		return out;
// 	}
//
// 	int& operator[] (const int index)
// 	{
// 		assert(index >= 0);
// 		assert(index < m_length);
// 		return m_array[index];
// 	}
//
// 	// 进行深拷贝的赋值运算符
// 	IntArray& operator= (const IntArray& array)
// 	{
// 		// 自赋值保护
// 		if (this == &array)
// 			return *this;
//
// 		// 如果这个数组已经存在，就先删除它，以免内存泄漏
// 		delete[] m_array;
//
// 		m_length = array.m_length;
//
// 		// 分配一个新数组
// 		m_array = new int[static_cast<std::size_t>(m_length)] {};
//
// 		// 把元素从原数组拷贝到新数组
// 		for (int count{ 0 }; count < array.m_length; ++count)
// 			m_array[count] = array.m_array[count];
//
// 		return *this;
// 	}
//
// };
//
// IntArray fillArray()
// {
// 	IntArray a(5);
// 	a[0] = 5;
// 	a[1] = 8;
// 	a[2] = 2;
// 	a[3] = 3;
// 	a[4] = 6;
//
// 	return a;
// }
//
// int main()
// {
// 	IntArray a{ fillArray() };
//
// 	// 如果这里的值乱七八糟，很可能你在拷贝构造函数中忘了做深拷贝
// 	std::cout << a << '\n';
//
// 	auto& ref{ a }; // 这里使用引用是为了避免编译器对自赋值报错
// 	a = ref;
//
// 	IntArray b(1);
// 	b = a;
//
// 	a[4] = 7; // 修改 a 的值，b 应当保持不变
//
// 	// 如果这里的值乱七八糟，很可能你忘了做自赋值检查
// 	// 如果 b 以 7 结尾，很可能你在拷贝赋值中忘了做深拷贝
// 	std::cout << b << '\n';
//
// 	return 0;
// }


// ▼ 问题 4
// 附加题：这道题稍微麻烦一些。
//
// 浮点数是指带小数点的数，其中小数点后的位数可以是变化的。定点数是指带有小数
// 部分的数，其中小数部分的位数是固定的。
//
// 本题我们要编写一个类来实现「小数点后两位」的定点数（例如12.34、3.00或
// 1278.99）。假设该类的取值范围是-32768.99到32767.99，小数部分可以是任意两位
// 数字，我们既不想有精度误差，又想节省空间。
//
// 第1步
//
// 你认为应当使用什么类型的成员变量来实现这个「小数点后两位」的定点数？（请务
// 必先看完答案再进行下一题）

// 【答案 · 查看答案】
// 实现定点数有很多种方式。由于定点数本质上是浮点数的一个特例（小数位数固定而
// 不是可变），使用浮点数看起来是个显而易见的选择。但浮点数存在精度问题。由于
// 小数位数固定，我们完全可以枚举出所有可能的小数值（本例中是.00到.99），因此
// 使用有精度问题的数据类型并非最佳选择。
//
// 更好的做法是：用一个16位有符号整数保存整数部分，用一个8位有符号整数保存小数
// 部分。
//
// 第2步
//
// 编写一个名为`FixedPoint2`的类，实现上一题的推荐方案。如果该数的整数部分或小
// 数部分（或两者）为负，则该数应被视为负数。提供让下面这个程序能够运行所需的
// 重载运算符和构造函数。暂时不必考虑小数部分越界（>99或<-99）的情况。

// [代码 5]
// #include <cassert>
// #include <iostream>
//
// int main()
// {
// 	FixedPoint2 a{ 34, 56 };
// 	std::cout << a << '\n';
// 	std::cout << static_cast<double>(a) << '\n';
// 	assert(static_cast<double>(a) == 34.56);
//
// 	FixedPoint2 b{ -2, 8 };
// 	assert(static_cast<double>(b) == -2.08);
//
// 	FixedPoint2 c{ 2, -8 };
// 	assert(static_cast<double>(c) == -2.08);
//
// 	FixedPoint2 d{ -2, -8 };
// 	assert(static_cast<double>(d) == -2.08);
//
// 	FixedPoint2 e{ 0, -5 };
// 	assert(static_cast<double>(e) == -0.05);
//
// 	FixedPoint2 f{ 0, 10 };
// 	assert(static_cast<double>(f) == 0.1);
//
// 	return 0;
// }

// 这个程序应当产生如下结果：

// [文本/输出]
// 34.56
// 34.56

// 提示：要输出这个数，可以把它static_cast为double。

// 【答案 · 查看答案】

// [代码 6]
// #include <cassert>
// #include <cstdint> // 用于固定宽度的整数
// #include <iostream>
//
// class FixedPoint2
// {
// private:
// 	std::int16_t m_base{}; // 这里是整数部分
// 	std::int8_t m_decimal{}; // 这里是小数部分
//
// public:
// 	FixedPoint2(std::int16_t base = 0, std::int8_t decimal = 0)
// 		: m_base{ base }, m_decimal{ decimal }
// 	{
// 		// 如果整数部分或小数部分（或两者）为负，就把这个数当作负数处理
// 		if (m_base < 0 || m_decimal < 0)
// 		{
// 			// 确保整数部分为负
// 			if (m_base > 0)
// 				m_base = -m_base;
// 			// 确保小数部分为负
// 			if (m_decimal > 0)
// 				m_decimal = -m_decimal;
// 		}
// 	}
//
// 	explicit operator double() const
// 	{
// 		return m_base + (static_cast<double>(m_decimal) / 100);
// 	}
// };
//
// // 它不需要访问类的内部细节，因此可以定义在类外
// std::ostream& operator<<(std::ostream& out, const FixedPoint2& fp)
// {
// 	out << static_cast<double>(fp);
// 	return out;
// }
//
// int main()
// {
// 	FixedPoint2 a{ 34, 56 };
// 	std::cout << a << '\n';
// 	std::cout << static_cast<double>(a) << '\n';
// 	assert(static_cast<double>(a) == 34.56);
//
// 	FixedPoint2 b{ -2, 8 };
// 	assert(static_cast<double>(b) == -2.08);
//
// 	FixedPoint2 c{ 2, -8 };
// 	assert(static_cast<double>(c) == -2.08);
//
// 	FixedPoint2 d{ -2, -8 };
// 	assert(static_cast<double>(d) == -2.08);
//
// 	FixedPoint2 e{ 0, -5 };
// 	assert(static_cast<double>(e) == -0.05);
//
// 	FixedPoint2 f{ 0, 10 };
// 	assert(static_cast<double>(f) == 0.1);
//
// 	return 0;
// }

// 第3步
//
// 现在来处理小数部分越界的情况。这里有两种合理的策略：
// - 截断小数部分（如果>99，就设为99）。
// - 把溢出当作有效处理（如果>99，就减去100并把整数部分加1）。
//
// 本题中我们把小数溢出当作有效处理，这在下一步中会很有用。
//
// 下面这段代码应当能够运行：

// [代码 7]
// #include <cassert>
// #include <iostream>
//
// // 你需要把 testDecimal 声明为 FixedPoint2 的友元
// // 这样这个函数才能访问 FixedPoint2 的私有成员
// bool testDecimal(const FixedPoint2 &fp)
// {
//     if (fp.m_base >= 0)
//         return fp.m_decimal >= 0 && fp.m_decimal < 100;
//     else
//         return fp.m_decimal <= 0 && fp.m_decimal > -100;
// }
//
// int main()
// {
// 	FixedPoint2 a{ 1, 104 };
// 	std::cout << a << '\n';
// 	std::cout << static_cast<double>(a) << '\n';
// 	assert(static_cast<double>(a) == 2.04);
// 	assert(testDecimal(a));
//
// 	FixedPoint2 b{ 1, -104 };
// 	assert(static_cast<double>(b) == -2.04);
// 	assert(testDecimal(b));
//
// 	FixedPoint2 c{ -1, 104 };
// 	assert(static_cast<double>(c) == -2.04);
// 	assert(testDecimal(c));
//
// 	FixedPoint2 d{ -1, -104 };
// 	assert(static_cast<double>(d) == -2.04);
// 	assert(testDecimal(d));
//
// 	return 0;
// }

// 并产生输出：

// [文本/输出]
// 2.04
// 2.04


// 【答案 · 查看答案】

// [代码 8]
// #include <cassert>
// #include <cstdint> // 用于固定宽度的整数
// #include <iostream>
//
// class FixedPoint2
// {
// private:
// 	std::int16_t m_base{}; // 这里是整数部分
// 	std::int8_t m_decimal{}; // 这里是小数部分
//
// public:
// 	FixedPoint2(std::int16_t base = 0, std::int8_t decimal = 0)
// 		: m_base{ base }, m_decimal{ decimal }
// 	{
// 		// 如果整数部分或小数部分（或两者）为负，就把这个数当作负数处理
// 		if (m_base < 0 || m_decimal < 0)
// 		{
// 			// 确保整数部分为负
// 			if (m_base > 0)
// 				m_base = -m_base;
// 			// 确保小数部分为负
// 			if (m_decimal > 0)
// 				m_decimal = -m_decimal;
// 		}
//
// 		// 如果小数部分越界（无论哪个方向），
// 		// 调整小数部分使其回到范围内，
// 		// 并相应调整整数部分，以补偿从小数部分移走的单位
// 		// 感谢读者 David Pinheiro 简化了这段代码
// 		m_base += m_decimal / 100;    // 整数除法
// 		m_decimal = m_decimal % 100;  // 整数取余
// 	}
//
// 	explicit operator double() const
// 	{
// 		return m_base + (static_cast<double>(m_decimal) / 100);
// 	}
//
// 	friend bool testDecimal(const FixedPoint2 &fp);
// };
//
// // 它不需要访问类的内部细节，因此可以定义在类外
// std::ostream& operator<<(std::ostream& out, const FixedPoint2& fp)
// {
// 	out << static_cast<double>(fp);
// 	return out;
// }
//
// // 你需要把 testDecimal 声明为 FixedPoint2 的友元
// // 这样这个函数才能访问 FixedPoint2 的私有成员
// bool testDecimal(const FixedPoint2 &fp)
// {
// 	if (fp.m_base >= 0)
// 		return fp.m_decimal >= 0 && fp.m_decimal < 100;
// 	else
// 		return fp.m_decimal <= 0 && fp.m_decimal > -100;
// }
//
// int main()
// {
// 	FixedPoint2 a{ 1, 104 };
// 	std::cout << a << '\n';
// 	std::cout << static_cast<double>(a) << '\n';
// 	assert(static_cast<double>(a) == 2.04);
// 	assert(testDecimal(a));
//
// 	FixedPoint2 b{ 1, -104 };
// 	assert(static_cast<double>(b) == -2.04);
// 	assert(testDecimal(b));
//
// 	FixedPoint2 c{ -1, 104 };
// 	assert(static_cast<double>(c) == -2.04);
// 	assert(testDecimal(c));
//
// 	FixedPoint2 d{ -1, -104 };
// 	assert(static_cast<double>(d) == -2.04);
// 	assert(testDecimal(d));
//
// 	return 0;
// }

// 第4步
//
// 现在添加一个接受double的构造函数。下面这个程序应当能够运行：

// [代码 9]
// #include <cassert>
// #include <iostream>
//
// int main()
// {
// 	FixedPoint2 a{ 0.01 };
// 	assert(static_cast<double>(a) == 0.01);
//
// 	FixedPoint2 b{ -0.01 };
// 	assert(static_cast<double>(b) == -0.01);
//
// 	FixedPoint2 c{ 1.9 }; // 确保能处理一位数的小数部分
// 	assert(static_cast<double>(c) == 1.9);
//
// 	FixedPoint2 d{ 5.01 }; // 实际存储为 5.0099999……因此需要四舍五入
// 	assert(static_cast<double>(d) == 5.01);
//
// 	FixedPoint2 e{ -5.01 }; // 实际存储为 -5.0099999……因此需要四舍五入
// 	assert(static_cast<double>(e) == -5.01);
//
// 	// 处理实参的小数部分四舍五入后为 100 的情况（需要把整数部分加 1）
// 	FixedPoint2 f { 106.9978 }; // 应当以整数部分 107、小数部分 0 存储
// 	assert(static_cast<double>(f) == 107.0);
//
// 	// 处理实参的小数部分四舍五入后为 -100 的情况（需要把整数部分减 1）
// 	FixedPoint2 g { -106.9978 }; // 应当以整数部分 -107、小数部分 0 存储
// 	assert(static_cast<double>(g) == -107.0);
//
// 	return 0;
// }

// 建议：这道题会稍微棘手一些。请分三步完成。首先解决double形参可以直接表示的
// 情况（上面变量a到c）。然后修改代码，处理double形参存在舍入误差的情况（变量d
// 和e）。变量f和g应当由上一步加入的溢出处理逻辑来应对。
//
// 所有情况：

// 【答案 · 显示提示】
// 把小数点右边的数字移到左边，可以乘以10；移动两位就乘以100。
//
// 变量a到c：

// 【答案 · 显示提示】
// 把double static_cast成整数，就能得到它的整数部分。要得到小数部分，可以减掉
// 整数部分。
//
// 变量d和e：

// 【答案 · 显示提示】
// 可以使用`std::round()`函数（位于`<cmath>`头文件）对数字（小数点左边部分）进
// 行四舍五入，并使用`std::trunc()`向零取整。

// 【答案 · 查看答案】

// [代码 10]
// #include <cassert>
// #include <cmath>
// #include <cstdint> // 用于固定宽度的整数
// #include <iostream>
//
// class FixedPoint2
// {
// private:
// 	std::int16_t m_base{}; // 这里是整数部分
// 	std::int8_t m_decimal{}; // 这里是小数部分
//
// public:
// 	FixedPoint2(std::int16_t base = 0, std::int8_t decimal = 0)
// 		: m_base{ base }, m_decimal{ decimal }
// 	{
// 		// 如果整数部分或小数部分（或两者）为负，就把这个数当作负数处理
// 		if (m_base < 0 || m_decimal < 0)
// 		{
// 			// 确保整数部分为负
// 			if (m_base > 0)
// 				m_base = -m_base;
// 			// 确保小数部分为负
// 			if (m_decimal > 0)
// 				m_decimal = -m_decimal;
// 		}
//
// 		// 如果小数部分越界（无论哪个方向），
// 		// 调整小数部分使其回到范围内，
// 		// 并相应调整整数部分，以补偿从小数部分移走的单位
// 		// 感谢读者 David Pinheiro 简化了这段代码
// 		m_base += m_decimal / 100;    // 整数除法
// 		m_decimal = m_decimal % 100;  // 整数取余
// 	}
//
// 	// 我们委托给前面的构造函数，以免重复处理负数和溢出的逻辑
// 	FixedPoint2(double d) :
// 		FixedPoint2(
// 			static_cast<std::int16_t>(std::trunc(d)),
// 			static_cast<std::int8_t>(std::round(d * 100) - std::trunc(d) * 100)
// 		)
// 	{
// 	}
//
// 	explicit operator double() const
// 	{
// 		return m_base + (static_cast<double>(m_decimal) / 100);
// 	}
// };
//
// // 它不需要访问类的内部细节，因此可以定义在类外
// std::ostream& operator<<(std::ostream& out, const FixedPoint2& fp)
// {
// 	out << static_cast<double>(fp);
// 	return out;
// }
//
// int main()
// {
// 	FixedPoint2 a{ 0.01 };
// 	std::cout << a << '\n';
// 	assert(static_cast<double>(a) == 0.01);
//
// 	FixedPoint2 b{ -0.01 };
// 	assert(static_cast<double>(b) == -0.01);
//
// 	FixedPoint2 c{ 1.9 }; // 确保能处理一位数的小数部分
// 	assert(static_cast<double>(c) == 1.9);
//
// 	FixedPoint2 d{ 5.01 }; // 实际存储为 5.0099999……因此需要四舍五入
// 	assert(static_cast<double>(d) == 5.01);
//
// 	FixedPoint2 e{ -5.01 }; // 实际存储为 -5.0099999……因此需要四舍五入
// 	assert(static_cast<double>(e) == -5.01);
//
// 	// 处理实参的小数部分四舍五入后为 100 的情况（需要把整数部分加 1）
// 	FixedPoint2 f { 106.9978 }; // 应当以整数部分 107、小数部分 0 存储
// 	assert(static_cast<double>(f) == 107.0);
//
// 	// 处理实参的小数部分四舍五入后为 -100 的情况（需要把整数部分减 1）
// 	FixedPoint2 g { -106.9978 }; // 应当以整数部分 -107、小数部分 0 存储
// 	assert(static_cast<double>(g) == -107.0);
//
// 	return 0;
// }

// 第5步
//
// 重载`operator==`、`operator>>`、`operator-`（一元）和`operator+`（二元）。
//
// 下面这个程序应当能够运行：

// [代码 11]
// #include <cassert>
// #include <iostream>
//
// int main()
// {
// 	assert(FixedPoint2{ 0.75 } == FixedPoint2{ 0.75 });    // 测试相等
// 	assert(!(FixedPoint2{ 0.75 } == FixedPoint2{ 0.76 })); // 测试不相等
//
// 	// 测试更多情况 —— 感谢读者 Sharjeel Safdar 提供这些测试用例
// 	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 });    // 两者都为正，小数部分不溢出
// 	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 });    // 两者都为正，小数部分溢出
// 	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }); // 两者都为负，小数部分不溢出
// 	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }); // 两者都为负，小数部分溢出
// 	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 });  // 第二个为负，小数部分不溢出
// 	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 });  // 第二个为负，小数部分可能溢出
// 	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 });   // 第一个为负，小数部分不溢出
// 	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 });   // 第一个为负，小数部分可能溢出
//
// 	FixedPoint2 a{ -0.48 };
// 	assert(static_cast<double>(a) == -0.48);
// 	assert(static_cast<double>(-a) == 0.48);
//
// 	std::cout << "Enter a number: "; // 输入 5.678
// 	std::cin >> a;
// 	std::cout << "You entered: " << a << '\n';
// 	assert(static_cast<double>(a) == 5.68);
//
// 	return 0;
// }


// 【答案 · 显示提示】
// 利用double转换把两个`FixedPoint2`相加：转换成double后相加，再转换回
// `FixedPoint2`。这样能够优雅地处理小数溢出。

// 【答案 · 显示提示】
// 对于`operator>>`，用你的double构造函数创建一个`FixedPoint2`类型的匿名对象，
// 再把它赋给你的`FixedPoint2`函数形参。

// 【答案 · 查看答案】

// [代码 12]
// #include <cassert>
// #include <cmath>
// #include <cstdint> // 用于固定宽度的整数
// #include <iostream>
//
// class FixedPoint2
// {
// private:
// 	std::int16_t m_base{}; // 这里是整数部分
// 	std::int8_t m_decimal{}; // 这里是小数部分
//
// public:
// 	FixedPoint2(std::int16_t base = 0, std::int8_t decimal = 0)
// 		: m_base{ base }, m_decimal{ decimal }
// 	{
// 		// 如果整数部分或小数部分（或两者）为负，就把这个数当作负数处理
// 		if (m_base < 0 || m_decimal < 0)
// 		{
// 			// 确保整数部分为负
// 			if (m_base > 0)
// 				m_base = -m_base;
// 			// 确保小数部分为负
// 			if (m_decimal > 0)
// 				m_decimal = -m_decimal;
// 		}
//
// 		// 如果小数部分越界（无论哪个方向），
// 		// 调整小数部分使其回到范围内，
// 		// 并相应调整整数部分，以补偿从小数部分移走的单位
// 		// 感谢读者 David Pinheiro 简化了这段代码
// 		m_base += m_decimal / 100;    // 整数除法
// 		m_decimal = m_decimal % 100;  // 整数取余
// 	}
//
// 	FixedPoint2(double d) :
// 		FixedPoint2(
// 			static_cast<std::int16_t>(std::trunc(d)),
// 			static_cast<std::int8_t>(std::round(d * 100) - std::trunc(d) * 100)
// 		)
// 	{
// 	}
//
// 	explicit operator double() const
// 	{
// 		return m_base + (static_cast<double>(m_decimal) / 100);
// 	}
//
// 	friend bool operator==(const FixedPoint2& fp1, const FixedPoint2& fp2)
// 	{
// 		return fp1.m_base == fp2.m_base && fp1.m_decimal == fp2.m_decimal;
// 	}
//
// 	FixedPoint2 operator-() const
// 	{
// 		// 转换为 double，取负，再转换回 FixedPoint2
// 		// 感谢读者 EmtyC 提供的这个版本
// 		return FixedPoint2{ -static_cast<double>(*this) };
// 	}
// };
//
// // 它不需要访问类的内部细节，因此可以定义在类外
// std::ostream& operator<<(std::ostream& out, const FixedPoint2& fp)
// {
// 	out << static_cast<double>(fp);
// 	return out;
// }
//
// std::istream& operator>>(std::istream& in, FixedPoint2& fp)
// {
// 	double d{};
// 	in >> d;
// 	fp = FixedPoint2{ d };
//
// 	return in;
// }
//
// FixedPoint2 operator+(const FixedPoint2& fp1, const FixedPoint2& fp2)
// {
// 	return FixedPoint2{ static_cast<double>(fp1) + static_cast<double>(fp2) };
// }
//
// int main()
// {
// 	assert(FixedPoint2{ 0.75 } == FixedPoint2{ 0.75 });    // 测试相等
// 	assert(!(FixedPoint2{ 0.75 } == FixedPoint2{ 0.76 })); // 测试不相等
//
// 	// 测试更多情况 —— 感谢读者 Sharjeel Safdar 提供这些测试用例
// 	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 });    // 两者都为正，小数部分不溢出
// 	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 });    // 两者都为正，小数部分溢出
// 	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }); // 两者都为负，小数部分不溢出
// 	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }); // 两者都为负，小数部分溢出
// 	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 });  // 第二个为负，小数部分不溢出
// 	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 });  // 第二个为负，小数部分可能溢出
// 	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 });   // 第一个为负，小数部分不溢出
// 	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 });   // 第一个为负，小数部分可能溢出
//
// 	FixedPoint2 a{ -0.48 };
// 	assert(static_cast<double>(a) == -0.48);
// 	assert(static_cast<double>(-a) == 0.48);
//
// 	std::cout << "Enter a number: "; // 输入 5.678
// 	std::cin >> a;
// 	std::cout << "You entered: " << a << '\n';
// 	assert(static_cast<double>(a) == 5.68);
//
// 	return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <cstdint> // 用于固定宽度的整数

class Average
{
private:
	std::int32_t m_total{ 0 }; // 目前见过的所有数字之和
	int m_numbers{ 0 }; // 目前见过的数字个数

public:
	Average()
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const Average& average)
	{
        // 处理还没有见过任何数字的情况
		if (average.m_numbers == 0)
		{
			out << 0;
			return out;
		}

		// 平均值等于已见过的数字之和除以已见过的数字个数
		// 注意这里要做浮点除法，而不是整数除法
		out << static_cast<double>(average.m_total) / average.m_numbers;

		return out;
	}

	// 由于 operator+= 会修改左操作数，我们把它实现为成员函数
	Average& operator+=(std::int32_t num)
	{
		// 用新数字累加总和
		m_total += num;
		// 并把计数加 1
		++m_numbers;

		// 返回 *this，以便有人想把多个 += 连起来写
		return *this;
	}
};

int main()
{
	Average avg{};
	std::cout << avg << '\n';

	avg += 4;
	std::cout << avg << '\n';

	avg += 8;
	std::cout << avg << '\n';

	avg += 24;
	std::cout << avg << '\n';

	avg += -10;
	std::cout << avg << '\n';

	(avg += 6) += 10; // 两次调用链式相连
	std::cout << avg << '\n';

	Average copy{ avg };
	std::cout << copy << '\n';

	return 0;
}
