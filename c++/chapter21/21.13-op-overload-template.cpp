// ==========================================================================
// 21.13 重载运算符和函数模板
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十一章 操作符重载
// 原文: https://www.studycpp.cn/basic/chapter21/op-overload-template/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "21.13-op-overload-template.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 运算符、函数调用和函数模板
//   · 另一个例子

// ==========================================================================
// 教程正文
// ==========================================================================

// 在函数模板实例化中，我们讨论了编译器如何使用函数模板实例化函数，然后编译这
// 些函数。我们还注意到，如果函数模板中的代码试图执行实际类型不支持的操作（例
// 如将整数值1添加到std::string），这些函数可能无法通过编译。
//
// 在本课中，我们将看几个示例：实例化后的函数因为实际类类型不支持某些运算符而
// 无法编译。然后，我们会展示如何定义这些运算符，使实例化函数能够通过编译。
//

// ―――― 运算符、函数调用和函数模板 ――――

// 首先，让我们创建一个简单的类：

// [代码 1]
// class Cents
// {
// private:
//     int m_cents{};
// public:
//     Cents(int cents)
//         : m_cents { cents }
//     {
//     }
//
//     friend std::ostream& operator<< (std::ostream& ostr, const Cents& c)
//     {
//         ostr << c.m_cents;
//         return ostr;
//     }
// };

// 并定义max函数模板：

// [代码 2]
// template <typename T>
// const T& max(const T& x, const T& y)
// {
//     return (x < y) ? y : x;
// }

// 现在，让我们看看当我们试图用Cents类型的对象调用max()时会发生什么：

// [代码 3]
// #include <iostream>
//
// class Cents
// {
// private:
//     int m_cents{};
// public:
//     Cents(int cents)
//         : m_cents { cents }
//     {
//     }
//
//     friend std::ostream& operator<< (std::ostream& ostr, const Cents& c)
//     {
//         ostr << c.m_cents;
//         return ostr;
//     }
// };
//
// template <typename T>
// const T& max(const T& x, const T& y)
// {
//     return (x < y) ? y : x;
// }
//
// int main()
// {
//     Cents nickel{ 5 };
//     Cents dime{ 10 };
//
//     Cents bigger { max(nickel, dime) };
//     std::cout << bigger << " is bigger\n";
//
//     return 0;
// }

// C++将为max()创建一个模板实例，如下所示：

// [代码 4]
// template <>
// const Cents& max(const Cents& x, const Cents& y)
// {
//     return (x < y) ? y : x;
// }

// 然后它会尝试编译这个函数。看到这里的问题了吗？当x和y是Cents类型时，C++不知
// 道如何计算"x < y"！因此，这会产生编译错误。
//
// 要解决此问题，只需要为我们希望与max一起使用的类重载运算符<：

// [代码 5]
// #include <iostream>
//
// class Cents
// {
// private:
//     int m_cents {};
// public:
//     Cents(int cents)
//         : m_cents { cents }
//     {
//     }
//
//     friend bool operator< (const Cents& c1, const Cents& c2)
//     {
//         return (c1.m_cents < c2.m_cents);
//     }
//
//     friend std::ostream& operator<< (std::ostream& ostr, const Cents& c)
//     {
//         ostr << c.m_cents;
//         return ostr;
//     }
// };
//
// template <typename T>
// const T& max(const T& x, const T& y)
// {
//     return (x < y) ? y : x;
// }
//
// int main()
// {
//     Cents nickel{ 5 };
//     Cents dime { 10 };
//
//     Cents bigger { max(nickel, dime) };
//     std::cout << bigger << " is bigger\n";
//
//     return 0;
// }

// 这按预期工作，并打印：

// [文本/输出]
// 10 is bigger

//

// ―――― 另一个例子 ――――

// 让我们再举一个函数模板的例子，它会因为缺少重载运算符而无法工作。
//
// 以下函数模板将计算数组中多个对象的平均值：

// [代码 6]
// #include <iostream>
//
// template <typename T>
// T average(const T* myArray, int numValues)
// {
//     T sum { 0 };
//     for (int count { 0 }; count < numValues; ++count)
//         sum += myArray[count];
//
//     sum /= numValues;
//     return sum;
// }
//
// int main()
// {
//     int intArray[] { 5, 3, 2, 1, 4 };
//     std::cout << average(intArray, 5) << '\n';
//
//     double doubleArray[] { 3.12, 3.45, 9.23, 6.34 };
//     std::cout << average(doubleArray, 4) << '\n';
//
//     return 0;
// }

// 这将产生以下值：

// [文本/输出]
// 3
// 5.535

// 正如您所看到的，它非常适合内置类型！
//
// 现在，让我们看看在Cents类上调用这个函数时会发生什么：

// [代码 7]
// #include <iostream>
//
// template <typename T>
// T average(const T* myArray, int numValues)
// {
//     T sum { 0 };
//     for (int count { 0 }; count < numValues; ++count)
//         sum += myArray[count];
//
//     sum /= numValues;
//     return sum;
// }
//
// class Cents
// {
// private:
//     int m_cents {};
// public:
//     Cents(int cents)
//         : m_cents { cents }
//     {
//     }
// };
//
// int main()
// {
//     Cents centsArray[] { Cents { 5 }, Cents { 10 }, Cents { 15 }, Cents { 14 } };
//     std::cout << average(centsArray, 4) << '\n';
//
//     return 0;
// }

// 编译器会产生大量错误消息！第一条错误消息如下所示：

// [文本/输出]
// error C2679: binary << : no operator found which takes a right-hand operand of type Cents (or there is no acceptable conversion)

// 请记住，average()会返回一个Cents对象，而我们试图使用运算符«将该对象输出到
// std::cout。然而，我们还没有为Cents类定义运算符«。让我们来定义它：

// [代码 8]
// #include <iostream>
//
// template <typename T>
// T average(const T* myArray, int numValues)
// {
//     T sum { 0 };
//     for (int count { 0 }; count < numValues; ++count)
//         sum += myArray[count];
//
//     sum /= numValues;
//     return sum;
// }
//
// class Cents
// {
// private:
//     int m_cents {};
// public:
//     Cents(int cents)
//         : m_cents { cents }
//     {
//     }
//
//     friend std::ostream& operator<< (std::ostream& out, const Cents& cents)
//     {
//         out << cents.m_cents << " cents ";
//         return out;
//     }
// };
//
// int main()
// {
//     Cents centsArray[] { Cents { 5 }, Cents { 10 }, Cents { 15 }, Cents { 14 } };
//     std::cout << average(centsArray, 4) << '\n';
//
//     return 0;
// }

// 如果我们再次编译，我们将得到另一个错误：

// [代码 9]
// error C2676: binary += : Cents does not define this operator or a conversion to a type acceptable to the predefined operator

// 此错误实际上是由调用average（const Cents*，int）时创建的函数模板实例引起的。
// 请记住，当我们调用模板函数时，编译器会“生成”该函数的一个副本，其中模板类型
// 参数（占位符类型）已被函数调用中的实际类型替换。下面是T为Cents时average（）
// 的函数模板实例：

// [代码 10]
// template <>
// Cents average(const Cents* myArray, int numValues)
// {
//     Cents sum { 0 };
//     for (int count { 0 }; count < numValues; ++count)
//         sum += myArray[count];
//
//     sum /= numValues;
//     return sum;
// }

// 错误消息来自以下这一行：

// [代码 11]
//         sum += myArray[count];

// 在这种情况下，sum是一个Cents对象，但我们没有为Cents对象定义运算符+=！我们需
// 要定义这个函数，average（）才能使用Cents。可以看到average（）也使用了运算符
// /=，因此也要定义它：

// [代码 12]
// #include <iostream>
//
// template <typename T>
// T average(const T* myArray, int numValues)
// {
//     T sum { 0 };
//     for (int count { 0 }; count < numValues; ++count)
//         sum += myArray[count];
//
//     sum /= numValues;
//     return sum;
// }
//
// class Cents
// {
// private:
//     int m_cents {};
// public:
//     Cents(int cents)
//         : m_cents { cents }
//     {
//     }
//
//     friend std::ostream& operator<< (std::ostream& out, const Cents& cents)
//     {
//         out << cents.m_cents << " cents ";
//         return out;
//     }
//
//     Cents& operator+= (const Cents &cents)
//     {
//         m_cents += cents.m_cents;
//         return *this;
//     }
//
//     Cents& operator/= (int x)
//     {
//         m_cents /= x;
//         return *this;
//     }
// };
//
// int main()
// {
//     Cents centsArray[] { Cents { 5 }, Cents { 10 }, Cents { 15 }, Cents { 14 } };
//     std::cout << average(centsArray, 4) << '\n';
//
//     return 0;
// }

// 最后，我们的代码可以编译并运行！结果如下：

// [文本/输出]
// 11 cents

// 请注意，我们根本不需要修改average（）本身，就能让它处理Cents类型的对象。我
// 们只需要定义average（）在Cents类上所需的运算符，其余工作由编译器处理！
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class Cents
{
private:
    int m_cents {};
public:
    Cents(int cents)
        : m_cents { cents }
    {
    }

    friend bool operator< (const Cents& c1, const Cents& c2)
    {
        return (c1.m_cents < c2.m_cents);
    }

    friend std::ostream& operator<< (std::ostream& ostr, const Cents& c)
    {
        ostr << c.m_cents;
        return ostr;
    }
};

template <typename T>
const T& max(const T& x, const T& y)
{
    return (x < y) ? y : x;
}

int main()
{
    Cents nickel{ 5 };
    Cents dime { 10 };

    Cents bigger { max(nickel, dime) };
    std::cout << bigger << " is bigger\n";

    return 0;
}
