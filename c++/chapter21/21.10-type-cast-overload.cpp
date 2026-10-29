// ==========================================================================
// 21.10 重载类型转换
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十一章 操作符重载
// 原文: https://www.studycpp.cn/basic/chapter21/type-cast-overload/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "21.10-type-cast-overload.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 显式类型转换
//   · 转换构造函数与重载类型转换

// ==========================================================================
// 教程正文
// ==========================================================================

// C++允许您将一种数据类型转换为另一种。下面的示例显示了将int转换为double的过
// 程：

// [代码 1]
// int n{ 5 };
// auto d{ static_cast<double>(n) }; // int 转换为 double

// C++知道如何在内置数据类型之间进行转换。然而，它不知道如何转换其他用户定义的
// 类。这正是重载类型转换运算符可以发挥作用的地方。
//
// 用户定义的转换允许将类转换为另一种数据类型。请看下面的示例：

// [代码 2]
// class Cents
// {
// private:
//     int m_cents{};
// public:
//     Cents(int cents=0)
//         : m_cents{ cents }
//     {
//     }
//
//     int getCents() const { return m_cents; }
//     void setCents(int cents) { m_cents = cents; }
// };

// 这个类相当简单：它将Cents的数量保存为int，并提供访问函数来获取和设置m_cents。
// 它还提供了一个构造函数，用于将int转换为Cents。
//
// 如果我们可以将int转换为Cents（通过构造函数），那么我们是否也可以将Cents转换
// 回int？
//
// 在下面的示例中，必须使用getCents()将Cents变量转换回int，才能使用printInt()
// 打印它：

// [代码 3]
// #include <iostream>
//
// void printInt(int value)
// {
//     std::cout << value;
// }
//
// int main()
// {
//     Cents cents{ 7 };
//     printInt(cents.getCents()); // 打印 7
//
//     std::cout << '\n';
//
//     return 0;
// }

// 如果我们已经编写了许多以int作为参数的函数，那么代码中就会充满对getCents()的
// 调用，显得很杂乱。
//
// 为了简化操作，可以通过重载int类型转换来提供用户定义的转换。这样就可以将
// Cents对象直接转换为int。下面的示例展示了如何完成此操作：

// [代码 4]
// class Cents
// {
// private:
//     int m_cents{};
// public:
//     Cents(int cents=0)
//         : m_cents{ cents }
//     {
//     }
//
//     // 重载int转换
//     operator int() const { return m_cents; }
//
//     int getCents() const { return m_cents; }
//     void setCents(int cents) { m_cents = cents; }
// };

// 需要注意三点：
// - 为了让自定义类可以转换为int，新增了一个成员函数“operator int()”。注意
//   “operator”和目标类型之间有一个空格，而且这样的函数不能是static成员函数。
// - 自定义转换函数不能有任何参数，也没有其他方式传递参数。不过这里仍然有一个
//   隐式的“*this”参数，指向正在被转换的对象。
// - 自定义转换函数不能写返回类型。函数名中的类型（例如上面的int）就代表返回
//   类型。
//
// 现在，在上面的示例中，可以这样调用printInt()：

// [代码 5]
// #include <iostream>
//
// int main()
// {
//     Cents cents{ 7 };
//     printInt(cents); // 打印 7
//
//     std::cout << '\n';
//
//     return 0;
// }

// 编译器会首先注意到函数printInt()接收整数参数。然后它会发现变量cents不是int。
// 最后，它会查看我们是否提供了将cents转换为int的方法。由于我们提供了，它将调
// 用“operator int()”函数，该函数返回int，而返回的int会被传递给printInt()。
//
// 这样的类型转换也可以通过static_cast显式调用：

// [代码 6]
// std::cout << static_cast<int>(cents);

// 您可以提供到任何数据类型的用户定义转换，包括您自己的程序定义类型！
//
// 这里有一个名为Dollars的新类，它提供了到Cents的重载转换：

// [代码 7]
// class Dollars
// {
// private:
//     int m_dollars{};
// public:
//     Dollars(int dollars=0)
//         : m_dollars{ dollars }
//     {
//     }
//
//      // 允许从 Dollars 转换到 Cents
//      operator Cents() const { return Cents{ m_dollars * 100 }; }
// };

// 这允许我们将Dollars对象直接转换为Cents对象！因此，您可以这样做：

// [代码 8]
// #include <iostream>
//
// class Cents
// {
// private:
//     int m_cents{};
// public:
//     Cents(int cents=0)
//         : m_cents{ cents }
//     {
//     }
//
//     // 重载 int 转换
//     operator int() const { return m_cents; }
//
//     int getCents() const { return m_cents; }
//     void setCents(int cents) { m_cents = cents; }
// };
//
// class Dollars
// {
// private:
//     int m_dollars{};
// public:
//     Dollars(int dollars=0)
//         : m_dollars{ dollars }
//     {
//     }
//
//     // 允许从 Dollars 转换到 Cents
//     operator Cents() const { return Cents { m_dollars * 100 }; }
// };
//
// void printCents(Cents cents)
// {
//     std::cout << cents; // cents 会隐式的转换为 int
// }
//
// int main()
// {
//     Dollars dollars{ 9 };
//     printCents(dollars); // dollars 可以隐式的转换为 Cents
//
//     std::cout << '\n';
//
//     return 0;
// }

// 因此，该程序将打印值：
//
// 这很有道理，因为9美元是900美分！
//

// ―――― 显式类型转换 ――――

// 就像我们可以标记构造函数为explicit，以便它们不能用于隐式转换一样，出于相同
// 的原因，也可以使重载类型转换标记为explicit。只能显式调用显式类型转换（例如，
// 不能使用复制初始化或通过使用类似static_cast的显式转换）。

// [代码 9]
// #include <iostream>
//
// class Cents
// {
// private:
//     int m_cents{};
// public:
//     Cents(int cents=0)
//         : m_cents{ cents }
//     {
//     }
//
//     explicit operator int() const { return m_cents; } // 现在标记为 explicit
//
//     int getCents() const { return m_cents; }
//     void setCents(int cents) { m_cents = cents; }
// };
//
// class Dollars
// {
// private:
//     int m_dollars{};
// public:
//     Dollars(int dollars=0)
//         : m_dollars{ dollars }
//     {
//     }
//
//     operator Cents() const { return Cents { m_dollars * 100 }; }
// };
//
// void printCents(Cents cents)
// {
//     std::cout << static_cast<int>(cents); // explicit，因此必须使用显式类型转换
// }
//
// int main()
// {
//     Dollars dollars{ 9 };
//     printCents(dollars);
//
//     std::cout << '\n';
//
//     return 0;
// }

// 类型转换通常应标记为explicit。如果转换成本很低，并且目标是含义相近的用户定
// 义类型，则可以例外。“Dollars::operator Cents()”类型转换被标记为非显式，因为
// 没有理由不允许Dollars对象用于预期为Cents的地方。
//
// 最佳实践
//
// 类型转换应标记为explicit，除非要转换的类型在含义上本质相同。
//

// ―――― 转换构造函数与重载类型转换 ――――

// 重载类型转换和转换构造函数扮演着类似的角色：重载类型转换允许我们定义一个函
// 数，将某个程序定义类型a转换为其他类型b。转换构造函数则允许我们定义一个函数，
// 从其他类型b创建某个程序定义类型a。那么，应该在什么时候使用它们呢？
//
// 通常，转换构造函数应该优先于重载类型转换。
//
// 在一些情况下，应该使用重载类型转换：
// - 提供到基本类型或无法修改的类的转换（因为不能为这些类型定义构造函数）。最
//   惯用的场景是：为了让对象能够用于条件语句，提供到bool的转换。
// - 当不希望正在构造的类型知道被转换的类型时。这有助于避免循环依赖。
//
// 对于最后一点，例如，std::string有一个构造函数，可以从std::string_view创建
// std::string。这意味着<string>必须包含<string_view>。如果std::string_view也
// 有一个构造函数，可以从std::string创建std::string_view，那么<string_view>就
// 需要包含<string>，从而导致头文件之间的循环依赖。
//
// 相反，std::string提供了一个重载类型转换，用于处理从std::string到
// std::string_view的转换（这没有问题，因为它已经包含了<string_view>）。而
// std::string_view完全不需要知道std::string的任何细节，因此不需要包含<string>。
// 这样就避免了循环依赖。
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
    Cents(int cents=0)
        : m_cents{ cents }
    {
    }

    // 重载 int 转换
    operator int() const { return m_cents; }

    int getCents() const { return m_cents; }
    void setCents(int cents) { m_cents = cents; }
};

class Dollars
{
private:
    int m_dollars{};
public:
    Dollars(int dollars=0)
        : m_dollars{ dollars }
    {
    }

    // 允许从 Dollars 转换到 Cents
    operator Cents() const { return Cents { m_dollars * 100 }; }
};

void printCents(Cents cents)
{
    std::cout << cents; // cents 会隐式的转换为 int
}

int main()
{
    Dollars dollars{ 9 };
    printCents(dollars); // dollars 可以隐式的转换为 Cents

    std::cout << '\n';

    return 0;
}
