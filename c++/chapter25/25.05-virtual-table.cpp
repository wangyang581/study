// ==========================================================================
// 25.5 虚函数表
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十五章 虚函数
// 原文: https://www.studycpp.cn/basic/chapter25/virtual-table/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "25.05-virtual-table.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 虚函数表

// ==========================================================================
// 教程正文
// ==========================================================================

// 考虑以下程序：

// [代码 1]
// #include <iostream>
// #include <string_view>
//
// class Base
// {
// public:
//     std::string_view getName() const { return "Base"; }                // 非 virtual
//     virtual std::string_view getNameVirtual() const { return "Base"; } // virtual
// };
//
// class Derived: public Base
// {
// public:
//     std::string_view getName() const { return "Derived"; }
//     virtual std::string_view getNameVirtual() const override { return "Derived"; }
// };
//
// int main()
// {
//     Derived derived {};
//     Base& base { derived };
//
//     std::cout << "base has static type " << base.getName() << '\n';
//     std::cout << "base has dynamic type " << base.getNameVirtual() << '\n';
//
//     return 0;
// }

// 首先，让我们看看对 base.getName() 的调用。由于这是一个非虚函数，编译器会使
// 用 base 的静态类型（Base）在编译时确定它应该解析为 Base::getName()。
//
// 尽管看起来几乎相同，但对 base.getNameVirtual() 的调用必须以不同方式解析。由
// 于这是虚函数调用，编译器必须使用 base 的动态类型来解析调用，而 base 的动态
// 类型要到运行时才知道。因此，只有在运行时才能确定这次 base.getNameVirtual()
// 调用会解析为 Derived::getNameVirtual()。
//
// 那么，虚函数实际上是如何工作的呢？
//

// ―――― 虚函数表 ――――

// C++ 标准没有指定应该如何实现虚函数（这些细节由具体编译器决定）。
//
// 然而，C++ 实现通常使用一种称为虚函数表的动态绑定机制来实现虚函数。
//
// 虚函数表是用于以动态绑定（延迟绑定）方式解析函数调用的查找表。虚函数表有时
// 也被称为 “vtable”、“虚方法表”或“分派表”。在 C++ 中，虚函数解析有时称为动态
// 分派。
//
// 由于使用虚函数不需要知道虚函数表的工作方式，因此可以将此部分视为可选阅读。
//
// 尽管用文字描述起来有点复杂，但虚函数表实际上相当简单。首先，每个使用虚函数
// 的类都有一个对应的虚函数表。该表只是编译器在编译时设置的静态数组。虚函数表
// 包含该类对象可以调用的每个虚函数条目。表中的每个条目都是一个函数指针，指向
// 该类可以访问的最底层派生函数。
//
// 其次，编译器还会添加一个隐藏指针。该指针是基类的成员，我们将其称为 *__vptr。
// *__vptr 会在创建类对象时自动设置，使它指向该类的虚函数表。与 this 指针（它
// 实际上是编译器用于解析自引用的函数参数）不同，*__vptr 是真正的指针成员。因
// 此，每个分配的类对象都会增大一个指针的大小。这也意味着 *__vptr 会被派生类继
// 承，这一点很重要。
//
// 现在，您可能会疑惑这些内容是如何组合在一起的，因此让我们看一个简单示例：

// [代码 2]
// class Base
// {
// public:
//     virtual void function1() {};
//     virtual void function2() {};
// };
//
// class D1: public Base
// {
// public:
//     void function1() override {};
// };
//
// class D2: public Base
// {
// public:
//     void function2() override {};
// };

// 因为这里有 3 个类，所以编译器将设置 3 个虚函数表：一个用于 Base，一个用于
// D1，另一个用于 D2。
//
// 编译器还会向使用虚函数的最顶层基类添加隐藏指针成员。尽管编译器会自动执行此
// 操作，但我们在下一个示例中把它写出来，只是为了展示它的添加位置：

// [代码 3]
// class Base
// {
// public:
//     VirtualTable* __vptr;
//     virtual void function1() {};
//     virtual void function2() {};
// };
//
// class D1: public Base
// {
// public:
//     void function1() override {};
// };
//
// class D2: public Base
// {
// public:
//     void function2() override {};
// };

// 创建类对象时，*__vptr 会被设置为指向该类的虚函数表。例如，创建 Base 类型的
// 对象时，*__vptr 会指向 Base 的虚函数表。构造 D1 或 D2 类型的对象时，*__vptr
// 会分别指向 D1 或 D2 的虚函数表。
//
// 现在，让我们讨论这些虚函数表如何填充。因为这里只有两个虚函数，所以每个虚函
// 数表都有两个条目（一个用于 function1()，另一个用于 function2()）。请记住，
// 填充这些虚函数表时，每个条目都会填入该类型对象可以调用的最底层派生函数。
//
// Base 对象的虚函数表很简单。Base 类型的对象只能访问 Base 的成员。Base 无权访
// 问 D1 或 D2 的函数。因此，function1 的条目指向 Base::function1()，function2
// 的条目指向 Base::function2()。
//
// D1 的虚函数表稍微复杂一些。D1 类型的对象可以访问 D1 和 Base 的成员。然而，
// D1 重写了 function1()，因此 D1::function1() 比 Base::function1() 更底层。因
// 此，function1 的条目指向 D1::function1()。D1 尚未重写 function2()，因此
// function2 的条目仍然指向 Base::function2()。
//
// D2 的虚函数表类似于 D1，只是 function1 的条目指向 Base::function1()，
// function2 的条目指向 D2::function2()。
//
// 下面是示意的图片：
// [图片] https://www.studycpp.cn/basic/chapter25/virtual-table/VTable.gif
// 虚函数表
//
// 尽管这个图看起来有点复杂，但它其实非常简单：每个类中的 *__vptr 指向该类的虚
// 函数表。虚函数表中的条目指向该类对象允许调用的最底层派生函数版本。
//
// 因此，请考虑创建 D1 类型的对象时会发生什么：

// [代码 4]
// int main()
// {
//     D1 d1 {};
// }

// 由于 d1 是 D1 对象，因此 d1 会将其 *__vptr 设置为指向 D1 虚函数表。
//
// 现在，让我们将 Base 指针设置为指向 D1：

// [代码 5]
// int main()
// {
//     D1 d1 {};
//     Base* dPtr = &d1;
//
//     return 0;
// }

// 请注意，由于 dPtr 是 Base 指针，因此它只指向 d1 的 Base 部分。然而，*__vptr
// 位于类的 Base 部分，因此 dPtr 可以访问该指针。最后，注意 dPtr->__vptr 指向
// D1 虚函数表！因此，即使 dPtr 是 Base* 类型，它仍然可以通过 __vptr 访问 D1
// 的虚函数表。
//
// 那么，当我们试图调用dPtr->function1()时会发生什么呢？

// [代码 6]
// int main()
// {
//     D1 d1 {};
//     Base* dPtr = &d1;
//     dPtr->function1();
//
//     return 0;
// }

// 首先，程序识别出 function1() 是虚函数。其次，程序使用 dPtr->__vptr 访问 D1
// 的虚函数表。第三，它在 D1 的虚函数表中查找应该调用 function1() 的哪个版本。
// 该条目已经被设置为 D1::function1()。因此，dPtr->function1() 会解析为
// D1::function1()！
//
// 现在，您可能会问：“但如果 dPtr 确实指向 Base 对象，而不是 D1 对象，它还会调
// 用 D1::function1() 吗？” 答案是否定的。

// [代码 7]
// int main()
// {
//     Base b {};
//     Base* bPtr = &b;
//     bPtr->function1();
//
//     return 0;
// }

// 在这种情况下，创建 b 时，b.__vptr 指向 Base 的虚函数表，而不是 D1 的虚函数
// 表。由于 bPtr 指向 b，因此 bPtr->__vptr 也指向 Base 的虚函数表。Base 虚函数
// 表中 function1() 的条目指向 Base::function1。因此，bPtr->function1() 解析为
// Base::function1()，这是 Base 对象能够调用的 function1() 的最底层派生版本。
//
// 通过使用这些表，编译器和程序能够确保函数调用解析到合适的虚函数，即使您只使
// 用指向基类的指针或引用！
//
// 调用虚函数比调用非虚函数慢，原因有几个：首先，我们必须使用 *__vptr 访问合适
// 的虚函数表。其次，我们必须索引虚函数表，以找到要调用的正确函数。只有这样，
// 才能调用对应的函数。因此，我们需要执行 3 个操作才能找到要调用的函数，而普通
// 间接函数调用通常只需要 2 个操作，直接函数调用只需要 1 个操作。当然，对于现
// 代计算机，这种额外时间通常相当微不足道。
//
// 另外，作为提醒，任何使用虚函数的类都有一个 *__vptr，因此该类的每个对象都会
// 多占用一个指针的空间。虚函数功能很强大，但确实存在性能成本。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <string_view>

class Base
{
public:
    std::string_view getName() const { return "Base"; }                // 非 virtual
    virtual std::string_view getNameVirtual() const { return "Base"; } // virtual
};

class Derived: public Base
{
public:
    std::string_view getName() const { return "Derived"; }
    virtual std::string_view getNameVirtual() const override { return "Derived"; }
};

int main()
{
    Derived derived {};
    Base& base { derived };

    std::cout << "base has static type " << base.getName() << '\n';
    std::cout << "base has dynamic type " << base.getNameVirtual() << '\n';

    return 0;
}
