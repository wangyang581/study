// ==========================================================================
// 17.3 std::array与类类型元素
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十七章 固定长度数组：std::array与c样式数组
// 原文: https://www.studycpp.cn/basic/chapter17/arr-of-class/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "17.03-arr-of-class.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 定义并分配结构体给std::array
//   · 初始化元素为结构体的std::array
//   · 初始化，而不显式指定每个初始值设定项的元素类型
//   · 大括号的省略
//   · 另一个例子
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 数组不限于只能存放基本类型的元素。相反，std::array的元素可以是任何对象类型，
// 包括复合类型。这意味着您可以创建指针的std::array，或结构体（或class）的
// std::array。
//
// 然而，初始化结构体或类类型的std::array常常会让新程序员困惑，因此我们将花一
// 节课专门讨论这个主题。
//
// 注
//
// 在本课中，将使用结构体来说明我们的观点。该材料同样适用于类。
//

// ―――― 定义并分配结构体给std::array ――――

// 让我们从一个简单的结构体开始:

// [代码 1]
// struct House
// {
//     int number{};
//     int stories{};
//     int roomsPerStory{};
// };

// 定义House的std::array并分配元素的工作方式与您预期的一样:

// [代码 2]
// #include <array>
// #include <iostream>
//
// struct House
// {
//     int number{};
//     int stories{};
//     int roomsPerStory{};
// };
//
// int main()
// {
//     std::array<House, 3> houses{};
//
//     houses[0] = { 13, 1, 7 };
//     houses[1] = { 14, 2, 5 };
//     houses[2] = { 15, 2, 4 };
//
//     for (const auto& house : houses)
//     {
//         std::cout << "House number " << house.number
//                   << " has " << (house.stories * house.roomsPerStory)
//                   << " rooms.\n";
//     }
//
//     return 0;
// }

// 上述输出如下:

// [文本/输出]
// House number 13 has 7 rooms.
// House number 14 has 10 rooms.
// House number 15 has 8 rooms.

//

// ―――― 初始化元素为结构体的std::array ――――

// 只要明确了元素类型，初始化也会按预期工作:

// [代码 3]
// #include <array>
// #include <iostream>
//
// struct House
// {
//     int number{};
//     int stories{};
//     int roomsPerStory{};
// };
//
// int main()
// {
//     constexpr std::array houses { // 使用CTAD去推导模版参数类型为 <House, 3>
//             House{ 13, 1, 7 },
//             House{ 14, 2, 5 },
//             House{ 15, 2, 4 }
//         };
//
//     for (const auto& house : houses)
//     {
//         std::cout << "House number " << house.number
//             << " has " << (house.stories * house.roomsPerStory)
//             << " rooms.\n";
//     }
//
//     return 0;
// }

// 在上面的示例中，CTAD会将std::array的类型推断为std::array<House，3>。随后提
// 供的3个House对象会作为初始值设定项。
//

// ―――― 初始化，而不显式指定每个初始值设定项的元素类型 ――――

// 在上面的示例中，您会注意到每个初始值设定项都要求我们列出元素类型:

// [代码 4]
//     constexpr std::array houses {
//             House{ 13, 1, 7 }, // 指定类型为 House
//             House{ 14, 2, 5 }, // 这里也是
//             House{ 15, 2, 4 }  // 这里也是
//         };

// 但在分配案例中，不必这样做:

// [代码 5]
//     // 编译器知道house中的每个元素类型为 House
//     // 因此会隐式地将右边的每个元素转换为 House
//     houses[0] = { 13, 1, 7 };
//     houses[1] = { 14, 2, 5 };
//     houses[2] = { 15, 2, 4 };

// 所以你可能会想试试这样的方法:

// [代码 6]
//     // 无法按预期工作
//     constexpr std::array<House, 3> houses { // 告诉编译器每个元素都是一个 House
//             { 13, 1, 7 }, // 这里不再声明元素类型
//             { 14, 2, 5 },
//             { 15, 2, 4 }
//         };

// 也许令人惊讶的是，这不起作用。让我们探索一下原因。
//
// 简要来说，std::array是定义为包含一个C样式数组的结构体，如下所示:

// [代码 7]
// template<typename T, std::size_t N>
// struct array
// {
//     T implementation_defined_name[N]; // C样式数组，有N个T类型的元素
// }

// 因此，当我们尝试根据上面的内容初始化House时，编译器将如下解释初始化:

// [代码 8]
// // 无法按预期工作
// constexpr std::array<House, 3> houses { // 初始化 houses
//     { 13, 1, 7 }, // 初始化 C 样式数组 implementation_defined_name
//     { 14, 2, 5 }, // ?
//     { 15, 2, 4 }  // ?
// };

// 编译器将把{13,1,7}解释为houses的第一个成员的初始值设定项，这是具有实现定义
// 名称的C样式数组。这将使用{13,1,7}初始化C样式数组元素0，其余成员将被零初始化。
// 然后编译器会发现我们又提供了两个初始化值（{14，2，5}和{15，2，4}），并产生
// 一个编译错误，告诉我们提供了太多的初始化值。
//
// 正确初始化上述数组的方法是添加一组额外的大括号，如下所示:

// [代码 9]
// // 按预期工作
// constexpr std::array<House, 3> houses { // 初始化 houses
//     { // 额外的大括号，用来初始化作为成员变量的C样式数组 implementation_defined_name
//         { 13, 4, 30 }, // 初始化元素 0
//         { 14, 3, 10 }, // 初始化元素 1
//         { 15, 3, 40 }, // 初始化元素 2
//      }
// };

// 请注意所需的额外大括号（在std::array结构体中开始的C样式数组成员的初始化）。
// 在这个大括号中，可以单独初始化每个元素，每个元素都在自己的大括号中。
//
// 这就是为什么当元素类型需要值列表，并且我们没有显式地将元素类型作为初始值设
// 定项的一部分提供时，将看到带有一组额外大括号的std::array初始化方式。
//
// 下面是一个完整的示例:

// [代码 10]
// #include <array>
// #include <iostream>
//
// struct House
// {
//     int number{};
//     int stories{};
//     int roomsPerStory{};
// };
//
// int main()
// {
//     constexpr std::array<House, 3> houses {{ // 注意这里有两个大括号
//         { 13, 1, 7 },
//         { 14, 2, 5 },
//         { 15, 2, 4 }
//     }};
//
//     for (const auto& house : houses)
//     {
//         std::cout << "House number " << house.number
//                   << " has " << (house.stories * house.roomsPerStory)
//                   << " rooms.\n";
//     }
//
//     return 0;
// }

// 注
//
// 我们还没有介绍C样式数组，但出于本课的目的，您只需要知道的是“T
// implementation_defined_name[N];”代表的是 T类型的N个元素的固定大小数组。
//
// 本章后续会对C样式数组进行介绍。
//
// 关键点
//
// 当使用结构体、类或数组初始化std::array，并且不为每个初始值设定项提供元素类
// 型时，您将需要一对额外的大括号，以便编译器正确解释要初始化的内容。
//
// 这是聚合初始化的需要，在这些情况下，其他标准库容器类型（使用列表构造函数）
// 不需要双大括号。
//

// ―――― 大括号的省略 ――――

// 鉴于上述解释，您可能会想知道为什么上面的情况需要双大括号，但我们看到的所有
// 其他情况都只需要单大括号:

// [代码 11]
// #include <array>
// #include <iostream>
//
// int main()
// {
//     constexpr std::array<int, 5> arr { 1, 2, 3, 4, 5 }; // 单个大括号
//
//     for (const auto n : arr)
//         std::cout << n << '\n';
//
//     return 0;
// }

// 事实证明，您可以为此类数组提供双大括号:

// [代码 12]
// #include <array>
// #include <iostream>
//
// int main()
// {
//     constexpr std::array<int, 5> arr {{ 1, 2, 3, 4, 5 }}; // 双大括号
//
//     for (const auto n : arr)
//         std::cout << n << '\n';
//
//     return 0;
// }

// C++中的聚合支持一个名为大括号省略的概念，它为何时可以省略多个大括号制定了一
// 些规则。通常，在使用单个值初始化std::array时，或者在使用类类型或数组进行初
// 始化时，可以省略大括号，其中每个元素必须显式带上类型。
//
// 始终用双大括号初始化std::array没有坏处，因为它避免了必须考虑大括号省略是否
// 适用于特定情况。或者，您可以尝试使用单大括号初始化，如果编译器无法识别它，
// 它通常会告警。在这种情况下，可以快速添加一组额外的大括号。
//

// ―――― 另一个例子 ――――

// 这里还有一个例子，我们用Student结构初始化std::array。

// [代码 13]
// #include <array>
// #include <iostream>
// #include <string_view>
//
// // 每个学生有一个 id 和 name
// struct Student
// {
// 	int id{};
// 	std::string_view name{};
// };
//
// // 有 3 个学生的数组 (因为这里指明了类型，所以单括号足够了)
// constexpr std::array students{ Student{0, "Alex"}, Student{ 1, "Joe" }, Student{ 2, "Bob" } };
//
// const Student* findStudentById(int id)
// {
// 	// 遍历所有学生
// 	for (auto& s : students)
// 	{
// 		// 返回指定id的学生
// 		if (s.id == id) return &s;
// 	}
//
// 	// 没有匹配到对应的id
// 	return nullptr;
// }
//
// int main()
// {
// 	constexpr std::string_view nobody { "nobody" };
//
// 	const Student* s1 { findStudentById(1) };
// 	std::cout << "You found: " << (s1 ? s1->name : nobody) << '\n';
//
// 	const Student* s2 { findStudentById(3) };
// 	std::cout << "You found: " << (s2 ? s2->name : nobody) << '\n';
//
// 	return 0;
// }

// 这将打印:

// [文本/输出]
// You found: Joe
// You found: nobody

// 注意，由于std::array students是constexpr，因此findStudentById()函数必须返回
// 常量指针，这意味着main()中的Student指针也必须是const。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 定义一个名为`Item`的结构体，包含两个成员：`std::string_view name`和`int
// gold`。定义一个`std::array`并用4个Item对象初始化它。使用CTAD推导元素类型和
// 数组大小。

// 【答案 · 显示提示】
// 你需要为每个初始化值显式指定元素类型。
//
// 程序应当打印如下内容：

// [文本/输出]
// A sword costs 5 gold.
// A dagger costs 3 gold.
// A club costs 2 gold.
// A spear costs 7 gold.


// 【答案 · 查看答案】

// [代码 14]
// #include <array>
// #include <iostream>
// #include <string_view>
//
// struct Item
// {
//     std::string_view name {};
//     int gold {};
// };
//
// template <std::size_t N>
// void printStore(const std::array<Item, N>& arr)
// {
//     for (const auto& item: arr)
//     {
//         std::cout << "A " << item.name << " costs " << item.gold << " gold.\n";
//     }
// }
//
// int main()
// {
//     constexpr std::array store { // 使用 CTAD，并因花括号省略而使用单层花括号
//         Item { "sword",    5 },
//         Item { "dagger",   3 },
//         Item { "club",     2 },
//         Item { "spear",    7 } };
//     printStore(store);
//
//     return 0;
// }

// 由于我们为每个初始化值显式指定了元素类型，这里可以使用CTAD和单层花括号（得
// 益于花括号省略）。

// ▼ 问题 2
// 修改你在第1题中的解答，不再为每个初始化值显式指定元素类型。

// 【答案 · 查看答案】

// [代码 15]
// #include <array>
// #include <iostream>
// #include <string_view>
//
// struct Item
// {
//     std::string_view name {};
//     int gold {};
// };
//
// template <std::size_t N>
// void printStore(const std::array<Item, N>& arr)
// {
//     for (const auto& item: arr)
//     {
//         std::cout << "A " << item.name << " costs " << item.gold << " gold.\n";
//     }
// }
//
// int main()
// {
//     constexpr std::array<Item, 4> store {{ // 不能用 CTAD，必须使用双层花括号
//         { "sword",    5 },
//         { "dagger",   3 },
//         { "club",     2 },
//         { "spear",    7 }
//     }};
//     printStore(store);
//
//     return 0;
// }

// 由于没有为每个初始化值显式指定元素类型，我们就不能使用CTAD，也不能使用花括
// 号省略。这意味着必须使用双层花括号。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    std::array<House, 3> houses{};

    houses[0] = { 13, 1, 7 };
    houses[1] = { 14, 2, 5 };
    houses[2] = { 15, 2, 4 };

    for (const auto& house : houses)
    {
        std::cout << "House number " << house.number
                  << " has " << (house.stories * house.roomsPerStory)
                  << " rooms.\n";
    }

    return 0;
}
