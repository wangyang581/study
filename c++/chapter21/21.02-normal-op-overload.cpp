// ==========================================================================
// 21.2 使用普通函数重载运算符
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十一章 操作符重载
// 原文: https://www.studycpp.cn/basic/chapter21/normal-op-overload/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "21.02-normal-op-overload.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================

// ==========================================================================
// 教程正文
// ==========================================================================

// 在上一课中，我们将operator+重载为了友元函数：

// [代码 1]
// #include <iostream>
//
// class Cents
// {
// private:
//   int m_cents{};
//
// public:
//   Cents(int cents)
//     : m_cents{ cents }
//   {}
//
//   // Cents + Cents 实现为友元函数
//   friend Cents operator+(const Cents& c1, const Cents& c2);
//
//   int getCents() const { return m_cents; }
// };
//
// // 注: 这个函数不是成员函数
// Cents operator+(const Cents& c1, const Cents& c2)
// {
// 	// 可以直接访问m_cents，因为本函数是 Cents 的友元函数
// 	// 返回 int，触发Cents的构造函数
//   return { c1.m_cents + c2.m_cents };
// }
//
// int main()
// {
//   Cents cents1{ 6 };
//   Cents cents2{ 8 };
//   Cents centsSum{ cents1 + cents2 };
//   std::cout << "I have " << centsSum.getCents() << " cents.\n";
//
//   return 0;
// }

// 使用友元函数重载运算符很方便，因为它可以直接访问所操作类的内部成员。在上面
// 的示例中，我们的友元函数版本operator+直接访问了成员变量m_cents。
//
// 然而，如果不需要这种访问能力，也可以将重载运算符编写为普通函数。请注意，上
// 面的Cents类包含一个访问函数（getCents()），它允许我们在不直接访问私有成员的
// 情况下获取m_cents。因此，我们可以将重载运算符+编写为非友元函数：

// [代码 2]
// #include <iostream>
//
// class Cents
// {
// private:
//   int m_cents{};
//
// public:
//   Cents(int cents)
//     : m_cents{ cents }
//   {}
//
//   int getCents() const { return m_cents; }
// };
//
// // 注: 这个函数，不是成员函数，也不是友元函数
// Cents operator+(const Cents& c1, const Cents& c2)
// {
//   // 不再需要直接访问Cents的私有成员
//   return Cents{ c1.getCents() + c2.getCents() };
// }
//
// int main()
// {
//   Cents cents1{ 6 };
//   Cents cents2{ 8 };
//   Cents centsSum{ cents1 + cents2 };
//   std::cout << "I have " << centsSum.getCents() << " cents.\n";
//
//   return 0;
// }

// 由于普通函数和友元函数的工作方式几乎相同（只是对私有成员的访问权限不同），
// 因此通常不需要刻意区分它们。一个区别是，类中的友元函数声明也会充当函数原型。
// 对于普通函数版本，您必须自己提供函数原型。
//
// Cents.h：

// [代码 3]
// #ifndef CENTS_H
// #define CENTS_H
//
// class Cents
// {
// private:
//   int m_cents{};
//
// public:
//   Cents(int cents)
//     : m_cents{ cents }
//   {}
//
//   int getCents() const { return m_cents; }
// };
//
// // 需要显式声明 operator+ 的原型，这样其他使用该.h文件的地方可以看到这个函数
// Cents operator+(const Cents& c1, const Cents& c2);
//
// #endif

// Cents.cpp：

// [代码 4]
// #include "Cents.h"
//
// // 注: 这个函数，不是成员函数，也不是友元函数
// Cents operator+(const Cents& c1, const Cents& c2)
// {
//   // 不再需要直接访问Cents的私有成员
//   return { c1.getCents() + c2.getCents() };
// }

// main.cpp：

// [代码 5]
// #include "Cents.h"
// #include <iostream>
//
// int main()
// {
//   Cents cents1{ 6 };
//   Cents cents2{ 8 };
//   Cents centsSum{ cents1 + cents2 }; // 如果 Cents.h 中没有对应的函数原型, 这里无法通过编译
//   std::cout << "I have " << centsSum.getCents() << " cents.\n";
//
//   return 0;
// }

// 通常，如果可以使用现有成员函数来实现，就应该优先选择普通函数，而不是友元函
// 数（接触类内部的函数越少越好）。然而，不要仅仅为了把运算符重载为普通函数，
// 而额外添加访问函数！
//
// 最佳实践
//
// 如果可以在不添加额外函数的情况下实现，请优先将重载运算符写成普通函数，而不
// 是友元函数。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Cents
{
private:
  int m_cents{};

public:
  Cents(int cents)
    : m_cents{ cents }
  {}

  // Cents + Cents 实现为友元函数
  friend Cents operator+(const Cents& c1, const Cents& c2);

  int getCents() const { return m_cents; }
};

// 注: 这个函数不是成员函数
Cents operator+(const Cents& c1, const Cents& c2)
{
	// 可以直接访问m_cents，因为本函数是 Cents 的友元函数
	// 返回 int，触发Cents的构造函数
  return { c1.m_cents + c2.m_cents };
}

int main()
{
  Cents cents1{ 6 };
  Cents cents2{ 8 };
  Cents centsSum{ cents1 + cents2 };
  std::cout << "I have " << centsSum.getCents() << " cents.\n";

  return 0;
}
