// ==========================================================================
// 25.11 第25章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十五章 虚函数
// 原文: https://www.studycpp.cn/basic/chapter25/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "25.11-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 章节摘要
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 至此，我们对 C++ 继承和虚函数的探索告一段落。继续前进时，C++ 还有许多其他领
// 域等待我们探索。
//

// ―――― 章节摘要 ――――

// C++ 允许您创建指向派生对象的基类指针或引用。当我们想编写一个可以处理任意派
// 生类对象的函数或数组时，这非常有用。
//
// 如果没有虚函数，指向派生对象的基类指针和引用只能访问基类版本的成员变量和函
// 数。
//
// 虚函数是一种特殊函数，它会解析为基类和派生类层次中最底层的派生版本（称为重
// 写）。要被视为重写，派生类函数必须具有与基类虚函数相同的签名和返回类型。一
// 个例外是：如果基类函数返回指向基类的指针或引用，则允许重写函数返回指向派生
// 类的指针或引用。
//
// 一个旨在作为重写的函数应该使用override说明符来确保它实际上是一个重写。
//
// final说明符可用于防止重写函数或类被继承。
//
// 如果你打算使用继承，应该将析构函数设置为 virtual。这样通过基类指针删除对象
// 时，才会调用正确的析构函数。
//
// 您可以使用作用域解析运算符直接指定所需函数的类版本，从而绕过虚函数解析，例
// 如 Base::getName()。
//
// 静态绑定发生在编译器遇到直接函数调用时。编译器或链接器可以直接解析这些函数
// 调用。当使用函数指针时，会发生动态绑定。在这些情况下，直到运行时才能解析将
// 调用哪个函数。虚函数使用动态绑定和虚函数表来确定要调用哪个版本的函数。
//
// 使用虚函数是有代价的：调用虚函数需要更长的时间，虚函数表的必要性使每个包含
// 虚函数的对象的大小增加了一个指针。
//
// 通过在虚函数原型末尾添加 “=0”，可以使虚函数成为纯虚函数（抽象函数）。包含纯
// 虚函数的类称为抽象类，不能被实例化。继承纯虚函数的类必须为它们提供具体定义，
// 否则也会被视为抽象类。纯虚函数可以有函数体，但它们仍然被视为抽象函数。
//
// 接口类是不包含成员变量、且所有函数都是纯虚函数的类。接口类通常以大写字母 I
// 开头命名。
//
// virtual 基类是一种只会被包含一次的基类，无论它在继承体系中被继承了多少次。
// 这常用于存在菱形继承的情况。
//
// 当将派生类对象赋值给基类对象时，基类对象只会接收派生对象中基类部分的副本。
// 这称为对象切片。
//
// dynamic_cast可用于将指向基类对象的指针转换为指向派生类对象的指针。这被称为
// 向下转换。转换失败将返回空指针。
//
// 为继承类重载 operator« 的最简单方法，是为基类编写 operator«，然后调用虚成员
// 函数进行打印。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 下面每个程序都存在某种缺陷。请逐个检查（靠观察，不要编译），判断程序有什么
// 问题。每个程序的输出都应当是「Derived」。
//
// 1a)

// [代码 1]
// #include <iostream>
//
// class Base
// {
// protected:
// 	int m_value;
//
// public:
// 	Base(int value)
// 		: m_value{ value }
// 	{
// 	}
//
// 	const char* getName() const { return "Base"; }
// };
//
// class Derived : public Base
// {
// public:
// 	Derived(int value)
// 		: Base{ value }
// 	{
// 	}
//
// 	const char* getName() const { return "Derived"; }
// };
//
// int main()
// {
// 	Derived d{ 5 };
// 	Base& b{ d };
// 	std::cout << b.getName() << '\n';
//
// 	return 0;
// }


// 【答案 · 查看答案】
// `Base::getName()`没有被声明为虚函数，因此`b.getName()`不会解析到
// `Derived::getName()`。
//
// 1b)

// [代码 2]
// #include <iostream>
//
// class Base
// {
// protected:
// 	int m_value;
//
// public:
// 	Base(int value)
// 		: m_value{ value }
// 	{
// 	}
//
// 	virtual const char* getName() { return "Base"; }
// };
//
// class Derived : public Base
// {
// public:
// 	Derived(int value)
// 		: Base{ value }
// 	{
// 	}
//
// 	virtual const char* getName() const { return "Derived"; }
// };
//
// int main()
// {
// 	Derived d{ 5 };
// 	Base& b{ d };
// 	std::cout << b.getName() << '\n';
//
// 	return 0;
// }


// 【答案 · 查看答案】
// `Base::getName()`不是const的，而`Derived::getName()`是const的，因此
// `Derived::getName()`不被视为覆盖版本。
//
// 1c)

// [代码 3]
// #include <iostream>
//
// class Base
// {
// protected:
// 	int m_value;
//
// public:
// 	Base(int value)
// 		: m_value{ value }
// 	{
// 	}
//
// 	virtual const char* getName() { return "Base"; }
// };
//
// class Derived : public Base
// {
// public:
// 	Derived(int value)
// 		: Base{ value }
// 	{
// 	}
//
// 	const char* getName() override { return "Derived"; }
// };
//
// int main()
// {
// 	Derived d{ 5 };
// 	Base b{ d };
// 	std::cout << b.getName() << '\n';
//
// 	return 0;
// }


// 【答案 · 查看答案】
// d被按值赋给了b，导致d被切割（object slicing）。
//
// 1d)

// [代码 4]
// #include <iostream>
//
// class Base final
// {
// protected:
// 	int m_value;
//
// public:
// 	Base(int value)
// 		: m_value{ value }
// 	{
// 	}
//
// 	virtual const char* getName() { return "Base"; }
// };
//
// class Derived : public Base
// {
// public:
// 	Derived(int value)
// 		: Base{ value }
// 	{
// 	}
//
// 	const char* getName() override { return "Derived"; }
// };
//
// int main()
// {
// 	Derived d{ 5 };
// 	Base& b{ d };
// 	std::cout << b.getName() << '\n';
//
// 	return 0;
// }


// 【答案 · 查看答案】
// Base被声明为final，因此不能从它派生出Derived。这会导致编译错误。
//
// 1e)

// [代码 5]
// #include <iostream>
//
// class Base
// {
// protected:
// 	int m_value;
//
// public:
// 	Base(int value)
// 		: m_value{ value }
// 	{
// 	}
//
// 	virtual const char* getName() { return "Base"; }
// };
//
// class Derived : public Base
// {
// public:
// 	Derived(int value)
// 		: Base{ value }
// 	{
// 	}
//
// 	virtual const char* getName() = 0;
// };
//
// const char* Derived::getName()
// {
// 	return "Derived";
// }
//
// int main()
// {
// 	Derived d{ 5 };
// 	Base& b{ d };
// 	std::cout << b.getName() << '\n';
//
// 	return 0;
// }


// 【答案 · 查看答案】
// `Derived::getName()`是纯虚函数（尽管带有函数体），因此Derived是抽象类，不能
// 被实例化。
//
// 1f)

// [代码 6]
// #include <iostream>
//
// class Base
// {
// protected:
// 	int m_value;
//
// public:
// 	Base(int value)
// 		: m_value{ value }
// 	{
// 	}
//
// 	virtual const char* getName() { return "Base"; }
// };
//
// class Derived : public Base
// {
// public:
// 	Derived(int value)
// 		: Base{ value }
// 	{
// 	}
//
// 	virtual const char* getName() { return "Derived"; }
// };
//
// int main()
// {
// 	auto* d{ new Derived(5) };
// 	Base* b{ d };
// 	std::cout << b->getName() << '\n';
// 	delete b;
//
// 	return 0;
// }


// 【答案 · 查看答案】
// 这个程序实际上输出了正确的结果，但存在另一个问题。我们删除的是Base指针b，但
// 从未给Base类添加虚析构函数。因此程序只删除了Derived对象中的Base部分，
// Derived部分就成了内存泄漏。

// ▼ 问题 2
// 2a) 创建一个名为Shape的抽象类。该类应当有三个函数：一个纯虚的print函数，接
// 受并返回`std::ostream&`；一个重载的`operator<<`；以及一个空的虚析构函数。

// 【答案 · 查看答案】

// [代码 7]
// class Shape
// {
// public:
// 	virtual std::ostream& print(std::ostream& out) const = 0;
//
// 	friend std::ostream& operator<<(std::ostream& out, const Shape& p)
// 	{
// 		return p.print(out);
// 	}
// 	virtual ~Shape() = default;
// };

// 2b) 从Shape派生出两个类：Triangle和Circle。Triangle应当有3个Point成员。
// Circle应当有一个圆心Point成员和一个整数半径成员。重写`print()`函数，使下面
// 这个程序能够运行：

// [代码 8]
// int main()
// {
//     Circle c{ Point{ 1, 2 }, 7 };
//     std::cout << c << '\n';
//
//     Triangle t{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }};
//     std::cout << t << '\n';
//
//     return 0;
// }

// 它应当打印：

// [文本/输出]
// Circle(Point(1, 2), radius 7)
// Triangle(Point(1, 2), Point(3, 4), Point(5, 6))

// 下面是一个可以使用的Point类：

// [代码 9]
// class Point
// {
// private:
// 	int m_x{};
// 	int m_y{};
//
// public:
// 	Point(int x, int y)
// 		: m_x{ x }, m_y{ y }
// 	{
//
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const Point& p)
// 	{
// 		return out << "Point(" << p.m_x << ", " << p.m_y << ')';
// 	}
// };


// 【答案 · 查看答案】

// [代码 10]
// #include <iostream>
//
// class Point
// {
// private:
// 	int m_x{};
// 	int m_y{};
//
// public:
// 	Point(int x, int y)
// 		: m_x{ x }, m_y{ y }
// 	{
//
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const Point& p)
// 	{
// 		return out << "Point(" << p.m_x << ", " << p.m_y << ')';
// 	}
// };
//
// class Shape
// {
// public:
// 	virtual std::ostream& print(std::ostream& out) const = 0;
//
// 	friend std::ostream& operator<<(std::ostream& out, const Shape& p)
// 	{
// 		return p.print(out);
// 	}
// 	virtual ~Shape() = default;
// };
//
// class Triangle : public Shape
// {
// private:
// 	Point m_p1;
// 	Point m_p2;
// 	Point m_p3;
//
// public:
// 	Triangle(const Point& p1, const Point& p2, const Point& p3)
// 		: m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 }
// 	{
// 	}
//
// 	std::ostream& print(std::ostream& out) const override
// 	{
// 		return out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ')';
// 	}
// };
//
// class Circle : public Shape
// {
// private:
// 	Point m_center;
// 	int m_radius;
//
// public:
// 	Circle(const Point& center, int radius)
// 		: m_center{ center }, m_radius{ radius }
// 	{
// 	}
//
// 	std::ostream& print(std::ostream& out) const override
// 	{
// 		return out << "Circle(" << m_center << ", radius " << m_radius << ')';
// 	}
// };
//
// int main()
// {
// 	Circle c{ Point{ 1, 2 }, 7 };
// 	std::cout << c << '\n';
//
// 	Triangle t{ Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 } };
// 	std::cout << t << '\n';
//
// 	return 0;
// }

// 2c) 给定上面的各个类（Point、Shape、Circle和Triangle），补全下面这个程序：

// [代码 11]
// #include <vector>
// #include <iostream>
//
// int main()
// {
// 	std::vector<Shape*> v{
// 	  new Circle{Point{ 1, 2 }, 7},
// 	  new Triangle{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }},
// 	  new Circle{Point{ 7, 8 }, 3}
// 	};
//
// 	// 在这里把 vector v 中的每个形状各打印一行
//
// 	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // 编写这个函数
//
// 	// 在这里删除 vector 中的每个元素
//
// 	return 0;
// }

// 程序应当打印如下内容：

// [文本/输出]
// Circle(Point(1, 2), radius 7)
// Triangle(Point(1, 2), Point(3, 4), Point(5, 6))
// Circle(Point(7, 8), radius 3)
// The largest radius is: 7

// 提示：需要给Circle添加一个`getRadius()`函数，并把`Shape*`向下转型为
// `Circle*`才能访问它。

// 【答案 · 查看答案】

// [代码 12]
// #include <vector>
// #include <iostream>
// #include <algorithm> // 用于 std::max
//
// class Point
// {
// private:
// 	int m_x{};
// 	int m_y{};
//
// public:
// 	Point(int x, int y)
// 		: m_x{ x }, m_y{ y }
// 	{
//
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const Point& p)
// 	{
// 		return out << "Point(" << p.m_x << ", " << p.m_y << ')';
// 	}
// };
//
// class Shape
// {
// public:
// 	virtual std::ostream& print(std::ostream& out) const = 0;
//
// 	friend std::ostream& operator<<(std::ostream& out, const Shape& p)
// 	{
// 		return p.print(out);
// 	}
// 	virtual ~Shape() = default;
// };
//
// class Triangle : public Shape
// {
// private:
// 	Point m_p1;
// 	Point m_p2;
// 	Point m_p3;
//
// public:
// 	Triangle(const Point& p1, const Point& p2, const Point& p3)
// 		: m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 }
// 	{
// 	}
//
// 	std::ostream& print(std::ostream& out) const override
// 	{
// 		return out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ')';
// 	}
// };
//
// class Circle : public Shape
// {
// private:
// 	Point m_center;
// 	int m_radius{};
//
// public:
// 	Circle(const Point& center, int radius)
// 		: m_center{ center }, m_radius{ radius }
// 	{
// 	}
//
// 	std::ostream& print(std::ostream& out) const override
// 	{
// 		out << "Circle(" << m_center << ", radius " << m_radius << ')';
// 		return out;
// 	}
//
// 	int getRadius() const { return m_radius; }
// };
//
// // 感谢读者 Olivier 提供这个更新后的解法
// // 假设半径都大于等于 0
// int getLargestRadius(const std::vector<Shape*>& v)
// {
// 	int largestRadius{ 0 };
//
// 	// 遍历 vector 中的所有形状
// 	for (const auto* element : v)
// 	{
// 		// // 通过检查结果是否为空指针来确认动态转换成功
// 		if (auto* c { dynamic_cast<const Circle*>(element) })
// 		{
// 			largestRadius = std::max(largestRadius, c->getRadius());
// 		}
// 	}
//
// 	return largestRadius;
// }
// int main()
// {
// 	std::vector<Shape*> v{
// 		  new Circle{Point{ 1, 2 }, 7},
// 		  new Triangle{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }},
// 		  new Circle{Point{ 7, 8 }, 3}
// 	};
//
// 	for (const auto* element : v) // 元素将是 Shape*
// 		std::cout << *element << '\n';
//
// 	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n';
//
// 	for (const auto* element : v)
// 		delete element;
//
// 	return 0;
// }

// 2d) 附加题：把上一题的解答改成使用`std::vector<std::unique_ptr<Shape>>`。记
// 住`std::unique_ptr`是不可拷贝的。
//
// （感谢读者surrealcereal提出的这个想法。）

// 【答案 · 显示提示】
// 不能用`std::initializer_list`来初始化这个vector，因为那要求元素可拷贝。

// 【答案 · 显示提示】
// `std::unique_ptr::get()`返回指向所管理元素的指针。

// 【答案 · 查看答案】

// [代码 13]
// #include <vector>
// #include <iostream>
// #include <algorithm> // 用于 std::max
// #include <memory>
//
// class Point
// {
// private:
// 	int m_x{};
// 	int m_y{};
//
// public:
// 	Point(int x, int y)
// 		: m_x{ x }, m_y{ y }
// 	{
//
// 	}
//
// 	friend std::ostream& operator<<(std::ostream& out, const Point& p)
// 	{
// 		return out << "Point(" << p.m_x << ", " << p.m_y << ')';
// 	}
// };
//
// class Shape
// {
// public:
// 	virtual std::ostream& print(std::ostream& out) const = 0;
//
// 	friend std::ostream& operator<<(std::ostream& out, const Shape& p)
// 	{
// 		return p.print(out);
// 	}
// 	virtual ~Shape() = default;
// };
//
// class Triangle : public Shape
// {
// private:
// 	Point m_p1;
// 	Point m_p2;
// 	Point m_p3;
//
// public:
// 	Triangle(const Point& p1, const Point& p2, const Point& p3)
// 		: m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 }
// 	{
// 	}
//
// 	std::ostream& print(std::ostream& out) const override
// 	{
// 		return out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ')';
// 	}
// };
//
// class Circle : public Shape
// {
// private:
// 	Point m_center;
// 	int m_radius{};
//
// public:
// 	Circle(const Point& center, int radius)
// 		: m_center{ center }, m_radius{ radius }
// 	{
// 	}
//
// 	std::ostream& print(std::ostream& out) const override
// 	{
// 		out << "Circle(" << m_center << ", radius " << m_radius << ')';
// 		return out;
// 	}
//
// 	int getRadius() const { return m_radius; }
// };
//
// int getLargestRadius(const std::vector<std::unique_ptr<Shape>>& v)
// {
// 	int largestRadius{ 0 };
//
// 	// 遍历 vector 中的所有形状
// 	for (const auto& element : v)
// 	{
// 		// // 通过检查结果是否为空指针来确认动态转换成功
// 		if (auto *c { dynamic_cast<const Circle*>(element.get()) })
// 		{
// 			largestRadius = std::max(largestRadius, c->getRadius());
// 		}
// 	}
//
// 	return largestRadius;
// }
// int main()
// {
// 	std::vector<std::unique_ptr<Shape>> v;
// 	v.reserve(3);
// 	v.push_back(std::make_unique<Circle>(Point{1, 2}, 7));
// 	v.push_back(std::make_unique<Triangle>(Point{1, 2}, Point{3, 4}, Point{5, 6}));
// 	v.push_back(std::make_unique<Circle>(Point{7, 8}, 3));
//
// 	for (const auto& element : v) std::cout << *element << '\n';
//
// 	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n';
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Base
{
protected:
	int m_value;

public:
	Base(int value)
		: m_value{ value }
	{
	}

	const char* getName() const { return "Base"; }
};

class Derived : public Base
{
public:
	Derived(int value)
		: Base{ value }
	{
	}

	const char* getName() const { return "Derived"; }
};

int main()
{
	Derived d{ 5 };
	Base& b{ d };
	std::cout << b.getName() << '\n';

	return 0;
}
