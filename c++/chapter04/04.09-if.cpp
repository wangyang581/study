// ==========================================================================
// 4.9 if语句简介
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第四章 基本数据类型
// 原文: https://www.studycpp.cn/basic/chapter4/if/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "04.09-if.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 使用if语句的示例程序
//   · if-else
//   · 串联if语句
//   · 布尔返回值和if语句
//   · 非布尔条件
//   · If语句和提前返回
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 考虑这样一个例子：你要去市场，你的室友告诉你，”如果草莓打折，就买一些”。这
// 是一个条件语句，意味着只有当条件（”草莓在打折”）为真时，你才会执行相应的操
// 作（”买一些”）。
//
// 这样的条件在编程中很常见，因为它使我们能够在程序中实现条件行为。C++中最简单
// 的条件语句称为if语句。if语句允许我们仅在某个条件为真时执行一行（或多行）代
// 码。
//
// 最简单的if语句采用以下形式：

// [代码 1]
// if (条件表达式) true_对应的语句;

// 为了可读性，这通常写为：

// [代码 2]
// if (条件表达式)
//     true_对应的语句;

// 条件（也称为条件表达式）是求值为布尔值的表达式。
//
// 如果if语句的条件求值为布尔值true，则执行 true_对应的语句。如果条件求值为布
// 尔值false，则跳过 true_对应的语句。
//

// ―――― 使用if语句的示例程序 ――――

// 给定以下程序：

// [代码 3]
// #include <iostream>
//
// int main()
// {
//     std::cout << "Enter an integer: ";
//     int x {};
//     std::cin >> x;
//
//     if (x == 0)
//         std::cout << "The value is zero\n";
//
//     return 0;
// }

// 下面是该程序一次运行的输出：

// [文本/输出]
// Enter an integer: 0
// The value is zero

// 首先，用户输入一个整数。然后对条件 x == 0 进行求值。相等运算符（==）用于测
// 试两个值是否相等。运算符== 在操作数相等时返回true，不相等时返回false。由于x
// 的值为0，而 0 == 0 为true，因此该表达式的求值结果为true。
//
// 由于条件求值结果为true，因此执行后续语句，打印出”The value is zero”。
//
// 下面是该程序的另一次运行结果：

// [文本/输出]
// Enter an integer: 5

// 在这种情况下，x==0 的求值结果为false。后续的语句被跳过，程序直接结束，不会
// 打印任何其他内容。
//
// 警告
//
// If语句仅能有条件地执行单个语句。我们将在后续课程中讨论如何有条件地执行多个
// 语句——If语句和块。
//

// ―――― if-else ――――

// 考虑上面的例子，如果我们还想告诉用户他们输入的数字不是零，该怎么办？
//
// 我们可以这样写：

// [代码 4]
// #include <iostream>
//
// int main()
// {
//     std::cout << "Enter an integer: ";
//     int x {};
//     std::cin >> x;
//
//     if (x == 0)
//         std::cout << "The value is zero\n";
//     if (x != 0)
//         std::cout << "The value is non-zero\n";
//
//     return 0;
// }

// 或者这样：

// [代码 5]
// #include <iostream>
//
// int main()
// {
//     std::cout << "Enter an integer: ";
//     int x {};
//     std::cin >> x;
//
//     bool zero { (x == 0) };
//     if (zero)
//         std::cout << "The value is zero\n";
//     if (!zero)
//         std::cout << "The value is non-zero\n";
//
//     return 0;
// }

// 这两个程序都比实际需要的更复杂。我们可以使用if语句的另一种形式，即 if-else。
// 其形式如下：

// [代码 6]
// if (条件表达式)
//     true_对应的语句;
// else
//     false_对应的语句;

// 如果条件求值为布尔true，则执行 true_对应的语句。否则执行 false_对应的语句。
//
// 让我们修改上面的程序，使用if-else。

// [代码 7]
// #include <iostream>
//
// int main()
// {
//     std::cout << "Enter an integer: ";
//     int x {};
//     std::cin >> x;
//
//     if (x == 0)
//         std::cout << "The value is zero\n";
//     else
//         std::cout << "The value is non-zero\n";
//
//     return 0;
// }

// 现在，我们的程序将产生以下输出：

// [文本/输出]
// Enter an integer: 0
// The value is zero


// [文本/输出]
// Enter an integer: 5
// The value is non-zero

//

// ―――― 串联if语句 ――――

// 有时候，我们需要依次检查多个条件是否为真。我们可以通过将if语句（或if-else）
// 串联到前一个if-else之后来实现，如下所示：

// [代码 8]
// #include <iostream>
//
// int main()
// {
//     std::cout << "Enter an integer: ";
//     int x {};
//     std::cin >> x;
//
//     if (x > 0)
//         std::cout << "The value is positive\n";
//     else if (x < 0)
//         std::cout << "The value is negative\n";
//     else
//         std::cout << "The value is zero\n";
//
//     return 0;
// }

// 小于运算符（<）用于测试一个值是否小于另一个值。类似地，大于运算符（>）用于
// 测试一个值是否大于另一个值。这些运算符都返回布尔值。
//
// 下面是该程序多次运行的输出：

// [文本/输出]
// Enter an integer: 4
// The value is positive


// [文本/输出]
// Enter an integer: -3
// The value is negative


// [文本/输出]
// Enter an integer: 0
// The value is zero

// 请注意，可以根据需要检查的条件数量多次串联if语句。
//

// ―――― 布尔返回值和if语句 ――――

// 在上一课中，我们编写了一个使用返回布尔值的函数的程序：

// [代码 9]
// #include <iostream>
//
// // x与y相等返回true, 不然返回false
// bool isEqual(int x, int y)
// {
//     return (x == y); // 操作符== ， x 等于y，返回true，否则返回false
// }
//
// int main()
// {
//     std::cout << "Enter an integer: ";
//     int x{};
//     std::cin >> x;
//
//     std::cout << "Enter another integer: ";
//     int y{};
//     std::cin >> y;
//
//     std::cout << std::boolalpha; // 以  true ， false 格式打印bool
//
//     std::cout << x << " and " << y << " are equal? ";
//     std::cout << isEqual(x, y) << '\n'; // isEqual返回true或false
//
//     return 0;
// }

// 让我们使用if语句来改进此程序：

// [代码 10]
// #include <iostream>
//
// // x与y相等返回true, 不然返回false
// bool isEqual(int x, int y)
// {
//     return (x == y); // 操作符== ， x 等于y，返回true，否则返回false
// }
//
// int main()
// {
//     std::cout << "Enter an integer: ";
//     int x {};
//     std::cin >> x;
//
//     std::cout << "Enter another integer: ";
//     int y {};
//     std::cin >> y;
//
//     if (isEqual(x, y))
//         std::cout << x << " and " << y << " are equal\n";
//     else
//         std::cout << x << " and " << y << " are not equal\n";
//
//     return 0;
// }

// 该程序两次运行的结果如下：

// [文本/输出]
// Enter an integer: 5
// Enter another integer: 5
// 5 and 5 are equal


// [文本/输出]
// Enter an integer: 6
// Enter another integer: 4
// 6 and 4 are not equal

// 在这种情况下，我们的条件表达式是对函数isEqual的调用，并获取其返回的布尔值。
//

// ―――― 非布尔条件 ――――

// 在上面的所有示例中，我们的条件要么是布尔值（true或false）、布尔变量，要么是
// 返回布尔值的函数。那么，如果条件是一个求值结果不是布尔值的表达式，会发生什
// 么呢？
//
// 在这种情况下，条件表达式会被转换为布尔值：非零值被转换为 true，零值被转换为
// false。
//
// 因此，如果我们这样做：

// [代码 11]
// #include <iostream>
//
// int main()
// {
//     if (4) // 无任何意义，用来作为示例...
//         std::cout << "hi\n";
//     else
//         std::cout << "bye\n";
//
//     return 0;
// }

// 这将打印“hi”，因为4是一个非零值，它被转换为布尔true。
//

// ―――― If语句和提前返回 ――――

// 不是函数中最后一个语句的return语句会导致函数提前返回。这样的语句会使函数在
// 执行到return时立即返回给调用方（在函数正常执行完毕之前就返回了，因此称为”提
// 前”返回）。
//
// 无条件的提前返回没有用处：

// [代码 12]
// void print()
// {
//     std::cout << "A";
//
//     return; // 函数在这里返回
//
//     std::cout << "B"; // 这行不会执行到
// }

// std::cout « “B”; 将永远不会被执行，我们可以将其删除，这样return语句就变成了
// 函数的最后一条语句。
//
// 然而，当与if语句结合使用时，提前返回提供了一种使函数有条件地返回的方法。

// [代码 13]
// #include <iostream>
//
// // 返回函数 x的绝对值
// int abs(int x)
// {
//     if (x < 0)
//         return -x; // 提前返回 (当 x < 0)
//
//     return x;
// }
//
// int main()
// {
//     std::cout << abs(4) << '\n'; // 打印 4
//     std::cout << abs(-3) << '\n'; // 打印 3
//
//     return 0;
// }

// 当调用 abs(4) 时，x的值为4。if (x < 0) 为false，提前返回语句不会执行。函数
// 继续执行到末尾，将x（值为4）返回给调用者。
//
// 当调用 abs(-3) 时，x的值为-3。if (x < 0) 为true，执行提前返回语句。此时，函
// 数将-x（值3）返回给调用方。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 什么是提前返回（early return）？它的行为是什么？

// 【答案 · 查看答案】
// 提前返回是指出现在函数最后一行之前的return语句。它会让函数立即返回到调用者。

// ▼ 问题 2
// 质数是大于1、且只能被1和自身整除的整数。编写一个程序，要求用户输入0到9（含）
// 之间的一个数字。如果用户输入的数字在这个范围内且是质数（2、3、5或7），打印
// 「The digit is prime」；否则打印「The digit is not prime」。

// 【答案 · 显示提示】
// 使用一串if-else语句，把用户输入的数字与各个质数逐一比较，看看是否匹配。

// 【答案 · 查看答案】

// [代码 14]
// #include <iostream>
//
// bool isPrime(int x)
// {
//     if (x == 2) // 如果用户输入 2，该数字是质数
//         return true;
//     else if (x == 3) // 如果用户输入 3，该数字是质数
//         return true;
//     else if (x == 5) // 如果用户输入 5，该数字是质数
//         return true;
//     else if (x == 7) // 如果用户输入 7，该数字是质数
//         return true;
//
//     return false; // 如果用户输入的不是 2、3、5、7，则该数字不是质数
// }
//
// int main()
// {
//     std::cout << "Enter a number 0 through 9: ";
//     int x {};
//     std::cin >> x;
//
//     if ( isPrime(x) )
//         std::cout << "The digit is prime\n";
//     else
//         std::cout << "The digit is not prime\n";
//
//     return 0;
// }

// 对于高级读者
//
// 如果上面这个`isPrime()`函数看起来有些啰嗦、重复——确实如此。我们可以用后续课
// 程中介绍的一些概念，把`isPrime()`写得更紧凑、更高效。
//
// 使用逻辑或（||）运算符（见「6.6 逻辑运算符」）：

// [代码 15]
// bool isPrime(int x)
// {
//     return x == 2 || x == 3 || x == 5 || x == 7; // 如果用户输入的是 2 或 3 或 5 或 7，该数字是质数
// }

// 使用switch语句（见「8.4 Switch语句基础」）：

// [代码 16]
// bool isPrime(int x)
// {
//     switch (x)
//     {
//         case 2: // 如果用户输入 2
//         case 3: // 或用户输入 3
//         case 5: // 或用户输入 5
//         case 7: // 或用户输入 7
//             return true; // 则该数字是质数
//     }
//
//     return false; // 否则该数字不是质数
// }


// ▼ 问题 3
// 在不改变格式的前提下，如何缩短下面这段代码的长度？

// [代码 17]
// #include <iostream>
//
// bool isAllowedToTakeFunRide()
// {
//   std::cout << "How tall are you? (cm)\n";
//
//   double height{};
//   std::cin >> height;
//
//   if (height >= 140.0)
//     return true;
//   else
//     return false;
// }
//
// int main()
// {
//   if (isAllowedToTakeFunRide())
//     std::cout << "Have fun!\n";
//   else
//     std::cout << "Sorry, you're too short.\n";
//
//   return 0;
// }


// 【答案 · 查看答案】
// `isAllowedToTakeFunRide()`中不需要if语句。表达式`height >= 140.0`求值结果是
// `bool`，可以直接返回。

// [代码 18]
// bool isAllowedToTakeFunRide()
// {
//   std::cout << "How tall are you? (cm)\n";
//
//   double height{};
//   std::cin >> height;
//
//   return height >= 140.0;
// }

// 你永远不需要下面这种形式的if语句：

// [代码 19]
// if (condition)
//   return true;
// else
//   return false;

// 它可以被单条语句`return condition;`取代。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    if (x == 0)
        std::cout << "The value is zero\n";

    return 0;
}
