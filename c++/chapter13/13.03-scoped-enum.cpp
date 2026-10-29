// ==========================================================================
// 13.3 限定作用域枚举（枚举类）
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十三章 复合类型：枚举与结构体
// 原文: https://www.studycpp.cn/basic/chapter13/scoped-enum/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "13.03-scoped-enum.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 限定作用域枚举
//   · 限定作用域枚举会定义自己的作用域
//   · 限定作用域枚举不隐式转换为整数
//   · 简化限定作用域枚举元素到整数的转换（高级）
//   · using enum 语句（C++20）
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 尽管不同的非限定作用域枚举在C++中是不同的类型，但它们并不是类型安全的，并且
// 在某些情况下允许您做一些没有意义的事情。考虑以下情况：

// [代码 1]
// #include <iostream>
//
// int main()
// {
//     enum Color
//     {
//         red,
//         blue,
//     };
//
//     enum Fruit
//     {
//         banana,
//         apple,
//     };
//
//     Color color { red };
//     Fruit fruit { banana };
//
//     if (color == fruit) // 编译器会把 color 和 fruit 当做整数来比较
//         std::cout << "color and fruit are equal\n"; // 然后发现它们相等!
//     else
//         std::cout << "color and fruit are not equal\n";
//
//     return 0;
// }

// 这将打印：

// [文本/输出]
// color and fruit are equal

// 当比较color和fruit时，编译器并不知道如何直接比较Color与Fruit类型。接下来，
// 它会尝试将color和fruit转换为整数，然后判断是否能进行比较。最终，编译器会确
// 定：如果将两者转换为整数，就可以进行比较。由于color和fruit都被设置为会转换
// 为整数值0的枚举元素，因此color等于fruit。
//
// 这在语义上没有意义，因为color和fruit来自不同的枚举，并且不打算进行比较。没
// 有简单的方法来防止这种情况发生。
//
// 由于这样的挑战，以及命名空间污染问题（在全局命名空间中定义的非限定作用域枚
// 举将其枚举元素放在全局命名空间中），C++设计者决定使用更干净的枚举解决方案。
//

// ―――― 限定作用域枚举 ――――

// 解决方案是使用限定作用域枚举（在C++中通常称为枚举类）。
//
// 限定作用域枚举的工作方式类似于非限定作用域枚举，但有两个主要区别：它不会隐
// 式转换为整数，并且枚举元素只会放在枚举自身的作用域中（而不是放在定义枚举的
// 作用域中）。
//
// 要使用限定作用域枚举，需要使用关键字 enum class 。其余部分与非限定作用域枚
// 举相同。下面是一个示例：

// [代码 2]
// #include <iostream>
// int main()
// {
//     enum class Color // "enum class" 定义了限定作用域枚举
//     {
//         red, // red 在 Color 的作用域中
//         blue,
//     };
//
//     enum class Fruit
//     {
//         banana, // banana 在 Fruit 的作用域中
//         apple,
//     };
//
//     Color color { Color::red }; // 注: red 不能直接使用, 需要使用 Color::red
//     Fruit fruit { Fruit::banana }; // 注: banana 不能直接使用, 需要使用 Fruit::banana
//
//     if (color == fruit) // 编译失败: 编译器不知道如何比较 Color 与 Fruit 类型
//         std::cout << "color and fruit are equal\n";
//     else
//         std::cout << "color and fruit are not equal\n";
//
//     return 0;
// }

// 该程序在第19行产生编译错误，因为限定作用域枚举之间不能互相比较。
//
// 旁白
//
// class关键字（与static一样）是C++语言中用途最多的关键字之一，根据上下文不同，
// 可以有不同含义。尽管限定作用域枚举使用class关键字，但它们不被认为是“类类型”
// （该术语保留给结构体、类和union）。
//
// enum struct 与 enum class 效果一致，但并不常用，请避免使用它。
//

// ―――― 限定作用域枚举会定义自己的作用域 ――――

// 限定作用域枚举会充当其枚举元素的命名空间。这个内置命名空间有助于减少全局命
// 名空间污染，并降低在全局空间中发生名称冲突的可能性。
//
// 要访问限定作用域枚举元素，就如同使用枚举同名的命名空间一样：

// [代码 3]
// #include <iostream>
//
// int main()
// {
//     enum class Color // "enum class" 定义了限定作用域枚举
//     {
//         red, // red 在 Color 的作用域内
//         blue,
//     };
//
//     std::cout << red << '\n';        // 编译失败: red 不在全局命名空间
//     std::cout << Color::red << '\n'; // 编译失败: std::cout 不知道如何打印 red (不会隐式的转换为 int)
//
//     Color color { Color::blue }; // okay
//
//     return 0;
// }

// 由于限定作用域枚举为枚举元素提供了自己的隐式命名空间，因此基本没有必要将它
// 的定义放在另一个作用域区域（如命名空间）中。
//

// ―――― 限定作用域枚举不隐式转换为整数 ――――

// 限定作用域枚举不会隐式转换为整数。在大多数情况下，这是一件好事，因为转换为
// 整数很少有明确意义。这有助于防止语义错误，例如比较来自不同枚举的枚举元素或
// 其他表达式（如red+5）。
//
// 请注意，您仍然可以比较同一枚举中的枚举元素（因为它们属于同一类型）：

// [代码 4]
// #include <iostream>
// int main()
// {
//     enum class Color
//     {
//         red,
//         blue,
//     };
//
//     Color shirt { Color::red };
//
//     if (shirt == Color::red) // Color 与 Color 的比较是 ok 的
//         std::cout << "The shirt is red!\n";
//     else if (shirt == Color::blue)
//         std::cout << "The shirt is blue!\n";
//
//     return 0;
// }

// 有时，将限定作用域枚举转换为整数值是有用的。在这些情况下，可以使用
// static_cast将它显式转换为整数。C++23中更好的选择是使用std::to_underlying()
// （在<utility>头文件中定义），它会将枚举元素转换为枚举底层类型的值。

// [代码 5]
// #include <iostream>
// #include <utility> // for std::to_underlying() (C++23)
//
// int main()
// {
//     enum class Color
//     {
//         red,
//         blue,
//     };
//
//     Color color { Color::blue };
//
//     std::cout << color << '\n'; // 编译失败, 因为无法隐式转换为 int
//     std::cout << static_cast<int>(color) << '\n';   // 显式转换为 int, 打印 1
//     std::cout << std::to_underlying(color) << '\n'; // 转换为底层类型, 打印 1 (C++23)
//
//     return 0;
// }

// 相反，也可以将整数static_cast为限定作用域枚举元素，这在获取用户输入时非常有
// 用：

// [代码 6]
// #include <iostream>
//
// int main()
// {
//     enum class Pet
//     {
//         cat, // 0
//         dog, // 1
//         pig, // 2
//         whale, // 3
//     };
//
//     std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";
//
//     int input{};
//     std::cin >> input; // 输入整数
//
//     Pet pet{ static_cast<Pet>(input) }; // static_cast 将 int 转换为 Pet
//
//     return 0;
// }

// 从C++17开始，可以使用整数来列表初始化限定作用域枚举。
//
// 尽管限定作用域枚举提供了好处，但在C++中仍然经常使用非限定作用域枚举，因为在
// 某些情况下，我们希望隐式转换为int（大量static_cast会很烦人），并且不需要额
// 外的命名空间。
//
// 最佳实践
//
// 使用限定作用域枚举，而不是非限定作用域枚举，除非有令人信服的理由这样做。
//

// ―――― 简化限定作用域枚举元素到整数的转换（高级） ――――

// 限定作用域枚举很好，但缺乏对整数的隐式转换有时可能是一个痛点。如果需要经常
// 将限定作用域枚举转换为整数（例如，在希望使用限定作用域枚举元素作为数组索引
// 的情况下），则每次需要转换时都必须使用static_cast可能会显著地扰乱代码。
//
// 如果处于这种情况，一种有用的方法是重载一元运算符+来执行此转换。我们还没有解
// 释这是如何工作的，所以它看起来可能有些神奇：

// [代码 7]
// #include <iostream>
// #include <type_traits> // for std::underlying_type_t
//
// enum class Animals
// {
//     chicken, // 0
//     dog, // 1
//     cat, // 2
//     elephant, // 3
//     duck, // 4
//     snake, // 5
//
//     maxAnimals,
// };
//
// // 重载 运算符+ 用来将 Animals 转换为 int
// // 来自 https://stackoverflow.com/a/42198760
// constexpr auto operator+(Animals a) noexcept
// {
//     return static_cast<std::underlying_type_t<Animals>>(a);
// }
//
// int main()
// {
//     std::cout << +Animals::elephant << '\n'; // 使用 运算符+ 将 Animals::elephant 转换为整数
//
//     return 0;
// }

// 这将打印：
//
// 该方法可以防止意外的隐式转换为整数类型，但提供了一种根据需要显式请求此类转
// 换的方便方法。
//

// ―――― using enum 语句（C++20） ――――

// C++20引入了using enum语句，该语句会将枚举中的所有枚举元素导入当前作用域。这
// 允许我们访问枚举元素时不必添加前缀。
//
// 在有许多相同、重复的前缀的情况下，例如在switch语句中，这可能很有用：

// [代码 8]
// #include <iostream>
// #include <string_view>
//
// enum class Color
// {
//     black,
//     red,
//     blue,
// };
//
// constexpr std::string_view getColor(Color color)
// {
//     using enum Color; // 将 Color中的所有枚举元素引入当前作用域 (C++20)
//     // 现在可以不带 Color:: 前缀使用其中的枚举元素
//
//     switch (color)
//     {
//     case black: return "black"; // 注: black 而不是 Color::black
//     case red:   return "red";
//     case blue:  return "blue";
//     default:    return "???";
//     }
// }
//
// int main()
// {
//     Color shirt{ Color::blue };
//
//     std::cout << "Your shirt is " << getColor(shirt) << '\n';
//
//     return 0;
// }

// 在上面的示例中，Color是一个enum class，因此通常会使用带作用域的名称（例如，
// Color::blue）来访问枚举元素。然而，在函数getColor()中，“using enum Color;“
// 语句允许在没有Color::前缀的情况下访问这些枚举元素。
//
// 这就避免了在switch语句中有多个冗余的明显前缀。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 定义一个名为Animal的枚举类，包含下列动物：pig、chicken、goat、cat、dog、
// duck。编写一个名为`getAnimalName()`的函数，它接受一个Animal形参，并使用
// switch语句返回该动物名称的`std::string_view`（如果使用C++14，则返回
// `std::string`）。再编写一个名为`printNumberOfLegs()`的函数，使用switch语句
// 打印每种动物行走所用的腿数。请确保这两个函数都有打印错误信息的default分支。
// 在`main()`中用cat和chicken调用`printNumberOfLegs()`。输出应当像下面这样：

// [文本/输出]
// A cat has 4 legs.
// A chicken has 2 legs.


// 【答案 · 查看答案】

// [代码 9]
// #include <iostream>
// #include <string_view> // C++17
// //#include <string> // C++14
//
// enum class Animal
// {
//     pig,
//     chicken,
//     goat,
//     cat,
//     dog,
//     duck,
// };
//
// constexpr std::string_view getAnimalName(Animal animal) // C++17
// // const std::string getAnimalName(Animal animal) // C++14
// {
//     // 如果支持 C++20，可以在这里使用 `using enum Animal`，减少 Animal 前缀的重复
//     switch (animal)
//     {
//         case Animal::chicken:
//             return "chicken";
//         case Animal::duck:
//             return "duck";
//         case Animal::pig:
//             return "pig";
//         case Animal::goat:
//             return "goat";
//         case Animal::cat:
//             return "cat";
//         case Animal::dog:
//             return "dog";
//
//         default:
//             return "???";
//     }
// }
//
// void printNumberOfLegs(Animal animal)
// {
//     std::cout << "A " << getAnimalName(animal) << " has ";
//
//     // 如果支持 C++20，可以在这里使用 `using enum Animal`，减少 Animal 前缀的重复
//     switch (animal)
//     {
//         case Animal::chicken:
//         case Animal::duck:
//             std::cout << 2;
//             break;
//
//         case Animal::pig:
//         case Animal::goat:
//         case Animal::cat:
//         case Animal::dog:
//             std::cout << 4;
//             break;
//
//         default:
//             std::cout << "???";
//             break;
//     }
//
//     std::cout << " legs.\n";
// }
//
// int main()
// {
//     printNumberOfLegs(Animal::cat);
//     printNumberOfLegs(Animal::chicken);
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
    enum Color
    {
        red,
        blue,
    };

    enum Fruit
    {
        banana,
        apple,
    };

    Color color { red };
    Fruit fruit { banana };

    if (color == fruit) // 编译器会把 color 和 fruit 当做整数来比较
        std::cout << "color and fruit are equal\n"; // 然后发现它们相等!
    else
        std::cout << "color and fruit are not equal\n";

    return 0;
}
