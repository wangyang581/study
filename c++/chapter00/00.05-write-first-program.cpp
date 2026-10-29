// ==========================================================================
// 0.5 第一个C++程序
// --------------------------------------------------------------------------
// 课程: C++学习网 · 序章
// 原文: https://www.studycpp.cn/basic/chapter0/write-first-program/
// 说明: 教程正文以注释形式完整收录在本文件中，可对照原文学习。
//       文末「可运行示例」取自教程代码块，已通过编译校验，可直接运行。
// 编译: g++ -std=c++20 -Wall -Wextra "00.05-write-first-program.cpp" -o /tmp/a.out && /tmp/a.out
// ==========================================================================
//
// 本节内容:
//   · 使用Visual Studio开发
//   · 使用命令行进行开发

// ==========================================================================
// 教程正文
// ==========================================================================

// 准备好开发环境后，来编写第一个程序。
//

// ―――― 使用Visual Studio开发 ――――

// - 打开VS（Visual Studio），选择「创建新项目」。
//
// 在IDE中，「项目」代表生成程序所需的所有资源的集合， 包括源代码、音频、数据
// 文件、编译链接设置等。
//
// 当需要创建新程序时，需要重新创建新的项目。 不同IDE的项目有不同的保存格式，
// 一般无法打开其他IDE创建的项目。
// [图片] https://www.studycpp.cn/basic/chapter0/write-first-program/create_project.png
// 创建项目
// - 选择控制台应用
//
// 学习C++基础知识时，建议选择「控制台应用」。
//
// 控制台应用是指生成的程序从命令行读取数据或打印数据到命令行。 不涉及复杂的图
// 形界面操作，同时无需修改即可在不同操作系统上运行，非常适合入门学习。
// [图片] https://www.studycpp.cn/basic/chapter0/write-first-program/console_project.png
// 选择项目类型
// - 填写项目名称
//
// 填写项目名称「HelloWorld」。推荐选择「将解决方案和项目放在同一目录」。
//
// 单个解决方案里，可包含多个项目，这里暂时不展开。
// [图片] https://www.studycpp.cn/basic/chapter0/write-first-program/project_name.png
// 填写项目名称
// - 运行项目
//
// 项目打开后，右侧「资源管理器」中包含解决方案和项目。 「源文件」中有「
// HelloWorld.cpp」。 在中间的编辑器中可以看到「HelloWorld.cpp」的源代码。 点
// 击「调试」-「开始执行不调试」即可运行程序。
// [图片] https://www.studycpp.cn/basic/chapter0/write-first-program/project.png
// 编辑界面
//
// 此时，窗口下方「输出」框里会显示如下文字，代表编译成功。 编译生成的可执行文
// 件路径为「D:\code\HelloWorld\x64\Debug\HelloWorld.exe」。

// [代码 1]
// 已启动生成...
// 1>------ 已启动生成: 项目: HelloWorld, 配置: Debug x64 ------
// 1>HelloWorld.cpp
// 1>HelloWorld.vcxproj -> D:\code\HelloWorld\x64\Debug\HelloWorld.exe
// ========== 版本: 1 成功，0 失败，0 更新，0 跳过 ==========
// ========== 占用时间 00:13.214 ==========

// - 查看运行效果
//
// 下图中，打印出「Hello World！」。
// [图片] https://www.studycpp.cn/basic/chapter0/write-first-program/result.png
// 运行结果
//

// ―――― 使用命令行进行开发 ――――

// 首先在编辑器中输入如下代码。保存为「HelloWorld.cpp」。

// [代码 2]
// #include <iostream>
//
// int main()
// {
//     std::cout << "Hello World!" << std::endl;
//     return 0;
// }

// 使用「g++」对cpp文件进行编译。

// [文本/输出]
// g++ -o HelloWorld HelloWorld.cpp

// 编译完成后，可以在当前目录下看到可执行文件「HelloWorld」。
//
// 执行如下命令即可查看运行效果。

// [文本/输出]
// ./HelloWorld

//

// ==========================================================================
// 可运行示例（来自教程代码块）
// ==========================================================================

#include <iostream>

int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}
