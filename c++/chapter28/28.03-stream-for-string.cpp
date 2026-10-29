// ==========================================================================
// 28.3 针对字符串的stream类
// --------------------------------------------------------------------------
// 课程: C++学习网 · 第二十八章 输入输出（I/O）
// 原文: https://www.studycpp.cn/basic/chapter28/stream-for-string/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       本节示例为片段或多文件程序，文末仅有占位 main()。
// 编译: g++ -std=c++20 -Wall -Wextra "28.03-stream-for-string.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 字符串和数字之间的转换
//   · 清空stringstream

// ==========================================================================
// 教程正文
// ==========================================================================

// 到目前为止，您看到的所有I/O示例都是向cout写入或从cin读取。然而，还有一组面
// 向字符串的流类，允许您使用熟悉的插入（<<）和提取（>>）运算符来处理字符串。
// 与istream和ostream一样，字符串流也基于保存数据的缓冲区。不过，与cin和cout不
// 同，这些流不连接到外部I/O通道（例如键盘、显示器等）。字符串流的主要用途之一，
// 是缓冲输出以供以后显示，或者逐行处理输入。
//
// 字符串有六个流类：istringstream（从istream派生）、ostringstream（从ostream
// 派生）和stringstream（从iostream派生）用于读取和写入字符串。wistringstream、
// wostringstream和wstringstream用于读取和写入宽字符串。要使用这些类，需要包含
// <sstream> 头文件。
//
// 有两种方法可以将数据写入stringstream：
//
// 使用插入（«）运算符：

// [代码 1]
// std::stringstream os {};
// os << "en garde!\n"; // 将 "en garde!" 插入到 stringstream

// 或者使用 str(string) 函数来设置缓冲区：

// [代码 2]
// std::stringstream os {};
// os.str("en garde!"); // 将 stringstream 的 buffer 设置为 "en garde!"

// 类似地，有两种方法可以从stringstream中获取数据：
//
// 使用 str() 函数从缓冲区中获取数据：

// [代码 3]
// std::stringstream os {};
// os << "12345 67.89\n";
// std::cout << os.str();

// 这会打印：

// [文本/输出]
// 12345 67.89

// 或者使用提取（»）运算符：

// [代码 4]
// std::stringstream os {};
// os << "12345 67.89"; // 将数字组成的字符串写入 os
//
// std::string strValue {};
// os >> strValue;
//
// std::string strValue2 {};
// os >> strValue2;
//
// // 打印提取结果
// std::cout << strValue << " - " << strValue2 << '\n';

// 该程序打印：

// [文本/输出]
// 12345 - 67.89

// 注意，» 运算符会迭代字符串——每次连续使用 » 都会返回流中的下一个可提取值。另
// 一方面，str()会返回流的完整内容。
//

// ―――― 字符串和数字之间的转换 ――――

// 因为插入和提取运算符知道如何处理所有基本数据类型，所以我们可以使用它们将字
// 符串转换为数字，反之亦然。
//
// 首先，让我们看看如何将数字转换为字符串：

// [代码 5]
// std::stringstream os {};
//
// constexpr int nValue { 12345 };
// constexpr double dValue { 67.89 };
// os << nValue << ' ' << dValue;
//
// std::string strValue1, strValue2;
// os >> strValue1 >> strValue2;
//
// std::cout << strValue1 << ' ' << strValue2 << '\n';

// 此代码段打印：

// [文本/输出]
// 12345 67.89

// 现在，让我们将字符串转换为数字：

// [代码 6]
// std::stringstream os {};
// os << "12345 67.89"; // 将字符串写入到 stringstream 中
// int nValue {};
// double dValue {};
//
// os >> nValue >> dValue;
//
// std::cout << nValue << ' ' << dValue << '\n';

// 该程序打印：

// [文本/输出]
// 12345 67.89

//

// ―――― 清空stringstream ――――

// 有几种方法可以清空stringstream的缓冲区。
//
// 使用 str() 设置一个空的C样式字符串：

// [代码 7]
// std::stringstream os {};
// os << "Hello ";
//
// os.str(""); // 清空 buffer
//
// os << "World!";
// std::cout << os.str();

// 使用 str() 设置一个空的 std::string 对象：

// [代码 8]
// std::stringstream os {};
// os << "Hello ";
//
// os.str(std::string{}); // 清空 buffer
//
// os << "World!";
// std::cout << os.str();

// 这两个程序都会产生以下结果：

// [文本/输出]
// World!

// 设置为空后，调用clear()函数通常是一个好主意：

// [代码 9]
// std::stringstream os {};
// os << "Hello ";
//
// os.str(""); // 清空 buffer
// os.clear(); // 重置错误标志
//
// os << "World!";
// std::cout << os.str();

// clear()会重置可能已经设置的任何错误标志，并将流设置回ok状态。在下一课中，我
// 们将详细讨论流的状态和错误标志。
//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
    // 本节教程的代码是多文件示例、片段或概念性内容，没有可直接编译的完整程序。
    // 请对照上面的注释和代码块，自己动手补全并运行验证。
    std::cout << "本节无独立可运行示例, 请阅读文件中的教程正文。\n";
    return 0;
}
