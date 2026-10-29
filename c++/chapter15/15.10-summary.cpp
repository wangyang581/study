// ==========================================================================
// 15.10 第15章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十五章 class第二部分
// 原文: https://www.studycpp.cn/basic/chapter15/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "15.10-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 章节回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 章节回顾 ――――

// 在每个（非静态）成员函数内部，关键字this都是保存当前隐式对象地址的常量指针。
// 可以让函数通过引用返回*this，以启用方法链接，从而在单个表达式中对同一对象连
// 续调用多个成员函数。
//
// 优先将类定义放在与类同名的头文件中。简单的成员函数（例如访问函数、空函数体
// 的构造函数等）可以在类定义中定义。
//
// 首选在与类同名的源文件中定义非平凡的成员函数。
//
// 在类类型内定义的类型称为嵌套类型（或成员类型）。类型别名也可以嵌套。
//
// 在类模板定义内定义的成员函数可以使用类模板本身的模板参数。在类模板定义之外
// 定义的成员函数必须重新提供模板参数声明，并且应该在类模板的正下方定义（位于
// 同一个文件中）。
//
// 静态成员变量是具有静态存储期、并由类的所有对象共享的成员。即使没有实例化类
// 对象，静态成员也依然存在。首选使用类名、域解析操作符和成员名称访问它们。
//
// 使静态成员内联允许在类定义中初始化它们。
//
// 静态成员函数是可以在没有对象的情况下调用的成员函数。它们没有*this指针，也不
// 能访问非静态数据成员。
//
// 在类的主体中，可以使用友元声明（使用friend关键字）告诉编译器，某些类或函数
// 现在是友元。友元是被授予对另一个类的私有成员和受保护成员完全访问权限的类或
// 函数（成员或非成员）。友元函数是一个可以访问类的私有成员和受保护成员的函数
// （成员或非成员），就像它是该类的成员一样。友元类则是可以访问另一个类的私有
// 成员和受保护成员的类。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 我们来写一个随机怪物生成器，这道题会很有意思。
//
// a) 首先创建一个名为`MonsterType`的限定作用域枚举，包含下列怪物类型：Dragon、
// Goblin、Ogre、Orc、Skeleton、Troll、Vampire和Zombie。再添加一个额外的
// maxMonsterTypes枚举元素，以便统计一共有多少个枚举元素。

// 【答案 · 查看答案】

// [代码 1]
// enum class MonsterType
// {
// 	dragon,
// 	goblin,
// 	ogre,
// 	orc,
// 	skeleton,
// 	troll,
// 	vampire,
// 	zombie,
// 	maxMonsterTypes,
// };

// b) 接下来创建`Monster`类。我们的`Monster`有4个属性（成员变量）：类型（
// `MonsterType`）、名字（`std::string`）、吼叫声（`std::string`）以及生命值（
// `int`）。

// 【答案 · 查看答案】

// [代码 2]
// #include <string>
//
// enum class MonsterType
// {
// 	dragon,
// 	goblin,
// 	ogre,
// 	orc,
// 	skeleton,
// 	troll,
// 	vampire,
// 	zombie,
// 	maxMonsterTypes,
// };
//
// class Monster
// {
// private:
// 	MonsterType m_type{};
// 	std::string m_name{"???"};
// 	std::string m_roar{"???"};
// 	int m_hitPoints{};
// };

// c) `enum class MonsterType`只对`Monster`有意义，因此把`MonsterType`改成
// `Monster`内部的嵌套非限定作用域枚举，并重命名为`Type`。

// 【答案 · 查看答案】

// [代码 3]
// #include <string>
//
// class Monster
// {
// public:
// 	enum Type
// 	{
// 		dragon,
// 		goblin,
// 		ogre,
// 		orc,
// 		skeleton,
// 		troll,
// 		vampire,
// 		zombie,
// 		maxMonsterTypes,
// 	};
//
// private:
//
// 	Type m_type{};
// 	std::string m_name{"???"};
// 	std::string m_roar{"???"};
// 	int m_hitPoints{};
// };

// d) 创建一个能够初始化所有成员变量的构造函数。
//
// 下面这个程序应当能够通过编译：

// [代码 4]
// int main()
// {
// 	Monster skeleton{ Monster::skeleton, "Bones", "*rattle*", 4 };
//
// 	return 0;
// }


// 【答案 · 查看答案】

// [代码 5]
// #include <string>
// #include <string_view>
//
// class Monster
// {
// public:
// 	enum Type
// 	{
// 		dragon,
// 		goblin,
// 		ogre,
// 		orc,
// 		skeleton,
// 		troll,
// 		vampire,
// 		zombie,
// 		maxMonsterTypes,
// 	};
//
// private:
//
// 	Type m_type{};
// 	std::string m_name{"???"};
// 	std::string m_roar{"???"};
// 	int m_hitPoints{};
//
// public:
// 	Monster(Type type, std::string_view name, std::string_view roar, int hitPoints)
// 		: m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints }
// 	{
// 	}
// };
//
// int main()
// {
// 	Monster skeleton{ Monster::skeleton, "Bones", "*rattle*", 4 };
//
// 	return 0;
// }

// e) 现在我们希望能够打印怪物，以便确认它是否正确。请编写两个函数：一个名为
// `getTypeString()`，以字符串形式返回怪物类型；另一个名为`print()`，其输出与
// 下面示例程序一致。
//
// 下面这个程序应当能够通过编译：

// [代码 6]
// int main()
// {
// 	Monster skeleton{ Monster::skeleton, "Bones", "*rattle*", 4 };
// 	skeleton.print();
//
// 	Monster vampire{ Monster::vampire, "Nibblez", "*hiss*", 0 };
// 	vampire.print();
//
// 	return 0;
// }

// 并打印：

// [文本/输出]
// Bones the skeleton has 4 hit points and says *rattle*.
// Nibblez the vampire is dead.


// 【答案 · 查看答案】

// [代码 7]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Monster
// {
// public:
// 	enum Type
// 	{
// 		dragon,
// 		goblin,
// 		ogre,
// 		orc,
// 		skeleton,
// 		troll,
// 		vampire,
// 		zombie,
// 		maxMonsterTypes,
// 	};
//
// private:
//
// 	Type m_type{};
// 	std::string m_name{"???"};
// 	std::string m_roar{"???"};
// 	int m_hitPoints{};
//
// public:
// 	Monster(Type type, std::string_view name, std::string_view roar, int hitPoints)
// 		: m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints }
// 	{
//
// 	}
//
// 	constexpr std::string_view getTypeString() const
// 	{
// 		switch (m_type)
// 		{
// 		case dragon:   return "dragon";
// 		case goblin:   return "goblin";
// 		case ogre:     return "ogre";
// 		case orc:      return "orc";
// 		case skeleton: return "skeleton";
// 		case troll:    return "troll";
// 		case vampire:  return "vampire";
// 		case zombie:   return "zombie";
// 		default:       return "???";
// 		}
// 	}
//
// 	void print() const
// 	{
// 		std::cout << m_name << " the " << getTypeString();
//
// 		if (m_hitPoints <= 0)
// 			std::cout << " is dead.\n";
// 		else
// 			std::cout << " has " << m_hitPoints << " hit points and says " << m_roar << ".\n";
// 	}
// };
//
// int main()
// {
// 	Monster skeleton{ Monster::skeleton, "Bones", "*rattle*", 4 };
// 	skeleton.print();
//
// 	Monster vampire{ Monster::vampire, "Nibblez", "*hiss*", 0 };
// 	vampire.print();
//
// 	return 0;
// }

// f) 现在可以创建随机怪物生成器了。先想一下`MonsterGenerator`应当如何工作。理
// 想情况下，我们让它给我们一个`Monster`，它就会随机创建一个。由于
// `MonsterGenerator`没有任何状态，用命名空间来实现是个好选择。
//
// 创建一个`MonsterGenerator`命名空间，在其中创建名为`generate()`的函数。它应
// 当返回一个`Monster`。现在先让它返回`Monster{ Monster::skeleton, "Bones",
// "*rattle*", 4}`。
//
// 下面这个程序应当能够通过编译：

// [代码 8]
// int main()
// {
// 	Monster m{ MonsterGenerator::generate() };
// 	m.print();
//
// 	return 0;
// }

// 并打印：

// [文本/输出]
// Bones the skeleton has 4 hit points and says *rattle*


// 【答案 · 查看答案】

// [代码 9]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Monster
// {
// public:
// 	enum Type
// 	{
// 		dragon,
// 		goblin,
// 		ogre,
// 		orc,
// 		skeleton,
// 		troll,
// 		vampire,
// 		zombie,
// 		maxMonsterTypes,
// 	};
//
// private:
//
// 	Type m_type{};
// 	std::string m_name{};
// 	std::string m_roar{};
// 	int m_hitPoints{};
//
// public:
// 	Monster(Type type, std::string_view name, const std::string& roar, int hitPoints)
// 		: m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints }
// 	{
//
// 	}
//
// 	constexpr std::string_view getTypeString() const
// 	{
// 		switch (m_type)
// 		{
// 		case Type::dragon: return "dragon";
// 		case Type::goblin: return "goblin";
// 		case Type::ogre: return "ogre";
// 		case Type::orc: return "orc";
// 		case Type::skeleton: return "skeleton";
// 		case Type::troll: return "troll";
// 		case Type::vampire: return "vampire";
// 		case Type::zombie: return "zombie";
// 		default: return "???";
// 		}
// 	}
//
// 	void print() const
// 	{
// 		if (m_hitPoints <= 0)
// 			std::cout << m_name << " is dead.\n";
// 		else
// 			std::cout << m_name << " the " << getTypeString() << " has " << m_hitPoints << " hit points and says " << m_roar << ".\n";
// 	}
// };
//
// namespace MonsterGenerator
// {
// 	Monster generate()
// 	{
// 		return Monster{ Monster::skeleton, "Bones", "*rattle*", 4 };
// 	}
// };
//
// int main()
// {
// 	Monster m{ MonsterGenerator::generate() };
// 	m.print();
//
// 	return 0;
// }

// g) 在`MonsterGenerator`命名空间中再添加两个函数。`getName(int)`接受一个0到5
// （含）之间的数字，返回一个你自己选的名字；`getRoar(int)`同样接受0到5（含）
// 之间的数字，返回一个你自己选的吼叫声。同时更新`generate()`函数，让它调用
// `getName(0)`和`getRoar(0)`。
//
// 下面这个程序应当能够通过编译：

// [代码 10]
// int main()
// {
// 	Monster m{ MonsterGenerator::generate() };
// 	m.print();
//
// 	return 0;
// }

// 并打印：

// [文本/输出]
// Blarg the skeleton has 4 hit points and says *ROAR*

// 你选的名字和声音可能与这里不同。

// 【答案 · 查看答案】

// [代码 11]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Monster
// {
// public:
// 	enum Type
// 	{
// 		dragon,
// 		goblin,
// 		ogre,
// 		orc,
// 		skeleton,
// 		troll,
// 		vampire,
// 		zombie,
// 		maxMonsterTypes,
// 	};
//
// private:
//
// 	Type m_type{};
// 	std::string m_name{"???"};
// 	std::string m_roar{"???"};
// 	int m_hitPoints{};
//
// public:
// 	Monster(Type type, std::string_view name, std::string_view roar, int hitPoints)
// 		: m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints }
// 	{
//
// 	}
//
// 	constexpr std::string_view getTypeString() const
// 	{
// 		switch (m_type)
// 		{
// 		case dragon:   return "dragon";
// 		case goblin:   return "goblin";
// 		case ogre:     return "ogre";
// 		case orc:      return "orc";
// 		case skeleton: return "skeleton";
// 		case troll:    return "troll";
// 		case vampire:  return "vampire";
// 		case zombie:   return "zombie";
// 		default: return "???";
// 		}
// 	}
//
// 	void print() const
// 	{
// 		std::cout << m_name << " the " << getTypeString();
//
// 		if (m_hitPoints <= 0)
// 			std::cout << " is dead.\n";
// 		else
// 			std::cout << " has " << m_hitPoints << " hit points and says " << m_roar << ".\n";
// 	}
// };
//
// namespace MonsterGenerator
// {
//     std::string_view getName(int n)
// 	{
//         switch (n)
//         {
//             case 0:  return "Blarg";
//             case 1:  return "Moog";
//             case 2:  return "Pksh";
//             case 3:  return "Tyrn";
//             case 4:  return "Mort";
//             case 5:  return "Hans";
//             default: return "???";
//         }
//     }
//
//     std::string_view getRoar(int n)
// 	{
//         switch (n)
//         {
//             case 0:  return "*ROAR*";
//             case 1:  return "*peep*";
//             case 2:  return "*squeal*";
//             case 3:  return "*whine*";
//             case 4:  return "*growl*";
//             case 5:  return "*burp*";
//             default: return "???";
//         }
//     }
//
// 	Monster generate()
// 	{
// 		return Monster{ Monster::skeleton, getName(0), getRoar(0), 4 };
// 	}
//
// };
//
// int main()
// {
// 	Monster m{ MonsterGenerator::generate() };
// 	m.print();
//
// 	return 0;
// }

// h) 现在把生成的怪物随机化。把「8.14 全局随机数」中的 Random.h 代码拿来保存
// 为 Random.h。然后用`Random::get()`随机生成怪物类型、随机名字、随机吼叫声，
// 以及1到100之间的随机生命值。
//
// 下面这个程序应当能够通过编译：

// [代码 12]
// #include "Random.h"
//
// int main()
// {
// 	Monster m{ MonsterGenerator::generate() };
// 	m.print();
//
// 	return 0;
// }

// 并打印类似下面的内容：

// [文本/输出]
// Mort the zombie has 61 hit points and says *growl*


// 【答案 · 查看答案】

// [代码 13]
// #include "Random.h"
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Monster
// {
// public:
// 	enum Type
// 	{
// 		dragon,
// 		goblin,
// 		ogre,
// 		orc,
// 		skeleton,
// 		troll,
// 		vampire,
// 		zombie,
// 		maxMonsterTypes,
// 	};
//
// private:
//
// 	Type m_type{};
// 	std::string m_name{"???"};
// 	std::string m_roar{"???"};
// 	int m_hitPoints{};
//
// public:
// 	Monster(Type type, std::string_view name, std::string_view roar, int hitPoints)
// 		: m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints }
// 	{
//
// 	}
//
// 	constexpr std::string_view getTypeString() const
// 	{
// 		switch (m_type)
// 		{
// 		case dragon:   return "dragon";
// 		case goblin:   return "goblin";
// 		case ogre:     return "ogre";
// 		case orc:      return "orc";
// 		case skeleton: return "skeleton";
// 		case troll:    return "troll";
// 		case vampire:  return "vampire";
// 		case zombie:   return "zombie";
// 		default: return "???";
// 		}
// 	}
//
// 	void print() const
// 	{
// 		std::cout << m_name << " the " << getTypeString();
//
// 		if (m_hitPoints <= 0)
// 			std::cout << " is dead.\n";
// 		else
// 			std::cout << " has " << m_hitPoints << " hit points and says " << m_roar << ".\n";
// 	}
// };
//
// namespace MonsterGenerator
// {
//     std::string_view getName(int n)
// 	{
//         switch (n)
//         {
//             case 0:  return "Blarg";
//             case 1:  return "Moog";
//             case 2:  return "Pksh";
//             case 3:  return "Tyrn";
//             case 4:  return "Mort";
//             case 5:  return "Hans";
//             default: return "???";
//         }
//     }
//
//     std::string_view getRoar(int n)
// 	{
//         switch (n)
//         {
//             case 0:  return "*ROAR*";
//             case 1:  return "*peep*";
//             case 2:  return "*squeal*";
//             case 3:  return "*whine*";
//             case 4:  return "*growl*";
//             case 5:  return "*burp*";
//             default: return "???";
//         }
//     }
//
//     Monster generate()
//     {
//         return Monster{
//             static_cast<Monster::Type>(Random::get(0, Monster::maxMonsterTypes-1)),
//             getName(Random::get(0,5)),
//             getRoar(Random::get(0,5)),
//             Random::get(1, 100)
//             };
// 	}
//
// };
//
// int main()
// {
// 	Monster m{ MonsterGenerator::generate() };
// 	m.print();
//
// 	return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <string>
#include <string_view>

class Monster
{
public:
	enum Type
	{
		dragon,
		goblin,
		ogre,
		orc,
		skeleton,
		troll,
		vampire,
		zombie,
		maxMonsterTypes,
	};

private:

	Type m_type{};
	std::string m_name{"???"};
	std::string m_roar{"???"};
	int m_hitPoints{};

public:
	Monster(Type type, std::string_view name, std::string_view roar, int hitPoints)
		: m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints }
	{
	}
};

int main()
{
	Monster skeleton{ Monster::skeleton, "Bones", "*rattle*", 4 };

	return 0;
}
