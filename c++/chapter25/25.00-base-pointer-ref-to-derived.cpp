// ==========================================================================
// 25.0 指向派生对象的基类指针和引用
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十五章 虚函数
// 原文: https://www.studycpp.cn/basic/chapter25/base-pointer-ref-to-derived/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "25.00-base-pointer-ref-to-derived.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 指针、引用和派生类
//   · 使用指向基类的指针和引用
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 在前一章中，我们学习了如何使用继承从现有类派生新类。在本章中，我们将关注继
// 承中最重要、最强大的方面之一——虚函数。
//
// 但在讨论什么是虚函数之前，让我们首先看看为什么需要虚函数。
//
// 在创建派生类时，它由多个部分组成：继承自基类的部分，以及自身新增的部分。
//
// 例如，这里有一个简单的例子：

// [代码 1]
// #include <string_view>
//
// class Base
// {
// protected:
//     int m_value {};
//
// public:
//     Base(int value)
//         : m_value{ value }
//     {
//     }
//
//     std::string_view getName() const { return "Base"; }
//     int getValue() const { return m_value; }
// };
//
// class Derived: public Base
// {
// public:
//     Derived(int value)
//         : Base{ value }
//     {
//     }
//
//     std::string_view getName() const { return "Derived"; }
//     int getValueDoubled() const { return m_value * 2; }
// };

// 当我们创建 Derived 对象时，它包含 Base 部分（先构造）和 Derived 部分（后构
// 造）。记住，继承意味着两个类之间存在 is-a 关系。由于 Base 是基类，因此
// Derived 包含 Base 部分是合理的。
//

// ―――― 指针、引用和派生类 ――――

// 很容易理解，我们可以创建指向派生对象的指针和引用：

// [代码 2]
// #include <iostream>
//
// int main()
// {
//     Derived derived{ 5 };
//     std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
//
//     Derived& rDerived{ derived };
//     std::cout << "rDerived is a " << rDerived.getName() << " and has value " << rDerived.getValue() << '\n';
//
//     Derived* pDerived{ &derived };
//     std::cout << "pDerived is a " << pDerived->getName() << " and has value " << pDerived->getValue() << '\n';
//
//     return 0;
// }

// 这会产生如下输出：

// [文本/输出]
// derived is a Derived and has value 5
// rDerived is a Derived and has value 5
// pDerived is a Derived and has value 5

// 然而，由于 Derived 有一个 Base 部分，一个更有趣的问题是：C++ 是否允许我们创
// 建指向 Derived 对象的 Base 指针或引用？事实证明，是可以的。

// [代码 3]
// #include <iostream>
//
// int main()
// {
//     Derived derived{ 5 };
//
//     // 下面都是合法的!
//     Base& rBase{ derived }; // rBase 是 左值引用
//     Base* pBase{ &derived };
//
//     std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
//     std::cout << "rBase is a " << rBase.getName() << " and has value " << rBase.getValue() << '\n';
//     std::cout << "pBase is a " << pBase->getName() << " and has value " << pBase->getValue() << '\n';
//
//     return 0;
// }

// 这会产生如下结果：

// [文本/输出]
// derived is a Derived and has value 5
// rBase is a Base and has value 5
// pBase is a Base and has value 5

// 这个结果可能并不是您最初期望的那样！
//
// 由于 rBase 和 pBase 是 Base 引用和指针，因此它们只能看到 Base 的成员（或
// Base 继承来的成员）。即使派生对象的 Derived::getName() 隐藏了
// Base::getName()，它们也仍然会调用 Base::getName()。这就是 rBase 和 pBase 表
// 现为 Base 而不是 Derived 的原因。
//
// 请注意，这也意味着不能使用rBase或pBase调用Derived::getValueDoubled()。它们
// 看不到 Derived 中的任何成员。
//
// 这里还有一个稍微复杂一些的示例，我们将在下一课中继续使用：

// [代码 4]
// #include <iostream>
// #include <string_view>
// #include <string>
//
// class Animal
// {
// protected:
//     std::string m_name;
//
//     // 将构造函数设置为 protected
//     // 因为我们不想Animal被直接构造
//     // 但是派生类仍然可以使用
//     Animal(std::string_view name)
//         : m_name{ name }
//     {
//     }
//
//     Animal(const Animal&) = delete;
//     Animal& operator=(const Animal&) = delete;
//
// public:
//     std::string_view getName() const { return m_name; }
//     std::string_view speak() const { return "???"; }
// };
//
// class Cat: public Animal
// {
// public:
//     Cat(std::string_view name)
//         : Animal{ name }
//     {
//     }
//
//     std::string_view speak() const { return "Meow"; }
// };
//
// class Dog: public Animal
// {
// public:
//     Dog(std::string_view name)
//         : Animal{ name }
//     {
//     }
//
//     std::string_view speak() const { return "Woof"; }
// };
//
// int main()
// {
//     const Cat cat{ "Fred" };
//     std::cout << "cat is named " << cat.getName() << ", and it says " << cat.speak() << '\n';
//
//     const Dog dog{ "Garbo" };
//     std::cout << "dog is named " << dog.getName() << ", and it says " << dog.speak() << '\n';
//
//     const Animal* pAnimal{ &cat };
//     std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';
//
//     pAnimal = &dog;
//     std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';
//
//     return 0;
// }

// 这会产生如下结果：

// [文本/输出]
// cat is named Fred, and it says Meow
// dog is named Garbo, and it says Woof
// pAnimal is named Fred, and it says ???
// pAnimal is named Garbo, and it says ???

// 这里出现了同样的问题。因为 pAnimal 是一个 Animal 指针，所以它只能看到对象中
// 的 Animal 部分。因此，pAnimal->speak() 会调用 Animal::speak。
//

// ―――― 使用指向基类的指针和引用 ――――

// 现在您可能会说：“上面的示例似乎有点奇怪。既然已经有派生对象了，为什么还要创
// 建指向它的基类指针或引用？”事实证明，这样做有许多充分的理由。
//
// 首先，假设您想编写一个打印动物名称和声音的函数。如果不使用指向基类的指针或
// 引用，就必须通过函数重载来实现，例如：

// [代码 5]
// void report(const Cat& cat)
// {
//     std::cout << cat.getName() << " says " << cat.speak() << '\n';
// }
//
// void report(const Dog& dog)
// {
//     std::cout << dog.getName() << " says " << dog.speak() << '\n';
// }

// 这看起来很简单，但如果有 30 种不同的动物会怎样？你必须编写 30 个几乎相同的
// 函数！另外，如果你添加了一种新的动物，你也必须为它编写一个新函数。考虑到唯
// 一真正的区别是参数的类型，这会浪费大量时间。
//
// 而且，由于猫和狗都是从 Animal 派生出来的，猫和狗对象中都包含 Animal 部分。
// 因此，我们应该能够做这样的事情：

// [代码 6]
// void report(const Animal& rAnimal)
// {
//     std::cout << rAnimal.getName() << " says " << rAnimal.speak() << '\n';
// }

// 这将允许我们传入任何从 Animal 派生的类，甚至是我们在编写函数后创建的类！这
// 样就不需要为每个派生类各写一个函数，而是只用一个函数处理所有从 Animal 派生
// 的类！
//
// 当然，问题是，由于 rAnimal 是一个 Animal 引用，因此 rAnimal.speak() 将调用
// Animal::speak。
//
// 其次，假设您有 3 只猫和 3 只狗，并希望将它们放在一个数组中以便访问。由于数
// 组只能保存一种类型的对象，如果没有指向基类的指针或引用，您就必须为每个派生
// 类型创建不同的数组，如下所示：

// [代码 7]
// #include <array>
// #include <iostream>
//
// // 上面例子中的 Cat 和 Dog
//
// int main()
// {
//     const auto& cats{ std::to_array<Cat>({{ "Fred" }, { "Misty" }, { "Zeke" }}) };
//     const auto& dogs{ std::to_array<Dog>({{ "Garbo" }, { "Pooky" }, { "Truffle" }}) };
//
//     // 在 C++20 以前
//     // const std::array<Cat, 3> cats{{ { "Fred" }, { "Misty" }, { "Zeke" } }};
//     // const std::array<Dog, 3> dogs{{ { "Garbo" }, { "Pooky" }, { "Truffle" } }};
//
//     for (const auto& cat : cats)
//     {
//         std::cout << cat.getName() << " says " << cat.speak() << '\n';
//     }
//
//     for (const auto& dog : dogs)
//     {
//         std::cout << dog.getName() << " says " << dog.speak() << '\n';
//     }
//
//     return 0;
// }

// 现在，考虑一下如果你有 30 种不同类型的动物会发生什么。你需要 30 个数组，每
// 种动物一个！然而，由于猫和狗都是从 Animal 派生而来的，因此我们应该能够这样
// 做：

// [代码 8]
// #include <array>
// #include <iostream>
//
// // 上面例子中的 Cat 和 Dog
//
// int main()
// {
//     const Cat fred{ "Fred" };
//     const Cat misty{ "Misty" };
//     const Cat zeke{ "Zeke" };
//
//     const Dog garbo{ "Garbo" };
//     const Dog pooky{ "Pooky" };
//     const Dog truffle{ "Truffle" };
//
//     // 存储指向动物的数组，里面装着指向Cat和Dog的指针
//     const auto animals{ std::to_array<const Animal*>({&fred, &garbo, &misty, &pooky, &truffle, &zeke }) };
//
//     // 在 C++20 前, 数组大小需要显式指定
//     // const std::array<const Animal*, 6> animals{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };
//
//     for (const auto animal : animals)
//     {
//         std::cout << animal->getName() << " says " << animal->speak() << '\n';
//     }
//
//     return 0;
// }

// 在编译和执行时，不幸的是，数组 “animals” 的每个元素都是指向 Animal 的指针，
// 这意味着 animal->speak() 将调用 Animal::speak。
//
// 输出为：

// [文本/输出]
// Fred says ???
// Garbo says ???
// Misty says ???
// Pooky says ???
// Truffle says ???
// Zeke says ???

// 这两种技术都可以为我们节省大量的时间和精力，但它们有相同的问题。基类的指针
// 或引用会调用函数的基类版本，而不是派生类版本。我们需要某种机制，让这些基类
// 指针或引用调用函数的派生类版本，而不是基类版本。
//
// 现在，想猜一猜虚函数是用于什么目的？
//

// ―――― 习题 ――――


// ▼ 问题 1
// 上面Animal/Cat/Dog的例子没有按我们期望的方式工作，因为指向Animal的引用或指
// 针无法访问派生版本的`speak()`，从而无法为Cat或Dog返回正确的值。绕过这个问题
// 的一种方法是：把`speak()`函数返回的数据作为Animal基类的一部分（就像Animal的
// 名字可以通过成员`m_name`访问那样）。
//
// 请更新上面这节课中的Animal、Cat和Dog类，为Animal添加一个新成员`m_speak`，并
// 恰当地初始化它。下面这个程序应当能够正确工作：

// [代码 9]
// #include <array>
// #include <iostream>
//
// int main()
// {
//     const Cat fred{ "Fred" };
//     const Cat misty{ "Misty" };
//     const Cat zeke{ "Zeke" };
//
//     const Dog garbo{ "Garbo" };
//     const Dog pooky{ "Pooky" };
//     const Dog truffle{ "Truffle" };
//
//     // 建立一个指向动物的指针数组，并让这些指针指向我们的 Cat 和 Dog 对象
//     const auto animals{ std::to_array<const Animal*>({ &fred, &garbo, &misty, &pooky, &truffle, &zeke }) };
//
//     // C++20 之前，显式指定数组大小
//     // const std::array<const Animal*, 6> animals{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };
//
//     for (const auto animal : animals)
//     {
//         std::cout << animal->getName() << " says " << animal->speak() << '\n';
//     }
//
//     return 0;
// }


// 【答案 · 查看答案】

// [代码 10]
// #include <array>
// #include <string>
// #include <string_view>
// #include <iostream>
//
// class Animal
// {
// protected:
//     std::string m_name;
//     std::string m_speak;
//
//     // 我们把这个构造函数声明为 protected，因为
//     // 我们不希望别人直接创建 Animal 对象，
//     // 但仍希望派生类能够使用它。
//     Animal(std::string_view name, std::string_view speak)
//         : m_name{ name }, m_speak{ speak }
//     {
//     }
//
//     // 为了防止对象切割（后续会讲到）
//     Animal(const Animal&) = delete;
//     Animal& operator=(const Animal&) = delete;
//
// public:
//     std::string_view getName() const { return m_name; }
//     std::string_view speak() const { return m_speak; }
// };
//
// class Cat: public Animal
// {
// public:
//     Cat(std::string_view name)
//         : Animal{ name, "Meow" }
//     {
//     }
// };
//
// class Dog: public Animal
// {
// public:
//     Dog(std::string_view name)
//         : Animal{ name, "Woof" }
//     {
//     }
// };
//
// int main()
// {
//     const Cat fred{ "Fred" };
//     const Cat misty{ "Misty" };
//     const Cat zeke{ "Zeke" };
//
//     const Dog garbo{ "Garbo" };
//     const Dog pooky{ "Pooky" };
//     const Dog truffle{ "Truffle" };
//
//     // 建立一个指向动物的指针数组，并让这些指针指向我们的 Cat 和 Dog 对象
//     const auto animals{ std::to_array<const Animal*>({ &fred, &garbo, &misty, &pooky, &truffle, &zeke }) };
//
//     // C++20 之前，显式指定数组大小
//     // const std::array<const Animal*, 6> animals{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };
//
//     // animal 不是引用，因为我们是在遍历指针
//     for (const auto animal : animals)
//     {
//         std::cout << animal->getName() << " says " << animal->speak() << '\n';
//     }
//
//     return 0;
// }


// ▼ 问题 2
// 上面这种方案为什么不是最优的？
//
// 提示：想一想将来我们想从更多方面区分猫和狗时，Cat和Dog会变成什么样。 提示：
// 想一想「需要一个在初始化时就必须设置好的成员」会带来哪些限制。

// 【答案 · 查看答案】
// 当前的方案在多个方面都不是最优的。
//
// 第一，我们想从多少个方面区分猫和狗，就得往Animal里加多少个成员。随着时间推
// 移，Animal类在内存上可能变得很庞大，而且很复杂！
//
// 第二，这种方案只有在基类成员能在初始化时确定的情况下才有效。例如，如果
// `speak()`为每只动物返回随机结果（比如调用`Dog::speak()`可能返回「woof」「
// arf」或「yip」），这类方案就会变得别扭并逐渐失效。
//
// 第三，由于`speak()`是Animal的成员，它对猫和狗的行为都一样（也就是说，它总是
// 返回`m_speak`）。如果我们希望`speak()`对猫和狗有不同的行为（例如让狗返回随
// 机声音），就必须把所有这些额外逻辑放进Animal里，这会让Animal更加复杂。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <string_view>
#include <string>

class Animal
{
protected:
    std::string m_name;

    // 将构造函数设置为 protected
    // 因为我们不想Animal被直接构造
    // 但是派生类仍然可以使用
    Animal(std::string_view name)
        : m_name{ name }
    {
    }

    Animal(const Animal&) = delete;
    Animal& operator=(const Animal&) = delete;

public:
    std::string_view getName() const { return m_name; }
    std::string_view speak() const { return "???"; }
};

class Cat: public Animal
{
public:
    Cat(std::string_view name)
        : Animal{ name }
    {
    }

    std::string_view speak() const { return "Meow"; }
};

class Dog: public Animal
{
public:
    Dog(std::string_view name)
        : Animal{ name }
    {
    }

    std::string_view speak() const { return "Woof"; }
};

int main()
{
    const Cat cat{ "Fred" };
    std::cout << "cat is named " << cat.getName() << ", and it says " << cat.speak() << '\n';

    const Dog dog{ "Garbo" };
    std::cout << "dog is named " << dog.getName() << ", and it says " << dog.speak() << '\n';

    const Animal* pAnimal{ &cat };
    std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

    pAnimal = &dog;
    std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

    return 0;
}
