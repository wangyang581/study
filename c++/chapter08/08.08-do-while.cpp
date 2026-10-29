// ==========================================================================
// 8.8 Do while语句
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第八章 控制流与错误处理
// 原文: https://www.studycpp.cn/basic/chapter8/do-while/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "08.08-do-while.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · Do while语句

// ==========================================================================
// 教程正文
// ==========================================================================

// 考虑这样一种情况：我们想向用户显示一个菜单，并要求他们进行选择。如果用户选
// 择了无效选项，就再次询问。显然，菜单显示和用户选择应该放在某种循环中（需要
// 一直询问用户，直到他们输入有效选项），但我们应该选择哪种循环？
//
// 由于while循环会先计算条件表达式，因此它不太适合这种“先选择，再判断”的场景。
// 可以这样解决问题：

// [代码 1]
// #include <iostream>
//
// int main()
// {
//     // 选项需要在循环外定义, 以便稍后使用
//     int selection{ 0 };
//
//     while (selection != 1 && selection != 2 &&
//         selection != 3 && selection != 4)
//     {
//         std::cout << "Please make a selection: \n";
//         std::cout << "1) Addition\n";
//         std::cout << "2) Subtraction\n";
//         std::cout << "3) Multiplication\n";
//         std::cout << "4) Division\n";
//         std::cin >> selection;
//     }
//
//     // 处理用户的选择
//     // 例如可以使用switch语句
//
//     std::cout << "You selected option #" << selection << '\n';
//
//     return 0;
// }

// 但这只是因为用于选择的初始值0不在有效值集合（1、2、3或4）中。如果0也是有效
// 选择怎么办？那就必须选择另一个初始值来表示“无效项”，从而在代码中引入魔数。
//
// 或者，也可以添加一个新变量，用来跟踪用户是否输入了有效值，如下所示：

// [代码 2]
// #include <iostream>
//
// int main()
// {
//     int selection { 0 };
//     bool invalid { true }; // 新变量，来代表用户是否输入有效值
//
//     while (invalid)
//     {
//         std::cout << "Please make a selection: \n";
//         std::cout << "1) Addition\n";
//         std::cout << "2) Subtraction\n";
//         std::cout << "3) Multiplication\n";
//         std::cout << "4) Division\n";
//
//         std::cin >> selection;
//         invalid = (selection != 1 && selection != 2 &&
//             selection != 3 && selection != 4);
//     }
//
//     // 处理用户的选择
//     // 例如可以使用switch语句
//
//     std::cout << "You selected option #" << selection << '\n';
//
//     return 0;
// }

// 虽然这避免了魔数，但它引入了一个新变量，而这个变量只是为了确保循环至少运行
// 一次。这会增加复杂性，也会增加出错的可能性。
//

// ―――― Do while语句 ――――

// 为了帮助解决上述问题，C++提供了do-while语句：

// [代码 3]
// do
//     语句; // 可以是单条语句，或代码块
// while (条件表达式);

// do-while语句是一种循环语句，其工作方式类似于while循环，但循环体至少会执行一
// 次。执行完循环体后，do-while循环会检查条件。如果条件的计算结果为true，则执
// 行路径会跳回do-while循环顶部，并再次执行循环体。
//
// 下面是使用do-while改造上面程序的示例：

// [代码 4]
// #include <iostream>
//
// int main()
// {
//     // 选项需要在循环外定义, 以便稍后使用
//     int selection{};
//
//     do
//     {
//         std::cout << "Please make a selection: \n";
//         std::cout << "1) Addition\n";
//         std::cout << "2) Subtraction\n";
//         std::cout << "3) Multiplication\n";
//         std::cout << "4) Division\n";
//         std::cin >> selection;
//     }
//     while (selection != 1 && selection != 2 &&
//         selection != 3 && selection != 4);
//
//     // 处理用户的选择
//     // 例如可以使用switch语句
//
//     std::cout << "You selected option #" << selection << '\n';
//
//     return 0;
// }

// 通过这种方式，我们避免了魔数，也不需要额外的变量。
//
// 在上面的例子中，有一点值得讨论：selection变量必须在do代码块之外声明。如果
// selection变量在do代码块内声明，那么当代码块结束时，变量会被销毁，而这发生在
// 条件表达式求值之前。因此，selection变量必须在do代码块之外声明（即使它之后没
// 有在函数体的其他位置使用）。
//
// 在实践中，do-while语句并不常用。将条件放在循环底部会让循环条件不够醒目，可
// 能导致错误。因此，许多开发人员建议完全避免do-while循环。这里采取更温和的立
// 场：在两者都适用时，优先选择while循环，而不是do-while循环。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
    // 选项需要在循环外定义, 以便稍后使用
    int selection{ 0 };

    while (selection != 1 && selection != 2 &&
        selection != 3 && selection != 4)
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }

    // 处理用户的选择
    // 例如可以使用switch语句

    std::cout << "You selected option #" << selection << '\n';

    return 0;
}
