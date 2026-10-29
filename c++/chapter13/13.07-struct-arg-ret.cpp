// ==========================================================================
// 13.7 结构体作为函数的输入与输出
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十三章 复合类型：枚举与结构体
// 原文: https://www.studycpp.cn/basic/chapter13/struct-arg-ret/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "13.07-struct-arg-ret.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 通过引用传递结构体
//   · 结构体作为返回值
//   · 返回类型推导
//   · 结构体是一个很重要的代码组件
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 考虑用3个松散变量表示的员工：

// [代码 1]
// int main()
// {
//     int id { 1 };
//     int age { 24 };
//     double wage { 52400.0 };
//
//     return 0;
// }

// 如果要将此员工传递给函数，必须传递三个变量：

// [代码 2]
// #include <iostream>
//
// void printEmployee(int id, int age, double wage)
// {
//     std::cout << "ID:   " << id << '\n';
//     std::cout << "Age:  " << age << '\n';
//     std::cout << "Wage: " << wage << '\n';
// }
//
// int main()
// {
//     int id { 1 };
//     int age { 24 };
//     double wage { 52400.0 };
//
//     printEmployee(id, age, wage);
//
//     return 0;
// }

// 虽然传递3个单独的员工变量还不算太糟，但如果函数需要传递多个员工变量，独立传
// 递每个变量就非常容易出错。此外，如果向员工添加新属性（例如名称），现在必须
// 修改所有函数声明、定义和函数调用，以接受新的参数！
//

// ―――― 通过引用传递结构体 ――――

// 与单个变量相比，使用结构体的一大优势是，可以将整个结构体传递给函数。结构体
// 通常通过引用传递（通常是常量引用），以避免进行复制。

// [代码 3]
// #include <iostream>
//
// struct Employee
// {
//     int id {};
//     int age {};
//     double wage {};
// };
//
// void printEmployee(const Employee& employee) // 注： 通过引用传递
// {
//     std::cout << "ID:   " << employee.id << '\n';
//     std::cout << "Age:  " << employee.age << '\n';
//     std::cout << "Wage: " << employee.wage << '\n';
// }
//
// int main()
// {
//     Employee joe { 14, 32, 24.15 };
//     Employee frank { 15, 28, 18.27 };
//
//     // 打印 Joe 的信息
//     printEmployee(joe);
//
//     std::cout << '\n';
//
//     // 打印 Frank 的信息
//     printEmployee(frank);
//
//     return 0;
// }

// 在上面的示例中，将整个Employee传递给printEmployee()（一次用于joe，一次用于
// frank）。
//
// 上述程序输出：

// [文本/输出]
// ID:   14
// Age:  32
// Wage: 24.15
//
// ID:   15
// Age:  28
// Wage: 18.27

// 因为传递的是整个结构体对象（而不是单个成员变量），所以无论有多少个成员变量，
// 都只需要一个参数。而且，如果决定向Employee结构体中添加新成员变量，也不必更
// 改函数声明或函数调用！新成员变量将自动包含在内。
//

// ―――― 结构体作为返回值 ――――

// 考虑这样的情况：有一个函数需要返回三维空间中的一个点。这样的点有3个属性：x
// 坐标、y坐标和z坐标。但函数只能返回一个值。那么如何将所有3个坐标返回给用户呢？
//
// 一种常见的方法是返回结构：

// [代码 4]
// #include <iostream>
//
// struct Point3d
// {
//     double x { 0.0 };
//     double y { 0.0 };
//     double z { 0.0 };
// };
//
// Point3d getZeroPoint()
// {
//     // 创建一个临时变量并返回
//     Point3d temp { 0.0, 0.0, 0.0 };
//     return temp;
// }
//
// int main()
// {
//     Point3d zero{ getZeroPoint() };
//
//     if (zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0)
//         std::cout << "The point is zero\n";
//     else
//         std::cout << "The point is not zero\n";
//
//     return 0;
// }

// 这将打印：

// [文本/输出]
// The point is zero

// 结构体通常按值返回，避免返回悬空引用。
//
// 在上面的getZeroPoint() 函数中，创建了一个新的命名对象（temp），以便可以返回
// 它：

// [代码 5]
// Point3d getZeroPoint()
// {
//     // 创建一个临时变量并返回
//     Point3d temp { 0.0, 0.0, 0.0 };
//     return temp;
// }

// 对象名称temp在这里没有提供任何有用的说明。
//
// 因此可以通过返回临时（未命名/匿名）对象来稍微改进函数：

// [代码 6]
// Point3d getZeroPoint()
// {
//     return Point3d { 0.0, 0.0, 0.0 }; // 返回一个未命名的 Point3d
// }

// 在这种情况下，将构造临时Point3d，将其复制回调用方，然后在表达式末尾销毁。这
// 里比上面更加简洁（一行替代两行，并且不需要判断temp是否被多次使用）。
//

// ―――― 返回类型推导 ――――

// 在函数具有显式返回类型（例如Point3d）的情况下，甚至可以在return语句中省略该
// 类型：

// [代码 7]
// Point3d getZeroPoint()
// {
//     // 因为函数声明中已经指定返回类型
//     // 因此这里无需再指定
//     return { 0.0, 0.0, 0.0 }; // 返回一个未命名的 Point3d
// }

// 还要注意，在这种情况下，如果想要返回一个全零的结构体，可以使用空大括号来返
// 回Point3d：

// [代码 8]
// Point3d getZeroPoint()
// {
//     // 空大括号，来进行值初始化
//     return {};
// }

//

// ―――― 结构体是一个很重要的代码组件 ――――

// 结构体很有用，类（C++和面向对象编程的核心）也直接构建在这里介绍的概念之上。
// 充分理解结构体（特别是数据成员、成员选择和默认成员初始化）将使您更容易过渡
// 到类。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 你在运营一个网站，想要计算广告收入。请编写一个程序，允许输入3项数据：
// - 观看了多少条广告。
// - 点击广告的用户所占的百分比。
// - 每次点击的平均收入。
//
// 把这3个值存放在一个结构体中。把这个结构体传给另一个函数并打印各项的值。这个
// 打印函数还应当打印出当天的收入（把3个成员相乘）。

// 【答案 · 显示提示】
// 如果你把百分比存成整数，那么在计算当天收入时还需要除以100。

// 【答案 · 查看答案】

// [代码 9]
// #include <iostream>
//
// // 首先定义我们的 Advertising 结构体
// struct Advertising
// {
//     int adsShown {};
//     double clickThroughRatePercentage {};
//     double averageEarningsPerClick {};
// };
//
// Advertising getAdvertising()
// {
//     Advertising temp {};
//     std::cout << "How many ads were shown today? ";
//     std::cin >> temp.adsShown;
//     std::cout << "What percentage of ads were clicked on by users? ";
//     std::cin >> temp.clickThroughRatePercentage;
//     std::cout << "What was the average earnings per click? ";
//     std::cin >> temp.averageEarningsPerClick;
//
//     return temp;
// }
//
// void printAdvertising(const Advertising& ad)
// {
//     std::cout << "Number of ads shown: " << ad.adsShown << '\n';
//     std::cout << "Click through rate: " << ad.clickThroughRatePercentage << '\n';
//     std::cout << "Average earnings per click: $" << ad.averageEarningsPerClick << '\n';
//
//     // 下面这一行为了缩短长度而拆成多行
//     // 需要把 ad.clickThroughRatePercentage 除以 100，因为它是百分比而不是倍数
//     std::cout << "Total Earnings: $"
//         << (ad.adsShown * ad.clickThroughRatePercentage / 100 * ad.averageEarningsPerClick) << '\n';
// }
//
// int main()
// {
//     // 声明一个 Advertising 结构体变量
//     Advertising ad{ getAdvertising() };
//     printAdvertising(ad);
//
//     return 0;
// }


// ▼ 问题 2
// 创建一个用于表示分数的结构体。该结构体应当有一个整数分子成员和一个整数分母
// 成员。
//
// 编写一个函数从用户处读入一个Fraction，并用它读入两个分数对象。再编写一个函
// 数把两个Fraction相乘，并以Fraction的形式返回结果（不需要约分）。另外编写一
// 个函数打印分数。
//
// 程序的输出应与下面一致：

// [文本/输出]
// Enter a value for the numerator: 1
// Enter a value for the denominator: 2
//
// Enter a value for the numerator: 3
// Enter a value for the denominator: 4
//
// Your fractions multiplied together: 3/8

// 两个分数相乘时，结果的分子是两个分子的乘积，结果的分母是两个分母的乘积。

// 【答案 · 查看答案】

// [代码 10]
// #include <iostream>
//
// struct Fraction
// {
//     int numerator{ 0 };
//     int denominator{ 1 };
// };
//
// Fraction getFraction()
// {
//     Fraction temp{};
//     std::cout << "Enter a value for numerator: ";
//     std::cin >> temp.numerator;
//     std::cout << "Enter a value for denominator: ";
//     std::cin >> temp.denominator;
//     std::cout << '\n';
//
//     return temp;
// }
//
// constexpr Fraction multiply(const Fraction& f1, const Fraction& f2)
// {
//     return { f1.numerator * f2.numerator, f1.denominator * f2.denominator };
// }
//
// void printFraction(const Fraction& f)
// {
//     std::cout << f.numerator << '/' << f.denominator << '\n';
// }
//
// int main()
// {
//     Fraction f1{ getFraction() };
//     Fraction f2{ getFraction() };
//
//     std::cout << "Your fractions multiplied together: ";
//
//     printFraction(multiply(f1, f2));
//
//     return 0;
// }


// ▼ 问题 3
// 在上一题的答案中，为什么`getFraction()`是按值返回，而不是按引用返回？

// 【答案 · 查看答案】
// 因为局部变量`temp`是一个Fraction对象，它会在函数结束时离开作用域。如果按引
// 用返回`temp`，就会把一个悬空引用返回给调用者。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

int main()
{
    int id { 1 };
    int age { 24 };
    double wage { 52400.0 };

    return 0;
}
