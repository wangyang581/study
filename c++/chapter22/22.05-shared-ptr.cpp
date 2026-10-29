// ==========================================================================
// 22.5 std::shared_ptr
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十二章 移动语义与智能指针
// 原文: https://www.studycpp.cn/basic/chapter22/shared-ptr/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "22.05-shared-ptr.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · std::make_shared
//   · 挖掘std::shared_ptr
//   · 可以从unique_ptr创建shared_ptr
//   · std::shared_ptr的风险
//   · std::shared_ptr和数组
//   · 结论

// ==========================================================================
// 教程正文
// ==========================================================================

// std::unique_ptr被设计为单独拥有和管理资源，而std::shared_ptr则用于解决多个
// 智能指针需要共同拥有资源的情况。
//
// 这意味着可以让多个std::shared_ptr指向同一资源。std::shared_ptr内部会跟踪有
// 多少个std::shared_ptr正在共享资源。只要至少有一个std::shared_ptr指向该资源，
// 资源就不会被释放，即使某个std::shared_ptr已经被销毁。一旦管理资源的最后一个
// std::shared_ptr超出作用域（或被重新赋值为其他数据），资源就会被释放。
//
// 与std::unique_ptr一样，std::shared_ptr也存在于<memory>头文件中。

// [代码 1]
// #include <iostream>
// #include <memory> // for std::shared_ptr
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// int main()
// {
// 	// 动态分配一个 Resource 对象，并将所有权赋给 std::shared_ptr
// 	Resource* res { new Resource };
// 	std::shared_ptr<Resource> ptr1{ res };
// 	{
// 		std::shared_ptr<Resource> ptr2 { ptr1 }; // 让另外的 std::shared_ptr 也指向相同的资源
//
// 		std::cout << "Killing one shared pointer\n";
// 	} // ptr2 超出作用域, 但资源仍被ptr1持有
//
// 	std::cout << "Killing another shared pointer\n";
//
// 	return 0;
// } // ptr1 超出作用域, 分配的 Resource 被销毁

// 这将打印：

// [文本/输出]
// Resource acquired
// Killing one shared pointer
// Killing another shared pointer
// Resource destroyed

// 在上面的代码中，我们创建了一个动态Resource对象，并设置一个名为ptr1的
// std::shared_ptr来管理它。在嵌套块中，我们使用拷贝构造函数创建了指向同一资源
// 的第二个std::shared_ptr（ptr2）。当ptr2超出作用域时，资源不会被释放，因为
// ptr1仍然指向该资源。当ptr1超出作用域时，ptr1发现不再有std::shared_ptr管理该
// 资源，因此释放资源。
//
// 请注意，我们从第一个shared_ptr创建了第二个shared_ptr。这很重要。考虑以下类
// 似的程序：

// [代码 2]
// #include <iostream>
// #include <memory> // for std::shared_ptr
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// int main()
// {
// 	Resource* res { new Resource };
// 	std::shared_ptr<Resource> ptr1 { res };
// 	{
// 		std::shared_ptr<Resource> ptr2 { res }; // 直接从res创建 ptr2
//
// 		std::cout << "Killing one shared pointer\n";
// 	} // ptr2 超出作用域, 分配的资源被销毁
//
// 	std::cout << "Killing another shared pointer\n";
//
// 	return 0;
// } // ptr1 超出作用域, 分配的资源被再次销毁

// 该程序打印：

// [文本/输出]
// Resource acquired
// Killing one shared pointer
// Resource destroyed
// Killing another shared pointer
// Resource destroyed

// 然后崩溃（至少在作者的机器上）。
//
// 这里的区别在于，我们独立创建了两个std::shared_ptr。因此，即使它们都指向同一
// 资源，它们也不会知道彼此的存在。当ptr2超出作用域时，它认为自己是资源的唯一
// 所有者，并释放该资源。当ptr1之后超出作用域时，它也会这样认为，并再次尝试删
// 除资源。于是问题就发生了。
//
// 幸运的是，这很容易避免：如果需要让多个std::shared_ptr指向同一资源，请复制现
// 有的std::shared_ptr。
//
// 就像std::unique_ptr一样，std::shared_ptr可以是空指针，因此在使用之前请检查
// 其是否有效。
//

// ―――― std::make_shared ――――

// C++14中的std::make_unique()可以用于创建std::unique_ptr。与之类似，
// std::make_shared()可以（并且应该）用于生成std::shared_ptr。
// std::make_shared()在C++11中可用。
//
// 下面是使用std::make_shared()的示例：

// [代码 3]
// #include <iostream>
// #include <memory> // for std::shared_ptr
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// int main()
// {
// 	// 动态分配一个 Resource 对象并将所有权交给 std::shared_ptr
// 	auto ptr1 { std::make_shared<Resource>() };
// 	{
// 		auto ptr2 { ptr1 }; // 从 ptr1 创建 ptr2
//
// 		std::cout << "Killing one shared pointer\n";
// 	} // ptr2 超出作用域, 但资源仍被ptr1持有
//
// 	std::cout << "Killing another shared pointer\n";
//
// 	return 0;
// } // ptr1 超出作用域, 分配的 Resource 被销毁

// 使用std::make_shared()的原因与使用std::make_unique()一样。
//

// ―――― 挖掘std::shared_ptr ――――

// 与内部只使用单个指针的std::unique_ptr不同，std::shared_ptr内部使用两个指针。
// 一个指针指向被管理的资源，另一个指针指向“控制块”。控制块是一个动态分配的对
// 象，用来跟踪一系列信息，包括有多少std::shared_ptr指向该资源。当通过
// std::shared_ptr构造函数创建std::shared_ptr时，托管对象（传入的对象）和控制
// 块（构造函数创建）的内存会分别分配。然而，当使用std::make_shared()时，这可
// 以优化为单次内存分配，从而获得更好的性能。
//
// 这也解释了为什么单独创建两个指向同一资源的std::shared_ptr会带来麻烦。每个
// std::shared_ptr都有一个指向资源的指针。然而，每个std::shared_ptr都会独立分
// 配自己的控制块，而控制块会表明它是唯一拥有该资源的指针。因此，当该
// std::shared_ptr超出作用域时，它会释放资源，却不知道还有其他std::shared_ptr
// 也在尝试管理同一资源。
//
// 然而，当使用拷贝赋值克隆std::shared_ptr时，控制块中的数据会被正确更新，以表
// 示现在有额外的std::shared_ptr共同管理该资源。
//

// ―――― 可以从unique_ptr创建shared_ptr ――――

// shared_ptr的构造函数可以接收右值unique_ptr。std::unique_ptr的内容会被移动到
// std::shared_ptr中。
//
// 然而，无法安全地将std::shared_ptr转换为std::unique_ptr。这意味着，如果您要
// 创建一个返回智能指针的函数，最好返回std::unique_ptr，并在适当时候将其分配给
// std::shared_ptr。
//

// ―――― std::shared_ptr的风险 ――――

// std::shared_ptr也有一些与std::unique_ptr相同的挑战：如果std::shared_ptr未被
// 正确处理（例如它本身是动态分配的但从未删除，或者它是某个动态分配但从未删除
// 的对象的一部分），那么它管理的资源也不会被释放。使用std::unique_ptr时，您只
// 需要担心一个智能指针是否被正确释放。使用std::shared_ptr时，必须确保所有相关
// 智能指针都被正确释放。如果管理资源的任何std::shared_ptr未被正确销毁，该资源
// 就不会被正确释放。
//

// ―――― std::shared_ptr和数组 ――――

// 在C++17和更早版本中，std::shared_ptr不支持管理数组，不能用于管理C样式的数组。
// 从C++20开始，std::shared_ptr开始支持数组。
//

// ―――― 结论 ――――

// std::shared_ptr是为多个智能指针共同管理同一资源的情况而设计的。当管理资源的
// 最后一个std::shared_ptr被销毁时，该资源会被释放。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>
#include <memory> // for std::shared_ptr

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
	// 动态分配一个 Resource 对象，并将所有权赋给 std::shared_ptr
	Resource* res { new Resource };
	std::shared_ptr<Resource> ptr1{ res };
	{
		std::shared_ptr<Resource> ptr2 { ptr1 }; // 让另外的 std::shared_ptr 也指向相同的资源

		std::cout << "Killing one shared pointer\n";
	} // ptr2 超出作用域, 但资源仍被ptr1持有

	std::cout << "Killing another shared pointer\n";

	return 0;
} // ptr1 超出作用域, 分配的 Resource 被销毁
