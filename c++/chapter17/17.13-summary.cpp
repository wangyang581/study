// ==========================================================================
// 17.13 第17章总结
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十七章 固定长度数组：std::array与c样式数组
// 原文: https://www.studycpp.cn/basic/chapter17/summary/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "17.13-summary.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 章节回顾
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// ―――― 章节回顾 ――――

// 固定大小的数组（或固定长度的数组）要求在实例化时知道数组的长度，并且该长度
// 不能在以后更改。C样式数组和std::array都是固定大小的数组。动态数组可以在运行
// 时调整大小。vector是一个动态数组。
//
// std::array的长度必须是常量表达式。通常，为长度提供的值将是整型字面值、
// constexpr变量或非限定作用域枚举元素。
//
// std::array是聚合。这意味着它没有构造函数，而是使用聚合初始化进行初始化。
//
// 尽可能将std::array定义为constexpr。如果您的std::array不是constexpr，请考虑
// 改用std::vector。
//
// 使用类模板参数演绎（CTAD）让编译器从其初始值设定项推断std::array的类型和长
// 度。
//
// std::array实现为模板结构，其声明如下:

// [代码 1]
// template<typename T, std::size_t N> // N 是非类型模版参数
// struct array;

// 表示数组长度（N）的非类型模板参数的类型为std::size_t。
//
// 要获取std::array的长度，请执行以下操作:
// - 我们可以使用size()成员函数询问std::array对象的长度（该函数将长度返回为无
//   符号size_type）。
// - 在C++17中，我们可以使用std::size()非成员函数（对于std::array，该函数仅调
//   用size()成员函数，从而将长度返回为无符号size_type）。
// - 在C++20中，我们可以使用std::ssize()非成员函数，该函数将长度返回为一个大
//   的有符号整数类型（通常为std::ptrdiff_t）。
//
// 这三个函数都将以constexpr值的形式返回长度，除非在通过引用传递的std::array上
// 调用。P2280在C++23中解决了此缺陷。
//
// 要索引std::array，请执行以下操作:
// - 使用下标运算符（运算符[]）。在这种情况下不进行边界检查，传入无效索引将导
//   致未定义的行为。
// - 使用at()成员函数，该函数会执行运行时边界检查。我们建议避免使用此函数，因
//   为我们通常希望在索引之前进行边界检查，或者希望进行编译时边界检查。
// - 使用std::get()函数模板，它将索引作为非类型模板参数，并执行编译时边界检查。
//
// 可以使用具有模板参数声明的函数模板将具有不同元素类型和长度的std::array传递
// 给函数。或者在C++20中，使用模板<typename T，auto N>。
//
// 按值返回std::array将制作数组和所有元素的副本，但如果数组很小，并且元素的复
// 制成本不高，则这可能没问题。在某些情况下，改用输出参数可能是更好的选择。
//
// 当使用结构体、类或数组初始化std::array，并且不为每个初始值设定项提供元素类
// 型时，您将需要一对额外的大括号，以便编译器正确解释要初始化的内容。这是聚合
// 初始化的工件，在这些情况下，其他标准库容器类型（使用列表构造函数）不需要双
// 大括号。
//
// C++中的聚合支持一个名为大括号省略的概念，该概念为何时可以省略多个大括号制定
// 了一些规则。通常，在使用单个值初始化std::array时，或者在使用类类型或数组进
// 行初始化时，可以省略大括号，其中类型是用每个元素显式命名的。
//
// 不能有引用数组，但可以有std::reference_wrapper数组，其行为类似于可修改的左
// 值引用。
//
// 关于std::reference_wrapper，有几点值得注意:
// - Operator=将重置std::reference_wrapper（更改正在引用的对象）。
// - std::reference_wrapper<T>将隐式转换为T&。
// - get()成员函数可用于获取T&。当我们想要更新被引用对象的值时，这很有用。
//
// 提供了std::ref()和std::cref()函数作为快捷方式来创建std::reference_wrapper和
// const std::reference_wrapper包装的对象。
//
// 尽可能使用static_assert来确保使用CTAD的constexpr std::array具有正确数量的初
// 始值设定项。
//
// C样式数组继承自C语言，并内置于C++的核心语言中。由于C样式数组是核心语言的一
// 部分，因此它们有自己的特殊声明语法。在C样式数组声明中，我们使用方括号（[]）
// 来告诉编译器声明的对象是C样式数组。在方括号内，我们可以选择提供数组的长度，
// 这是类型为std::size_t的整数值，它告诉编译器数组中有多少个元素。C样式数组的
// 长度必须是常量表达式。
//
// C样式数组是聚合，这意味着可以使用聚合初始化来初始化它们。当使用初始值设定项
// 列表来初始化C样式数组的所有元素时，最好省略长度，并让编译器计算数组的长度。
//
// C样式数组可以通过运算符[]进行索引。C样式数组的索引可以是有符号或无符号整数，
// 也可以是非限定作用域枚举。这意味着C样式数组不会受到标准库容器类所具有的所有
// 符号转换索引问题的影响！
//
// C样式数组可以是const或constexpr。
//
// 要获取C样式数组的长度，请执行以下操作:
// - 在C++17中，我们可以使用std::size()非成员函数，该函数将长度返回为无符号的
//   std::size_t。
// - 在C++20中，我们可以使用std::ssize()非成员函数，该函数将长度返回为一个大
//   的有符号整数类型（通常为std::ptrdiff_t）。
//
// 在大多数情况下，当在表达式中使用C样式数组时，数组将隐式转换为指向元素类型的
// 指针，并用第一个元素的地址（索引为0）初始化。通俗地说，这称为数组退化。
//
// 指针运算是一种功能，它允许我们将某些整数算术运算符（加法、减法、自增或自减）
// 应用于指针，以产生新的内存地址。给定某个指针ptr，ptr+1返回内存中下一个对象
// 的地址（基于所指向的类型）。
//
// 从数组（元素0）的开头进行索引时使用下标，以便数组索引与元素对齐。在从给定元
// 素进行相对定位时使用指针运算。
//
// C样式字符串只是C样式数组，其元素类型为char或const char。因此，C样式字符串也
// 会退化。
//
// 数组的维数是选择元素所需的索引数。
//
// 仅包含一维的数组称为一维数组。数组的数组被称为二维数组，因为它有两个下标。
// 具有多个维度的数组称为多维数组。展平数组是降低数组维数的过程（通常降到单个
// 维数）。
//
// 在C++23中，std::mdspan是一个视图，为连续的元素序列提供多维数组接口。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 下面每一段代码有什么问题？如何修正？
//
// a)

// [代码 2]
// #include <array>
// #include <iostream>
//
// int main()
// {
//     std::array arr { 0, 1, 2, 3 };
//
//     for (std::size_t count{ 0 }; count <= std::size(arr); ++count)
//     {
//         std::cout << arr[count] << ' ';
//     }
//
//     std::cout << '\n';
//
//     return 0;
// }


// 【答案 · 查看答案】
// 这个for循环存在「差一错误」，它试图访问下标为4的数组元素，而该元素并不存在。
//
// 解决办法：for循环中的条件应当使用`<`而不是`<=`。
//
// b)

// [代码 3]
// #include <iostream>
//
// void printArray(int array[])
// {
//     for (int element : array)
//     {
//         std::cout << element << ' ';
//     }
// }
//
// int main()
// {
//     int array[] { 9, 7, 5, 3, 1 };
//
//     printArray(array);
//
//     std::cout << '\n';
//
//     return 0;
// }


// 【答案 · 查看答案】
// `array`被传给`printArray()`时会退化为指针。范围for循环无法用于指向数组的指
// 针，因为数组的大小未知。
//
// 解决办法：改用`std::array`，它不会退化。
//
// c)

// [代码 4]
// #include <array>
// #include <iostream>
//
// int main()
// {
//     std::cout << "Enter the number of test scores: ";
//     std::size_t length{};
//     std::cin >> length;
//
//     std::array<int, length> scores;
//
//     for (std::size_t i { 0 } ; i < length; ++i)
//     {
//         std::cout << "Enter score " << i << ": ";
//         std::cin >> scores[i];
//     }
//     return 0;
// }


// 【答案 · 查看答案】
// `length`不是常量表达式，不能用来定义`std::array`的长度。
//
// 解决办法：改用`std::vector`。

// ▼ 问题 2
// 本题我们要实现「罗斯科的魔药店」，这是全国最好的魔药店！这道题会比较大。
//
// 实现一个程序，输出如下内容：

// [文本/输出]
// Welcome to Roscoe's potion emporium!
// Enter your name: Alex
// Hello, Alex, you have 85 gold.
//
// Here is our selection for today:
// 0) healing costs 20
// 1) mana costs 30
// 2) speed costs 12
// 3) invisibility costs 50
// Enter the number of the potion you'd like to buy, or 'q' to quit: a
// That is an invalid input.  Try again: 3
// You purchased a potion of invisibility.  You have 35 gold left.
//
// Here is our selection for today:
// 0) healing costs 20
// 1) mana costs 30
// 2) speed costs 12
// 3) invisibility costs 50
// Enter the number of the potion you'd like to buy, or 'q' to quit: 4
// That is an invalid input.  Try again: 2
// You purchased a potion of speed.  You have 23 gold left.
//
// Here is our selection for today:
// 0) healing costs 20
// 1) mana costs 30
// 2) speed costs 12
// 3) invisibility costs 50
// Enter the number of the potion you'd like to buy, or 'q' to quit: 2
// You purchased a potion of speed.  You have 11 gold left.
//
// Here is our selection for today:
// 0) healing costs 20
// 1) mana costs 30
// 2) speed costs 12
// 3) invisibility costs 50
// Enter the number of the potion you'd like to buy, or 'q' to quit: 4
// You can not afford that.
//
// Here is our selection for today:
// 0) healing costs 20
// 1) mana costs 30
// 2) speed costs 12
// 3) invisibility costs 50
// Enter the number of the potion you'd like to buy, or 'q' to quit: q
//
// Your inventory contains:
// 2x potion of speed
// 1x potion of invisibility
// You escaped with 11 gold remaining.
//
// Thanks for shopping at Roscoe's potion emporium!

// 玩家初始拥有随机的金币数量，介于80到120之间。
//
// 看起来很有意思？那就动手吧！由于一次实现全部功能比较困难，我们分步进行。
//
// 第1步
//
// 创建一个`Potion`命名空间，其中包含一个名为`Type`的枚举，列出各种药水类型。
// 创建两个`std::array`：一个int数组保存药水价格，一个`std::string_view`数组保
// 存药水名称。
//
// 再编写一个名为`shop()`的函数，遍历这些药水并打印它们的编号、名称和价格。
//
// 程序应当输出如下内容：

// [文本/输出]
// Here is our selection for today:
// 0) healing costs 20
// 1) mana costs 30
// 2) speed costs 12
// 3) invisibility costs 50


// 【答案 · 显示提示】
// 在「17.5 std::array和枚举」中，我们给出了用范围for循环遍历枚举的方法。

// 【答案 · 查看答案】

// [代码 5]
// #include <array>
// #include <iostream>
// #include <string_view>
//
// namespace Potion
// {
//     enum Type
//     {
//     healing,
//     mana,
//     speed,
//     invisibility,
//     max_potions
//     };
//
//     constexpr std::array types { healing, mana, speed, invisibility }; // 保存各枚举元素的数组
//
//     // 这些本可以放进一个结构体，但目前只有两个属性，暂时分开保存
//     // 这里显式写出元素类型，这样就不必使用 sv 后缀
//     constexpr std::array<std::string_view, max_potions> name { "healing", "mana", "speed", "invisibility" };
//     constexpr std::array cost { 20, 30, 12, 50 };
//
//     static_assert(std::size(types) == max_potions);  // 确保 'all' 中包含正确数量的枚举元素
//     static_assert(std::size(cost) == max_potions);
//     static_assert(std::size(name) == max_potions);
// }
//
// void shop()
// {
//     std::cout << "Here is our selection for today:\n";
//
//     for (auto p: Potion::types)
//         std::cout << p << ") " << Potion::name[p] << " costs " << Potion::cost[p] << '\n';
// }
//
// int main()
// {
//     shop();
//
//     return 0;
// }

// 第2步
//
// 创建一个`Player`类，保存玩家的名字、药水库存和金币。加上罗斯科魔药店的欢迎
// 语和告别语。获取玩家的名字并随机生成他们的金币数量。
//
// 使用「8.14 全局随机数」中的 Random.h 文件，让随机化更简单。
//
// 程序应当输出如下内容：

// [文本/输出]
// Welcome to Roscoe's potion emporium!
// Enter your name: Alex
// Hello, Alex, you have 84 gold.
//
// Here is our selection for today:
// 0) healing costs 20
// 1) mana costs 30
// 2) speed costs 12
// 3) invisibility costs 50
//
// Thanks for shopping at Roscoe's potion emporium!


// 【答案 · 查看答案】

// [代码 6]
// #include <array>
// #include <iostream>
// #include <string_view>
// #include "Random.h"
//
// namespace Potion
// {
//     enum Type
//     {
//         healing,
//         mana,
//         speed,
//         invisibility,
//         max_potions
//     };
//
//     constexpr std::array types { healing, mana, speed, invisibility }; // 保存各枚举元素的数组
//
//     // 这些本可以放进一个结构体，但目前只有两个属性，暂时分开保存
//     // 这里显式写出元素类型，这样就不必使用 sv 后缀
//     constexpr std::array<std::string_view, max_potions> name { "healing", "mana", "speed", "invisibility" };
//     constexpr std::array cost { 20, 30, 12, 50 };
//
//     static_assert(std::size(types) == max_potions);  // 确保 'all' 中包含正确数量的枚举元素
//     static_assert(std::size(cost) == max_potions);
//     static_assert(std::size(name) == max_potions);
// }
//
// class Player
// {
// private:
//     static constexpr int s_minStartingGold { 80 };
//     static constexpr int s_maxStartingGold { 120 };
//
//     std::string m_name {};
//     int m_gold {};
//     std::array<int, Potion::max_potions> m_inventory { };
//
// public:
//     explicit Player(std::string_view name) :
//         m_name { name },
//         m_gold { Random::get(s_minStartingGold, s_maxStartingGold) }
//     {
//     }
//
//     int gold() const { return m_gold; }
//     int inventory(Potion::Type p) const { return m_inventory[p]; }
// };
//
// void shop()
// {
//     std::cout << "Here is our selection for today:\n";
//
//     for (auto p: Potion::types)
//         std::cout << p << ") " << Potion::name[p] << " costs " << Potion::cost[p] << '\n';
// }
//
// int main()
// {
//     std::cout << "Welcome to Roscoe's potion emporium!\n";
//     std::cout << "Enter your name: ";
//
//     std::string name{};
//     std::getline(std::cin >> std::ws, name); // 把一整行文本读入 name
//
//     Player player { name };
//
//     std::cout << "Hello, " << name << ", you have " << player.gold() << " gold.\n\n";
//
//     shop();
//
//     std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";
//
//     return 0;
// }

// 第3步
//
// 加入购买药水的功能，并处理无效输入（任何多余的输入都视为失败）。在玩家离开
// 后打印他们的库存。完成这一步后程序就完整了。
//
// 请务必测试下列情况：
// - 用户输入了无效的药水编号（例如「d」）
// - 用户输入了合法的药水编号但带有额外输入（例如`2d`、`25`）
//
// 我们在「9.4 std::cin和处理无效输入」中介绍了无效输入的处理。

// 【答案 · 显示提示】
// 用户既可以输入数字也可以输入「q」，因此要把用户的输入提取为`char`类型。
//
// 要把ASCII数字字符转换为int（例如把`'5'`变成`5`），可以使用下面这个函数：

// [代码 7]
// int charNumToInt(char c)
// {
//     return c - '0';
// }


// 【答案 · 显示提示】
// 编写一个函数处理用户输入。它应当返回用户选择的`Potion::Type`。如果用户选择
// 退出，函数可以返回`Potion::max_potions`。你需要把用户的输入static_cast为
// `Potion::Type`。

// 【答案 · 查看答案】

// [代码 8]
// #include <array>
// #include <iostream>
// #include <limits> // 用于 std::numeric_limits
// #include <string_view>
// #include "Random.h"
//
// namespace Potion
// {
//     enum Type
//     {
//         healing,
//         mana,
//         speed,
//         invisibility,
//         max_potions
//     };
//
//     constexpr std::array types { healing, mana, speed, invisibility }; // 保存各枚举元素的数组
//
//     // 这些本可以放进一个结构体，但目前只有两个属性，暂时分开保存
//     // 这里显式写出元素类型，这样就不必使用 sv 后缀
//     constexpr std::array<std::string_view, max_potions> name { "healing", "mana", "speed", "invisibility" };
//     constexpr std::array cost { 20, 30, 12, 50 };
//
//     static_assert(std::size(types) == max_potions);  // 确保 'all' 中包含正确数量的枚举元素
//     static_assert(std::size(cost) == max_potions);
//     static_assert(std::size(name) == max_potions);
// }
//
// class Player
// {
// private:
//     static constexpr int s_minStartingGold { 80 };
//     static constexpr int s_maxStartingGold { 120 };
//
//     std::string m_name {};
//     int m_gold {};
//     std::array<int, Potion::max_potions> m_inventory { };
//
// public:
//     explicit Player(std::string_view name) :
//         m_name { name },
//         m_gold { Random::get(s_minStartingGold, s_maxStartingGold) }
//     {
//     }
//
//     // 买不起时返回 false，购买成功时返回 true
//     bool buy(Potion::Type type)
//     {
//         if (m_gold < Potion::cost[type])
//             return false;
//
//         m_gold -= Potion::cost[type];
//         ++m_inventory[type];
//         return true;
//     }
//
//     int gold() const { return m_gold; }
//     int inventory(Potion::Type p) const { return m_inventory[p]; }
// };
//
// void ignoreLine()
// {
//     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
// }
//
// int charNumToInt(char c)
// {
//     return c - '0';
// }
//
// Potion::Type whichPotion()
// {
//     std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
//     char input{};
//     while (true)
//     {
//         std::cin >> input;
//         if (!std::cin)
//         {
//             std::cin.clear(); // 让流回到「正常」工作模式
//             ignoreLine(); // 并移除错误的输入
//             continue;
//         }
//
//         // 如果有多余输入，就按失败处理
//         if (!std::cin.eof() && std::cin.peek() != '\n')
//         {
//             std::cout << "That is an invalid input.  Try again: ";
//             ignoreLine(); // 忽略所有多余输入
//             continue;
//         }
//
//         if (input == 'q')
//             return Potion::max_potions;
//
//         // 把这个 char 转换成数字，判断它是不是合法的药水选择
//         int val { charNumToInt(input) };
//         if (val >= 0 && val < Potion::max_potions)
//             return static_cast<Potion::Type>(val);
//
//         // 这不是合法的药水选择
//         std::cout << "That is an invalid input.  Try again: ";
//         ignoreLine();
//     }
// }
//
// void shop(Player &player)
// {
//     while (true)
//     {
//         std::cout << "Here is our selection for today:\n";
//
//         for (auto p: Potion::types)
//             std::cout << p << ") " << Potion::name[p] << " costs " << Potion::cost[p] << '\n';
//
//         Potion::Type which { whichPotion() };
//         if (which == Potion::max_potions)
//             return;
//
//         bool success { player.buy(which) };
//         if (!success)
//             std::cout << "You can not afford that.\n\n";
//         else
//             std::cout << "You purchased a potion of " << Potion::name[which] << ".  You have " << player.gold() << " gold left.\n\n";
//     }
// }
//
// void printInventory(Player& player)
// {
//     std::cout << "Your inventory contains: \n";
//
//     for (auto p: Potion::types)
//     {
//         if (player.inventory(p) > 0)
//             std::cout << player.inventory(p) << "x potion of " << Potion::name[p] << '\n';
//     }
//
//     std::cout << "You escaped with " << player.gold() << " gold remaining.\n";
// }
//
// int main()
// {
//     std::cout << "Welcome to Roscoe's potion emporium!\n";
//     std::cout << "Enter your name: ";
//
//     std::string name{};
//     std::cin >> name;
//
//     Player player { name };
//
//     std::cout << "Hello, " << name << ", you have " << player.gold() << " gold.\n\n";
//
//     shop(player);
//
//     std::cout << '\n';
//
//     printInventory(player);
//
//     std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";
//
//     return 0;
// }


// ▼ 问题 3
// 假设我们要写一个使用标准52张牌堆的纸牌游戏。为此，我们需要某种方式来表示牌
// 和牌堆。我们先把这部分功能搭起来。
//
// 在下一题中我们会用它来实现一个真正的游戏。
//
// 第1步
//
// 一副牌有52张互不相同的牌（13种点数、4种花色）。为点数（ace、2、3、4、5、6、
// 7、8、9、10、jack、queen、king）和花色（clubs、diamonds、hearts、spades）各
// 创建一个枚举。

// 【答案 · 查看答案】

// [代码 9]
// // 由于标识符不能以数字开头，这些枚举元素使用 "rank_" 前缀
// enum Rank
// {
//     rank_ace,
//     rank_2,
//     rank_3,
//     rank_4,
//     rank_5,
//     rank_6,
//     rank_7,
//     rank_8,
//     rank_9,
//     rank_10,
//     rank_jack,
//     rank_queen,
//     rank_king,
//
//     max_ranks
// };
//
// // 为了保持一致，这些也加上前缀
// enum Suit
// {
//     suit_club,
//     suit_diamond,
//     suit_heart,
//     suit_spade,
//
//     max_suits
// };

// 第2步
//
// 每张牌用一个名为`Card`的结构体表示，其中包含一个点数成员和一个花色成员。创
// 建这个结构体，并把上面的枚举移入其中。

// 【答案 · 查看答案】

// [代码 10]
// struct Card
// {
//     enum Rank
//     {
//         rank_ace,
//         rank_2,
//         rank_3,
//         rank_4,
//         rank_5,
//         rank_6,
//         rank_7,
//         rank_8,
//         rank_9,
//         rank_10,
//         rank_jack,
//         rank_queen,
//         rank_king,
//
//         max_ranks
//     };
//
//     enum Suit
//     {
//         suit_club,
//         suit_diamond,
//         suit_heart,
//         suit_spade,
//
//         max_suits
//     };
//
//     Rank rank{};
//     Suit suit{};
// };

// 第3步
//
// 接下来给Card结构体添加一些有用的函数。首先，重载`operator<<`，把牌的点数和
// 花色打印成2个字母的编码（例如黑桃J会打印成JS）。可以通过补全下面这个函数来
// 完成：

// [代码 11]
// struct Card
// {
//     // 你的其他代码写在这里
//
//     friend std::ostream& operator<<(std::ostream& out, const Card &card)
//     {
//         out << // 在这里打印牌的点数和花色
//         return out;
//     }
// };

// 其次，添加一个返回牌面值的函数。把A当作11。最后，添加两个`std::array`，分别
// 保存所有点数和所有花色（命名为`allRanks`和`allSuits`），以便遍历它们。由于
// 这些是结构体（而不是命名空间）的一部分，请把它们声明为static，这样它们只会
// 被实例化一次（而不是每个对象一份）。
//
// 下面这段代码应当能够通过编译：

// [代码 12]
// int main()
// {
//     // 打印一张牌
//     Card card { Card::rank_5, Card::suit_heart };
//     std::cout << card << '\n';
//
//     // 打印所有牌
//     for (auto suit : Card::allSuits)
//         for (auto rank : Card::allRanks)
//             std::cout << Card { rank, suit } << ' ';
//     std::cout << '\n';
//
//     return 0;
// }

// 并产生如下输出：

// [文本/输出]
// 5H
// AC 2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC AD 2D 3D 4D 5D 6D 7D 8D 9D TD JD QD KD AH 2H 3H 4H 5H 6H 7H 8H 9H TH JH QH KH AS 2S 3S 4S 5S 6S 7S 8S 9S TS JS QS KS


// 【答案 · 查看答案】

// [代码 13]
// #include <array>
// #include <iostream>
//
// struct Card
// {
//     enum Rank
//     {
//         rank_ace,
//         rank_2,
//         rank_3,
//         rank_4,
//         rank_5,
//         rank_6,
//         rank_7,
//         rank_8,
//         rank_9,
//         rank_10,
//         rank_jack,
//         rank_queen,
//         rank_king,
//
//         max_ranks
//     };
//
//     enum Suit
//     {
//         suit_club,
//         suit_diamond,
//         suit_heart,
//         suit_spade,
//
//         max_suits
//     };
//
//     // 这些需要声明为 static，使它们整个程序只创建一次，而不是每张牌一份
//     static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
//     static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };
//
//     Rank rank{};
//     Suit suit{};
//
//     friend std::ostream& operator<<(std::ostream& out, const Card &card)
//     {
//         static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
//         static constexpr std::array suits { 'C', 'D', 'H', 'S' };
//
//         out << ranks[card.rank] << suits[card.suit];
//         return out;
//     }
//
//     int value() const
//     {
//         static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
//         return rankValues[rank];
//     }
// };
//
// int main()
// {
//     // 打印一张牌
//     Card card { Card::rank_5, Card::suit_heart };
//     std::cout << card << '\n';
//
//     // 打印所有牌
//     for (auto suit : Card::allSuits)
//         for (auto rank : Card::allRanks)
//             std::cout << Card { rank, suit } << ' ';
//     std::cout << '\n';
//
//     return 0;
// }

// 第4步
//
// 接下来创建我们的牌堆。创建一个名为`Deck`的类，其中包含一个由Card构成的
// `std::array`。可以假设一副牌有52张。
//
// Deck应当有三个函数：
//
// 第一，默认构造函数要初始化这个牌数组。可以使用与上一个例子中`main()`函数类
// 似的范围for循环，遍历所有的花色和点数。
//
// 第二，添加一个`dealCard()`函数，按值返回牌堆中的下一张牌。由于`std::array`
// 是固定大小的数组，请思考如何记录下一张牌的位置。当牌堆的牌已经发完时调用该
// 函数，应当触发assert。
//
// 第三，编写一个`shuffle()`成员函数来洗牌。为简便起见，我们借助`std::shuffle`：

// [代码 14]
// #include <algorithm> // 用于 std::shuffle
// #include "Random.h"  // 用于 Random::mt
//
//     // 把这一行放进你的 shuffle 函数中，用 Random::mt 这个梅森旋转引擎打乱 m_cards
//     // 这会把牌堆中所有牌的顺序随机打乱
//     std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);

// `shuffle()`函数还应当把记录下一张牌位置的变量重置到牌堆开头。
//
// 下面这个程序应当能够运行：

// [代码 15]
// int main()
// {
//     Deck deck{};
//     std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';
//
//     deck.shuffle();
//     std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';
//
//     return 0;
// }

// 并产生如下输出（最后3张牌应当是随机的）：

// [文本/输出]
// AC 2C 3C
// 2H 7H 9C


// 【答案 · 查看答案】

// [代码 16]
// #include <algorithm> // 用于 std::shuffle
// #include <array>
// #include <cassert>
// #include <iostream>
// #include "Random.h"
//
// struct Card
// {
//     enum Rank
//     {
//         rank_ace,
//         rank_2,
//         rank_3,
//         rank_4,
//         rank_5,
//         rank_6,
//         rank_7,
//         rank_8,
//         rank_9,
//         rank_10,
//         rank_jack,
//         rank_queen,
//         rank_king,
//
//         max_ranks
//     };
//
//     enum Suit
//     {
//         suit_club,
//         suit_diamond,
//         suit_heart,
//         suit_spade,
//
//         max_suits
//     };
//
//     static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
//     static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };
//
//     Rank rank{};
//     Suit suit{};
//
//     friend std::ostream& operator<<(std::ostream& out, const Card &card)
//     {
//         static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
//         static constexpr std::array suits { 'C', 'D', 'H', 'S' };
//
//         out << ranks[card.rank] << suits[card.suit];
//         return out;
//     }
//
//     int value() const
//     {
//         static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
//         return rankValues[rank];
//     }
// };
//
// class Deck
// {
// private:
//     std::array<Card, 52> m_cards {};
//     std::size_t m_nextCardIndex { 0 };
//
// public:
//     Deck()
//     {
//         std::size_t count { 0 };
//         for (auto suit: Card::allSuits)
//             for (auto rank: Card::allRanks)
//                 m_cards[count++] = Card{rank, suit};
//     }
//
//     void shuffle()
//     {
//         std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
//         m_nextCardIndex = 0;
//     }
//
//     Card dealCard()
//     {
//         assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
//         return m_cards[m_nextCardIndex++];
//     }
// };
//
// int main()
// {
//     Deck deck{};
//     std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';
//
//     deck.shuffle();
//     std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';
//
//     return 0;
// }


// ▼ 问题 4
// 好，现在用我们的Card和Deck来实现一个简化版的21点（Blackjack）！如果你不熟悉
// 21点，维基百科上的Blackjack词条有简要介绍。
//
// 我们的21点规则如下：
// - 庄家起始拿一张牌（现实中庄家拿两张，但其中一张是暗牌，所以现阶段不必考虑）
//   。
// - 玩家起始拿两张牌。
// - 玩家先行动。
// - 玩家可以反复「要牌」（hit）或「停牌」（stand）。
// - 如果玩家停牌，他的回合结束，根据已发的牌计算得分。
// - 如果玩家要牌，他会再拿一张牌，该牌的点数加到总分上。
// - A通常算1点或11点（以对总分更有利者为准）。为简单起见，这里都算11点。
// - 如果玩家的得分超过21，他就「爆牌」并立即输掉。
// - 玩家结束后轮到庄家。
// - 庄家反复拿牌，直到得分达到17或以上，此时必须停止拿牌。
// - 如果庄家得分超过21，他就爆牌，玩家立即获胜。
// - 否则，如果玩家的得分高于庄家，玩家获胜；否则玩家失败（为简单起见，平局算
//   庄家赢）。
//
// 在我们的简化版21点中，不记录玩家和庄家具体拿到了哪些牌，只记录双方已发牌的
// 点数之和。这样更简单。
//
// 请从你在上一题中编写的代码开始（也可以使用我们提供的参考解答）。
//
// 第1步
//
// 创建一个名为`Player`的结构体，表示游戏中的一个参与者（庄家或玩家）。由于本
// 游戏只关心参与者的得分，这个结构体只需要一个成员。
//
// 编写一个（最终将）进行一局21点的函数。目前这个函数应当为庄家随机抽一张牌、
// 为玩家随机抽两张牌，并返回一个bool值表示谁的得分更高。
//
// 代码应当输出如下内容：

// [文本/输出]
// The dealer is showing: 10
// You have score: 13
// You win!


// [文本/输出]
// The dealer is showing: 10
// You have score: 8
// You lose!


// 【答案 · 查看答案】

// [代码 17]
// #include <algorithm> // 用于 std::shuffle
// #include <array>
// #include <cassert>
// #include <iostream>
// #include "Random.h"
//
// struct Card
// {
//     enum Rank
//     {
//         rank_ace,
//         rank_2,
//         rank_3,
//         rank_4,
//         rank_5,
//         rank_6,
//         rank_7,
//         rank_8,
//         rank_9,
//         rank_10,
//         rank_jack,
//         rank_queen,
//         rank_king,
//
//         max_ranks
//     };
//
//     enum Suit
//     {
//         suit_club,
//         suit_diamond,
//         suit_heart,
//         suit_spade,
//
//         max_suits
//     };
//
//     static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
//     static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };
//
//     Rank rank{};
//     Suit suit{};
//
//     friend std::ostream& operator<<(std::ostream& out, const Card &card)
//     {
//         static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
//         static constexpr std::array suits { 'C', 'D', 'H', 'S' };
//
//         out << ranks[card.rank] << suits[card.suit];
//         return out;
//     }
//
//     int value() const
//     {
//         static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
//         return rankValues[rank];
//     }
// };
//
// class Deck
// {
// private:
//     std::array<Card, 52> m_cards {};
//     std::size_t m_nextCardIndex { 0 };
//
// public:
//     Deck()
//     {
//         std::size_t count { 0 };
//         for (auto suit: Card::allSuits)
//             for (auto rank: Card::allRanks)
//                 m_cards[count++] = Card{rank, suit};
//     }
//
//     void shuffle()
//     {
//         std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
//         m_nextCardIndex = 0;
//     }
//
//     Card dealCard()
//     {
//         assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
//         return m_cards[m_nextCardIndex++];
//     }
// };
//
// struct Player
// {
//     int score{};
// };
//
// bool playBlackjack()
// {
//     Deck deck{};
//     deck.shuffle();
//
//     Player dealer{ deck.dealCard().value() };
//
//     std::cout << "The dealer is showing: " << dealer.score << '\n';
//
//     Player player { deck.dealCard().value() + deck.dealCard().value() };
//
//     std::cout << "You have score: " << player.score << '\n';
//
//     return (player.score > dealer.score);
// }
//
// int main()
// {
//     if (playBlackjack())
//     {
//         std::cout << "You win!\n";
//     }
//     else
//     {
//         std::cout << "You lose!\n";
//     }
//
//     return 0;
// }

// 第2步
//
// 添加一个`Settings`命名空间，其中包含两个常量：玩家爆牌的阈值，以及庄家必须
// 停止拿牌的阈值。
//
// 加入处理庄家回合的逻辑。庄家会一直拿牌直到达到17，然后必须停止。如果他爆牌，
// 玩家获胜。
//
// 输出示例如下：

// [文本/输出]
// The dealer is showing: 8
// You have score: 9
// The dealer flips a 4D.  They now have: 12
// The dealer flips a JS.  They now have: 22
// The dealer went bust!
// You win!


// [文本/输出]
// The dealer is showing: 6
// You have score: 13
// The dealer flips a 3D.  They now have: 9
// The dealer flips a 3H.  They now have: 12
// The dealer flips a 9S.  They now have: 21
// You lose!


// [文本/输出]
// The dealer is showing: 7
// You have score: 21
// The dealer flips a JC.  They now have: 17
// You win!


// 【答案 · 查看答案】

// [代码 18]
// #include <algorithm> // 用于 std::shuffle
// #include <array>
// #include <cassert>
// #include <iostream>
// #include "Random.h"
//
// struct Card
// {
//     enum Rank
//     {
//         rank_ace,
//         rank_2,
//         rank_3,
//         rank_4,
//         rank_5,
//         rank_6,
//         rank_7,
//         rank_8,
//         rank_9,
//         rank_10,
//         rank_jack,
//         rank_queen,
//         rank_king,
//
//         max_ranks
//     };
//
//     enum Suit
//     {
//         suit_club,
//         suit_diamond,
//         suit_heart,
//         suit_spade,
//
//         max_suits
//     };
//
//     static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
//     static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };
//
//     Rank rank{};
//     Suit suit{};
//
//     friend std::ostream& operator<<(std::ostream& out, const Card &card)
//     {
//         static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
//         static constexpr std::array suits { 'C', 'D', 'H', 'S' };
//
//         out << ranks[card.rank] << suits[card.suit];
//         return out;
//     }
//
//     int value() const
//     {
//         static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
//         return rankValues[rank];
//     }
// };
//
// class Deck
// {
// private:
//     std::array<Card, 52> m_cards {};
//     std::size_t m_nextCardIndex { 0 };
//
// public:
//     Deck()
//     {
//         std::size_t count { 0 };
//         for (auto suit: Card::allSuits)
//             for (auto rank: Card::allRanks)
//                 m_cards[count++] = Card{rank, suit};
//     }
//
//     void shuffle()
//     {
//         std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
//         m_nextCardIndex = 0;
//     }
//
//     Card dealCard()
//     {
//         assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
//         return m_cards[m_nextCardIndex++];
//     }
//
// };
//
// struct Player
// {
//     int score{};
// };
//
// namespace Settings
// {
//     // 超过这个分数就算输。
//     constexpr int bust{ 21 };
//
//     // 庄家必须达到的最低分数。
//     constexpr int dealerStopsAt{ 17 };
// }
//
// // 庄家爆牌时返回 true，否则返回 false。
// bool dealerTurn(Deck& deck, Player& dealer)
// {
//     while (dealer.score < Settings::dealerStopsAt)
//     {
//         Card card { deck.dealCard() };
//         dealer.score += card.value();
//         std::cout << "The dealer flips a " << card << ".  They now have: " << dealer.score << '\n';
//     }
//
//     if (dealer.score > Settings::bust)
//     {
//         std::cout << "The dealer went bust!\n";
//         return true;
//     }
//
//     return false;
// }
//
// bool playBlackjack()
// {
//     Deck deck{};
//     deck.shuffle();
//
//     Player dealer{ deck.dealCard().value() };
//
//     std::cout << "The dealer is showing: " << dealer.score << '\n';
//
//     Player player { deck.dealCard().value() + deck.dealCard().value() };
//
//     std::cout << "You have score: " << player.score << '\n';
//
//     if (dealerTurn(deck, dealer))
//         return true;
//
//     return (player.score > dealer.score);
// }
//
// int main()
// {
//     if (playBlackjack())
//     {
//         std::cout << "You win!\n";
//     }
//     else
//     {
//         std::cout << "You lose!\n";
//     }
//
//     return 0;
// }

// 第3步
//
// 最后加入玩家回合的逻辑，游戏至此完成。
//
// 输出示例如下：

// [文本/输出]
// The dealer is showing: 2
// You have score: 14
// (h) to hit, or (s) to stand: h
// You were dealt KH.  You now have: 24
// You went bust!
// You lose!


// [文本/输出]
// The dealer is showing: 10
// You have score: 9
// (h) to hit, or (s) to stand: h
// You were dealt TH.  You now have: 19
// (h) to hit, or (s) to stand: s
// The dealer flips a 3D.  They now have: 13
// The dealer flips a 7H.  They now have: 20
// You lose!


// [文本/输出]
// The dealer is showing: 7
// You have score: 12
// (h) to hit, or (s) to stand: h
// You were dealt 7S.  You now have: 19
// (h) to hit, or (s) to stand: h
// You were dealt 2D.  You now have: 21
// (h) to hit, or (s) to stand: s
// The dealer flips a 6H.  They now have: 13
// The dealer flips a QC.  They now have: 23
// The dealer went bust!
// You win!


// 【答案 · 查看答案】

// [代码 19]
// #include <algorithm> // 用于 std::shuffle
// #include <array>
// #include <cassert>
// #include <iostream>
// #include "Random.h"
//
// struct Card
// {
//     enum Rank
//     {
//         rank_ace,
//         rank_2,
//         rank_3,
//         rank_4,
//         rank_5,
//         rank_6,
//         rank_7,
//         rank_8,
//         rank_9,
//         rank_10,
//         rank_jack,
//         rank_queen,
//         rank_king,
//
//         max_ranks
//     };
//
//     enum Suit
//     {
//         suit_club,
//         suit_diamond,
//         suit_heart,
//         suit_spade,
//
//         max_suits
//     };
//
//     static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
//     static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };
//
//     Rank rank{};
//     Suit suit{};
//
//     friend std::ostream& operator<<(std::ostream& out, const Card &card)
//     {
//         static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
//         static constexpr std::array suits { 'C', 'D', 'H', 'S' };
//
//         out << ranks[card.rank] << suits[card.suit];
//         return out;
//     }
//
//     int value() const
//     {
//         static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
//         return rankValues[rank];
//     }
// };
//
// class Deck
// {
// private:
//     std::array<Card, 52> m_cards {};
//     std::size_t m_nextCardIndex { 0 };
//
// public:
//     Deck()
//     {
//         std::size_t count { 0 };
//         for (auto suit: Card::allSuits)
//             for (auto rank: Card::allRanks)
//                 m_cards[count++] = Card{rank, suit};
//     }
//
//     void shuffle()
//     {
//         std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
//         m_nextCardIndex = 0;
//     }
//
//     Card dealCard()
//     {
//         assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
//         return m_cards[m_nextCardIndex++];
//     }
//
// };
//
// struct Player
// {
//     int score{};
// };
//
// namespace Settings
// {
//     // 超过这个分数就算输。
//     constexpr int bust{ 21 };
//
//     // 庄家必须达到的最低分数。
//     constexpr int dealerStopsAt{ 17 };
// }
//
// bool playerWantsHit()
// {
//     while (true)
//     {
//         std::cout << "(h) to hit, or (s) to stand: ";
//
//         char ch{};
//         std::cin >> ch;
//
//         switch (ch)
//         {
//             case 'h':
//                 return true;
//             case 's':
//                 return false;
//         }
//     }
// }
//
// // 玩家爆牌时返回 true，否则返回 false。
// bool playerTurn(Deck& deck, Player& player)
// {
//     while (player.score < Settings::bust && playerWantsHit())
//     {
//         Card card { deck.dealCard() };
//         player.score += card.value();
//
//         std::cout << "You were dealt " << card  << ". You now have: " << player.score << '\n';
//     }
//
//     if (player.score > Settings::bust)
//     {
//         std::cout << "You went bust!\n";
//         return true;
//     }
//
//     return false;
// }
//
// // 庄家爆牌时返回 true，否则返回 false。
// bool dealerTurn(Deck& deck, Player& dealer)
// {
//     while (dealer.score < Settings::dealerStopsAt)
//     {
//         Card card { deck.dealCard() };
//         dealer.score += card.value();
//         std::cout << "The dealer flips a " << card << ".  They now have: " << dealer.score << '\n';
//     }
//
//     if (dealer.score > Settings::bust)
//     {
//         std::cout << "The dealer went bust!\n";
//         return true;
//     }
//
//     return false;
// }
//
// bool playBlackjack()
// {
//     Deck deck{};
//     deck.shuffle();
//
//     Player dealer{ deck.dealCard().value() };
//
//     std::cout << "The dealer is showing: " << dealer.score << '\n';
//
//     Player player { deck.dealCard().value() + deck.dealCard().value() };
//
//     std::cout << "You have score: " << player.score << '\n';
//
//     if (playerTurn(deck, player))
//         return false;
//
//     if (dealerTurn(deck, dealer))
//         return true;
//
//     return (player.score > dealer.score);
// }
//
// int main()
// {
//     if (playBlackjack())
//     {
//         std::cout << "You win!\n";
//     }
//     else
//     {
//         std::cout << "You lose!\n";
//     }
//
//     return 0;
// }


// ▼ 问题 5
// a) 描述你会如何修改上面的程序，以支持A可以算1点或11点的情况。
//
// 需要注意，我们只跟踪了牌面点数之和，而没有记录玩家具体持有哪些牌。

// 【答案 · 查看答案】
// 一种做法是记录玩家和庄家各拿到多少张A（在`Player`结构体中用一个int保存）。
// 如果玩家或庄家的得分超过21，而他们的A计数器大于0，就可以把他们的得分减去10
// （相当于把一张A从11点改成1点），并把A计数器减1。只要A计数器还没减到0，就可
// 以重复这样做。
//
// b) 在真正的21点中，如果玩家和庄家的得分相同（且玩家没有爆牌），则是平局，双
// 方都不算获胜。描述你会如何修改上面的程序来体现这一点。

// 【答案 · 查看答案】
// 我们的`playBlackjack()`目前返回一个bool值，表示玩家是否获胜。需要把这个函数
// 改成返回三种可能的结果：庄家赢、玩家赢、平局。最好的做法是为这三种情况定义
// 一个枚举，让函数返回相应的枚举元素。
//
// c) 附加题：把上面两个想法实现到你的21点游戏中。注意，你需要显示庄家的初始牌
// 和玩家初始的两张牌，这样玩家才知道自己有没有A。
//
// 输出示例如下：

// [文本/输出]
// The dealer is showing JH (10)
// You are showing AH 7D (18)
// (h) to hit, or (s) to stand: h
// You were dealt JD.  You now have: 18
// (h) to hit, or (s) to stand: s
// The dealer flips a 6C.  They now have: 16
// The dealer flips a AD.  They now have: 17
// You win!


// 【答案 · 查看答案】

// [代码 20]
// #include <algorithm> // 用于 std::shuffle
// #include <array>
// #include <cassert>
// #include <iostream>
// #include "Random.h"
//
// namespace Settings
// {
//     // 超过这个分数就算输。
//     constexpr int bust{ 21 };
//
//     // 庄家必须达到的最低分数。
//     constexpr int dealerStopsAt{ 17 };
// }
//
// struct Card
// {
//     enum Rank
//     {
//         rank_ace,
//         rank_2,
//         rank_3,
//         rank_4,
//         rank_5,
//         rank_6,
//         rank_7,
//         rank_8,
//         rank_9,
//         rank_10,
//         rank_jack,
//         rank_queen,
//         rank_king,
//
//         max_ranks
//     };
//
//     enum Suit
//     {
//         suit_club,
//         suit_diamond,
//         suit_heart,
//         suit_spade,
//
//         max_suits
//     };
//
//     static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
//     static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };
//
//     Rank rank{};
//     Suit suit{};
//
//     friend std::ostream& operator<<(std::ostream& out, const Card &card)
//     {
//         static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
//         static constexpr std::array suits { 'C', 'D', 'H', 'S' };
//
//         out << ranks[card.rank] << suits[card.suit];
//         return out;
//     }
//
//     int value() const
//     {
//         static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
//         return rankValues[rank];
//     }
// };
//
// class Deck
// {
// private:
//     std::array<Card, 52> m_cards {};
//     std::size_t m_nextCardIndex { 0 };
//
// public:
//     Deck()
//     {
//         std::size_t count { 0 };
//         for (auto suit: Card::allSuits)
//             for (auto rank: Card::allRanks)
//                 m_cards[count++] = Card{rank, suit};
//     }
//
//     void shuffle()
//     {
//         std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
//         m_nextCardIndex = 0;
//     }
//
//     Card dealCard()
//     {
//         assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
//         return m_cards[m_nextCardIndex++];
//     }
//
// };
//
// class Player
// {
// private:
//     int m_score{ };
//     int m_ace11Count { 0 }; // 玩家手中有多少张算 11 点的 A
//
// public:
//     // 我们用一个函数把这张牌加到玩家的得分上
//     // 因为现在需要统计 A 的个数
//     void addToScore(Card card)
//     {
//         m_score += card.value();
//         if (card.rank == Card::rank_ace)
//             ++m_ace11Count; // A 初始算 11 点
//         consumeAces();
//     }
//
//     // 把 aceCount 减 1，
//     void consumeAces()
//     {
//         // 如果玩家会爆牌，看看能否把某张 A 从 11 点改成 1 点
//         while (m_score > Settings::bust && m_ace11Count > 0)
//         {
//             m_score -= 10;
//             --m_ace11Count;
//         }
//     }
//
//     int score() { return m_score; }
// };
//
// bool playerWantsHit()
// {
//     while (true)
//     {
//         std::cout << "(h) to hit, or (s) to stand: ";
//
//         char ch{};
//         std::cin >> ch;
//
//         switch (ch)
//         {
//             case 'h':
//                 return true;
//             case 's':
//                 return false;
//         }
//     }
// }
//
// // 玩家爆牌时返回 true，否则返回 false。
// bool playerTurn(Deck& deck, Player& player)
// {
//     while (player.score() < Settings::bust && playerWantsHit())
//     {
//         Card card { deck.dealCard() };
//         player.addToScore(card);
//
//         std::cout << "You were dealt " << card  << ". You now have: " << player.score() << '\n';
//     }
//
//     if (player.score() > Settings::bust)
//     {
//         std::cout << "You went bust!\n";
//         return true;
//     }
//
//     return false;
// }
//
// // 庄家爆牌时返回 true，否则返回 false。
// bool dealerTurn(Deck& deck, Player& dealer)
// {
//     while (dealer.score() < Settings::dealerStopsAt)
//     {
//         Card card { deck.dealCard() };
//         dealer.addToScore(card);
//
//         std::cout << "The dealer flips a " << card << ".  They now have: " << dealer.score() << '\n';
//     }
//
//     if (dealer.score() > Settings::bust)
//     {
//         std::cout << "The dealer went bust!\n";
//         return true;
//     }
//
//     return false;
// }
//
// enum class GameResult
// {
//     playerWon,
//     dealerWon,
//     tie
// };
//
// GameResult playBlackjack()
// {
//     Deck deck{};
//     deck.shuffle();
//
//     Player dealer{};
//     Card card1 { deck.dealCard() };
//     dealer.addToScore(card1);
//     std::cout << "The dealer is showing " << card1 << " (" << dealer.score() << ")\n";
//
//     Player player{};
//     Card card2 { deck.dealCard() };
//     Card card3 { deck.dealCard() };
//     player.addToScore(card2);
//     player.addToScore(card3);
//     std::cout << "You are showing " << card2 << ' ' << card3 << " (" << player.score() << ")\n";
//
//     if (playerTurn(deck, player)) // 如果玩家爆牌
//         return GameResult::dealerWon;
//
//     if (dealerTurn(deck, dealer)) // 如果庄家爆牌
//         return GameResult::playerWon;
//
//     if (player.score() == dealer.score())
//         return GameResult::tie;
//
//     return (player.score() > dealer.score() ? GameResult::playerWon : GameResult::dealerWon);
// }
//
// int main()
// {
//     switch (playBlackjack())
//     {
//     case GameResult::playerWon:
//         std::cout << "You win!\n";
//         return 0;
//     case GameResult::dealerWon:
//         std::cout << "You lose!\n";
//         return 0;
//     case GameResult::tie:
//         std::cout << "It's a tie.\n";
//         return 0;
//     }
//
//     return 0;
// }

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <array>
#include <iostream>

int main()
{
    std::array arr { 0, 1, 2, 3 };

    for (std::size_t count{ 0 }; count <= std::size(arr); ++count)
    {
        std::cout << arr[count] << ' ';
    }

    std::cout << '\n';

    return 0;
}
