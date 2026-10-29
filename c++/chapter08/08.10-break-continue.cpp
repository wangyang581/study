// ==========================================================================
// 8.10 break与continue
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第八章 控制流与错误处理
// 原文: https://www.studycpp.cn/basic/chapter8/break-continue/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "08.10-break-continue.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · break
//   · switch中的break
//   · break跳出循环
//   · break与return
//   · continue
//   · 提前返回

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― break ――――

// 之前学习switch语句时，我们已经对break有了一定了解。这里对break做一个更全面
// 的总结。break语句会结束while循环、do-while循环、for循环或switch语句，并继续
// 执行循环或switch之后的下一条语句。
//

// ―――― switch中的break ――――

// 在switch语句的上下文中，通常在每个case的末尾使用break来表示case已完成（这可
// 以防止fallthrough到下一个case中）：

// [代码 1]
// #include <iostream>
//
// void printMath(int x, int y, char ch)
// {
//     switch (ch)
//     {
//     case '+':
//         std::cout << x << " + " << y << " = " << x + y << '\n';
//         break; // 不会 fall-through 到下一个标签
//     case '-':
//         std::cout << x << " - " << y << " = " << x - y << '\n';
//         break; // 不会 fall-through 到下一个标签
//     case '*':
//         std::cout << x << " * " << y << " = " << x * y << '\n';
//         break; // 不会 fall-through 到下一个标签
//     case '/':
//         std::cout << x << " / " << y << " = " << x / y << '\n';
//         break;
//     }
// }
//
// int main()
// {
//     printMath(2, 3, '+');
//
//     return 0;
// }

//

// ―――― break跳出循环 ――――

// 在循环的上下文中，可以使用break语句提前结束循环，并继续执行循环后的下一条语
// 句。
//
// 例如：

// [代码 2]
// #include <iostream>
//
// int main()
// {
//     int sum{ 0 };
//
//     // 允许用户最多输入10次
//     for (int count{ 0 }; count < 10; ++count)
//     {
//         std::cout << "Enter a number to add, or 0 to exit: ";
//         int num{};
//         std::cin >> num;
//
//         // 用户输入0，直接跳出循环
//         if (num == 0)
//             break; // 跳出循环
//
//         // 将用户输入的值累加
//         sum += num;
//     }
//
//     // for循环break之后继续执行
//     std::cout << "The sum of all the numbers you entered is: " << sum << '\n';
//
//     return 0;
// }

// 该程序允许用户最多键入10个数字，并打印所有输入数字的总和。如果用户输入0，
// break会导致循环提前终止（在输入10个数字之前）。
//
// 下面是执行示例：

// [文本/输出]
// Enter a number to add, or 0 to exit: 5
// Enter a number to add, or 0 to exit: 2
// Enter a number to add, or 0 to exit: 1
// Enter a number to add, or 0 to exit: 0
// The sum of all the numbers you entered is: 8

// break也是主动跳出无限循环的常见方法：

// [代码 3]
// #include <iostream>
//
// int main()
// {
//     while (true) // 无限循环
//     {
//         std::cout << "Enter 0 to exit or any other integer to continue: ";
//         int num{};
//         std::cin >> num;
//
//         // 用户输入0，直接跳出循环
//         if (num == 0)
//             break;
//     }
//
//     std::cout << "We're out!\n";
//
//     return 0;
// }

// 上述程序的示例运行：

// [文本/输出]
// Enter 0 to exit or any other integer to continue: 5
// Enter 0 to exit or any other integer to continue: 3
// Enter 0 to exit or any other integer to continue: 0
// We're out!

//

// ―――― break与return ――――

// 新程序员有时难以理解break与return之间的区别。break语句会终止switch或循环，
// 并在switch或循环之后的第一条语句处继续执行。return语句会终止循环所在的整个
// 函数，并回到调用该函数的位置继续执行。

// [代码 4]
// #include <iostream>
//
// int breakOrReturn()
// {
//     while (true) // 无限循环
//     {
//         std::cout << "Enter 'b' to break or 'r' to return: ";
//         char ch{};
//         std::cin >> ch;
//
//         if (ch == 'b')
//             break; // 会执行循环后的第一条语句
//
//         if (ch == 'r')
//             return 1; // 结束执行，并返回到调用函数（这里是main()函数）
//     }
//
//     // 上面的break语句执行后，会在这里继续执行
//
//     std::cout << "We broke out of the loop\n";
//
//     return 0;
// }
//
// int main()
// {
//     int returnValue{ breakOrReturn() };
//     std::cout << "Function breakOrReturn returned " << returnValue << '\n';
//
//     return 0;
// }

// 下面是该程序的两次运行：

// [文本/输出]
// Enter 'b' to break or 'r' to return: r
// Function breakOrReturn returned 1


// [文本/输出]
// Enter 'b' to break or 'r' to return: b
// We broke out of the loop
// Function breakOrReturn returned 0

//

// ―――― continue ――――

// continue语句提供了一种方法，可以在不终止整个循环的情况下结束当前迭代。
//
// 下面是使用continue的示例：

// [代码 5]
// #include <iostream>
//
// int main()
// {
//     for (int count{ 0 }; count < 10; ++count)
//     {
//         // 如果count被4整除, 结束本轮迭代
//         if ((count % 4) == 0)
//             continue; // 进入下一次迭代
//
//         // 否则正常执行
//         std::cout << count << '\n';
//
//         // 后续的其他可能的语句
//     }
//
//     return 0;
// }

// 该程序打印0到9之间不能被4整除的所有数字：
//
// continue语句的工作方式是让当前执行点跳到当前循环的底部。
//
// 在for循环中，for循环的递增/递减语句（在上面的示例中是++count）仍然会在
// continue之后执行（因为它发生在循环体末尾之后）。
//
// 将continue语句与while或do-while循环一起使用时要小心。这些循环通常在循环体内
// 修改循环变量。如果continue语句跳过了这些修改语句，循环可能会变成无限循环！
//
// 考虑以下程序：

// [代码 6]
// #include <iostream>
//
// int main()
// {
//     int count{ 0 };
//     while (count < 10)
//     {
//         if (count == 5)
//             continue; // 调到循环体末尾
//
//         std::cout << count << '\n';
//
//         ++count; // 如果count加到 5 之后，这条语句永远不会再执行
//
//         // continue 语句跳到这里
//     }
//
//     return 0;
// }

// 该程序本想打印0到9之间除5以外的每个数字。但它实际打印：
//
// 然后进入无限循环。当count为5时，if语句的计算结果为true，continue导致执行跳
// 到循环底部。++count不会被执行。因此，在下一次迭代中，count仍然是5，if语句仍
// 然为true，程序会一直循环下去。
//
// 当然，您已经知道，如果有一个明显的计数器变量，则应该使用for循环，而不是
// while或do-while循环。
//

// ―――― 提前返回 ――――

// 不是函数中最后一条语句的return语句称为提前返回（early return）。许多程序员
// 认为应该避免提前返回。只在函数最底部使用return语句有其简单性——函数接收参数，
// 执行逻辑，然后返回结果。额外的return会让逻辑变复杂。
//
// 但是，使用提前返回可以让函数在完成任务后立即退出，减少不必要的逻辑判断，并
// 尽量减少条件嵌套，从而让代码更具可读性。
//
// 一些开发人员采取中间立场，只在函数顶部使用提前返回来进行参数验证（捕获传入
// 的错误参数）。
//
// 我们的立场是：提前返回通常利大于弊。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

void printMath(int x, int y, char ch)
{
    switch (ch)
    {
    case '+':
        std::cout << x << " + " << y << " = " << x + y << '\n';
        break; // 不会 fall-through 到下一个标签
    case '-':
        std::cout << x << " - " << y << " = " << x - y << '\n';
        break; // 不会 fall-through 到下一个标签
    case '*':
        std::cout << x << " * " << y << " = " << x * y << '\n';
        break; // 不会 fall-through 到下一个标签
    case '/':
        std::cout << x << " / " << y << " = " << x / y << '\n';
        break;
    }
}

int main()
{
    printMath(2, 3, '+');

    return 0;
}
