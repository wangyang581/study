// ==========================================================================
// 25.3 虚析构函数、虚赋值函数以及虚函数重写
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十五章 虚函数
// 原文: https://www.studycpp.cn/basic/chapter25/virtual-destructor-assign-override/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "25.03-virtual-destructor-assign-override.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 虚析构函数
//   · 虚赋值函数
//   · 忽略virtual
//   · 应该让所有的析构函数都是virtual的吗？

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 虚析构函数 ――――

// 尽管 C++ 会为类提供默认析构函数，但有时您会希望提供自己的析构函数，尤其是在
// 类需要释放内存时。如果这个类会参与继承，就应该始终让析构函数成为虚函数。考
// 虑以下示例：

// [代码 1]
// #include <iostream>
// class Base
// {
// public:
//     ~Base() // 注: 非 virtual
//     {
//         std::cout << "Calling ~Base()\n";
//     }
// };
//
// class Derived: public Base
// {
// private:
//     int* m_array {};
//
// public:
//     Derived(int length)
//       : m_array{ new int[length] }
//     {
//     }
//
//     ~Derived() // 注: 非 virtual (您的编译器可能会因此有警告)
//     {
//         std::cout << "Calling ~Derived()\n";
//         delete[] m_array;
//     }
// };
//
// int main()
// {
//     Derived* derived { new Derived(5) };
//     Base* base { derived };
//
//     delete base;
//
//     return 0;
// }

// 注意：如果编译上面的示例，编译器可能会警告您有关非虚析构函数的信息（这是本
// 例中有意设置的）。您可能需要禁用「将警告视为错误」的编译器选项才能编译通过。
//
// 由于 base 是 Base 指针，因此执行 “delete base;” 时，程序会检查 Base 的析构
// 函数是否是虚函数。它不是，所以程序会认为只需要调用 Base 析构函数。我们可以
// 从上面示例的输出中看到这一点：

// [文本/输出]
// Calling ~Base()

// 然而，我们真正希望 delete 调用 Derived 的析构函数（随后它会调用 Base 的析构
// 函数），否则 m_array 将不会被释放。将 Base 的析构函数设置为 virtual 即可实
// 现这一点：

// [代码 2]
// #include <iostream>
// class Base
// {
// public:
//     virtual ~Base() // note: virtual
//     {
//         std::cout << "Calling ~Base()\n";
//     }
// };
//
// class Derived: public Base
// {
// private:
//     int* m_array {};
//
// public:
//     Derived(int length)
//       : m_array{ new int[length] }
//     {
//     }
//
//     virtual ~Derived() // note: virtual
//     {
//         std::cout << "Calling ~Derived()\n";
//         delete[] m_array;
//     }
// };
//
// int main()
// {
//     Derived* derived { new Derived(5) };
//     Base* base { derived };
//
//     delete base;
//
//     return 0;
// }

// 现在，该程序产生以下结果：

// [文本/输出]
// Calling ~Derived()
// Calling ~Base()

// 和普通 virtual 成员函数一样，如果基类函数是虚函数，则所有派生类中的重写都会
// 被视为虚函数。没有必要仅仅为了标记 virtual 而创建空的派生类析构函数。
//
// 请注意，如果希望基类具有一个空的虚析构函数，可以这样定义：

// [代码 3]
// virtual ~Base() = default; // 生成默认虚析构函数


// ―――― 虚赋值函数 ――――

// 赋值运算符也可以成为 virtual。然而，与析构函数不同，virtual 赋值运算符很容
// 易引入大量 bug，并涉及一些超出本教程范围的高级主题。因此，为了简单起见，我
// 们建议您暂时不要考虑这种情况。

// ―――― 忽略virtual ――――

// 在少数情况下，您可能希望绕过函数的虚函数解析。例如，考虑以下代码：

// [代码 4]
// #include <string_view>
// class Base
// {
// public:
//     virtual ~Base() = default;
//     virtual std::string_view getName() const { return "Base"; }
// };
//
// class Derived: public Base
// {
// public:
//     virtual std::string_view getName() const { return "Derived"; }
// };

// 在某些情况下，您可能希望指向 Derived 对象的 Base 指针调用 Base::getName()，
// 而不是 Derived::getName()。为此，只需使用作用域解析运算符：

// [代码 5]
// #include <iostream>
// int main()
// {
//     Derived derived {};
//     const Base& base { derived };
//
//     // 调用 Base::getName() 而不是 Derived::getName()
//     std::cout << base.Base::getName() << '\n';
//
//     return 0;
// }

// 您可能不会经常使用这种写法，但至少应该知道它可以实现。

// ―――― 应该让所有的析构函数都是virtual的吗？ ――――

// 这是新程序员常见的问题。如上面的示例所示，如果基类析构函数未标记为 virtual，
// 之后又通过指向派生对象的基类指针删除对象，程序就有内存泄漏的风险。避免这种
// 情况的一种方法是将所有析构函数都标记为 virtual。但应该这样做吗？
//
// 回答“是”很容易，因为这样以后就可以把任何类当作基类使用。但这样做会降低性能
// （会为类的每个实例添加 virtual 指针）。因此，你必须在成本和设计意图之间做权
// 衡。
//
// 我们的建议如下：如果类没有明确设计为基类，那么通常最好不要包含虚成员和虚析
// 构函数。该类仍然可以通过组合来使用。如果类被设计为基类，或者具有任何虚函数，
// 那么它应该始终具有虚析构函数。
//
// 如果决定使类不可继承，那么下一个问题是，是否可以强制执行这一点。
//
// 传统经验（正如备受推崇的 C++ 专家 Herb Sutter 最初提出的那样）建议这样避免
// 非虚析构函数造成的内存泄漏：“基类析构函数应该是 public 且 virtual 的，或者
// 是 protected 且非 virtual 的。”如果基类析构函数是 protected，就不能通过基类
// 指针删除对象，这会阻止通过基类指针删除派生类对象。
//
// 不幸的是，这也阻止了外部对基类析构函数的任何使用。这意味着：
// - 我们不应该动态分配基类对象，因为没有常规方法删除它们（虽然有非常规的变通
//   方法，但并不理想）。
// - 我们甚至不能静态分配基类对象，因为当它们超出作用域时，析构函数是不可访问
//   的。
//
// 换句话说，使用这种方法时，为了让派生类安全，我们会让基类本身几乎不可用。
//
// 既然 final 说明符已经引入到语言中，我们的建议如下：
// - 如果希望类可以被继承，请确保析构函数是 virtual 且 public 的。
// - 如果您不希望任何人继承您的类，请将类标记为 final。这会直接防止其他类继承
//   它，而不会对类本身施加其他使用限制。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
class Base
{
public:
    ~Base() // 注: 非 virtual
    {
        std::cout << "Calling ~Base()\n";
    }
};

class Derived: public Base
{
private:
    int* m_array {};

public:
    Derived(int length)
      : m_array{ new int[length] }
    {
    }

    ~Derived() // 注: 非 virtual (您的编译器可能会因此有警告)
    {
        std::cout << "Calling ~Derived()\n";
        delete[] m_array;
    }
};

int main()
{
    Derived* derived { new Derived(5) };
    Base* base { derived };

    delete base;

    return 0;
}
