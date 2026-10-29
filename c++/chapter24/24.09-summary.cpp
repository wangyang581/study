// ==========================================================================
// 24.9 第24章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十四章 继承
// 原文: https://www.studycpp.cn/basic/chapter24/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "24.09-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 继承允许我们对两个对象之间的关系进行建模。被继承的对象称为父类、基类或超类。
// 进行继承的对象称为子类或派生类。
//
// 当派生类继承自基类时，派生类会获得基类的所有成员。
//
// 构造派生类时，会先构造类的基类部分，然后构造派生部分。更详细地说：
// - 留出内存（足够用于基类和派生部分）。
// - 调用相应的派生类构造函数。
// - 使用适当的基类构造函数构造基类对象。如果没有指定基类构造函数，则将使用默
//   认构造函数。
// - 派生类的初始化列表初始化派生类的成员。
// - 执行派生类构造函数的主体。
// - 控制权返回给调用者。
// - 析构发生的顺序相反，从最底层的派生类到最上层的基类。
//
// C++有3个访问说明符：public、private和protected。protected允许成员所属的类、
// 友元和派生类访问protected成员，但不允许外部访问。
//
// 类可以以public、private或protected方式继承另一个类。类几乎总是使用public继
// 承。
//
// 以下是所有访问说明符和继承类型组合的表：

// [表格 1]
//   | 基类中的访问说明符 | public继承时对应的派生类的访问说明符 | private继承时对
//   | 应的派生类的访问说明符 | protected继承时对应的派生类的访问说明符
//   | Public | Public | Private | Protected
//   | Protected | Protected | Private | Protected
//   | Private | 不可访问 | 不可访问 | 不可访问

//
// 派生类可以添加新函数、更改基类已有函数在派生类中的工作方式、更改继承成员的
// 访问级别，或隐藏功能。
//
// 多重继承使派生类能够从多个父类继承成员。通常应该避免多重继承，除非替代方案
// 会导致更复杂的情况。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 对下面每一个程序，判断它们的输出是什么；如果无法通过编译，请说明原因。本题
// 要求靠观察完成，不要编译运行这些程序（否则答案就太简单了）。
//
// a)

// [代码 1]
// #include <iostream>
//
// class Base
// {
// public:
// 	Base()
// 	{
// 		std::cout << "Base()\n";
// 	}
// 	~Base()
// 	{
// 		std::cout << "~Base()\n";
// 	}
// };
//
// class Derived: public Base
// {
// public:
// 	Derived()
// 	{
// 		std::cout << "Derived()\n";
// 	}
// 	~Derived()
// 	{
// 		std::cout << "~Derived()\n";
// 	}
// };
//
// int main()
// {
// 	Derived d;
//
// 	return 0;
// }


// 【答案 · 查看答案】
// 构造的顺序是从最「父」到最「子」，析构的顺序则相反。

// [文本/输出]
// Base()
// Derived()
// ~Derived()
// ~Base()

// b)

// [代码 2]
// #include <iostream>
//
// class Base
// {
// public:
// 	Base()
// 	{
// 		std::cout << "Base()\n";
// 	}
// 	~Base()
// 	{
// 		std::cout << "~Base()\n";
// 	}
// };
//
// class Derived: public Base
// {
// public:
// 	Derived()
// 	{
// 		std::cout << "Derived()\n";
// 	}
// 	~Derived()
// 	{
// 		std::cout << "~Derived()\n";
// 	}
// };
//
// int main()
// {
// 	Derived d;
// 	Base b;
//
// 	return 0;
// }

// 提示：局部变量的销毁顺序与定义顺序相反。

// 【答案 · 查看答案】
// 首先构造d，打印：

// [文本/输出]
// Base()
// Derived()

// 接着构造b，打印：

// [文本/输出]
// Base()

// 然后销毁b，打印：

// [文本/输出]
// ~Base()

// 最后销毁d，打印：

// [文本/输出]
// ~Derived()
// ~Base()

// c)

// [代码 3]
// #include <iostream>
//
// class Base
// {
// private:
// 	int m_x {};
// public:
// 	Base(int x): m_x{ x }
// 	{
// 		std::cout << "Base()\n";
// 	}
// 	~Base()
// 	{
// 		std::cout << "~Base()\n";
// 	}
//
// 	void print() const { std::cout << "Base: " << m_x << '\n';  }
// };
//
// class Derived: public Base
// {
// public:
// 	Derived(int y):  Base{ y }
// 	{
// 		std::cout << "Derived()\n";
// 	}
// 	~Derived()
// 	{
// 		std::cout << "~Derived()\n";
// 	}
//
// 	void print() const { std::cout << "Derived: " << m_x << '\n'; }
// };
//
// int main()
// {
// 	Derived d{ 5 };
// 	d.print();
//
// 	return 0;
// }


// 【答案 · 查看答案】
// 无法通过编译，`Derived::print()`不能访问私有成员`m_x`。
//
// d)

// [代码 4]
// #include <iostream>
//
// class Base
// {
// protected:
// 	int m_x {};
// public:
// 	Base(int x): m_x{ x }
// 	{
// 		std::cout << "Base()\n";
// 	}
// 	~Base()
// 	{
// 		std::cout << "~Base()\n";
// 	}
//
// 	void print() const { std::cout << "Base: " << m_x << '\n';  }
// };
//
// class Derived: public Base
// {
// public:
// 	Derived(int y):  Base{ y }
// 	{
// 		std::cout << "Derived()\n";
// 	}
// 	~Derived()
// 	{
// 		std::cout << "~Derived()\n";
// 	}
//
// 	void print() const { std::cout << "Derived: " << m_x << '\n'; }
// };
//
// int main()
// {
// 	Derived d{ 5 };
// 	d.print();
//
// 	return 0;
// }


// 【答案 · 查看答案】

// [文本/输出]
// Base()
// Derived()
// Derived: 5
// ~Derived()
// ~Base()

// e)

// [代码 5]
// #include <iostream>
//
// class Base
// {
// protected:
// 	int m_x {};
// public:
// 	Base(int x): m_x{ x }
// 	{
// 		std::cout << "Base()\n";
// 	}
// 	~Base()
// 	{
// 		std::cout << "~Base()\n";
// 	}
//
// 	void print() const { std::cout << "Base: " << m_x << '\n';  }
// };
//
// class Derived: public Base
// {
// public:
// 	Derived(int y):  Base{ y }
// 	{
// 		std::cout << "Derived()\n";
// 	}
// 	~Derived()
// 	{
// 		std::cout << "~Derived()\n";
// 	}
//
// 	void print() const { std::cout << "Derived: " << m_x << '\n'; }
// };
//
// class D2 : public Derived
// {
// public:
// 	D2(int z): Derived{ z }
// 	{
// 		std::cout << "D2()\n";
// 	}
// 	~D2()
// 	{
// 		std::cout << "~D2()\n";
// 	}
//
//         // 注意：这里没有 print() 函数
// };
//
// int main()
// {
// 	D2 d{ 5 };
// 	d.print();
//
// 	return 0;
// }


// 【答案 · 查看答案】

// [文本/输出]
// Base()
// Derived()
// D2()
// Derived: 5
// ~D2()
// ~Derived()
// ~Base()


// ▼ 问题 2
// a) 编写一个Apple类和一个Banana类，它们都继承自共同的Fruit类。Fruit应当有两
// 个成员：名字和颜色。
//
// 下面这个程序应当能够运行：

// [代码 6]
// int main()
// {
// 	Apple a{ "red" };
// 	Banana b{};
//
// 	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
// 	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
//
// 	return 0;
// }

// 并产生结果：

// [文本/输出]
// My apple is red.
// My banana is yellow.


// 【答案 · 查看答案】

// [代码 7]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Fruit
// {
// private:
// 	std::string m_name;
// 	std::string m_color;
//
// public:
// 	Fruit(std::string_view name, std::string_view color)
// 		: m_name{ name }, m_color{ color }
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// 	const std::string& getColor() const { return m_color; }
// };
//
// class Apple: public Fruit
// {
// public:
// 	Apple(std::string_view color="red")
// 		: Fruit{ "apple", color }
// 	{
// 	}
// };
//
// class Banana : public Fruit
// {
// public:
// 	Banana()
// 		: Fruit{ "banana", "yellow" }
// 	{
// 	}
// };
//
// int main()
// {
// 	Apple a{ "red" };
// 	Banana b;
//
// 	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
// 	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
//
// 	return 0;
// }

// b) 在上一个程序中新增一个名为GrannySmith的类，它继承自Apple。
//
// 下面这个程序应当能够运行：

// [代码 8]
// int main()
// {
// 	Apple a{ "red" };
// 	Banana b;
// 	GrannySmith c;
//
// 	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
// 	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
// 	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
//
// 	return 0;
// }

// 并产生结果：

// [文本/输出]
// My apple is red.
// My banana is yellow.
// My granny smith apple is green.


// 【答案 · 查看答案】

// [代码 9]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Fruit
// {
// private:
// 	std::string m_name;
// 	std::string m_color;
//
// public:
// 	Fruit(std::string_view name, std::string_view color)
// 		: m_name{ name }, m_color{ color }
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// 	const std::string& getColor() const { return m_color; }
// };
//
// class Apple: public Fruit
// {
// // 我们之前给 Apple 使用的构造函数把名字固定为「apple」。
// // 需要为 GrannySmith 新增一个构造函数，用来设置水果的名字
// protected: // protected 使得只有派生类可以访问
// 	Apple(std::string_view name, std::string_view color)
// 		: Fruit{ name, color }
// 	{
// 	}
//
// public:
// 	Apple(std::string_view color="red")
// 		: Fruit{ "apple", color }
// 	{
// 	}
// };
//
// class Banana : public Fruit
// {
// public:
// 	Banana()
// 		: Fruit{ "banana", "yellow" }
// 	{
// 	}
// };
//
// class GrannySmith : public Apple
// {
// public:
// 	GrannySmith()
// 		: Apple{ "granny smith apple", "green" }
// 	{
// 	}
// };
//
// int main()
// {
// 	Apple a{ "red" };
// 	Banana b;
// 	GrannySmith c;
//
// 	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
// 	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
// 	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
//
// 	return 0;
// }


// ▼ 问题 3
// 挑战时间！下面这道习题更难、也更长。我们要写一个简单的打怪游戏。游戏目标是
// 在死亡或达到20级之前尽可能多地收集金币。
//
// 我们的程序由3个类组成：Creature类、Player类和Monster类。Player与Monster都继
// 承自Creature。
//
// a) 首先创建Creature类。生物有5个属性：名字（std::string）、符号（char）、生
// 命值（int）、每次攻击造成的伤害（int），以及携带的金币数量（int）。把它们实
// 现为类成员。编写一整套getter（每个成员一个获取函数）。再添加三个函数：`void
// reduceHealth(int)`把生物的生命值减少指定的整数；`bool isDead()`在生物生命值
// 为0或更少时返回true；`void addGold(int)`给生物增加金币。
//
// 下面这个程序应当能够运行：

// [代码 10]
// #include <iostream>
// #include <string>
//
// int main()
// {
// 	Creature o{ "orc", 'o', 4, 2, 10 };
// 	o.addGold(5);
// 	o.reduceHealth(1);
// 	std::cout << "The " << o.getName() << " has " << o.getHealth() << " health and is carrying " << o.getGold() << " gold.\n";
//
// 	return 0;
// }

// 并产生结果：

// [文本/输出]
// The orc has 3 health and is carrying 15 gold.


// 【答案 · 查看答案】

// [代码 11]
// #include <iostream>
// #include <string>
// #include <string_view> // 需要 C++17
//
// class Creature
// {
// protected:
// 	std::string m_name;
// 	char m_symbol {};
// 	int m_health {};
// 	int m_damage {};
// 	int m_gold {};
//
// public:
// 	Creature(std::string_view name, char symbol, int health, int damage, int gold)
// 		: m_name{ name }
// 		, m_symbol{ symbol }
// 		, m_health{ health }
// 		, m_damage{ damage }
// 		, m_gold{ gold }
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// 	char getSymbol() const { return m_symbol; }
// 	int getHealth() const { return m_health; }
// 	int getDamage() const { return m_damage; }
// 	int getGold() const { return m_gold; }
//
// 	void reduceHealth(int health) { m_health -= health; }
// 	bool isDead() const { return m_health <= 0; }
// 	void addGold(int gold) { m_gold += gold; }
// };
//
// int main()
// {
// 	Creature o{ "orc", 'o', 4, 2, 10 };
// 	o.addGold(5);
// 	o.reduceHealth(1);
// 	std::cout << "The " << o.getName() << " has " << o.getHealth() << " health and is carrying " << o.getGold() << " gold.\n";
//
// 	return 0;
// }

// b) 接下来创建Player类。Player继承自Creature。Player额外有一个成员——玩家等级，
// 初始为1。玩家有自定义的名字（由用户输入），使用符号「@」，生命值为10，初始
// 伤害为1，初始金币为0。编写一个名为`levelUp()`的函数，把玩家的等级和伤害各增
// 加1。再为等级成员编写一个getter。最后编写一个名为`hasWon()`的函数，当玩家达
// 到20级时返回true。
//
// 编写一个新的`main()`函数，询问用户的名字，并产生如下输出：

// [文本/输出]
// Enter your name: Alex
// Welcome, Alex.
// You have 10 health and are carrying 0 gold.


// 【答案 · 查看答案】

// [代码 12]
// #include <iostream>
// #include <string>
// #include <string_view> // std::string_view 需要 C++17
//
// class Creature
// {
// protected:
// 	std::string m_name;
// 	char m_symbol {};
// 	int m_health {};
// 	int m_damage {};
// 	int m_gold {};
//
// public:
// 	Creature(std::string_view name, char symbol, int health, int damage, int gold)
// 		: m_name{ name }
// 		, m_symbol{ symbol }
// 		, m_health{ health }
// 		, m_damage{ damage }
// 		, m_gold{ gold }
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// 	char getSymbol() const { return m_symbol; }
// 	int getHealth() const { return m_health; }
// 	int getDamage() const { return m_damage; }
// 	int getGold() const { return m_gold; }
//
// 	void reduceHealth(int health) { m_health -= health; }
// 	bool isDead() const { return m_health <= 0; }
// 	void addGold(int gold) { m_gold += gold; }
// };
//
// class Player : public Creature
// {
// 	int m_level{ 1 };
//
// public:
// 	Player(std::string_view name)
// 		: Creature{ name, '@', 10, 1, 0 }
// 	{
// 	}
//
// 	void levelUp()
// 	{
// 		++m_level;
// 		++m_damage;
// 	}
//
// 	int getLevel() const { return m_level; }
// 	bool hasWon() const { return m_level >= 20; }
// };
//
// int main()
// {
// 	std::cout << "Enter your name: ";
// 	std::string playerName;
// 	std::cin >> playerName;
//
// 	Player p{ playerName };
// 	std::cout << "Welcome, " << p.getName() << ".\n";
//
// 	std::cout << "You have " << p.getHealth() << " health and are carrying " << p.getGold() << " gold.\n";
//
// 	return 0;
// }

// c) 接下来是Monster类。Monster同样继承自Creature。怪物没有自己新增的成员变量。
//
// 首先编写一个继承自Creature的空Monster类，然后在Monster类内部添加一个名为
// Type的枚举，包含本游戏中3种怪物的枚举元素：`dragon`、`orc`和`slime`（你还需
// 要一个`max_types`枚举元素，稍后会用得上）。

// 【答案 · 查看答案】

// [代码 13]
// class Monster : public Creature
// {
// public:
// 	enum Type
// 	{
// 		dragon,
// 		orc,
// 		slime,
// 		max_types
// 	};
// };

// d) 每种怪物类型都有不同的名字、符号、初始生命值、金币和伤害。下表列出了每种
// 怪物的属性：

// [表格 2]
//   | 类型 | 名字 | 符号 | 生命值 | 伤害 | 金币
//   | dragon | dragon | D | 20 | 4 | 100
//   | orc | orc | o | 4 | 2 | 25
//   | slime | slime | s | 1 | 1 | 10

//
// 下一步是编写Monster构造函数，以便创建怪物。Monster构造函数应当接受一个Type
// 枚举作为形参，然后创建一个具有该类怪物相应属性的Monster。
//
// 实现方式有多种（有的更好，有的更差）。不过在本例中，由于所有怪物属性都是预
// 先定义好的（不是随机或逐个定制的），我们可以使用查找表。查找表是一个
// Creature的C样式数组，用Type作为下标即可得到该Type对应的Creature。
//
// 由于这个Creature表是Monster专用的，我们可以在Monster类内部把它定义为`static
// inline Creature monsterData[] { }`，用各个Creature元素初始化。
//
// 这样Monster构造函数就很简单了：调用Creature的拷贝构造函数，把monsterData表
// 中相应的Creature传给它。
//
// 下面这个程序应当能够通过编译：

// [代码 14]
// #include <iostream>
// #include <string>
//
// int main()
// {
// 	Monster m{ Monster::Type::orc };
// 	std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
//
// 	return 0;
// }

// 并打印：

// [文本/输出]
// A orc (o) was created.


// 【答案 · 查看答案】

// [代码 15]
// #include <array>
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Creature
// {
// protected:
//     std::string m_name;
//     char m_symbol {};
//     int m_health {};
//     int m_damage {};
//     int m_gold {};
//
// public:
//      Creature(std::string_view name, char symbol, int health, int damage, int gold)
//         : m_name{ name }
//         , m_symbol{ symbol }
//         , m_health{ health }
//         , m_damage{ damage }
//         , m_gold{ gold }
//     { }
//
//     char getSymbol() const { return m_symbol; }
//     const std::string& getName() const { return m_name; }
//     bool isDead() const { return m_health <= 0; }
//     int getGold() const { return m_gold; }
//     void addGold(int gold) { m_gold += gold; }
//     void reduceHealth(int health) { m_health -= health; }
//     int getHealth() const { return m_health; }
//     int getDamage() const { return m_damage; }
// };
//
// class Player : public Creature
// {
//     int m_level{ 1 };
//
// public:
//     Player(const std::string& name)
//         : Creature{ name, '@', 10, 1, 0 }
//     {
//     }
//
//     void levelUp()
//     {
//         ++m_level;
//         ++m_damage;
//     }
//
//     int getLevel() const { return m_level; }
//     bool hasWon() const { return m_level >= 20; }
// };
//
// class Monster : public Creature
// {
// public:
//     enum Type
//     {
//         dragon,
//         orc,
//         slime,
//         max_types
//     };
//
// private:
//     inline static Creature monsterData[] {
//         Creature { "dragon", 'D', 20, 4, 100 },
//         Creature { "orc", 'o', 4, 2, 25 },
//         Creature { "slime", 's', 1, 1, 10 }
//         };
//
//     static_assert(std::size(monsterData) == max_types);
//
// public:
//     Monster(Type type)
//         : Creature{ monsterData[type] }
//     {
//     }
// };
//
// int main()
// {
//     Monster m{ Monster::Type::orc };
//     std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
//
//   return 0;
// }

// e) 最后，给Monster添加一个`static`函数`getRandomMonster()`。该函数应当从`0`
// 到`max_types-1`中随机取一个数，并返回该`Type`的怪物（按值返回）（需要把
// `int`用`static_cast`转换成`Type`再传给Monster构造函数）。
//
// 「8.14 全局随机数」中有可以用来取随机数的代码。
//
// 下面这个main函数应当能够运行：

// [代码 16]
// #include <iostream>
// #include <string>
//
// int main()
// {
// 	for (int i{ 0 }; i < 10; ++i)
// 	{
// 		Monster m{ Monster::getRandomMonster() };
// 		std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
// 	}
//
// 	return 0;
// }

// 这个程序的结果应当是随机的。

// 【答案 · 查看答案】

// [代码 17]
// #include "Random.h" // https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/
// #include <array>
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Creature
// {
// protected:
//     std::string m_name;
//     char m_symbol {};
//     int m_health {};
//     int m_damage {};
//     int m_gold {};
//
// public:
//      Creature(std::string_view name, char symbol, int health, int damage, int gold)
//         : m_name{ name }
//         , m_symbol{ symbol }
//         , m_health{ health }
//         , m_damage{ damage }
//         , m_gold{ gold }
//     { }
//
//     char getSymbol() const { return m_symbol; }
//     const std::string& getName() const { return m_name; }
//     bool isDead() const { return m_health <= 0; }
//     int getGold() const { return m_gold; }
//     void addGold(int gold) { m_gold += gold; }
//     void reduceHealth(int health) { m_health -= health; }
//     int getHealth() const { return m_health; }
//     int getDamage() const { return m_damage; }
// };
//
// class Player : public Creature
// {
//     int m_level{ 1 };
//
// public:
//     Player(const std::string& name)
//         : Creature{ name, '@', 10, 1, 0 }
//     {
//     }
//
//     void levelUp()
//     {
//         ++m_level;
//         ++m_damage;
//     }
//
//     int getLevel() const { return m_level; }
//     bool hasWon() const { return m_level >= 20; }
// };
//
// class Monster : public Creature
// {
// public:
//     enum Type
//     {
//         dragon,
//         orc,
//         slime,
//         max_types
//     };
//
// private:
//     inline static Creature monsterData[] {
//         Creature { "dragon", 'D', 20, 4, 100 },
//         Creature { "orc", 'o', 4, 2, 25 },
//         Creature { "slime", 's', 1, 1, 10 }
//         };
//
//     static_assert(std::size(monsterData) == max_types);
//
// public:
//     Monster(Type type)
//         : Creature{ monsterData[type] }
//     {
//     }
//
//     static Monster getRandomMonster()
//     {
//         int num{ Random::get(0, max_types - 1) };
//         return Monster{ static_cast<Type>(num) };
//     }
// };
//
// int main()
// {
//     for (int i{ 0 }; i < 10; ++i)
//     {
//         Monster m{ Monster::getRandomMonster() };
//         std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
//     }
//
//   return 0;
// }

// f) 终于可以来写游戏逻辑了！
//
// 游戏规则如下：
//
// 玩家每次会遇到一只随机生成的怪物。 对每只怪物，玩家有两个选择：(R)逃跑或(F)
// 战斗。 如果玩家决定逃跑，有50%的概率逃脱成功。 如果逃脱成功，玩家继续前进，
// 不会受到任何不利影响。 如果没有逃脱成功，怪物会获得一次免费攻击，然后玩家再
// 次选择下一步行动。 如果玩家选择战斗，则玩家先攻击，怪物的生命值减少玩家的伤
// 害值。 如果怪物死亡，玩家获得怪物携带的所有金币，同时玩家升级，等级和伤害各
// 增加1。 如果怪物没有死亡，怪物反击玩家，玩家的生命值减少怪物的伤害值。 游戏
// 在玩家死亡（失败）或达到20级（胜利）时结束。 如果玩家死亡，游戏应当告诉玩家
// 死亡时的等级和拥有的金币数。 如果玩家获胜，游戏应当告诉玩家他赢了，以及拥有
// 多少金币。
//
// 下面是一次游戏的示例：

// [文本/输出]
// Enter your name: Alex
// Welcome, Alex
// You have encountered a slime (s).
// (R)un or (F)ight: f
// You hit the slime for 1 damage.
// You killed the slime.
// You are now level 2.
// You found 10 gold.
// You have encountered a dragon (D).
// (R)un or (F)ight: r
// You failed to flee.
// The dragon hit you for 4 damage.
// (R)un or (F)ight: r
// You successfully fled.
// You have encountered a orc (o).
// (R)un or (F)ight: f
// You hit the orc for 2 damage.
// The orc hit you for 2 damage.
// (R)un or (F)ight: f
// You hit the orc for 2 damage.
// You killed the orc.
// You are now level 3.
// You found 25 gold.
// You have encountered a dragon (D).
// (R)un or (F)ight: r
// You failed to flee.
// The dragon hit you for 4 damage.
// You died at level 3 and with 35 gold.
// Too bad you can’t take it with you!

// 提示：创建4个函数：
// - `main()`函数负责游戏的初始化（创建Player）和主游戏循环。
// - `fightMonster()`负责处理Player与单只Monster之间的战斗，包括询问玩家想做
//   什么，以及处理逃跑和战斗两种情况。
// - `attackMonster()`负责处理玩家攻击怪物，包括升级。
// - `attackPlayer()`负责处理怪物攻击玩家。

// 【答案 · 查看答案】

// [代码 18]
// #include "Random.h" // https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/
// #include <array>
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Creature
// {
// protected:
//     std::string m_name;
//     char m_symbol {};
//     int m_health {};
//     int m_damage {};
//     int m_gold {};
//
// public:
//      Creature(std::string_view name, char symbol, int health, int damage, int gold)
//         : m_name{ name }
//         , m_symbol{ symbol }
//         , m_health{ health }
//         , m_damage{ damage }
//         , m_gold{ gold }
//     { }
//
//     char getSymbol() const { return m_symbol; }
//     const std::string& getName() const { return m_name; }
//     bool isDead() const { return m_health <= 0; }
//     int getGold() const { return m_gold; }
//     void addGold(int gold) { m_gold += gold; }
//     void reduceHealth(int health) { m_health -= health; }
//     int getHealth() const { return m_health; }
//     int getDamage() const { return m_damage; }
// };
//
// class Player : public Creature
// {
//     int m_level{ 1 };
//
// public:
//     Player(const std::string& name)
//         : Creature{ name, '@', 10, 1, 0 }
//     {
//     }
//
//     void levelUp()
//     {
//         ++m_level;
//         ++m_damage;
//     }
//
//     int getLevel() const { return m_level; }
//     bool hasWon() const { return m_level >= 20; }
// };
//
// class Monster : public Creature
// {
// public:
//     enum Type
//     {
//         dragon,
//         orc,
//         slime,
//         max_types
//     };
//
// private:
//     inline static Creature monsterData[] {
//         Creature { "dragon", 'D', 20, 4, 100 },
//         Creature { "orc", 'o', 4, 2, 25 },
//         Creature { "slime", 's', 1, 1, 10 }
//         };
//
//     static_assert(std::size(monsterData) == max_types);
//
// public:
//     Monster(Type type)
//         : Creature{ monsterData[type] }
//     {
//     }
//
//     static Monster getRandomMonster()
//     {
//         int num{ Random::get(0, max_types - 1) };
//         return Monster{ static_cast<Type>(num) };
//     }
// };
//
// // 这个函数处理玩家攻击怪物
// void attackMonster(Player& player, Monster& monster)
// {
//     // 如果玩家已经死亡，就不能攻击怪物
//     if (player.isDead())
//         return;
//
//     std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";
//
//     // 用玩家的伤害值减少怪物的生命值
//     monster.reduceHealth(player.getDamage());
//
//     // 如果怪物已经死亡，就让玩家升级
//     if (monster.isDead())
//     {
//         std::cout << "You killed the " << monster.getName() << ".\n";
//         player.levelUp();
//         std::cout << "You are now level " << player.getLevel() << ".\n";
//         std::cout << "You found " << monster.getGold() << " gold.\n";
//         player.addGold(monster.getGold());
//     }
// }
//
// // 这个函数处理怪物攻击玩家
// void attackPlayer(const Monster& monster, Player& player)
// {
//     // 如果怪物已经死亡，它就不能攻击玩家
//     if (monster.isDead())
//         return;
//
//     // 用怪物的伤害值减少玩家的生命值
//     player.reduceHealth(monster.getDamage());
//     std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
// }
//
// // 这个函数处理玩家与随机生成的怪物之间的整场战斗
// void fightMonster(Player& player)
// {
//     // 首先随机生成一只怪物
//     Monster monster{ Monster::getRandomMonster() };
//     std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";
//
//     // 只要怪物和玩家都还活着，战斗就继续
//     while (!monster.isDead() && !player.isDead())
//     {
//         std::cout << "(R)un or (F)ight: ";
//         char input{};
//         std::cin >> input;
//         if (input == 'R' || input == 'r')
//         {
//             // 50% 的概率逃跑成功
//             if (Random::get(1, 2) == 1)
//             {
//                 std::cout << "You successfully fled.\n";
//                 return; // 成功即结束这次遭遇
//             }
//             else
//             {
//                 // 逃跑失败时，怪物会对玩家发起一次免费攻击
//                 std::cout << "You failed to flee.\n";
//                 attackPlayer(monster, player);
//                 continue;
//             }
//         }
//
//         if (input == 'F' || input == 'f')
//         {
//             // 玩家先攻击，怪物后攻击
//             attackMonster(player, monster);
//             attackPlayer(monster, player);
//         }
//     }
// }
//
// int main()
// {
//     std::cout << "Enter your name: ";
//     std::string playerName;
//     std::cin >> playerName;
//
//     Player player{ playerName };
//     std::cout << "Welcome, " << player.getName() << '\n';
//
//     // 如果玩家既没死亡也没获胜，游戏继续
//     while (!player.isDead() && !player.hasWon())
//         fightMonster(player);
//
//     // 此时玩家要么已经死亡，要么已经获胜
//     if (player.isDead())
//     {
//         std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n";
//         std::cout << "Too bad you can't take it with you!\n";
//     }
//     else
//     {
//         std::cout << "You won the game with " << player.getGold() << " gold!\n";
//     }
//
//   return 0;
// }

// g) 附加题：
//
// 读者Tom的剑没磨够快，打不过强大的巨龙。请实现下列不同规格的药水来帮助他：

// [表格 3]
//   | 类型 | 效果（小） | 效果（中） | 效果（大）
//   | Health | +2 生命值 | +2 生命值 | +5 生命值
//   | Strength | +1 伤害 | +1 伤害 | +1 伤害
//   | Poison | -1 生命值 | -1 生命值 | -1 生命值

//
// 欢迎自由发挥，添加更多药水或修改它们的效果！
//
// 玩家每次战斗获胜后有30%的概率找到一瓶药水，并可以选择喝或不喝。如果玩家不喝，
// 药水就消失了。在玩家喝下之前，玩家不知道这是什么类型的药水；喝下时会显示药
// 水的类型和规格，并产生相应效果。
//
// 在下面的例子中，玩家找到了一瓶毒药并因喝下它而死亡（本例中毒药的伤害要大得
// 多）：

// [文本/输出]
// You have encountered a slime (s).
// (R)un or (F)ight: f
// You hit the slime for 1 damage.
// You killed the slime.
// You are now level 2.
// You found 10 gold.
// You found a mythical potion! Do you want to drink it? [y/n]: y
// You drank a Medium potion of Poison
// You died at level 2 and with 10 gold.
// Too bad you can't take it with you!


// 【答案 · 显示提示】
// 添加一个Potion类，包含类型和规格两个成员变量，以及一个返回其名称的成员函数，
// 还有一个用于随机创建药水的静态成员函数（类似于`getRandomMonster()`函数）。
// 在Player类中添加一个`drinkPotion()`成员函数，用于施加药水的效果。

// 【答案 · 查看答案】

// [代码 19]
// #include "Random.h" // https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/
// #include <array>
// #include <iostream>
// #include <sstream>
// #include <string>
// #include <string_view>
//
// class Potion
// {
// public:
//     // 所有可能的药水类型
//     enum Type
//     {
//         health,
//         strength,
//         poison,
//
//         // 用于随机生成药水
//         max_type
//     };
//
//     enum Size
//     {
//         small,
//         medium,
//         large,
//
//         max_size
//     };
//
// private:
//     Type m_type{};
//     Size m_size{};
//
// public:
//     Potion(Type type, Size size)
//         : m_type{ type },
//         m_size{ size }
//     {
//     }
//
//     Type getType() const { return m_type; }
//     Size getSize() const { return m_size; }
//
//     // 药水名称是编译期字面值，我们可以
//     // 返回 std::string_view。
//     static std::string_view getPotionTypeName(Type type)
//     {
//         static constexpr std::string_view names[] {
//           "Health",
//           "Strength",
//           "Poison"
//         };
//
//         return names[type];
//     }
//
//     static std::string_view getPotionSizeName(Size size)
//     {
//         static constexpr std::string_view names[] {
//           "Small",
//           "Medium",
//           "Large"
//         };
//
//         return names[size];
//     }
//
//     std::string getName() const
//     {
//         // 这里使用了 std::stringstream，但这也可以用
//         // std::string.
//         // 我们第一次使用 std::stringstream 是在「7.13」。
//         std::stringstream result{};
//
//         result << getPotionSizeName(getSize()) << " potion of " << getPotionTypeName(getType());
//
//         // 可以用 str() 从 std::stringstream 中取出字符串
//         // 成员函数。
//         return result.str();
//     }
//
//     static Potion getRandomPotion()
//     {
//         return Potion{
//           static_cast<Type>(Random::get(0, max_type - 1)),
//           static_cast<Size>(Random::get(0, max_size - 1))
//         };
//     }
// };
//
// class Creature
// {
// protected:
//     std::string m_name;
//     char m_symbol {};
//     int m_health {};
//     int m_damage {};
//     int m_gold {};
//
// public:
//      Creature(std::string_view name, char symbol, int health, int damage, int gold)
//         : m_name{ name }
//         , m_symbol{ symbol }
//         , m_health{ health }
//         , m_damage{ damage }
//         , m_gold{ gold }
//     { }
//
//     char getSymbol() const { return m_symbol; }
//     const std::string& getName() const { return m_name; }
//     bool isDead() const { return m_health <= 0; }
//     int getGold() const { return m_gold; }
//     void addGold(int gold) { m_gold += gold; }
//     void reduceHealth(int health) { m_health -= health; }
//     int getHealth() const { return m_health; }
//     int getDamage() const { return m_damage; }
// };
//
// class Player : public Creature
// {
//     int m_level{ 1 };
//
// public:
//     Player(const std::string& name)
//         : Creature{ name, '@', 10, 1, 0 }
//     {
//     }
//
//     void levelUp()
//     {
//         ++m_level;
//         ++m_damage;
//     }
//
//     // 把药水的效果施加到玩家身上
//     void drinkPotion(const Potion& potion)
//     {
//         switch (potion.getType())
//         {
//         case Potion::health:
//             // 只有治疗药水的规格会影响它的效力。其他
//             // 药水的效力与规格无关。
//             m_health += ((potion.getSize() == Potion::large) ? 5 : 2);
//             break;
//         case Potion::strength:
//             ++m_damage;
//             break;
//         case Potion::poison:
//             reduceHealth(1);
//             break;
//             // 显式处理 max_type 以消除编译器警告。不要使用 default:
//             // 因为我们希望以后新增药水却
//             // 却忘记实现它的效果时，编译器能给出警告。
//         case Potion::max_type:
//             break;
//         }
//     }
//
//     int getLevel() const { return m_level; }
//     bool hasWon() const { return m_level >= 20; }
// };
//
// class Monster : public Creature
// {
// public:
//     enum Type
//     {
//         dragon,
//         orc,
//         slime,
//         max_types
//     };
//
// private:
//     inline static Creature monsterData[] {
//         Creature { "dragon", 'D', 20, 4, 100 },
//         Creature { "orc", 'o', 4, 2, 25 },
//         Creature { "slime", 's', 1, 1, 10 }
//         };
//
//     static_assert(std::size(monsterData) == max_types);
//
// public:
//     Monster(Type type)
//         : Creature{ monsterData[type] }
//     {
//     }
//
//     static Monster getRandomMonster()
//     {
//         int num{ Random::get(0, max_types - 1) };
//         return Monster{ static_cast<Type>(num) };
//     }
// };
//
// // 我们把这部分从 attackMonster() 中移出来，让函数更短。
// void onMonsterKilled(Player& player, const Monster& monster)
// {
//     std::cout << "You killed the " << monster.getName() << ".\n";
//     player.levelUp();
//     std::cout << "You are now level " << player.getLevel() << ".\n";
//     std::cout << "You found " << monster.getGold() << " gold.\n";
//     player.addGold(monster.getGold());
//
//     // 30% 的概率找到一瓶药水
//     constexpr int potionChance{ 30 };
//     if (Random::get(1, 100) <= potionChance)
//     {
//         // 随机生成一瓶药水
//         auto potion{ Potion::getRandomPotion() };
//
//         std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";
//         char choice{};
//         std::cin >> choice;
//
//         if (choice == 'Y' || choice == 'y')
//         {
//             // 施加效果
//             player.drinkPotion(potion);
//             // 揭示药水的类型和规格
//             std::cout << "You drank a " << potion.getName() << ".\n";
//         }
//     }
// }
//
// // 这个函数处理玩家攻击怪物
// void attackMonster(Player& player, Monster& monster)
// {
//     // 如果玩家已经死亡，就不能攻击怪物
//     if (player.isDead())
//         return;
//
//     std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";
//
//     // 用玩家的伤害值减少怪物的生命值
//     monster.reduceHealth(player.getDamage());
//
//     // 如果怪物已经死亡，就让玩家升级
//     if (monster.isDead())
//     {
//         // 给玩家奖励
//         onMonsterKilled(player, monster);
//     }
// }
//
// // 这个函数处理怪物攻击玩家
// void attackPlayer(const Monster& monster, Player& player)
// {
//     // 如果怪物已经死亡，它就不能攻击玩家
//     if (monster.isDead())
//         return;
//
//     // 用怪物的伤害值减少玩家的生命值
//     player.reduceHealth(monster.getDamage());
//     std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
// }
//
// // 这个函数处理玩家与随机生成的怪物之间的整场战斗
// void fightMonster(Player& player)
// {
//     // 首先随机生成一只怪物
//     Monster monster{ Monster::getRandomMonster() };
//     std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";
//
//     // 只要怪物和玩家都还活着，战斗就继续
//     while (!monster.isDead() && !player.isDead())
//     {
//         std::cout << "(R)un or (F)ight: ";
//         char input{};
//         std::cin >> input;
//         if (input == 'R' || input == 'r')
//         {
//             // 50% 的概率逃跑成功
//             if (Random::get(1, 2) == 1)
//             {
//                 std::cout << "You successfully fled.\n";
//                 return; // 成功即结束这次遭遇
//             }
//             else
//             {
//                 // 逃跑失败时，怪物会对玩家发起一次免费攻击
//                 std::cout << "You failed to flee.\n";
//                 attackPlayer(monster, player);
//                 continue;
//             }
//         }
//
//         if (input == 'F' || input == 'f')
//         {
//             // 玩家先攻击，怪物后攻击
//             attackMonster(player, monster);
//             attackPlayer(monster, player);
//         }
//     }
// }
//
// int main()
// {
//     std::cout << "Enter your name: ";
//     std::string playerName;
//     std::cin >> playerName;
//
//     Player player{ playerName };
//     std::cout << "Welcome, " << player.getName() << '\n';
//
//     // 如果玩家既没死亡也没获胜，游戏继续
//     while (!player.isDead() && !player.hasWon())
//         fightMonster(player);
//
//     // 此时玩家要么已经死亡，要么已经获胜
//     if (player.isDead())
//     {
//         std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n";
//         std::cout << "Too bad you can't take it with you!\n";
//     }
//     else
//     {
//         std::cout << "You won the game with " << player.getGold() << " gold!\n";
//     }
//
//   return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Base
{
public:
	Base()
	{
		std::cout << "Base()\n";
	}
	~Base()
	{
		std::cout << "~Base()\n";
	}
};

class Derived: public Base
{
public:
	Derived()
	{
		std::cout << "Derived()\n";
	}
	~Derived()
	{
		std::cout << "~Derived()\n";
	}
};

int main()
{
	Derived d;

	return 0;
}
