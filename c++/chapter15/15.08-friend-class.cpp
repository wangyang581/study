// ==========================================================================
// 15.8 友元类和友元成员函数
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十五章 class第二部分
// 原文: https://www.studycpp.cn/basic/chapter15/friend-class/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "15.08-friend-class.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 友元类
//   · 友元成员函数
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 友元类 ――――

// 友元类是指可以访问另一个类的私有成员和受保护成员的类。
//
// 下面是一个示例：

// [代码 1]
// #include <iostream>
//
// class Storage
// {
// private:
//     int m_nValue {};
//     double m_dValue {};
// public:
//     Storage(int nValue, double dValue)
//        : m_nValue { nValue }, m_dValue { dValue }
//     { }
//
//     // 设置 Display 是 Storage 的友元类
//     friend class Display;
// };
//
// class Display
// {
// private:
//     bool m_displayIntFirst {};
//
// public:
//     Display(bool displayIntFirst)
//          : m_displayIntFirst { displayIntFirst }
//     {
//     }
//
//     // 因为 Display 是 Storage 的友元, Display 中可以访问 Storage 的所有成员
//     void displayStorage(const Storage& storage)
//     {
//         if (m_displayIntFirst)
//             std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
//         else // 首先显示 double 值
//             std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
//     }
//
//     void setDisplayIntFirst(bool b)
//     {
//          m_displayIntFirst = b;
//     }
// };
//
// int main()
// {
//     Storage storage { 5, 6.7 };
//     Display display { false };
//
//     display.displayStorage(storage);
//
//     display.setDisplayIntFirst(true);
//     display.displayStorage(storage);
//
//     return 0;
// }

// 由于Display类是Storage的友元，因此Display可以访问任何Storage对象的私有成员。
//
// 该程序产生以下结果：

// [文本/输出]
// 6.7 5
// 5 6.7

// 关于友元类，还有一些补充说明。
//
// 首先，尽管Display是Storage的友元，但Display不能访问Storage对象的this指针（
// 因为this实际上是函数参数）。
//
// 第二，友元关系不是对等的。Display是Storage的友元，并不意味着Storage也是
// Display的友元。如果希望两个类互为友元，则两者都必须将对方声明为友元。
//
// 友元关系也不可传递。如果A类是B的友元，而B是C的友元，这并不意味着A也是C的友
// 元。
//
// 友元类声明可以充当前向声明。这意味着不需要在将某个类声明为友元之前先前向声
// 明它。在上面的示例中，「friend class Display;」同时充当Display的前向声明和
// 友元声明。
//
// 对于高级读者
//
// 友元也是不可继承的。如果B是A的友元，则从B派生的类不是A的友元。
//

// ―――― 友元成员函数 ――――

// 可以只将单个成员函数设置为友元，而不是将整个类设置为友元。这类似于让非成员
// 函数成为友元，只是这里改为使用成员函数。
//
// 然而，实际操作可能比预期更复杂一些。让我们改造前面的示例，使
// Display::displayStorage成为友元成员函数。您可能会尝试这样写：

// [代码 2]
// #include <iostream>
//
// class Display; // 前向声明 Display
//
// class Storage
// {
// private:
// 	int m_nValue {};
// 	double m_dValue {};
// public:
// 	Storage(int nValue, double dValue)
// 		: m_nValue { nValue }, m_dValue { dValue }
// 	{
// 	}
//
// 	// 让 Display::displayStorage 成员函数成为 Storage 的友元函数
// 	friend void Display::displayStorage(const Storage& storage); // 编译失败: Storage 这里看不到 Display 类的定义
// };
//
// class Display
// {
// private:
// 	bool m_displayIntFirst {};
//
// public:
// 	Display(bool displayIntFirst)
// 		: m_displayIntFirst { displayIntFirst }
// 	{
// 	}
//
// 	void displayStorage(const Storage& storage)
// 	{
// 		if (m_displayIntFirst)
// 			std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
// 		else
// 			std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
// 	}
// };
//
// int main()
// {
//     Storage storage { 5, 6.7 };
//     Display display { false };
//     display.displayStorage(storage);
//
//     return 0;
// }

// 然而，这行不通。为了让单个成员函数成为友元，编译器必须看到该友元成员函数所
// 属类的完整定义（而不仅仅是前向声明）。由于类Storage此时还没有看到类Display
// 的完整定义，因此编译器会在尝试将该成员函数设为友元时报错。
//
// 幸运的是，通过将类Display的定义移动到类Storage的定义之前（在同一文件中，或
// 者将Display的定义移动到头文件中，并在定义Storage之前包含它），可以很容易地
// 解决这个问题。

// [代码 3]
// #include <iostream>
//
// class Display
// {
// private:
// 	bool m_displayIntFirst {};
//
// public:
// 	Display(bool displayIntFirst)
// 		: m_displayIntFirst { displayIntFirst }
// 	{
// 	}
//
// 	void displayStorage(const Storage& storage) // 编译失败: 编译器不知道 Storage 是啥东西
// 	{
// 		if (m_displayIntFirst)
// 			std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
// 		else // display double first
// 			std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
// 	}
// };
//
// class Storage
// {
// private:
// 	int m_nValue {};
// 	double m_dValue {};
// public:
// 	Storage(int nValue, double dValue)
// 		: m_nValue { nValue }, m_dValue { dValue }
// 	{
// 	}
//
// 	// 让 Display::displayStorage 成员函数成为 Storage 的友元函数
// 	friend void Display::displayStorage(const Storage& storage); // okay now
// };
//
// int main()
// {
//     Storage storage { 5, 6.7 };
//     Display display { false };
//     display.displayStorage(storage);
//
//     return 0;
// }

// 然而，现在又出现了另一个问题。因为成员函数Display::displayStorage() 使用
// Storage作为引用参数，而我们刚刚又把Storage的定义移到了Display的定义之后，编
// 译器会抱怨它不知道Storage是什么。这个问题不能单纯通过重新排列定义顺序来修复，
// 因为那会撤销前面的修复。
//
// 幸运的是，通过几个简单步骤也可以修复这个问题。首先，可以添加类Storage的前向
// 声明，以便编译器在看到类的完整定义之前就能引用Storage。
//
// 其次，可以将 Display::displayStorage() 的定义移出Display类，并放到Storage类
// 的完整定义之后。
//
// 下面是修改后的样子：

// [代码 4]
// #include <iostream>
//
// class Storage; // 前向声明 Storage
//
// class Display
// {
// private:
// 	bool m_displayIntFirst {};
//
// public:
// 	Display(bool displayIntFirst)
// 		: m_displayIntFirst { displayIntFirst }
// 	{
// 	}
//
// 	void displayStorage(const Storage& storage); // 这一行需要看到 Storage 的前向声明
// };
//
// class Storage // Storage 的完整定义
// {
// private:
// 	int m_nValue {};
// 	double m_dValue {};
// public:
// 	Storage(int nValue, double dValue)
// 		: m_nValue { nValue }, m_dValue { dValue }
// 	{
// 	}
//
// 	// 让 Display::displayStorage 成员函数成为 Storage 的友元函数
// 	// 需要看到 Display 类的完整定义
// 	friend void Display::displayStorage(const Storage& storage);
// };
//
// // 现在来定义 Display::displayStorage
// // 需要看到 Storage 的完整定义 (因为要访问 Storage 的成员)
// void Display::displayStorage(const Storage& storage)
// {
// 	if (m_displayIntFirst)
// 		std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
// 	else
// 		std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
// }
//
// int main()
// {
//     Storage storage { 5, 6.7 };
//     Display display { false };
//     display.displayStorage(storage);
//
//     return 0;
// }

// 现在一切都能正确编译：类Storage的前向声明足以满足Display类中
// Display::displayStorage()的声明。Display的完整定义满足了将
// Display::displayStorage()声明为Storage友元的要求。类Storage的完整定义则足以
// 满足成员函数Display::displayStorage() 的定义。
//
// 如果这有点令人困惑，请参阅上面程序中的注释。关键点是：类前向声明足以支持对
// 类的引用；但要访问类的成员，编译器必须看到完整的类定义。
//
// 这看起来确实有些麻烦。幸运的是，这只是因为我们试图在单个文件中完成所有事情。
// 更好的解决方案是将每个类定义放在单独的头文件中，并将成员函数定义放在相应的.cpp
// 文件中。这样，所有类定义都可以在.cpp文件中可用，也不需要重新排列类或函数！
//

// ―――― 习题 ――――


// ▼ 问题 1
// 在几何学中，点表示空间中的一个位置。我们可以用坐标x、y、z来定义三维空间中的
// 点。例如`Point { 2.0, 1.0, 0.0 }`表示坐标为x=2.0、y=1.0、z=0.0的点。
//
// 在物理学中，向量是一个既有大小（长度）又有方向的量（但没有位置）。我们可以
// 用x、y、z三个值来定义三维空间中的向量，它们表示向量沿x、y、z轴的方向（长度
// 可以由这些值推导出来）。例如`Vector { 2.0, 0.0, 0.0 }`表示一个仅沿x轴正方向
// 的向量，长度为2.0。
//
// 可以把一个`Vector`作用于一个`Point`，把`Point`移动到新的位置。做法是把向量
// 的方向加到点的位置上，得到新的位置。例如`Point { 2.0, 1.0, 0.0 }` + `Vector
// { 2.0, 0.0, 0.0 }`会得到`Point { 4.0, 1.0, 0.0 }`。
//
// 这类点和向量常用于计算机图形学（点表示形状的顶点，向量表示形状的移动）。
//
// 给定下面这个程序：

// [代码 5]
// #include <iostream>
//
// class Vector3d
// {
// private:
// 	double m_x{};
// 	double m_y{};
// 	double m_z{};
//
// public:
// 	Vector3d(double x, double y, double z)
// 		: m_x{x}, m_y{y}, m_z{z}
// 	{
// 	}
//
// 	void print() const
// 	{
// 		std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
// 	}
// };
//
// class Point3d
// {
// private:
// 	double m_x{};
// 	double m_y{};
// 	double m_z{};
//
// public:
// 	Point3d(double x, double y, double z)
// 		: m_x{x}, m_y{y}, m_z{z}
// 	{ }
//
// 	void print() const
// 	{
// 		std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
// 	}
//
// 	void moveByVector(const Vector3d& v)
// 	{
// 		// 把这个函数实现为 Vector3d 类的友元
// 	}
// };
//
// int main()
// {
// 	Point3d p { 1.0, 2.0, 3.0 };
// 	Vector3d v { 2.0, 2.0, -3.0 };
//
// 	p.print();
// 	p.moveByVector(v);
// 	p.print();
//
// 	return 0;
// }


// ▼ 第1步
// 把`Point3d`设为`Vector3d`的友元类，并实现函数`Point3d::moveByVector()`。

// 【答案 · 查看答案】

// [代码 6]
// #include <iostream>
//
// class Vector3d
// {
// private:
// 	double m_x{};
// 	double m_y{};
// 	double m_z{};
//
// public:
// 	Vector3d(double x, double y, double z)
// 		: m_x{x}, m_y{y}, m_z{z}
// 	{
//
// 	}
//
// 	void print() const
// 	{
// 		std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
// 	}
//
// 	friend class Point3d; // Point3d 现在是 Vector3d 类的友元
// };
//
// class Point3d
// {
// private:
// 	double m_x{};
// 	double m_y{};
// 	double m_z{};
//
// public:
// 	Point3d(double x, double y, double z)
// 		: m_x{x}, m_y{y}, m_z{z}
// 	{
//
// 	}
//
// 	void print() const
// 	{
// 		std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
// 	}
//
// 	void moveByVector(const Vector3d& v)
// 	{
// 		m_x += v.m_x;
// 		m_y += v.m_y;
// 		m_z += v.m_z;
// 	}
// };
//
// int main()
// {
// 	Point3d p { 1.0, 2.0, 3.0 };
// 	Vector3d v { 2.0, 2.0, -3.0 };
//
// 	p.print();
// 	p.moveByVector(v);
// 	p.print();
//
// 	return 0;
// }


// ▼ 第2步
// 不把`Point3d`整个类设为`Vector3d`的友元，而是只把成员函数
// `Point3d::moveByVector`设为`Vector3d`类的友元。

// 【答案 · 查看答案】

// [代码 7]
// #include <iostream>
//
// class Vector3d; // 首先，告诉编译器存在一个名为 Vector3d 的类
//
// class Point3d
// {
// private:
// 	double m_x{};
// 	double m_y{};
// 	double m_z{};
//
// public:
// 	Point3d(double x, double y, double z)
// 		: m_x{x}, m_y{y}, m_z{z}
// 	{
//
// 	}
//
// 	void print() const
// 	{
// 		std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
// 	}
//
// 	void moveByVector(const Vector3d& v); // 这样这里就能使用 Vector3d 了
//        // 注意：这里不能定义这个函数，因为 Vector3d 还没有被定义（只是前向声明）
// };
//
// class Vector3d
// {
// private:
// 	double m_x{};
// 	double m_y{};
// 	double m_z{};
//
// public:
// 	Vector3d(double x, double y, double z)
// 		: m_x{x}, m_y{y}, m_z{z}
// 	{
//
// 	}
//
// 	void print() const
// 	{
// 		std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
// 	}
//
// 	friend void Point3d::moveByVector(const Vector3d& v); // Point3d::moveByVector() 现在成为 Vector3d 类的友元
// };
//
// // 现在 Vector3d 已经定义好了，我们可以定义函数 Point3d::moveByVector()
// void Point3d::moveByVector(const Vector3d& v)
// {
// 	m_x += v.m_x;
// 	m_y += v.m_y;
// 	m_z += v.m_z;
// }
//
// int main()
// {
// 	Point3d p { 1.0, 2.0, 3.0 };
// 	Vector3d v { 2.0, 2.0, -3.0 };
//
// 	p.print();
// 	p.moveByVector(v);
// 	p.print();
//
// 	return 0;
// }


// ▼ 第3步
// 用5个独立的文件重新实现上一步的解法：Point3d.h、Point3d.cpp、Vector3d.h、
// Vector3d.cpp 和 main.cpp。
//
// 感谢读者Shiva提出的建议和提供的解法。

// 【答案 · 查看答案】
// Point3d.h：

// [代码 8]
// // 定义 Point3d 类的头文件
//
// #ifndef POINT3D_H
// #define POINT3D_H
//
// class Vector3d; // 函数 moveByVector() 用到的类 Vector3d 的前向声明
//
// class Point3d
// {
//     private:
//         double m_x{};
//         double m_y{};
//         double m_z{};
//
//     public:
//         Point3d(double x, double y, double z);
//
//         void print() const;
//         void moveByVector(const Vector3d& v); // 这一行需要上面的前向声明
// };
//
// #endif

// Point3d.cpp：

// [代码 9]
// // Point3d 类的成员函数在此定义
//
// #include "Point3d.h" // 这里定义了 Point3d 类
// #include "Vector3d.h" // 函数 moveByVector() 的形参需要它
//
// #include <iostream>
//
// Point3d::Point3d(double x, double y, double z)
//   : m_x{x}, m_y{y}, m_z{z}
// {}
//
// void Point3d::moveByVector(const Vector3d& v)
// {
//     // 把向量的各个分量加到点对应的坐标上
//     m_x += v.m_x;
//     m_y += v.m_y;
//     m_z += v.m_z;
// }
//
// void Point3d::print() const
// {
//     std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
// }

// Vector3d.h：

// [代码 10]
// // 定义 Vector3d 类的头文件
//
// #ifndef VECTOR3D_H
// #define VECTOR3D_H
//
// #include "Point3d.h" // 用于把 Point3d::moveByVector() 声明为友元
//
// class Vector3d
// {
//     private:
//         double m_x{};
//         double m_y{};
//         double m_z{};
//
//     public:
//         Vector3d(double x, double y, double z);
//
//         void print() const;
//         friend void Point3d::moveByVector(const Vector3d& v);
// };
//
// #endif

// Vector3d.cpp：

// [代码 11]
// // Vector3d 类的成员函数在此定义
//
// #include "Vector3d.h" // Vector3d 类在本文件中定义
//
// #include <iostream>
//
// Vector3d::Vector3d(double x, double y, double z)
//   : m_x{x}, m_y{y}, m_z{z}
// {}
//
// void Vector3d::print() const
// {
//     std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n";
// }

// main.cpp：

// [代码 12]
// #include "Vector3d.h"
// #include "Point3d.h"
//
// int main()
// {
//     Point3d p { 1.0, 2.0, 3.0 };
//     Vector3d v { 2.0, 2.0, -3.0 };
//
//     p.print();
//     p.moveByVector(v);
//     p.print();
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Storage
{
private:
    int m_nValue {};
    double m_dValue {};
public:
    Storage(int nValue, double dValue)
       : m_nValue { nValue }, m_dValue { dValue }
    { }

    // 设置 Display 是 Storage 的友元类
    friend class Display;
};

class Display
{
private:
    bool m_displayIntFirst {};

public:
    Display(bool displayIntFirst)
         : m_displayIntFirst { displayIntFirst }
    {
    }

    // 因为 Display 是 Storage 的友元, Display 中可以访问 Storage 的所有成员
    void displayStorage(const Storage& storage)
    {
        if (m_displayIntFirst)
            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
        else // 首先显示 double 值
            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
    }

    void setDisplayIntFirst(bool b)
    {
         m_displayIntFirst = b;
    }
};

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };

    display.displayStorage(storage);

    display.setDisplayIntFirst(true);
    display.displayStorage(storage);

    return 0;
}
