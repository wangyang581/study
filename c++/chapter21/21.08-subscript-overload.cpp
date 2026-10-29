// ==========================================================================
// 21.8 重载下标运算符
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十一章 操作符重载
// 原文: https://www.studycpp.cn/basic/chapter21/subscript-overload/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "21.08-subscript-overload.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 重载运算符[]
//   · 运算符[]返回引用的原因
//   · const对象的重载运算符[]
//   · 删除常量重载和非常量重载之间的重复代码
//   · 检测下标的有效性
//   · 指向对象的指针和重载运算符[]不能混用
//   · 函数参数不需要是整型
//   · 习题

// ==========================================================================
// 教程正文
// ==========================================================================

// 使用数组时，我们通常使用下标运算符（[]）来索引数组的特定元素：

// [代码 1]
// myArray[0] = 7; // 将7赋值给数组的第0个元素

// 然而，考虑以下IntList类，它有一个数组作为成员变量：

// [代码 2]
// class IntList
// {
// private:
//     int m_list[10]{};
// };
//
// int main()
// {
//     IntList list{};
//     // 如何从 m_list 访问元素?
//     return 0;
// }

// 由于m_list成员变量是私有的，因此不能从类外直接访问它。这意味着我们无法直接
// 获取或设置m_list数组中的值。那么，应该如何从列表中获取元素，或者向列表中放
// 入元素呢？
//
// 在没有运算符重载的情况下，典型的方法是创建访问函数：

// [代码 3]
// class IntList
// {
// private:
//     int m_list[10]{};
//
// public:
//     void setItem(int index, int value) { m_list[index] = value; }
//     int getItem(int index) const { return m_list[index]; }
// };

// 虽然这种方法有效，但对使用者并不友好。考虑以下示例：

// [代码 4]
// int main()
// {
//     IntList list{};
//     list.setItem(2, 3);
//
//     return 0;
// }

// 我们是在把索引2的元素设置为3，还是把索引3的元素设置为2？如果没有看到setItem
// （）的定义，根本不清楚。
//
// 您也可以返回整个列表，然后使用运算符[]访问元素：

// [代码 5]
// class IntList
// {
// private:
//     int m_list[10]{};
//
// public:
//     int* getList() { return m_list; }
// };

// 虽然这也有效，但语法看起来很奇怪：

// [代码 6]
// int main()
// {
//     IntList list{};
//     list.getList()[2] = 3;
//
//     return 0;
// }

//

// ―――― 重载运算符[] ――――

// 在这种情况下，更好的解决方案是重载下标运算符（[]），以允许访问m_list的元素。
// 下标运算符是必须重载为成员函数的运算符之一。重载运算符[]的函数始终接收一个
// 参数：用户放在方括号中的下标。在IntList示例中，我们期望用户传入整数索引，并
// 返回对应的结果。

// [代码 7]
// #include <iostream>
//
// class IntList
// {
// private:
//     int m_list[10]{};
//
// public:
//     int& operator[] (int index)
//     {
//         return m_list[index];
//     }
// };
//
// /*
// // 也可以放在函数外实现
// int& IntList::operator[] (int index)
// {
//     return m_list[index];
// }
// */
//
// int main()
// {
//     IntList list{};
//     list[2] = 3; // 赋值
//     std::cout << list[2] << '\n'; // 获取值
//
//     return 0;
// }

// 现在，每当我们在类对象上使用下标运算符（[]）时，编译器都会从m_list成员变量
// 中返回对应元素！这样我们就可以直接获取和设置m_list的值。
//
// 无论从语法还是理解角度来看，这都很自然。当list[2]求值时，编译器首先检查是否
// 存在重载运算符[]函数。如果存在，它会将方括号中的值（本例中为2）作为参数传递
// 给函数。
//
// 请注意，尽管可以为函数参数提供默认值，但使用没有下标的运算符[]仍然是无效语
// 法，无法通过编译。
//
// 提示
//
// C++23增加了对具有多个下标的重载 运算符[] 的支持。
//

// ―――― 运算符[]返回引用的原因 ――――

// 让我们仔细看看list[2] = 3是如何计算的。由于下标运算符的优先级高于赋值运算符，
// 因此list[2]会先求值。list[2]调用运算符[]，而我们定义的这个运算符会返回对
// list.m_list[2]的引用。由于运算符[]返回引用，因此它返回的是实际的
// list.m_list[2]数组元素。这个部分表达式随后变为list.m_list[2] = 3，这是一个
// 简单的赋值。
//
// 赋值语句左侧的值必须是左值（具有实际内存地址的变量）。由于运算符[]的结果可
// 以用于赋值左侧（例如list[2] = 3），因此运算符[]返回的值必须是左值。引用总是
// 左值，因为您只能引用具有内存地址的变量。因此，通过返回引用，编译器可以确定
// 我们返回的是左值。
//
// 考虑一下，如果运算符[]按值而不是按引用返回整数，会发生什么。list[2]会调用运
// 算符[]，该运算符将返回list.m_list[2]的值。例如，如果m_list[2]的值为6，则运
// 算符[]将返回值6。list[2] = 3的部分计算结果就会变成6 = 3，这没有意义！如果尝
// 试这样做，C++编译器将报错：

// [代码 8]
// C:VCProjectsTest.cpp(386) : error C2106: '=' : left operand must be l-value

//

// ―――― const对象的重载运算符[] ――――

// 在上面的IntList示例中，operator[]是非常量成员函数，我们可以将其用作左值来更
// 改非常量对象的状态。然而，如果IntList对象是常量，该怎么办？在这种情况下，不
// 能调用operator[]的非常量版本，因为那可能允许我们更改常量对象的状态。
//
// 好消息是，我们可以分别定义非常量和常量版本的运算符[]。非常量版本用于非常量
// 对象，常量版本用于常量对象。

// [代码 9]
// #include <iostream>
//
// class IntList
// {
// private:
//     int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 给定一些初始值
//
// public:
//     // 适用非常量对象，可以用来赋值
//     int& operator[] (int index)
//     {
//         return m_list[index];
//     }
//
//     // 适用常量对象: 只能用来访问
//     // 这个函数也是返回引用，来避免数据拷贝
//     const int& operator[] (int index) const
//     {
//         return m_list[index];
//     }
// };
//
// int main()
// {
//     IntList list{};
//     list[2] = 3; // okay: 调用非 const operator[]
//     std::cout << list[2] << '\n';
//
//     const IntList clist{};
//     // clist[2] = 3; // 编译会失败: clist[2] 返回 const 引用, 无法进行赋值
//     std::cout << clist[2] << '\n';
//
//     return 0;
// }

//

// ―――― 删除常量重载和非常量重载之间的重复代码 ――――

// 在上面的示例中，请注意"int& IntList::operator[]（int）“和"const int&
// IntList::operator[]（int）const"的实现是相同的。唯一的区别是函数返回类型。
//
// 在实现非常简单（例如只有一行）的情况下，让两个函数各自保留相同实现是可以的
// （并且通常是首选）。这点少量冗余不值得专门消除。
//
// 但是，如果这些运算符的实现很复杂，需要许多语句，该怎么办？例如，验证索引是
// 否有效可能很重要，这就需要在每个函数中添加许多重复代码。
//
// 在这种情况下，大量重复语句带来的冗余就更成问题了，我们会希望用一个实现服务
// 两个重载函数。但该怎么做呢？通常，我们只需要基于另一个函数实现当前函数（例
// 如，让一个函数调用另一个）。但在当前场景下，这有点棘手。const版本不能调用非
// const版本，因为这需要丢弃常量对象的const属性。虽然非const版本可以调用const
// 版本，但当我们需要返回非const引用时，const版本返回的是const引用。幸运的是，
// 有一种方法可以解决这个问题。
//
// 首选解决方案如下：
// - 实现函数的const版本的逻辑。
// - 让非const函数调用const函数，并使用const_cast删除const。
//
// 最终解决方案如下所示：

// [代码 10]
// #include <iostream>
// #include <utility> // for std::as_const
//
// class IntList
// {
// private:
//     int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 给定一些初始值
//
// public:
//     int& operator[] (int index)
//     {
//         // 使用 std::as_const 获取 `this` 对象的const版本 (作为引用)
//         // 以便可以调用const版本的 operator[]
//         // 然后使用 const_cast 丢弃返回值的const属性
//         return const_cast<int&>(std::as_const(*this)[index]);
//     }
//
//     const int& operator[] (int index) const
//     {
//         return m_list[index];
//     }
// };
//
// int main()
// {
//     IntList list{};
//     list[2] = 3; // okay: 调用 非const 版本的 operator[]
//     std::cout << list[2] << '\n';
//
//     const IntList clist{};
//     // clist[2] = 3; // 编译失败: clist[2] 返回 const 引用, 无法进行赋值
//     std::cout << clist[2] << '\n';
//
//     return 0;
// }

// 通常，我们希望避免使用const_cast删除const，但在这种情况下，这是可以接受的。
// 如果调用的是非const重载，就说明正在处理非const对象。此时，可以删除对非常量
// 对象的const引用上的const属性。
//
// 对于高级读者，在C++23中，通过使用本教程系列尚未介绍的几个功能，我们可以写得
// 更好：

// [代码 11]
// #include <iostream>
//
// class IntList
// {
// private:
//     int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 给定一些初始值
//
// public:
//     // 使用显示对象参数 (self) 和 auto&& 去自动区分 const 和 非const
//     auto&& operator[](this auto&& self, int index)
//     {
//         // Complex code goes here
//         return self.m_list[index];
//     }
// };
//
// int main()
// {
//     IntList list{};
//     list[2] = 3; // okay: 调用 非const 版本的 operator[]
//     std::cout << list[2] << '\n';
//
//     const IntList clist{};
//     // clist[2] = 3; // 编译失败: clist[2] 返回 const 引用, 无法进行赋值
//     std::cout << clist[2] << '\n';
//
//     return 0;
// }

//

// ―――― 检测下标的有效性 ――――

// 重载下标运算符的另一个优点是，可以让它比直接访问数组更安全。通常，在访问数
// 组时，下标运算符不会检查索引是否有效。例如，编译器不会对以下代码报错：

// [代码 12]
// int list[5]{};
// list[7] = 3; // 下标 7 超出了 list 的边界!

// 然而，如果我们知道数组的大小，可以重载下标运算符进行边界检查，以确保索引在
// 界限内：

// [代码 13]
// #include <cassert> // for assert()
// #include <iterator> // for std::size()
//
// class IntList
// {
// private:
//     int m_list[10]{};
//
// public:
//     int& operator[] (int index)
//     {
//         assert(index >= 0 && static_cast<std::size_t>(index) < std::size(m_list));
//
//         return m_list[index];
//     }
// };

// 在上面的示例中，我们使用assert（）函数来确保索引有效。如果断言中的表达式计
// 算结果为false（这意味着用户传入了无效索引），程序将以错误消息结束，这比访问
// 无效数据要好得多。这可能是进行这种错误检查最常见的方法。
//
// 如果不想使用断言，则可以改用If语句或您喜欢的错误处理方法（例如引发异常、调
// 用std::exit等）：

// [代码 14]
// #include <iterator> // for std::size()
//
// class IntList
// {
// private:
//     int m_list[10]{};
//
// public:
//     int& operator[] (int index)
//     {
//         if (!(index >= 0 && static_cast<std::size_t>(index) < std::size(m_list)))
//         {
//             // 处理异常的索引
//         }
//
//         return m_list[index];
//     }
// };

//

// ―――― 指向对象的指针和重载运算符[]不能混用 ――――

// 如果试图在指向对象的指针上调用运算符[]，C++会假定您正在尝试索引该类型对象的
// 数组。
//
// 考虑以下示例：

// [代码 15]
// #include <cassert> // for assert()
// #include <iterator> // for std::size()
//
// class IntList
// {
// private:
//     int m_list[10]{};
//
// public:
//     int& operator[] (int index)
//     {
//         return m_list[index];
//     }
// };
//
// int main()
// {
//     IntList* list{ new IntList{} };
//     list [2] = 3; // 错误: 这里会认为访问的是 IntList数组的 第二个元素
//     delete list;
//
//     return 0;
// }

// 因为我们不能将整数赋给IntList，所以这段代码无法通过编译。然而，如果这种赋值
// 是有效的，那么它将通过编译并运行，结果会是未定义行为。
//
// 正确的语法是先解引用指针（需要使用括号，因为运算符[]的优先级高于运算符*），
// 然后再调用运算符[]：

// [代码 16]
// int main()
// {
//     IntList* list{ new IntList{} };
//     (*list)[2] = 3; // 先获取到 IntList 对象, 然后调用重载函数 operator[]
//     delete list;
//
//     return 0;
// }

// 这种写法难看且容易出错。如果不需要，请避免使用指向对象的指针。
//

// ―――― 函数参数不需要是整型 ――――

// 如上所述，C++会将用户写在方括号中的内容作为参数传递给重载函数。在大多数情况
// 下，这会是一个整数值。然而，这并不是必须的。事实上，您可以定义重载运算符[]
// 来接收任意类型的值。您可以将重载运算符[]定义为接受double、std::string或其他
// 任何类型。
//
// 下面是一个有些荒谬的例子，只是为了展示它的工作原理：

// [代码 17]
// #include <iostream>
// #include <string_view> // C++17
//
// class Stupid
// {
// private:
//
// public:
// 	void operator[] (std::string_view index);
// };
//
// // 让 operator[] 去打印东西，但其实有些荒谬
// // 这里是为了演示，重载函数的参数不一定非是 整形
// void Stupid::operator[] (std::string_view index)
// {
// 	std::cout << index;
// }
//
// int main()
// {
// 	Stupid stupid{};
// 	stupid["Hello, world!"];
//
// 	return 0;
// }

// 如您所料，此打印：

// [文本/输出]
// Hello, world!

// 在编写某些类型的类时（例如使用单词作为索引的类），让重载运算符[]接收
// std::string作为参数可能很有用。
//

// ―――― 习题 ――――


// ▼ 问题 1
// 映射（map）是一种把元素存成「键-值对」的类。键必须唯一，并用来访问相关联的
// 值。本次习题我们要写一个简单的map类，用于按姓名给学生打分。学生的姓名是键，
// 成绩（char类型）是值。
//
// a) 首先编写一个名为`StudentGrade`的结构体，包含学生姓名（`std::string`）和
// 成绩（`char`）。

// 【答案 · 查看答案】

// [代码 18]
// #include <string>
//
// struct StudentGrade
// {
//     std::string name{};
//     char grade{};
// };

// b) 添加一个名为`GradeMap`的类，其中包含一个名为`m_map`的元素类型为
// `StudentGrade`的`std::vector`。

// 【答案 · 查看答案】

// [代码 19]
// #include <string>
// #include <vector>
//
// struct StudentGrade
// {
// 	std::string name{};
// 	char grade{};
// };
//
// class GradeMap
// {
// private:
// 	std::vector<StudentGrade> m_map{};
// };

// c) 为这个类编写重载的`operator[]`。该函数应当接受一个`std::string`形参，并
// 返回char的引用。在函数体中，先检查该学生姓名是否已经存在（可以使用中的
// `std::find_if`）。如果学生已存在，就返回其成绩的引用，任务完成。否则，使用
// `std::vector::emplace_back()`或`std::vector::push_back()`为这个新学生添加一
// 个`StudentGrade`。这样做时，`std::vector`会把你的`StudentGrade`副本添加到自
// 身（必要时会重新分配，从而使之前返回的所有引用失效）。最后，我们需要返回刚
// 刚加入`std::vector`的那个学生成绩的引用，可以使用`std::vector::back()`函数
// 访问刚加入的学生。
//
// 下面这个程序应当能够运行：

// [代码 20]
// #include <iostream>
//
// // ...
//
// int main()
// {
// 	GradeMap grades{};
//
// 	grades["Joe"] = 'A';
// 	grades["Frank"] = 'B';
//
// 	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
// 	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
//
// 	return 0;
// }


// 【答案 · 查看答案】

// [代码 21]
// #include <algorithm>
// #include <iostream>
// #include <string>
// #include <string_view>
// #include <vector>
//
// struct StudentGrade
// {
// 	std::string name{};
// 	char grade{};
// };
//
// class GradeMap
// {
// private:
// 	std::vector<StudentGrade> m_map{};
//
// public:
// 	char& operator[](std::string_view name);
// };
//
// char& GradeMap::operator[](std::string_view name)
// {
// 	auto found{ std::find_if(m_map.begin(), m_map.end(),
// 				[name](const auto& student) { // 这是一个从外围作用域捕获 name 的 lambda
// 					return (student.name == name); // 这样这里就能使用 name
// 				}) };
//
// 	if (found != m_map.end())
// 	{
// 		return found->grade;
// 	}
//
// 	// 否则为这个学生新建一个 StudentGrade 并把
// 	// 把它加到我们 vector 的末尾，然后返回该成绩。
//
// 	// emplace_back 版本（C++20 起）
// 	// StudentGrade 是聚合类型，而 emplace_back 从 C++20 起才支持聚合类型
// 	return m_map.emplace_back(std::string{name}).grade;
//
// 	// push_back 版本（C++17 或更早）
// 	// m_map.push_back(StudentGrade{std::string{name}});
// 	// return m_map.back().grade;
// }
//
// int main()
// {
// 	GradeMap grades{};
//
// 	grades["Joe"] = 'A';
// 	grades["Frank"] = 'B';
//
// 	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
// 	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
//
// 	return 0;
// }

// 提醒：
//
// 关于lambda的更多信息，参见「20.5 lambda（匿名函数）简介」。
//
// 提示：
//
// 由于map很常见，标准库提供了`std::map`（本教程暂未介绍）。使用`std::map`，可
// 以把我们的代码简化为

// [代码 22]
// #include <iostream>
// #include <map> // std::map
// #include <string>
//
// int main()
// {
// 	// std::map 可以初始化
// 	std::map<std::string, char> grades{
// 		{ "Joe", 'A' },
// 		{ "Frank", 'B' }
// 	};
//
// 	// 以及赋值
// 	grades["Susan"] = 'C';
// 	grades["Tom"] = 'D';
//
// 	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
// 	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
//
// 	return 0;
// }

// 比起自己实现，更推荐使用`std::map`。

// ▼ 问题 2
// 附加题1：我们编写的`GradeMap`类和示例程序在很多方面效率不高。请描述一种可以
// 改进`GradeMap`类的方式。

// 【答案 · 查看答案】
// `std::vector`本质上无序。这意味着每次调用`operator[]`时，我们可能要遍历整个
// `std::vector`才能找到目标元素。元素少时这不是问题，但随着名字越来越多，会变
// 得越来越慢。我们可以通过保持`m_map`有序并使用二分查找来优化，从而把为了找到
// 目标元素而需要查看的元素个数降到最少。

// ▼ 问题 3
// 附加题2：为什么下面这个程序有可能不按预期工作？

// [代码 23]
// #include <iostream>
//
// int main()
// {
// 	GradeMap grades{};
//
// 	char& gradeJoe{ grades["Joe"] }; // 进行一次 emplace_back
// 	gradeJoe = 'A';
//
// 	char& gradeFrank{ grades["Frank"] }; // 进行一次 emplace_back
// 	gradeFrank = 'B';
//
// 	std::cout << "Joe has a grade of " << gradeJoe << '\n';
// 	std::cout << "Frank has a grade of " << gradeFrank << '\n';
//
// 	return 0;
// }


// 【答案 · 查看答案】
// 添加Frank时，`std::vector`可能需要扩容来容纳它。这需要动态分配一块新的内存，
// 把数组中的元素拷贝到新内存块中，再释放旧内存块。发生这种情况时，所有指向该
// vector中已有元素的引用都会失效（变成指向已释放内存的悬空引用）。
//
// 换句话说，在执行`emplace_back("Frank")`之后，如果std::vector为了容纳Frank而
// 扩容了，那么`gradeJoe`引用就会失效。再用`gradeJoe`打印Joe的成绩，就会导致未
// 定义的结果。
//
// std::vector的扩容方式是编译器相关的细节，因此上面这个程序在某些编译器上能正
// 常工作，在其他编译器上则不能。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

class IntList
{
private:
    int m_list[10]{};

public:
    int& operator[] (int index)
    {
        return m_list[index];
    }
};

/*
// 也可以放在函数外实现
int& IntList::operator[] (int index)
{
    return m_list[index];
}
*/

int main()
{
    IntList list{};
    list[2] = 3; // 赋值
    std::cout << list[2] << '\n'; // 获取值

    return 0;
}
