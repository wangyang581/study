// ==========================================================================
// 13.14 如何使用c++语言手册
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十三章 复合类型：枚举与结构体
// 原文: https://www.studycpp.cn/basic/chapter13/use-cpp-ref/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "13.14-use-cpp-ref.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 概述
//   · std::string::length
//   · std::cin.ignore
//   · 语言语法示例
//   · 关于cppreference准确性的警告
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 根据您当前学习的进度，本网站可能是您用于学习C++或查找内容的唯一资源。本网站
// 旨在以初学者友好的方式解释概念，但它不能涵盖C++语言的所有方面。当您开始探索
// 本教程无法覆盖的主题时，不可避免地会遇到本教程无法回答的问题。在这种情况下，
// 您需要利用外部资源。
//
// 一个非常好的查询来源是C++语言手册。本教程倾向于关注比较重要的主题，并使用非
// 正式或通用语言来降低学习难度；与之不同，语言手册使用正式术语精确地描述C++。
// 因此，参考手册往往全面、准确，但也更难理解。
//
// 在本课中，将通过3个示例来展示如何使用cppreference网站（
// https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5 ）。
//

// ―――― 概述 ――――

// 网站首页上包含核心语言以及标准库：
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/sy.png
// 首页
//
// 从这里可以看到C++手册网站上的所有内容，不过使用搜索功能或搜索引擎通常更容易
// 找到想了解的部分。完成本网站上的教程后，这个概览页面是进一步研究标准库、查
// 看语言特性的好入口。
//
// 表的上半部分显示该语言当前已有的功能，而下半部分显示技术规范。这些功能可能
// 会在未来版本中加入C++，也可能不会加入，或者已经被语言部分接受。如果想了解即
// 将推出的新功能，这可能很有用。
//
// 从C++11开始，新增的功能会标记出来是哪个版本添加的。这是上图中一些链接旁边的
// 绿色小数字。没有版本号的功能从C++98/03开始提供。版本号不仅在概述中，而且在
// 手册上无处不在，让您确切地知道在特定的C++版本中可以使用或不能使用什么。
//
// 提示
//
// C++语言手册中包含C语言与C++语言两部分。由于C++与C共享一些函数名，因此搜索某
// 些内容后，您可能会进入C语言部分。
//

// ―――― std::string::length ――――

// 我们之前已经了解过std::string::length，该函数返回字符串的长度。
//
// 在cppreference首页，点击字符串库，查看字符串相关的文档。
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/str.png
// 字符串库
//
// 这里可以看到，字符串库会根据字符串中存储的字符类型提供多个对应类型。
// std::string其实是std::basic_string<char>的别名。<char>表示字符串里的每个字
// 符都是char类型；当想在字符串里存储Unicode而不是ASCII字符时，其他类型可能会
// 更合适。
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/str_char.jpg
// 字符串库详情
//
// 点击std::string，可以查看对应的手册。在下面，对应的小节里，可以看到，有一个
// length成员函数，返回字符串中的字符数。
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/str_len.png
// 字符串库详情
//
// 点击进去，可以看到length函数对应的功能介绍、参数、返回值以及使用样例。
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/str_len_detail.png
// str len详情
//
// 因为std::string::length是一个简单的函数，所以该页面上没有太多内容。
//
// 学习C++时，示例中会出现一些您以前没有见过的功能。可以点击对应的链接跳转过去
// 学习。
//

// ―――― std::cin.ignore ――――

// 在前面，我们学习了std::cin.ignore，它用于忽略直到换行符的所有内容。该函数的
// 参数之一是一些冗长的值。那又是什么？让我们弄清楚！
//
// 首先，cin是流式输入，因此，我们点击“基于流的输入/输出”。
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/index_iostream.png
// 基于流的输入输出
//
// 在对应的页面上，可以找到cin的说明，继续点击查看细节。
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/iostream.png
// iostream
//
// 这个页面上，可以看到std::cin和std::wcin的声明，并告诉我们它们所在的头文件。
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/cin.png
// cin
//
// 这里并没有ignore相关的讲解，但可以看到，std::cin是一个类型为std::istream的
// 对象。让我们访问std::istream的链接。
//
// 哦，在这个页面，我们看到了熟悉的内容，继续点击。
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/istream.png
// istream 、
//
// 在页面顶部有函数签名和其两个参数的描述。参数后面的=符号表示默认参数）。如果
// 没有为具有默认值的参数提供值，则使用默认值。
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/ignore.png
// ignore
//
// 这里回到了我们最初的问题。可以看到，
// std::numeric_limits<std::streamsize>::max()对std::cin.ignore具有特殊意义，
// 它会禁用字符计数检查。这意味着std::cin.ignore将继续忽略字符，直到找到分隔符，
// 或者直到没有更多可查看的字符。
//
// 许多时候，如果您已经知道函数的整个描述，但忘记了参数或返回值的含义，则不需
// 要阅读它的整个描述。在这种情况下，读取参数或返回值描述就足够了。
//

// ―――― 语言语法示例 ――――

// 除了标准库之外，cppreference还记录了语言语法。下面是一个示例程序：

// [代码 1]
// #include <iostream>
//
// int getUserInput()
// {
//   int i{};
//   std::cin >> i;
//   return i;
// }
//
// int main()
// {
//   std::cout << "How many bananas did you eat today? \n";
//
//   if (int iBananasEaten{ getUserInput() }; iBananasEaten <= 2)
//   {
//     std::cout << "Yummy\n";
//   }
//   else
//   {
//     std::cout << iBananasEaten << " is a lot!\n";
//   }
//
//   return 0;
// }

// 为什么在if语句的条件中会有变量定义？让我们使用cppreference查看一下if的语法。
// [图片] https://www.studycpp.cn/basic/chapter13/use-cpp-ref/if.png
// if
//
// 在这里可以看到，在条件之前有一个可选的初始化语句，它正对应上面代码中的写法。
//
// 在语法参考下面，有语法的每个部分的解释，包括初始化语句。它表示初始化语句通
// 常是具有初始值设定项的变量的声明。
//
// 然后，将页面往下滚动一点，就可以看到对应示例。当然，这里的例子包含很多我们
// 还没介绍的功能，但即使不理解这些，也可以看明白初始化语句的使用方式：

// [代码 2]
// // 迭代器, 还没学过，跳过
// if (auto it = m.find(10); it != m.end()) { return it->second.size(); }
//
// // [10], 啥东西? 跳过.
// if (char buf[10]; std::fgets(buf, 10, stdin)) { m[0] += buf; }
//
// // std::lock_guard, 肯定是个类型反正
// if (std::lock_guard lock(mx); shared_flag) { unsafe_ping(); shared_flag = false; }
//
// // 这个很简单, 定了个 int 变量!
// if (int s; int count = ReadBytesWithSignal(&s)) { publish(count); raise(s); }
//
// // Oh, 似乎有些复杂!
// if (auto keywords = {"if", "for", "while"};
//     std::any_of(keywords.begin(), keywords.end(),
//                 [&s](const char* kw) { return s == kw; })) {
//   std::cerr << "Token must not be a keyword\n";
// }

//

// ―――― 关于cppreference准确性的警告 ――――

// Cppreference不是官方文档——它是一个wiki。作为Wiki，任何人都可以添加和修改内
// 容，内容来自社区。尽管这意味着有人可能添加错误信息，但错误信息通常会很快被
// 发现并删除，使cppreference成为相当可靠的来源。
//
// C++的唯一官方来源是官方标准（ https://isocpp.org/std/the-standard ），这是
// 正式文档，但不太适合作为日常参考。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 下面这个程序会打印什么？不要运行它，而是查阅语言手册弄清`erase`的作用。

// [代码 3]
// #include <iostream>
// #include <string>
//
// int main()
// {
//   std::string str{ "The rice is cooking" };
//
//   str.erase(4, 11);
//
//   std::cout << str << '\n';
//
//   return 0;
// }

// 提示：
//
// 在cppreference上找到`erase`后，可以忽略那些使用迭代器的重载版本。
//
// C++中的下标从0开始。字符串「House」中下标0处的字符是「H」，下标1处是「o」，
// 依此类推。

// 【答案 · 查看答案】
// 输出为：

// [文本/输出]
// The king

// 下面是通过cppreference上的搜索功能找到答案的过程（你可能用搜索引擎跳过了第
// 一步）：
//
// 搜索string并点击「std::string」，会跳转到`std::basic_string`。
//
// 向下滚动到「Member functions」列表，找到erase。正如上面提示中提到的，这里使
// 用的是第一个函数重载。它接受2个`size_type`（无符号整数类型）实参，在本例中
// 是4和11。按照(1)的描述，它会从`index`处开始删除「`min(count, size() -
// index)`个字符」。代入实参，即从下标4处开始删除`min(11, 19 - 4) = 11`个字符。

// ▼ 问题 2
// 在下面的代码中，修改`str`，使它的值为「I saw a blue car yesterday.」，但不
// 要重复书写整个字符串。例如，不要这样写：

// [代码 4]
// str = "I saw a blue car yesterday.";

// 你只需要调用一个函数，把「red」替换为「blue」。

// [代码 5]
// #include <iostream>
// #include <string>
//
// int main()
// {
//   std::string str{ "I saw a red car yesterday." };
//
//   // ...
//
//   std::cout << str << '\n'; // I saw a blue car yesterday.
//
//   return 0;
// }


// 【答案 · 显示提示】
// `std::basic_string`

// 【答案 · 显示提示】
// `std::basic_string`的成员函数

// 【答案 · 显示提示】
// `std::basic_string`的修饰符（Modifiers）

// 【答案 · 显示提示】
// `std::basic_string::replace`

// 【答案 · 查看答案】

// [代码 6]
// #include <iostream>
// #include <string>
//
// int main()
// {
//   std::string str{ "I saw a red car yesterday." };
//
//   str.replace(8, 3, "blue");
//
//   std::cout << str << '\n'; // I saw a blue car yesterday.
//
//   return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int getUserInput()
{
  int i{};
  std::cin >> i;
  return i;
}

int main()
{
  std::cout << "How many bananas did you eat today? \n";

  if (int iBananasEaten{ getUserInput() }; iBananasEaten <= 2)
  {
    std::cout << "Yummy\n";
  }
  else
  {
    std::cout << iBananasEaten << " is a lot!\n";
  }

  return 0;
}
