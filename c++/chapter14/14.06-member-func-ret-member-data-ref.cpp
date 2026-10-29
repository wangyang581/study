// ==========================================================================
// 14.6 成员函数返回对数据成员的引用
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第十四章 class介绍
// 原文: https://www.studycpp.cn/basic/chapter14/member-func-ret-member-data-ref/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "14.06-member-func-ret-member-data-ref.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 按值返回数据成员可能很昂贵
//   · 通过左值引用返回数据成员
//   · 返回对数据成员的引用的成员函数的返回类型应与数据成员的类型匹配
//   · 右值隐式对象并通过引用返回
//   · 安全使用成员函数返回的引用
//   · 不返回对私有数据成员的非常量引用
//   · Const成员函数不能返回对数据成员的非常量引用

// ==========================================================================
// 教程正文
// ==========================================================================

// 在前面，我们讨论了函数通过引用返回数据。特别是，可以注意到，“通过引用返回的
// 对象必须在函数返回后仍然存在”。这意味着不应该通过引用返回局部变量，因为在局
// 部变量被销毁后，引用将悬空。通常可以通过引用返回：a. 通过引用传递的函数参数，
// 或 b. 具有静态存储期的变量（静态局部变量或全局变量），因为它们通常不会在函
// 数返回后被销毁。
//
// 例如：

// [代码 1]
// // 接受两个std::string , 返回字典序最小的
// const std::string& firstAlphabetical(const std::string& a, const std::string& b)
// {
// 	return (a < b) ? a : b; // 可以对 std::string 使用 operator< ，按字典序来比较两个字符串
// }
//
// int main()
// {
// 	std::string hello { "Hello" };
// 	std::string world { "World" };
//
// 	std::cout << firstAlphabetical(hello, world); // 按引用传递，按引用返回
//
// 	return 0;
// }

// 成员函数也可以通过引用返回数据，并且也遵循与非成员函数相同的规则。然而，成
// 员函数还有一个额外的情况需要讨论：通过引用返回数据成员。
//
// 这在getter访问函数中最常见，因此将使用getter成员函数来说明这个主题。但请注
// 意，该主题适用于返回数据成员引用的任何成员函数。
//

// ―――― 按值返回数据成员可能很昂贵 ――――

// 考虑以下示例：

// [代码 2]
// #include <iostream>
// #include <string>
//
// class Employee
// {
// 	std::string m_name{};
//
// public:
// 	void setName(std::string_view name) { m_name = name; }
// 	std::string getName() const { return m_name; } //  getter 按值返回
// };
//
// int main()
// {
// 	Employee joe{};
// 	joe.setName("Joe");
// 	std::cout << joe.getName();
//
// 	return 0;
// }

// 在本例中，getName() 访问函数按值返回std::string m_name。
//
// 虽然这是最安全的做法，但这也意味着每次调用 getName() 时都会生成m_name的昂贵
// 副本。由于访问函数往往会被大量调用，因此这通常不是最佳选择。
//

// ―――― 通过左值引用返回数据成员 ――――

// 成员函数还可以通过（常量）左值引用返回数据成员。
//
// 数据成员与包含它们的对象具有相同的生存期。由于成员函数总是在对象上调用，并
// 且该对象必须存在于调用方的作用域中，因此成员函数通过（常量）左值引用返回数
// 据成员通常是安全的（因为当函数返回时，通过引用返回的成员仍然存在于调用者的
// 作用域）。
//
// 让我们更新上面的示例，以便getName()通过常量左值引用返回m_name：

// [代码 3]
// #include <iostream>
// #include <string>
//
// class Employee
// {
// 	std::string m_name{};
//
// public:
// 	void setName(std::string_view name) { m_name = name; }
// 	const std::string& getName() const { return m_name; } //  getter 返回 const 左值引用
// };
//
// int main()
// {
// 	Employee joe{}; // joe 在函数结束前都会存在
// 	joe.setName("Joe");
//
// 	std::cout << joe.getName(); // 获取 joe.m_name 的引用
//
// 	return 0;
// }

// 现在，当调用joe.getName() 时，joe.m_name通过引用返回调用方，避免了复制。然
// 后，调用者使用该引用将joe.m_name打印到控制台。
//
// 由于在main()函数结束之前，joe一直存在于调用方的作用域中，因此对joe.m_name的
// 引用在相同的持续时间内也是有效的。
//
// 关键点
//
// 可以将（常量）左值引用返回给数据成员。在函数返回后，隐式对象（包含数据成员）
// 仍然存在于调用方的作用域中，因此任何返回的引用都是有效的。
//

// ―――― 返回对数据成员的引用的成员函数的返回类型应与数据成员的类型匹配 ――――

// 通常，通过引用返回的成员函数，其返回类型应与返回的数据成员的类型匹配。在上
// 面的示例中，m_name的类型为std::string，因此getName()返回const std::string&。
//
// 返回std::string_view将需要创建一个临时std::string_view，并在每次调用函数时
// 返回。这种低效是不必要的。如果调用者需要std::string_view，他们可以自己进行
// 转换。
//
// 对于getter，使用auto可以让编译器从返回的成员推断返回类型，这是确保不发生转
// 换的有用方法：

// [代码 4]
// #include <iostream>
// #include <string>
//
// class Employee
// {
// 	std::string m_name{};
//
// public:
// 	void setName(std::string_view name) { m_name = name; }
// 	const auto& getName() const { return m_name; } // 使用 `auto` 让编译器从 m_name 自动推导返回类型
// };
//
// int main()
// {
// 	Employee joe{}; // joe 在函数结束前都会存在
// 	joe.setName("Joe");
//
// 	std::cout << joe.getName(); // 获取 joe.m_name 的引用
//
// 	return 0;
// }

// 然而，从文档的角度来看，使用auto返回类型会模糊getter的返回类型。例如：

// [代码 5]
// 	const auto& getName() const { return m_name; } // 使用 `auto` 让编译器从 m_name 自动推导返回类型

// 不清楚该函数实际返回的字符串类型（它可能是std::string、std::string_view、C
// 样式的字符串，或者完全是其他类型的字符串！）。
//
// 因此，通常更推荐显式返回类型。
//
// 最佳实践
//
// 返回引用的成员函数，应返回与所返回的数据成员类型相同的引用，以避免不必要的
// 转换。
//

// ―――― 右值隐式对象并通过引用返回 ――――

// 有一种情况需要小心一点。在上面的例子中，joe是一个左值对象，它一直存在到函数
// 结束。因此，joe.getName()返回的引用在函数结束之前也是有效的。
//
// 但是，如果隐式对象是一个右值（例如某个按值返回的函数的返回值），该怎么办？
// 右值对象在创建它们的完整表达式的末尾被销毁。当右值对象被破坏时，对该右值成
// 员的任何引用都将无效并悬空，并且使用这种引用将产生未定义的行为。
//
// 因此，对右值对象成员的引用只能在创建右值对象的完整表达式中安全使用。
//
// 让我们探讨一些与此相关的案例：

// [代码 6]
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Employee
// {
// 	std::string m_name{};
//
// public:
// 	void setName(std::string_view name) { m_name = name; }
// 	const std::string& getName() const { return m_name; } //  getter 返回const引用
// };
//
// // createEmployee() 创建一个 Employee 值 (返回的是右值)
// Employee createEmployee(std::string_view name)
// {
// 	Employee e;
// 	e.setName(name);
// 	return e;
// }
//
// int main()
// {
// 	// Case 1: okay: 在相同表达式中获取右值对象成员的引用
// 	std::cout << createEmployee("Frank").getName();
//
// 	// Case 2: 有误: 保存右值对象成员的引用在之后使用
// 	const std::string& ref { createEmployee("Garbo").getName() }; // createEmployee() 创建的对象被销毁后，返回的引用将会悬空
// 	std::cout << ref; // 未定义的行为
//
// 	// Case 3: okay: 将引用的值拷贝到其他对象
// 	std::string val { createEmployee("Hans").getName() };
// 	std::cout << val; // okay: val 是一个独立的对象
//
// 	return 0;
// }

// 当调用createEmployee()时，它将按值返回Employee对象。这个返回的Employee对象
// 是一个右值，它将一直存在到包含对createEmployee()的调用的完整表达式的末尾。
// 当该右值对象被销毁时，对该对象成员的任何引用都将成为悬空的。
//
// 在Case 1中，调用createEmployee(“Frank”)，它返回一个右值Employee对象。然后对
// 这个右值对象调用getName()，它返回对m_name的引用。然后立即使用该引用将名称打
// 印到控制台。此时，包含对createEmployee(“Frank”)的调用的完整表达式结束，右值
// 对象及其成员被销毁。由于右值对象或其成员都没有在这一处之外使用，因此这种情
// 况可以正常运行。
//
// 在Case 2中，遇到了问题。首先，createEmployee(“Garbo”)返回一个右值对象。然后
// 调用getName()来获取对该右值的m_name成员的引用。接着使用该m_name成员初始化
// ref。此时，包含对createEmployee(“Garbo”)的调用的完整表达式结束，右值对象及
// 其成员被销毁。这使得ref悬空。因此，当在后续语句中使用ref时，访问的是悬空引
// 用，会产生未定义行为。
//
// 但如果想保存函数中的值，该函数通过引用返回成员以供以后使用，该怎么办？可以
// 使用返回的引用来初始化非引用局部变量。
//
// 在Case 3中，使用返回的引用来初始化非引用局部变量val。这将导致被引用的成员被
// 复制到val。初始化后，val独立于引用而存在。因此，当右值对象随后被销毁时，val
// 不受影响。val可以在之后的语句中输出，而不会出现问题。
//
// 警告
//
// 右值对象在创建它的完整表达式的末尾被销毁。对右值对象成员的任何引用都将在该
// 点悬空。
//
// 对右值对象成员的引用只能在创建右值对象的完整表达式中安全使用。
//
// 关键点
//
// 在将完整表达式用作初始值设定项后，对该完整表达式的求值将结束。这允许使用相
// 同类型的右值初始化对象（因为在初始化发生之前右值不会被销毁）。
//

// ―――― 安全使用成员函数返回的引用 ――――

// 尽管右值隐式对象存在潜在的危险，但getter通常返回常量引用，而不是复制对象。
//
// 鉴于此，让我们讨论一下如何安全地使用这些函数的返回值。上述示例中的三个案例
// 说明了三个关键点：
// - 优先立即使用成员函数返回的引用（如情况1所示）。由于这对左值和右值对象都
//   有效，因此如果总是这样做，将避免麻烦。
// - 不要“保存”返回的引用以供以后使用（如案例2所示），除非确定隐式对象是左值。
//   如果对右值隐式对象执行此操作，则悬空引用将导致未定义行为。
// - 如果确实需要持久化返回的引用以供以后使用，并且不确定隐式对象是左值，则使
//   用返回的引用来初始化一个新的对象，这将制作一个新的副本（如案例3所示）。
//

// ―――― 不返回对私有数据成员的非常量引用 ――――

// 因为引用的操作就像操作被引用的对象，所以返回非常量引用的成员函数提供对该成
// 员的直接访问（即使该成员是私有的）。
//
// 例如：

// [代码 7]
// #include <iostream>
//
// class Foo
// {
// private:
//     int m_value{ 4 }; // private 成员
//
// public:
//     int& value() { return m_value; } // 返回了非常量引用 (不要这样做)
// };
//
// int main()
// {
//     Foo f{};                // f.m_value 初始化是 4
//     f.value() = 5;          // 相当于 m_value = 5
//     std::cout << f.value(); // 打印 5
//
//     return 0;
// }

// 因为 value() 返回对m_value的非常量引用，所以调用方可以使用该引用直接访问（
// 并更改）m_value。
//
// 这允许调用者破坏访问控制系统。
//

// ―――― Const成员函数不能返回对数据成员的非常量引用 ――――

// 不允许const成员函数返回对成员的非常量引用。这是有意义的——不允许常量成员函数
// 修改对象的状态，也不允许它调用将修改对象状态的函数。它不应该做任何可能导致
// 修改对象的事情。
//
// 如果允许const成员函数返回对成员的非常量引用，则它将为调用方提供一种直接修改
// 该成员的方法。这违反了const成员函数的意图。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	std::string getName() const { return m_name; } //  getter 按值返回
};

int main()
{
	Employee joe{};
	joe.setName("Joe");
	std::cout << joe.getName();

	return 0;
}
