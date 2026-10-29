// ==========================================================================
// 13.13 第13章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十三章 复合类型：枚举与结构体
// 原文: https://www.studycpp.cn/basic/chapter13/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "13.13-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 章节回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 章节回顾 ――――

// 程序定义类型（也称为用户定义类型）是一种自定义类型，我们可以创建它以在自己
// 的程序中使用。枚举类型和类类型（包括结构体、类和联合）允许创建程序定义的类
// 型。
//
// 必须先定义程序定义的类型，然后才能使用它们。程序定义类型的定义称为类型定义。
// 类型定义不受单定义规则的约束。
//
// 枚举（也称为枚举类型）是一种复合数据类型，其中每个可能的值都定义为符号常量
// （称为枚举元素）。不同枚举是不同的类型，这意味着编译器可以将它们与其他类型
// 区分开来（与类型别名不同）。
//
// 非限定作用域枚举之所以如此命名，是因为它们将其枚举元素名称放入与枚举定义本
// 身相同的作用域中（而不是像命名空间那样创建新的作用域）。它也会为其枚举元素
// 提供作用域。非限定作用域枚举会隐式转换为整数值。
//
// 限定作用域枚举的工作方式类似于非限定作用域枚举，但不会隐式转换为整数，并且
// 枚举元素仅放在枚举的作用域中（而不是放在定义枚举的作用域中）。
//
// struct（structure的缩写）是一种程序定义的数据类型，它允许将多个变量绑定到一
// 个类型中。作为结构体（或类）一部分的变量称为数据成员（或成员变量）。为了访
// 问特定成员变量，可以在结构体变量名称和成员名称之间使用成员选择操作符（
// operator.，用于普通结构体和引用），或者使用指针操作符（operator->，用于结构
// 体指针）。
//
// 在一般编程中，聚合数据类型（也称为聚合）是可以包含多个数据成员的任何类型。
// 在C++中，只有C样式数组和结构体是聚合类型。
//
// 聚合可以使用一种称为聚合初始化的初始化形式，它允许直接初始化聚合的成员。为
// 此，需要提供一个初始化列表，也就是一个由逗号分隔值组成的列表。聚合初始化执
// 行成员级初始化，这意味着结构体中的每个成员都是按声明顺序初始化的。
//
// 在C++20中，指定初始值设定项允许您显式定义哪些初始化值映射到哪些成员。成员必
// 须按照在结构中声明的顺序进行初始化，否则将导致错误。
//
// 当定义结构体（或类）类型时，可以为每个成员提供默认的初始化值，作为类型定义
// 的一部分。该过程称为非静态成员初始化，初始化值称为成员默认初始值设定项。
//
// 出于性能原因，编译器有时会在结构体中添加间隙（这称为填充），因此结构体的大
// 小可能大于其成员大小的总和。
//
// 类模板是用于实例化类类型（结构体、类或联合）的模板定义。类模板参数推导（
// CTAD）是C++17的一个功能，它允许编译器从初始值设定项中推导模板类型参数。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 在设计一个游戏时，我们决定加入怪物，因为大家都喜欢打怪物。请声明一个表示怪
// 物的结构体。怪物的类型可以是下列之一：ogre、dragon、orc、giant spider或
// slime。
//
// 每个怪物还应当有一个名字（使用`std::string`），以及一个表示它在死亡前能承受
// 多少伤害的生命值。编写一个名为`printMonster()`的函数，打印该结构体的所有成
// 员。实例化一个ogre和一个slime，使用初始化列表初始化它们，并把它们传给
// `printMonster()`。
//
// 程序应当产生如下输出：

// [文本/输出]
// This Ogre is named Torg and has 145 health.
// This Slime is named Blurp and has 23 health.


// 【答案 · 查看答案】

// [代码 1]
// #include <iostream>
// #include <string>
// #include <string_view> // C++17
//
// // 我们的 Monster 结构体表示单个怪物
//
// struct Monster
// {
// 	// 用枚举定义不同的怪物类型
// 	enum Type
// 	{
// 		ogre,
// 		dragon,
// 		orc,
// 		giant_spider,
// 		slime,
// 	};
//
// 	Type type{};
// 	std::string name{}; // Monster 应当拥有自己的名字
// 	int health{};
// };
//
// // 以字符串形式返回怪物类型名称
// // 由于这个函数可能在其他地方也能用到，单独抽出来更好
// constexpr std::string_view getMonsterTypeString(Monster::Type type)
// {
// 	switch (type)
// 	{
// 	case Monster::ogre:          return "Ogre";
// 	case Monster::dragon:        return "Dragon";
// 	case Monster::orc:           return "Orc";
// 	case Monster::giant_spider:  return "Giant Spider";
// 	case Monster::slime:         return "Slime";
// 	}
//
// 	return "Unknown";
// }
//
// // 打印怪物的属性
// void printMonster(const Monster& monster)
// {
// 	std::cout << "This " << getMonsterTypeString(monster.type) <<
// 		" is named " << monster.name <<
// 		" and has " << monster.health << " health.\n";
// }
//
// int main()
// {
// 	Monster ogre{ Monster::ogre, "Torg", 145 };
// 	Monster slime{ Monster::slime, "Blurp", 23 };
//
// 	printMonster(ogre);
// 	printMonster(slime);
//
// 	return 0;
// }


// ▼ 问题 2
// 指出下列各种类型的对象应当按值传递、按const地址传递还是按const引用传递。可
// 以假设接受这些类型形参的函数不会修改它们。
//
// a) `char`

// 【答案 · 查看答案】
// `char`是基本类型，因此应当按值传递。
//
// b) `std::string`

// 【答案 · 查看答案】
// `std::string`每次被拷贝时都必须创建字符串的副本，因此按const引用传递。
//
// c) `unsigned long`

// 【答案 · 查看答案】
// `unsigned long`是基本类型，因此应当按值传递。
//
// d) `bool`

// 【答案 · 查看答案】
// `bool`是基本类型，因此应当按值传递。
//
// e) 枚举类型

// 【答案 · 查看答案】
// 枚举类型保存的是整数值（通常是int）。由于整数值按值传递，枚举类型也应当按值
// 传递。
//
// f)

// [代码 2]
// struct Position
// {
//   double x{};
//   double y{};
//   double z{};
// };


// 【答案 · 查看答案】
// `Position`是结构体类型，应当按const引用传递。
//
// g)

// [代码 3]
// struct Player
// {
//   int health{};
//   // Player 结构体仍在开发中，以后还会加入更多成员
// };


// 【答案 · 查看答案】
// 虽然`Player`目前只包含一个`int`，按值传递会很快，但将来还会加入更多成员。我
// 们不希望到时再去修改每一处使用`Player`的地方，因此按const引用传递。
//
// h) `int`（当null是一个合法实参时）

// 【答案 · 查看答案】
// 通常`int`会按值传递，但如果还希望能够传递一个「空」值，那么按地址传递是个好
// 选择，因为既可以传入`int`的地址，也可以传入`nullptr`。
//
// i) `std::string_view`

// 【答案 · 查看答案】
// `std::string_view`不会创建所观察字符串的副本，而且拷贝开销很小，因此按值传
// 递。

// ▼ 问题 3
// 创建一个名为`Triad`的类模板，其中包含3个相同模板类型的成员。再创建一个名为
// `print`的函数模板，用于打印Triad。下面这个程序应当能够编译：

// [代码 4]
// int main()
// {
// 	Triad t1{ 1, 2, 3 }; // 注意：使用 CTAD 推导模板实参
// 	print(t1);
//
// 	Triad t2{ 1.2, 3.4, 5.6 }; // 注意：使用 CTAD 推导模板实参
// 	print(t2);
//
// 	return 0;
// }

// 并产生如下结果：

// [文本/输出]
// [1, 2, 3][1.2, 3.4, 5.6]

// 如果你使用的是C++17，需要为CTAD提供一个推导指引才能正常工作（参见「13.11 类
// 模板参数推导（CTAD）」）。

// 【答案 · 查看答案】

// [代码 5]
// #include <iostream>
//
// template <typename T>
// struct Triad
// {
// 	T first {};
// 	T second {};
// 	T third {};
// };
//
// // 如果使用 C++17，需要提供推导指引（C++20 中不需要）
// // 由三个相同类型的实参构造的 Triad 应当推导为 Triad<T>
// template <typename T>
// Triad(T, T, T) -> Triad<T>;
//
// template <typename T>
// void print(const Triad<T>& t)
// {
// 	std::cout << '[' << t.first << ", " << t.second << ", " << t.third << ']';
// }
//
// int main()
// {
// 	Triad t1{ 1, 2, 3 };
// 	print(t1);
//
// 	Triad t2{ 1.2, 3.4, 5.6 };
// 	print(t2);
//
// 	return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <string>
#include <string_view> // C++17

// 我们的 Monster 结构体表示单个怪物

struct Monster
{
	// 用枚举定义不同的怪物类型
	enum Type
	{
		ogre,
		dragon,
		orc,
		giant_spider,
		slime,
	};

	Type type{};
	std::string name{}; // Monster 应当拥有自己的名字
	int health{};
};

// 以字符串形式返回怪物类型名称
// 由于这个函数可能在其他地方也能用到，单独抽出来更好
constexpr std::string_view getMonsterTypeString(Monster::Type type)
{
	switch (type)
	{
	case Monster::ogre:          return "Ogre";
	case Monster::dragon:        return "Dragon";
	case Monster::orc:           return "Orc";
	case Monster::giant_spider:  return "Giant Spider";
	case Monster::slime:         return "Slime";
	}

	return "Unknown";
}

// 打印怪物的属性
void printMonster(const Monster& monster)
{
	std::cout << "This " << getMonsterTypeString(monster.type) <<
		" is named " << monster.name <<
		" and has " << monster.health << " health.\n";
}

int main()
{
	Monster ogre{ Monster::ogre, "Torg", 145 };
	Monster slime{ Monster::slime, "Blurp", 23 };

	printMonster(ogre);
	printMonster(slime);

	return 0;
}
