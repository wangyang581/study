// ==========================================================================
// 8.5 switch fallthrough机制与作用域
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第八章 控制流与错误处理
// 原文: https://www.studycpp.cn/basic/chapter8/switch-fallthrough-scope/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "08.05-switch-fallthrough-scope.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · Fallthrough机制
//   · [[fallthrough]]属性
//   · 连续case标签
//   · switch语句中case的作用域
//   · case语句中的变量声明和初始化
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 在上一课中，我们提到标签下的每一组语句都应该以break语句或return语句结尾。
//
// 本课将探索其中的原因，并讨论一些有时会困扰新程序员的switch作用域问题。
//

// ―――― Fallthrough机制 ――――

// 当switch表达式与case标签或可选的默认标签匹配时，执行从匹配标签之后的第一条
// 语句开始。然后继续按顺序执行，直到发生以下终止条件之一：
// - switch代码块结束
// - 另一个控制流语句（通常是break或return）导致退出代码块或函数。
// - 其他打断程序正常控制流的事情（例如操作系统杀死了对应的进程）
//
// 请注意，另一个case标签的存在并不是这些终止条件之一。因此，如果没有中断或返
// 回，执行会继续流入后续case中。
//
// 下面是一个显示此行为的程序：

// [代码 1]
// #include <iostream>
//
// int main()
// {
//     switch (2)
//     {
//     case 1: // 不匹配
//         std::cout << 1 << '\n'; // 跳过
//     case 2: // 匹配
//         std::cout << 2 << '\n'; // 从这里开始执行
//     case 3:
//         std::cout << 3 << '\n'; // 这里也会执行
//     case 4:
//         std::cout << 4 << '\n'; // 这里也会执行
//     default:
//         std::cout << 5 << '\n'; // 这里也会执行
//     }
//
//     return 0;
// }

// 该程序输出以下内容：
//
// 这可能不是我们想要的！当执行从某个标签下的语句继续流入后续标签下的语句时，
// 这称为fallthrough。
//
// 由于很少需要有意进行fallthrough，因此许多编译器和代码分析工具会将
// fallthrough标记为警告。
//
// 警告
//
// 一旦case或默认标签下的语句开始执行，它们将溢出（fallthrough）到后续的case中。
// Break或return语句通常用于防止这种情况。
//

// ―――― [[fallthrough]]属性 ――――

// 可以通过注释告诉其他开发人员，switch中的fallthrough行为是有意设计的。虽然这
// 对其他开发人员有效，但编译器和代码分析工具不知道如何解释注释，因此不会消除
// 警告。
//
// 为了帮助解决这个问题，C++17添加了一个名为[[fallthrough]]的新属性。
//
// 属性是一种现代C++功能，它允许程序员向编译器提供一些有关代码的附加信息。要指
// 定属性，请将属性名称放在双括号之间。属性不是语句——相反，它们几乎可以用在任
// 何上下文允许的位置。
//
// 下面的例子中，[[fallthrough]]属性修改null语句，以指示fallthrough是有意的（
// 不应触发任何警告）：

// [代码 2]
// #include <iostream>
//
// int main()
// {
//     switch (2)
//     {
//     case 1:
//         std::cout << 1 << '\n';
//         break;
//     case 2:
//         std::cout << 2 << '\n'; // 这里开始执行
//         [[fallthrough]]; // 有意的进行 fallthrough -- 注意这里的分号代表空语句
//     case 3:
//         std::cout << 3 << '\n'; // 这里也会执行到
//         break;
//     }
//
//     return 0;
// }

// 该程序打印：
//
// 并且它不应该生成任何关于fallthrough的警告。
//
// 最佳实践
//
// 使用[[fallthrough]]属性（以及null语句）来指示有意的fallthrough。
//

// ―――― 连续case标签 ――――

// 您可以使用逻辑OR运算符将多个测试组合到单个语句中：

// [代码 3]
// bool isVowel(char c)
// {
//     return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
//         c=='A' || c=='E' || c=='I' || c=='O' || c=='U');
// }

// 这里c被多次求值。
//
// 通过按顺序放置多个case标签，可以使用switch语句执行类似的操作：

// [代码 4]
// bool isVowel(char c)
// {
//     switch (c)
//     {
//         case 'a': // if c is 'a'
//         case 'e': // or if c is 'e'
//         case 'i': // or if c is 'i'
//         case 'o': // or if c is 'o'
//         case 'u': // or if c is 'u'
//         case 'A': // or if c is 'A'
//         case 'E': // or if c is 'E'
//         case 'I': // or if c is 'I'
//         case 'O': // or if c is 'O'
//         case 'U': // or if c is 'U'
//             return true;
//         default:
//             return false;
//     }
// }

// 请记住，执行会从匹配的case标签之后的第一条语句开始。case标签不是语句（它们
// 是标签），因此它们不算作语句。
//
// 上面程序中所有case语句之后的第一个语句都返回true，因此如果任何case标签匹配，
// 函数将返回true。
//
// 因此，我们可以“堆叠”case标签，让这些case标签共享后续的同一组语句。这不被认
// 为是fallthrough行为，因此这里不需要使用注释或[[fallthrough]]。
//

// ―――― switch语句中case的作用域 ――――

// 使用if语句时，if条件之后只能有一条语句，并且该语句会被视为隐式地位于代码块
// 内：

// [代码 5]
// if (x > 10)
//     std::cout << x << " is greater than 10\n"; // 该语句被认为隐式地位于代码块内

// 然而，对于switch语句，标签后的语句都属于switch块本身。不会创建隐式代码块。

// [代码 6]
// switch (1)
// {
//     case 1: // 不会创建隐式块
//         foo(); // 在switch的作用域内，而不是case 1内
//         break; // 在switch的作用域内，而不是case 1内
//     default:
//         std::cout << "default case\n";
//         break;
// }

// 在上面的示例中，case 1标签和default标签之间的2条语句的作用域属于switch块，
// 而不是case 1隐含的代码块。
//

// ―――― case语句中的变量声明和初始化 ――――

// 您可以在switch语句内、case标签之前或之后声明或定义变量（但不能初始化）：

// [代码 7]
// switch (1)
// {
//     int a; // okay: case标签之前可以声明变量
//     int b{ 5 }; // 不合法: case 标签之前，不可以初始化变量
//
//     case 1:
//         int y; // okay 但不推荐
//         y = 4; // okay: 赋值语句可以
//         break;
//
//     case 2:
//         int z{ 4 }; // 不合法: 后面还有case标签，不允许初始化变量
//         y = 5; // okay: y 在上面声明，所以这里可以赋值
//         break;
//
//     case 3:
//         break;
// }

// 在case 1中定义了变量y，并在case 2中使用了它。switch内的所有语句都被视为同一
// 作用域的一部分。因此，在case 1内声明或定义的变量可以在之后使用。
//
// 然而，变量初始化需要在运行时执行（因为需要把初始值设置给变量）。如果后续还
// 有case标签，则不允许初始化变量（因为初始化可能被跳过，从而使变量未初始化）。
// 在第一个case标签之前也不允许初始化，因为这些语句永远不会执行，switch语句无
// 法跳转到它们。
//
// 如果case标签内需要定义并初始化新变量，最佳实践是在case语句下的显式代码块内
// 完成：

// [代码 8]
// switch (1)
// {
//     case 1:
//     { // 这里有一个显示的代码块
//         int x{ 4 }; // okay, 变量在一个新的代码块内初始化
//         std::cout << x;
//         break;
//     }
//     default:
//         std::cout << "default case\n";
//         break;
// }

// 最佳实践
//
// 如果定义case语句中使用的变量，请在case内的显示代码块中定义。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 编写一个名为`calculate()`的函数，它接受两个整数和一个表示数学运算的char（可
// 选 +、-、*、/ 或 %（取余））。使用switch语句对这两个整数执行相应的数学运算
// 并返回结果。如果传入了无效的运算符，函数应当打印一条错误信息。对于除法，执
// 行整数除法，不必考虑除数为0的情况。
//
// 提示：「operator」是关键字，变量不能命名为「operator」。

// 【答案 · 查看答案】

// [代码 9]
// #include <iostream>
//
// int calculate(int x, int y, char op)
// {
//     switch (op)
//     {
//     case '+':
//         return x + y;
//     case '-':
//         return x - y;
//     case '*':
//         return x * y;
//     case '/':
//         return x / y;
//     case '%':
//         return x % y;
//     default:
//         std::cout << "calculate(): Unhandled case\n";
//         return 0;
//     }
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
//     std::cout << "Enter a mathematical operator (+, -, *, /, or %): ";
//     char op{};
//     std::cin >> op;
//
//     // 先调用 calculate，这样遇到无效运算符时错误信息会单独占一行
//     int result{ calculate(x, y, op) };
//     std::cout << x << ' ' << op << ' ' << y << " is " << result << '\n';
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
    switch (2)
    {
    case 1: // 不匹配
        std::cout << 1 << '\n'; // 跳过
    case 2: // 匹配
        std::cout << 2 << '\n'; // 从这里开始执行
    case 3:
        std::cout << 3 << '\n'; // 这里也会执行
    case 4:
        std::cout << 4 << '\n'; // 这里也会执行
    default:
        std::cout << 5 << '\n'; // 这里也会执行
    }

    return 0;
}
