// ==========================================================================
// 13.2 非限定作用域枚举的输入与输出
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十三章 复合类型：枚举与结构体
// 原文: https://www.studycpp.cn/basic/chapter13/unscoped-enum-io/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "13.02-unscoped-enum-io.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 非限定作用域枚举将隐式转换为整数值
//   · 打印枚举元素名称
//   · 设定运算符«以打印枚举数
//   · 枚举大小和底层类型
//   · 整数到非限定作用域枚举转换
//   · 非限定作用域枚举输入
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 在上一课中，我们提到枚举元素是符号常量。还没有说明的是，枚举元素是整型符号
// 常量。因此，枚举类型实际上保存的是整数值。
//
// 这类似于使用char的情况。考虑：

// [代码 1]
// char ch { 'A' };

// char本质上只是一个1字节的整数值，字符’A’会被转换为整数值（在本例中为65）并
// 存储。
//
// 定义枚举时，每个枚举元素都会根据其在枚举列表中的位置自动分配一个整数值。默
// 认情况下，为第一个枚举元素分配整数值0，并且每个后续枚举元素的值都比前一个大
// 一：

// [代码 2]
// enum Color
// {
//     black, // 值为 0
//     red, // 1
//     blue, // 2
//     green, // 3
//     white, // 4
//     cyan, // 5
//     yellow, // 6
//     magenta, // 7
// };
//
// int main()
// {
//     Color shirt{ blue }; // shirt 实际存储了整数值 2
//
//     return 0;
// }

// 可以显式定义枚举元素的值。这些整数值可以是正值或负值，并且可以与其他枚举元
// 素共享相同的值。任何未定义的枚举元素都被赋予比前一个大一的值。

// [代码 3]
// enum Animal
// {
//     cat = -3,
//     dog,         // 值为 -2
//     pig,         // -1
//     horse = 5,
//     giraffe = 5, // 与 horse 存储相同的值
//     chicken,      // 6
// };

// 注意，在这种情况下，horse和giraffe被赋予了相同的值。发生这种情况时，枚举元
// 素会变得无法区分——本质上，horse和giraffe在使用时可以互换。尽管C++允许这样做，
// 但通常应避免将相同的值分配给同一枚举中的两个枚举元素。
//
// 最佳实践
//
// 避免将显式值分配给枚举元素，除非有令人信服的理由这样做。
//

// ―――― 非限定作用域枚举将隐式转换为整数值 ――――

// 考虑以下程序：

// [代码 4]
// #include <iostream>
//
// enum Color
// {
//     black, // 0
//     red, // 1
//     blue, // 2
//     green, // 3
//     white, // 4
//     cyan, // 5
//     yellow, // 6
//     magenta, // 7
// };
//
// int main()
// {
//     Color shirt{ blue };
//
//     std::cout << "Your shirt is " << shirt << '\n'; // 这一行的效果是?
//
//     return 0;
// }

// 由于枚举类型保存的是整数值，因此正如您所预期的那样，这会打印：

// [文本/输出]
// Your shirt is 2

// 在函数调用中或与运算符一起使用枚举类型时，编译器会首先尝试查找与枚举类型匹
// 配的函数或运算符。例如，当编译器尝试编译 std::cout « shirt 时，会先查看 运
// 算符« 是否知道如何将Color类型的对象（因为shirt的类型是Color）打印到
// std::cout。这里找不到匹配项。
//
// 如果编译器找不到匹配项，则编译器将隐式地将枚举元素转换为其相应的整数值。因
// 为std::cout可以打印整数值，所以shirt中的值被转换为整数并打印为整数值2。
//

// ―――― 打印枚举元素名称 ――――

// 在大多数情况下，将枚举打印为整数值（如2）并不是我们想要的。相反，通常希望打
// 印枚举元素表示的名称（blue）。但要做到这一点，需要某种方法将枚举的整数值（2）
// 转换为与枚举元素名称（“blue”）匹配的字符串。
//
// 截至C++20，C++没有简单的内置方式来实现这一点，因此必须自己实现解决方案。幸
// 运的是，这并不困难。典型方法是编写一个函数，将枚举类型作为参数，然后输出相
// 应的字符串（或将字符串返回给调用方）。

// [代码 5]
// // 这里使用if else，运行效率不高
// void printColor(Color color)
// {
//     if (color == black) std::cout << "black";
//     else if (color == red) std::cout << "red";
//     else if (color == blue) std::cout << "blue";
//     else std::cout << "???";
// }

// 然而，为此使用一系列if-else语句是低效的，因为它需要在找到匹配之前进行多次比
// 较。执行相同操作的更有效的方法是使用switch语句。在下面的示例中，将Color转换
// 为std::string返回，以使调用方能够更灵活地对名称执行任何操作（包括打印它）：

// [代码 6]
// #include <iostream>
// #include <string>
//
// enum Color
// {
//     black,
//     red,
//     blue,
// };
//
// std::string getColor(Color color)
// {
//     switch (color)
//     {
//     case black: return "black";
//     case red:   return "red";
//     case blue:  return "blue";
//     default:    return "???";
//     }
// }
//
// int main()
// {
//     Color shirt { blue };
//
//     std::cout << "Your shirt is " << getColor(shirt) << '\n';
//
//     return 0;
// }

// 这将打印：

// [文本/输出]
// Your shirt is blue

// 这比if-else链执行得更好（switch语句往往比if-else链更有效），并且也更容易阅
// 读。然而，这个版本仍然效率低下，因为需要在每次调用函数时创建并返回
// std::string（这很昂贵）。
//
// 在C++17中，一个更有效的选项是用std::string_view替换std::string。string_view
// 允许以一种复制成本低得多的方式返回字符串文本。

// [代码 7]
// #include <iostream>
// #include <string_view> // C++17
//
// enum Color
// {
//     black,
//     red,
//     blue,
// };
//
// constexpr std::string_view getColor(Color color) // C++17
// {
//     switch (color)
//     {
//     case black: return "black";
//     case red:   return "red";
//     case blue:  return "blue";
//     default:    return "???";
//     }
// }
//
// int main()
// {
//     constexpr Color shirt{ blue };
//
//     std::cout << "Your shirt is " << getColor(shirt) << '\n';
//
//     return 0;
// }

//

// ―――― 设定运算符«以打印枚举数 ――――

// 尽管上面的示例运行良好，但我们仍然必须记住创建的函数名称，才能获得枚举元素
// 名称。虽然这通常不算繁琐，但如果有许多枚举，就可能变得麻烦。使用运算符重载
// （类似于函数重载的功能），实际上可以设定运算符«如何打印程序定义的枚举！我们
// 还没有解释这是如何工作的，所以现在它看起来有点神奇：

// [代码 8]
// #include <iostream>
//
// enum Color
// {
// 	black,
// 	red,
// 	blue,
// };
//
// // 设定 operator<< 如何打印 Color
// // 现在可能看起来有点神奇，后续进行介绍
// // std::ostream 是 std::cout 的类型
// // 返回值与参数都是引用 (避免制作副本)!
// std::ostream& operator<<(std::ostream& out, Color color)
// {
// 	switch (color)
// 	{
// 	case black: return out << "black";
// 	case red:   return out << "red";
// 	case blue:  return out << "blue";
// 	default:    return out << "???";
// 	}
// }
//
// int main()
// {
// 	Color shirt{ blue };
// 	std::cout << "Your shirt is " << shirt << '\n'; // it works!
//
// 	return 0;
// }

// 这将打印：

// [文本/输出]
// Your shirt is blue

// 我们会在后续课程中讨论I/O运算符的重载。现在，您可以复制此代码，并将Color替
// 换为自己的枚举类型。
//
// 对于高级读者
//
// 这里简要介绍上面代码的作用。当尝试使用std::cout和 运算符« 打印shirt时，编译
// 器将看到我们重载了 运算符« 来处理Color类型的对象。然后使用std::cout作为out
// 参数，使用shirt作为参数color来调用该重载 运算符« 对应的函数。由于out是对
// std::cout的引用，因此像 out « “blue” 这样的语句实际上只是将"blue"打印到
// std::cout。
//

// ―――― 枚举大小和底层类型 ――――

// 枚举元素是整型常量。用于表示枚举元素的具体整型类型称为其底层类型。
//
// 对于非限定作用域枚举，C++标准没有指定应将哪个特定的整型用作底层类型。大多数
// 编译器将使用类型int作为底层类型（这意味着非限定作用域枚举将与int大小相同），
// 除非需要更大的类型来存储枚举元素值。
//
// 可以指定不同的底层类型。例如，如果您在某些对带宽敏感的环境中工作（例如通过
// 网络发送数据），可能需要指定较小的类型：

// [代码 9]
// #include <cstdint>  // for std::int8_t
// #include <iostream>
//
// // 使用 8-bit 整数作为 Color 的底层类型
// enum Color : std::int8_t
// {
//     black,
//     red,
//     blue,
// };
//
// int main()
// {
//     Color c{ black };
//     std::cout << sizeof(c) << '\n'; // 打印 1 (字节)
//
//     return 0;
// }

// 最佳实践
//
// 仅在必要时指定枚举的底层类型。
//
// 警告
//
// 由于std::int8_t和std::uint8_t通常是char类型的类型别名，因此使用这两种类型之
// 一作为枚举底层类型很可能会导致枚举元素打印为char值，而不是int值。
//

// ―――― 整数到非限定作用域枚举转换 ――――

// 虽然编译器会隐式地将非限定作用域枚举转换为整数，但它不会隐式地把整数转换为
// 非限定作用域枚举。以下操作会产生编译器错误：

// [代码 10]
// enum Pet // 未指定底层类型
// {
//     cat, // 0
//     dog, // 1
//     pig, // 2
//     whale, // 3
// };
//
// int main()
// {
//     Pet pet { 2 }; // 编译错误: 整数 2 不能隐式的转换为 Pet
//     pet = 3;       // 编译错误: 整数 3 不能隐式的转换为 Pet
//
//     return 0;
// }

// 有两种方法可以解决这个问题。
//
// 首先，可以使用static_cast强制编译器将整数转换为枚举元素：

// [代码 11]
// enum Pet // 未指定底层类型
// {
//     cat, // 0
//     dog, // 1
//     pig, // 2
//     whale, // 3
// };
//
// int main()
// {
//     Pet pet { static_cast<Pet>(2) }; // 将整数 2 转换为 Pet
//     pet = static_cast<Pet>(3);       // pet 从 pig 变成了 whale!
//
//     return 0;
// }

// 稍后我们将看到一个示例，这个功能是有实际用途的。
//
// 第二，在C++17中，如果非限定作用域枚举具有指定的底层类型，则编译器将允许您使
// 用整数值来列表初始化非限定作用域枚举：

// [代码 12]
// enum Pet: int // 指定底层类型
// {
//     cat, // 0
//     dog, // 1
//     pig, // 2
//     whale, // 3
// };
//
// int main()
// {
//     Pet pet1 { 2 }; // ok: 使用列表初始化
//     Pet pet2 (2);   // 编译错误: 不能使用整数做直接初始化
//     Pet pet3 = 2;   // 编译错误: 不能使用整数做复制初始化
//
//     pet1 = 3;       // 编译错误: 不能使用整数赋值
//
//     return 0;
// }

//

// ―――― 非限定作用域枚举输入 ――――

// 由于Pet是程序定义的类型，因此C++不知道如何使用std::cin获取Pet：

// [代码 13]
// #include <iostream>
//
// enum Pet
// {
//     cat, // 0
//     dog, // 1
//     pig, // 2
//     whale, // 3
// };
//
// int main()
// {
//     Pet pet { pig };
//     std::cin >> pet; // 编译失败, std::cin 不知道如何获取Pet
//
//     return 0;
// }

// 为了解决这个问题，可以读取整数，并使用static_cast将该整数转换为适当枚举元素：

// [代码 14]
// #include <iostream>
//
// enum Pet
// {
//     cat, // 0
//     dog, // 1
//     pig, // 2
//     whale, // 3
// };
//
// int main()
// {
//     std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";
//
//     int input{};
//     std::cin >> input; // 输入整数
//
//     Pet pet{ static_cast<Pet>(input) }; // static_cast 将整数转换为Pet
//
//     return 0;
// }

// 对于高级读者
//
// 类似于如何设定 运算符« 输出枚举类型，还可以设定 运算符» 如何输入枚举类型：

// [代码 15]
// #include <iostream>
//
// enum Pet
// {
//     cat, // 0
//     dog, // 1
//     pig, // 2
//     whale, // 3
// };
//
// // 目前可能看起来有些神奇
// // 传递引用，以便可以在函数中修改输入
// std::istream& operator>> (std::istream& in, Pet& pet)
// {
//     int input{};
//     in >> input; // 读取一个整数
//
//     pet = static_cast<Pet>(input);
//     return in;
// }
//
// int main()
// {
//     std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";
//
//     Pet pet{};
//     std::cin >> pet; // 使用 std::cin 获取输入的 pet
//
//     std::cout << pet << '\n'; // 验证运行正常
//
//     return 0;
// }

//

// ―――― 习题 ――――


// ▼ 问题 1
// 判断下列说法是否正确。枚举元素可以被：
// - 赋予一个整数值

// 【答案 · 查看答案】
// 正确
// - 不赋予显式值

// 【答案 · 查看答案】
// 正确。没有被显式赋值的枚举元素会被隐式赋予前一个枚举元素的整数值加1。如果前
// 面没有枚举元素，则该枚举元素取值为0。
// - 赋予一个浮点值

// 【答案 · 查看答案】
// 错误
// - 赋予一个负值

// 【答案 · 查看答案】
// 正确
// - 赋予一个不唯一的值

// 【答案 · 查看答案】
// 正确
// - 赋予前面某个枚举元素的值（例如 magenta = red）

// 【答案 · 查看答案】
// 正确。枚举元素不必互不相同。由于枚举元素会隐式转换为整数，而整数可以被赋予
// 枚举元素，因此枚举元素可以用其他枚举元素来初始化（不过通常没什么理由这样做！
// ）。
// - 赋予一个非constexpr值

// 【答案 · 查看答案】
// 错误。由于枚举元素是constexpr的，因此它们的值也必须是constexpr。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

enum Color
{
    black, // 0
    red, // 1
    blue, // 2
    green, // 3
    white, // 4
    cyan, // 5
    yellow, // 6
    magenta, // 7
};

int main()
{
    Color shirt{ blue };

    std::cout << "Your shirt is " << shirt << '\n'; // 这一行的效果是?

    return 0;
}
