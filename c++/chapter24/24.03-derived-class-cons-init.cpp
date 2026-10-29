// ==========================================================================
// 24.3 派生类的构造函数与初始化
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十四章 继承
// 原文: https://www.studycpp.cn/basic/chapter24/derived-class-cons-init/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "24.03-derived-class-cons-init.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 初始化基类成员
//   · 将成员变量设置为private
//   · 另一个例子
//   · 继承链
//   · 析构函数
//   · 总结
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 在过去的两节课中，我们探讨了C++继承的一些基础知识以及派生类的初始化顺序。在
// 本课中，我们将更仔细地了解派生类初始化中的构造函数。这里继续使用上一课中开
// 发的简单Base和Derived类：

// [代码 1]
// class Base
// {
// public:
//     int m_id {};
//
//     Base(int id=0)
//         : m_id{ id }
//     {
//     }
//
//     int getId() const { return m_id; }
// };
//
// class Derived: public Base
// {
// public:
//     double m_cost {};
//
//     Derived(double cost=0.0)
//         : m_cost{ cost }
//     {
//     }
//
//     double getCost() const { return m_cost; }
// };

// 对于非派生类，构造函数只需初始化自己的成员。例如，考虑Base。可以如下所示创
// 建Base对象：

// [代码 2]
// int main()
// {
//     Base base{ 5 }; // 使用 Base(int) 构造函数
//
//     return 0;
// }

// 下面是实例化base时实际发生的情况：
// - 内存分配
// - 找到合适的构造函数
// - 对成员变量进行列表初始化
// - 构造函数体中的代码被执行
// - 实例化完成，构造函数返回
//
// 这很简单。对于派生类，事情稍微复杂一些：

// [代码 3]
// int main()
// {
//     Derived derived{ 1.3 }; // 使用 Derived(double) 构造函数
//
//     return 0;
// }

// 下面是实例化derived时实际发生的情况：
// - 分配内存（需要能装下Base和Derived部分）
// - 找到合适的Derived构造函数
// - Base部分使用对应的Base构造函数进行构造。如果没有显式声明的构造函数，则使
//   用默认构造函数。
// - 对成员变量进行列表初始化
// - 构造函数体中的代码被执行
// - 实例化完成，构造函数返回
//
// 这种情况和无继承情况之间唯一真正的区别是，在派生类构造函数做任何实质性工作
// 之前，必须先调用基类构造函数。Base构造函数会设置对象的Base部分，然后将控制
// 权返回给派生类构造函数，此时派生类构造函数才可以完成自己的工作。
//

// ―――― 初始化基类成员 ――――

// 我们当前编写的Derived类有一个缺点：创建Derived对象时无法初始化m_id。如果在
// 创建派生对象时，需要同时设置m_cost（来自对象的Derived部分）和m_id（来自对象
// 的Base部分），该怎么办？
//
// 新程序员通常会尝试如下方式解决此问题：

// [代码 4]
// class Derived: public Base
// {
// public:
//     double m_cost {};
//
//     Derived(double cost=0.0, int id=0)
//         // 无法工作
//         : m_cost{ cost }
//         , m_id{ id }
//     {
//     }
//
//     double getCost() const { return m_cost; }
// };

// 这是一个不错的尝试，思路也几乎正确。我们确实需要向构造函数中添加另一个参数，
// 否则C++无法知道要将m_id初始化为什么值。
//
// 然而，C++不允许在构造函数的成员初始化列表中设置继承来的成员变量。换句话说，
// 成员变量的值只能在该变量所属类的构造函数成员初始化列表中设置。
//
// C++为什么要这样做？答案与常量和引用变量有关。考虑如果m_id是常量会发生什么？
// 由于常量必须在创建时用值初始化，因此基类构造函数必须在创建变量时设置其值。
// 然而，当基类构造函数完成后，派生类构造函数的成员初始化列表随后会被执行。这
// 样，每个派生类都有机会修改该变量，并可能更改其值！通过将变量的初始化限制在
// 变量所属类的构造函数中，C++确保所有变量只初始化一次。
//
// 最终结果是，上面的示例无法工作，因为m_id是从Base继承来的，而成员初始化列表
// 中只能初始化非继承而来的变量。
//
// 然而，继承而来的变量仍然可以在构造函数主体中更改其值。因此，新程序员也经常
// 尝试这样做：

// [代码 5]
// class Derived: public Base
// {
// public:
//     double m_cost {};
//
//     Derived(double cost=0.0, int id=0)
//         : m_cost{ cost }
//     {
//         m_id = id;
//     }
//
//     double getCost() const { return m_cost; }
// };

// 虽然在这种情况下这实际上是可行的，但如果m_id是常量或引用，则无法工作（因为
// 常量值和引用必须在构造函数的成员初始化列表中初始化）。它也不够高效，因为
// m_id被设置了两次：一次在基类构造函数的成员初始化列表中，一次在派生类构造函
// 数的主体中。最后，如果基类在构造期间需要使用该值，该怎么办？它将无法访问正
// 确的值，因为该值直到Derived构造函数执行时才被设置（这几乎是最后发生的事情）。
//
// 那么，在创建派生类对象时，如何正确初始化m_id？
//
// 在迄今为止的所有示例中，当我们实例化Derived类对象时，Base部分都是使用默认的
// Base构造函数创建的。为什么它总是使用默认的Base构造函数？因为我们从来没有告
// 诉它使用别的构造函数！
//
// 幸运的是，C++允许我们显式选择要调用哪个基类构造函数！为此，只需在派生类的成
// 员初始化列表中添加对基类构造函数的调用：

// [代码 6]
// class Derived: public Base
// {
// public:
//     double m_cost {};
//
//     Derived(double cost=0.0, int id=0)
//         : Base{ id } // 使用 id 调用 Base(int) 构造函数!
//         , m_cost{ cost }
//     {
//     }
//
//     double getCost() const { return m_cost; }
// };

// 现在，当我们执行此代码时：

// [代码 7]
// #include <iostream>
//
// int main()
// {
//     Derived derived{ 1.3, 5 }; // 使用 Derived(double, int) 构造函数
//     std::cout << "Id: " << derived.getId() << '\n';
//     std::cout << "Cost: " << derived.getCost() << '\n';
//
//     return 0;
// }

// 基类构造函数 Base(int) 用于将m_id初始化为5，派生类构造函数用于将m_cost初始
// 化为1.3！
//
// 因此，程序将打印：

// [文本/输出]
// Id: 5
// Cost: 1.3

// 更详细地说，下面是发生的情况：
// - 分配derived的内存
// - Derived(double, int) 构造函数被调用，cost = 1.3, id = 5.
// - 编译器看到，这里调用基类的构造函数 Base(int)，id = 5
// - 基类构造函数执行成员初始化列表，将 m_id 设置为 5
// - 基类构造函数的函数体执行，这里为空，不发生任何事情
// - 从基类构造函数返回
// - 派生类构造函数执行成员初始化列表，将 m_cost 设置为 1.3
// - 派生类构造函数的函数体执行，这里为空，不发生任何事情
// - 派生类构造函数返回
//
// 这看起来有点复杂，但实际上非常简单。发生的事情只是：Derived构造函数正在调用
// 特定的Base构造函数来初始化对象的Base部分。由于m_id位于对象的Base部分，因此
// Base构造函数是唯一可以且应该初始化该值的构造函数。
//
// 注意，在Derived构造函数成员初始化列表中的何处调用Base构造函数并不重要——它总
// 是首先执行。
//

// ―――― 将成员变量设置为private ――――

// 我们已经知道了如何初始化基类成员，现在就没有必要再将成员变量保持为public。
// 我们再次将成员变量设置为private，这也是更合适的做法。
//
// 任何人都可以访问public成员。private成员只能由同一类的成员函数访问。注意，这
// 意味着派生类不能直接访问基类的private成员！派生类需要使用访问函数来访问基类
// 的私有成员。
//
// 参考以下示例：

// [代码 8]
// #include <iostream>
//
// class Base
// {
// private: // 成员现在设置为 private
//     int m_id {};
//
// public:
//     Base(int id=0)
//         : m_id{ id }
//     {
//     }
//
//     int getId() const { return m_id; }
// };
//
// class Derived: public Base
// {
// private: // 成员现在是 private
//     double m_cost;
//
// public:
//     Derived(double cost=0.0, int id=0)
//         : Base{ id } // 使用 id 调用 Base(int) 构造函数
//         , m_cost{ cost }
//     {
//     }
//
//     double getCost() const { return m_cost; }
// };
//
// int main()
// {
//     Derived derived{ 1.3, 5 }; // 使用 Derived(double, int) 构造函数
//     std::cout << "Id: " << derived.getId() << '\n';
//     std::cout << "Cost: " << derived.getCost() << '\n';
//
//     return 0;
// }

// 在上面的代码中，我们将m_id和m_cost设置为private。这很好，因为我们使用相应的
// 构造函数来初始化它们，并使用public访问函数来获取值。
//
// 按预期打印：

// [文本/输出]
// Id: 5
// Cost: 1.3

// 在下一课中，我们将详细讨论访问说明符。
//

// ―――― 另一个例子 ――――

// 让我们看一看以前使用过的另一个类：

// [代码 9]
// #include <string>
// #include <string_view>
//
// class Person
// {
// public:
//     std::string m_name;
//     int m_age {};
//
//     Person(std::string_view name = "", int age = 0)
//         : m_name{ name }, m_age{ age }
//     {
//     }
//
//     const std::string& getName() const { return m_name; }
//     int getAge() const { return m_age; }
// };
//
// // BaseballPlayer public 继承 Person
// class BaseballPlayer : public Person
// {
// public:
//     double m_battingAverage {};
//     int m_homeRuns {};
//
//     BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
//        : m_battingAverage{ battingAverage },
//          m_homeRuns{ homeRuns }
//     {
//     }
// };

// 按照之前的写法，BaseballPlayer只初始化自己的成员，而不指定要使用的Person构
// 造函数。这意味着我们创建的每个BaseballPlayer都会使用默认的Person构造函数，
// 该构造函数会将m_name初始化为空，将m_age初始化为0。因为在创建棒球运动员时指
// 定姓名和年龄是有意义的，所以我们应该修改此构造函数并添加这些参数。
//
// 下面是使用私有成员更新后的类，其中BaseballPlayer类会调用适当的Person构造函
// 数来初始化继承而来的Person成员变量：

// [代码 10]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Person
// {
// private:
//     std::string m_name;
//     int m_age {};
//
// public:
//     Person(std::string_view name = "", int age = 0)
//         : m_name{ name }, m_age{ age }
//     {
//     }
//
//     const std::string& getName() const { return m_name; }
//     int getAge() const { return m_age; }
//
// };
// // BaseballPlayer public 继承 Person
// class BaseballPlayer : public Person
// {
// private:
//     double m_battingAverage {};
//     int m_homeRuns {};
//
// public:
//     BaseballPlayer(std::string_view name = "", int age = 0,
//         double battingAverage = 0.0, int homeRuns = 0)
//         : Person{ name, age } // 调用 Person(std::string_view, int) 来初始化对应的成员
//         , m_battingAverage{ battingAverage }, m_homeRuns{ homeRuns }
//     {
//     }
//
//     double getBattingAverage() const { return m_battingAverage; }
//     int getHomeRuns() const { return m_homeRuns; }
// };

// 现在我们可以创建这样的BaseballPlayer：

// [代码 11]
// #include <iostream>
//
// int main()
// {
//     BaseballPlayer pedro{ "Pedro Cerrano", 32, 0.342, 42 };
//
//     std::cout << pedro.getName() << '\n';
//     std::cout << pedro.getAge() << '\n';
//     std::cout << pedro.getBattingAverage() << '\n';
//     std::cout << pedro.getHomeRuns() << '\n';
//
//     return 0;
// }

// 输出：

// [文本/输出]
// Pedro Cerrano
// 32
// 0.342
// 42

// 正如您所看到的，基类中的姓名和年龄已经正确初始化，派生类中的
// m_battingAverage和m_homeRuns也是如此。
//

// ―――― 继承链 ――――

// 继承链中的类也以完全相同的方式工作。

// [代码 12]
// #include <iostream>
//
// class A
// {
// public:
//     A(int a)
//     {
//         std::cout << "A: " << a << '\n';
//     }
// };
//
// class B: public A
// {
// public:
//     B(int a, double b)
//     : A{ a }
//     {
//         std::cout << "B: " << b << '\n';
//     }
// };
//
// class C: public B
// {
// public:
//     C(int a, double b, char c)
//     : B{ a, b }
//     {
//         std::cout << "C: " << c << '\n';
//     }
// };
//
// int main()
// {
//     C c{ 5, 4.3, 'R' };
//
//     return 0;
// }

// 在这个例子中，类C从类B派生，类B又从类A派生。那么，当我们实例化类C的对象时会
// 发生什么呢？
//
// 首先，main()调用C(int, double, char)。C构造函数调用B(int, double)。B构造函
// 数调用A(int)。因为A没有从任何类继承，所以它是第一个要构造的类。构造A，打印
// 值5，并返回给B。构造B，打印值4.3，并将控制权返回给C。构造C，打印值“R”，然后
// 将控制权返回到main()。至此结束！
//
// 因此，该程序打印：

// [文本/输出]
// A: 5
// B: 4.3
// C: R

// 值得一提的是，构造函数只能调用其直接父类的构造函数。因此，C构造函数不能直接
// 调用A构造函数，也不能直接向A构造函数传递参数。C构造函数只能调用B构造函数（
// 由B负责调用A构造函数）。
//

// ―――― 析构函数 ――――

// 当派生类被销毁时，各个析构函数会以与构造相反的顺序调用。在上面的例子中，当c
// 被销毁时，首先调用C析构函数，然后调用B析构函数和A析构函数。
//
// 警告
//
// 如果基类具有虚函数，则析构函数也应该是虚函数；否则在某些情况下会导致未定义
// 行为。
//

// ―――― 总结 ――――

// 构造派生类时，派生类构造函数负责确定调用哪个基类构造函数。如果未指定基类构
// 造函数，则会使用默认的基类构造函数。在这种情况下，如果找不到默认基类构造函
// 数，编译器将报错。随后，构造会按照从最初的基类到最终派生类的顺序执行。
//
// 现在，您已经足够了解C++继承，可以创建自己的继承类了！
//

// ―――― 习题 ――――


// ▼ 问题 1
// 来实现我们在继承简介中提到的Fruit例子。创建一个Fruit基类，包含两个私有成员：
// 名字（std::string）和颜色（std::string）。创建一个继承自Fruit的Apple类，
// Apple要额外增加一个私有成员：纤维含量（double）。再创建一个同样继承自Fruit
// 的Banana类，Banana没有额外的成员。
//
// 下面这个程序应当能够运行：

// [代码 13]
// #include <iostream>
//
// int main()
// {
// 	const Apple a{ "Red delicious", "red", 4.2 };
// 	std::cout << a << '\n';
//
// 	const Banana b{ "Cavendish", "yellow" };
// 	std::cout << b << '\n';
//
// 	return 0;
// }

// 并打印：

// [文本/输出]
// Apple(Red delicious, red, 4.2)
// Banana(Cavendish, yellow)

// 提示：由于a和b都是const，需要注意const的正确性。确保你的形参和函数都恰当地
// 加了const。

// 【答案 · 查看答案】

// [代码 14]
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
//
// };
//
// class Apple : public Fruit
// {
// private:
// 	double m_fiber;
//
// public:
// 	Apple(std::string_view name, std::string_view color, double fiber)
// 		:Fruit{ name, color },
// 		m_fiber{ fiber }
// 	{
// 	}
//
// 	double getFiber() const { return m_fiber; }
//
// };
//
// std::ostream& operator<<(std::ostream& out, const Apple& a)
// {
// 	out << "Apple(" << a.getName() << ", " << a.getColor() << ", " << a.getFiber() << ')';
// 	return out;
// }
//
// class Banana : public Fruit
// {
// public:
// 	Banana(std::string_view name, std::string_view color)
// 		:Fruit{ name, color }
// 	{
// 	}
// };
//
// std::ostream& operator<<(std::ostream& out, const Banana& b)
// {
// 	out << "Banana(" << b.getName() << ", " << b.getColor() << ')';
// 	return out;
// }
//
// int main()
// {
// 	const Apple a{ "Red delicious", "red", 4.2 };
// 	std::cout << a << '\n';
//
// 	const Banana b{ "Cavendish", "yellow" };
// 	std::cout << b << '\n';
//
// 	return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Base
{
private: // 成员现在设置为 private
    int m_id {};

public:
    Base(int id=0)
        : m_id{ id }
    {
    }

    int getId() const { return m_id; }
};

class Derived: public Base
{
private: // 成员现在是 private
    double m_cost;

public:
    Derived(double cost=0.0, int id=0)
        : Base{ id } // 使用 id 调用 Base(int) 构造函数
        , m_cost{ cost }
    {
    }

    double getCost() const { return m_cost; }
};

int main()
{
    Derived derived{ 1.3, 5 }; // 使用 Derived(double, int) 构造函数
    std::cout << "Id: " << derived.getId() << '\n';
    std::cout << "Cost: " << derived.getCost() << '\n';

    return 0;
}
