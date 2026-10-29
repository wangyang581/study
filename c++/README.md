# C++ 学习笔记（基于 C++学习网）

本站内容按照 [C++学习网](https://www.studycpp.cn/) 的教程组织：**每章一个目录，每节一个可编译的 `.cpp` 文件**。

每个 `.cpp` 文件里包含：

1. **文件头**：章节、节号、原文链接、编译命令、本节目录；
2. **教程正文**：把原文（含代码块、表格、习题答案）以 `//` 注释形式完整收录，便于对照学习；
3. **可运行示例**：从教程代码块中挑出的完整程序（已通过 `clang++ -std=c++20` 语法校验），
   没有完整程序时给出占位 `main()`。

## 编译方式

```bash
# 推荐：直接编译并运行某一节
./tools/run.sh chapter04/04.09-if.cpp

# 手动编译单个文件
g++ -std=c++20 -Wall -Wextra "chapter04/04.09-if.cpp" -o /tmp/a.out && /tmp/a.out

# macOS 自带的 clang++
clang++ -std=c++20 -Wall -Wextra "chapter04/04.09-if.cpp" -o /tmp/a.out && /tmp/a.out
```

## 目录约定

```
c++/
├── README.md              # 本文件（含全部 313 节的学习进度清单）
├── chapter00 ~ chapter28/ # 每章一个目录，内含 README + 每节一个 .cpp
└── tools/
    ├── run.sh             # 一键编译运行脚本
    └── studycpp_gen.py    # 抓取/生成脚本（页面缓存在 tools/.cache）
```

## 章节

| 章 | 目录 | 节数 | 内容 |
| --- | --- | --- | --- |
| 0 | [`chapter00/`](./chapter00) | 6 | 序章 |
| 1 | [`chapter01/`](./chapter01) | 12 | 第一章 基础知识 |
| 2 | [`chapter02/`](./chapter02) | 14 | 第二章 函数 |
| 3 | [`chapter03/`](./chapter03) | 11 | 第三章 程序调试 |
| 4 | [`chapter04/`](./chapter04) | 13 | 第四章 基本数据类型 |
| 5 | [`chapter05/`](./chapter05) | 12 | 第五章 常量，字符串 |
| 6 | [`chapter06/`](./chapter06) | 8 | 第六章 运算符 |
| 7 | [`chapter07/`](./chapter07) | 14 | 第七章 作用域与编译链接 |
| 8 | [`chapter08/`](./chapter08) | 16 | 第八章 控制流与错误处理 |
| 9 | [`chapter09/`](./chapter09) | 7 | 第九章 错误检查与处理 |
| 10 | [`chapter10/`](./chapter10) | 10 | 第十章 类型转换，类型别名与类型推导 |
| 11 | [`chapter11/`](./chapter11) | 10 | 第十一章 函数重载与函数模版 |
| 12 | [`chapter12/`](./chapter12) | 15 | 第十二章 复合类型：引用与指针 |
| 13 | [`chapter13/`](./chapter13) | 15 | 第十三章 复合类型：枚举与结构体 |
| 14 | [`chapter14/`](./chapter14) | 17 | 第十四章 class介绍 |
| 15 | [`chapter15/`](./chapter15) | 11 | 第十五章 class第二部分 |
| 16 | [`chapter16/`](./chapter16) | 13 | 第十六章 动态数组：std::vector |
| 17 | [`chapter17/`](./chapter17) | 14 | 第十七章 固定长度数组：std::array与c样式数组 |
| 18 | [`chapter18/`](./chapter18) | 4 | 第十八章 迭代器与算法 |
| 19 | [`chapter19/`](./chapter19) | 5 | 第十九章 动态内存分配 |
| 20 | [`chapter20/`](./chapter20) | 8 | 第二十章 函数 |
| 21 | [`chapter21/`](./chapter21) | 15 | 第二十一章 操作符重载 |
| 22 | [`chapter22/`](./chapter22) | 8 | 第二十二章 移动语义与智能指针 |
| 23 | [`chapter23/`](./chapter23) | 8 | 第二十三章 对象关系 |
| 24 | [`chapter24/`](./chapter24) | 10 | 第二十四章 继承 |
| 25 | [`chapter25/`](./chapter25) | 12 | 第二十五章 虚函数 |
| 26 | [`chapter26/`](./chapter26) | 7 | 第二十六章 模板 |
| 27 | [`chapter27/`](./chapter27) | 11 | 第二十七章 异常 |
| 28 | [`chapter28/`](./chapter28) | 7 | 第二十八章 输入输出（I/O） |

## 学习进度

### 序章

- [ ] [`00.00-introduction-to-site.cpp`](./chapter00/00.00-introduction-to-site.cpp) 0.0 网站简介
- [ ] [`00.01-introduction-to-programming-languages.cpp`](./chapter00/00.01-introduction-to-programming-languages.cpp) 0.1 什么是编程语言
- [ ] [`00.02-introduction-to-c-cpp.cpp`](./chapter00/00.02-introduction-to-c-cpp.cpp) 0.2 C与C++
- [ ] [`00.03-introduction-to-development.cpp`](./chapter00/00.03-introduction-to-development.cpp) 0.3 程序开发流程
- [ ] [`00.04-install-dev-env.cpp`](./chapter00/00.04-install-dev-env.cpp) 0.4 安装开发环境
- [ ] [`00.05-write-first-program.cpp`](./chapter00/00.05-write-first-program.cpp) 0.5 第一个C++程序

### 第一章 基础知识

- [ ] [`01.00-program-structure.cpp`](./chapter01/01.00-program-structure.cpp) 1.0 程序结构介绍
- [ ] [`01.01-comment.cpp`](./chapter01/01.01-comment.cpp) 1.1 注释
- [ ] [`01.02-variable.cpp`](./chapter01/01.02-variable.cpp) 1.2 对象与变量
- [ ] [`01.03-variable-init-assign.cpp`](./chapter01/01.03-variable-init-assign.cpp) 1.3 变量初始化和赋值
- [ ] [`01.04-iostream.cpp`](./chapter01/01.04-iostream.cpp) 1.4 iostream:cout、cin和endl简介
- [ ] [`01.05-uninit-variable.cpp`](./chapter01/01.05-uninit-variable.cpp) 1.5 未初始化的变量及未定义的行为
- [ ] [`01.06-keywords-and-naming-identifiers.cpp`](./chapter01/01.06-keywords-and-naming-identifiers.cpp) 1.6 关键字和变量命名规则
- [ ] [`01.07-whitespace.cpp`](./chapter01/01.07-whitespace.cpp) 1.7 空白字符与代码样式
- [ ] [`01.08-literal-operator.cpp`](./chapter01/01.08-literal-operator.cpp) 1.8 字面值和操作符简介
- [ ] [`01.09-exp.cpp`](./chapter01/01.09-exp.cpp) 1.9 表达式简介
- [ ] [`01.10-dev-first-program.cpp`](./chapter01/01.10-dev-first-program.cpp) 1.10 开发第一个程序
- [ ] [`01.11-summary.cpp`](./chapter01/01.11-summary.cpp) 1.11 第1章总结

### 第二章 函数

- [ ] [`02.00-intro-func.cpp`](./chapter02/02.00-intro-func.cpp) 2.0 函数简介
- [ ] [`02.01-func-ret.cpp`](./chapter02/02.01-func-ret.cpp) 2.1 函数返回值
- [ ] [`02.02-func-ret-void.cpp`](./chapter02/02.02-func-ret-void.cpp) 2.2 无返回值函数
- [ ] [`02.03-func-arg.cpp`](./chapter02/02.03-func-arg.cpp) 2.3 函数参数简介
- [ ] [`02.04-local-var.cpp`](./chapter02/02.04-local-var.cpp) 2.4 局部变量
- [ ] [`02.05-why-func.cpp`](./chapter02/02.05-why-func.cpp) 2.5 为什么需要函数
- [ ] [`02.06-forward-declare.cpp`](./chapter02/02.06-forward-declare.cpp) 2.6 前向声明
- [ ] [`02.07-multi-file.cpp`](./chapter02/02.07-multi-file.cpp) 2.7 多代码文件程序
- [ ] [`02.08-namespace.cpp`](./chapter02/02.08-namespace.cpp) 2.8 命名冲突和名称空间简介
- [ ] [`02.09-preprocess.cpp`](./chapter02/02.09-preprocess.cpp) 2.9 预处理器简介
- [ ] [`02.10-header-file.cpp`](./chapter02/02.10-header-file.cpp) 2.10 头文件
- [ ] [`02.11-header-guard.cpp`](./chapter02/02.11-header-guard.cpp) 2.11 头文件保护
- [ ] [`02.12-design-first-program.cpp`](./chapter02/02.12-design-first-program.cpp) 2.12 设计第一个程序
- [ ] [`02.13-summary.cpp`](./chapter02/02.13-summary.cpp) 2.13 第2章总结

### 第三章 程序调试

- [ ] [`03.00-syntax-semantic-errors.cpp`](./chapter03/03.00-syntax-semantic-errors.cpp) 3.0 语法和语义错误
- [ ] [`03.01-debug-process.cpp`](./chapter03/03.01-debug-process.cpp) 3.1 程序调试过程
- [ ] [`03.02-debug-strategy.cpp`](./chapter03/03.02-debug-strategy.cpp) 3.2 调试策略
- [ ] [`03.03-debug-tatics.cpp`](./chapter03/03.03-debug-tatics.cpp) 3.3 基本调试策略
- [ ] [`03.04-more-tatics.cpp`](./chapter03/03.04-more-tatics.cpp) 3.4 更多调试策略
- [ ] [`03.05-step.cpp`](./chapter03/03.05-step.cpp) 3.5 使用集成调试器：单步执行
- [ ] [`03.06-breakpoint.cpp`](./chapter03/03.06-breakpoint.cpp) 3.6 断点
- [ ] [`03.07-watch-var.cpp`](./chapter03/03.07-watch-var.cpp) 3.7 监视变量
- [ ] [`03.08-call-stack.cpp`](./chapter03/03.08-call-stack.cpp) 3.8 调用堆栈
- [ ] [`03.09-avoid-problem.cpp`](./chapter03/03.09-avoid-problem.cpp) 3.9 在问题变成问题前进行避免
- [ ] [`03.10-summary.cpp`](./chapter03/03.10-summary.cpp) 3.10 第3章总结

### 第四章 基本数据类型

- [ ] [`04.00-intro.cpp`](./chapter04/04.00-intro.cpp) 4.0 基本数据类型简介
- [ ] [`04.01-void.cpp`](./chapter04/04.01-void.cpp) 4.1 Void
- [ ] [`04.02-size-of.cpp`](./chapter04/04.02-size-of.cpp) 4.2 对象大小和sizeof运算符
- [ ] [`04.03-sign-int.cpp`](./chapter04/04.03-sign-int.cpp) 4.3 有符号整数
- [ ] [`04.04-unsign-int.cpp`](./chapter04/04.04-unsign-int.cpp) 4.4 无符号整数，以及为什么要避免使用它们
- [ ] [`04.05-fix-int.cpp`](./chapter04/04.05-fix-int.cpp) 4.5 固定宽度整数和size_t
- [ ] [`04.06-sci-notation.cpp`](./chapter04/04.06-sci-notation.cpp) 4.6 科学记数法
- [ ] [`04.07-float.cpp`](./chapter04/04.07-float.cpp) 4.7 浮点数
- [ ] [`04.08-bool.cpp`](./chapter04/04.08-bool.cpp) 4.8 布尔值（Boolean）
- [ ] [`04.09-if.cpp`](./chapter04/04.09-if.cpp) 4.9 if语句简介
- [ ] [`04.10-char.cpp`](./chapter04/04.10-char.cpp) 4.10 字符
- [ ] [`04.11-type-convert.cpp`](./chapter04/04.11-type-convert.cpp) 4.11 类型转换和static_cast简介
- [ ] [`04.12-summary.cpp`](./chapter04/04.12-summary.cpp) 4.12 第4章总结

### 第五章 常量，字符串

- [ ] [`05.00-const-var.cpp`](./chapter05/05.00-const-var.cpp) 5.0 常量（命名常量）
- [ ] [`05.01-const-exp.cpp`](./chapter05/05.01-const-exp.cpp) 5.1 常量表达式、编译时常量和运行时常量
- [ ] [`05.02-constexpr.cpp`](./chapter05/05.02-constexpr.cpp) 5.2 Constexpr
- [ ] [`05.03-literal.cpp`](./chapter05/05.03-literal.cpp) 5.3 字面值常量
- [ ] [`05.04-num-sys.cpp`](./chapter05/05.04-num-sys.cpp) 5.4 数字系统（十进制、二进制、十六进制和八进制）
- [ ] [`05.05-cond-op.cpp`](./chapter05/05.05-cond-op.cpp) 5.5 条件运算符
- [ ] [`05.06-inline.cpp`](./chapter05/05.06-inline.cpp) 5.6 内联函数和变量
- [ ] [`05.07-const-eval.cpp`](./chapter05/05.07-const-eval.cpp) 5.7 Constexpr和consteval函数
- [ ] [`05.08-string.cpp`](./chapter05/05.08-string.cpp) 5.8 std::string简介
- [ ] [`05.09-string-view.cpp`](./chapter05/05.09-string-view.cpp) 5.9 std::string_view简介
- [ ] [`05.10-string-view2.cpp`](./chapter05/05.10-string-view2.cpp) 5.10 std::string_view（第2部分）
- [ ] [`05.11-summary.cpp`](./chapter05/05.11-summary.cpp) 5.11 第五章总结

### 第六章 运算符

- [ ] [`06.00-op-precedence.cpp`](./chapter06/06.00-op-precedence.cpp) 6.0 运算符优先级和结合性
- [ ] [`06.01-arithmetic-op.cpp`](./chapter06/06.01-arithmetic-op.cpp) 6.1 算术运算符
- [ ] [`06.02-remaind-exp.cpp`](./chapter06/06.02-remaind-exp.cpp) 6.2 余数和指数
- [ ] [`06.03-incre-decre.cpp`](./chapter06/06.03-incre-decre.cpp) 6.3 自增/自减运算符和副作用
- [ ] [`06.04-comma.cpp`](./chapter06/06.04-comma.cpp) 6.4 逗号运算符
- [ ] [`06.05-relation-op.cpp`](./chapter06/06.05-relation-op.cpp) 6.5 关系运算符和浮点比较
- [ ] [`06.06-logic-op.cpp`](./chapter06/06.06-logic-op.cpp) 6.6 逻辑运算符
- [ ] [`06.07-summary.cpp`](./chapter06/06.07-summary.cpp) 6.7 第六章总结

### 第七章 作用域与编译链接

- [ ] [`07.00-code-block.cpp`](./chapter07/07.00-code-block.cpp) 7.0 代码块
- [ ] [`07.01-user-def-namespace.cpp`](./chapter07/07.01-user-def-namespace.cpp) 7.1 自定义命名空间和作用域解析操作符
- [ ] [`07.02-local-var.cpp`](./chapter07/07.02-local-var.cpp) 7.2 局部变量
- [ ] [`07.03-global-var.cpp`](./chapter07/07.03-global-var.cpp) 7.3 全局变量
- [ ] [`07.04-name-shadow.cpp`](./chapter07/07.04-name-shadow.cpp) 7.4 变量名称遮挡（Variable shadowing）
- [ ] [`07.05-internal-link.cpp`](./chapter07/07.05-internal-link.cpp) 7.5 内部链接
- [ ] [`07.06-external-link.cpp`](./chapter07/07.06-external-link.cpp) 7.6 外部链接和变量前向声明
- [ ] [`07.07-why-non-const-global-var-evil.cpp`](./chapter07/07.07-why-non-const-global-var-evil.cpp) 7.7 为什么（非常量）全局变量是邪恶的
- [ ] [`07.08-share-const-global.cpp`](./chapter07/07.08-share-const-global.cpp) 7.8 在多个文件中共享全局常量（使用内联变量）
- [ ] [`07.09-static-local-var.cpp`](./chapter07/07.09-static-local-var.cpp) 7.9 静态局部变量
- [ ] [`07.10-scope-duration-linkage.cpp`](./chapter07/07.10-scope-duration-linkage.cpp) 7.10 作用域、存储期和链接摘要
- [ ] [`07.11-using.cpp`](./chapter07/07.11-using.cpp) 7.11 using声明和using指令
- [ ] [`07.12-unname-namespace.cpp`](./chapter07/07.12-unname-namespace.cpp) 7.12 未命名与内联的命名空间
- [ ] [`07.13-summary.cpp`](./chapter07/07.13-summary.cpp) 7.13 第七章总结

### 第八章 控制流与错误处理

- [ ] [`08.00-control-flow-intro.cpp`](./chapter08/08.00-control-flow-intro.cpp) 8.0 控制流简介
- [ ] [`08.01-if-block.cpp`](./chapter08/08.01-if-block.cpp) 8.1 If语句与代码块
- [ ] [`08.02-if-problem.cpp`](./chapter08/08.02-if-problem.cpp) 8.2 常见的if语句问题
- [ ] [`08.03-constexpr-if.cpp`](./chapter08/08.03-constexpr-if.cpp) 8.3 Constexpr if语句
- [ ] [`08.04-switch.cpp`](./chapter08/08.04-switch.cpp) 8.4 Switch语句基础
- [ ] [`08.05-switch-fallthrough-scope.cpp`](./chapter08/08.05-switch-fallthrough-scope.cpp) 8.5 switch fallthrough机制与作用域
- [ ] [`08.06-goto.cpp`](./chapter08/08.06-goto.cpp) 8.6 goto语句
- [ ] [`08.07-loop.cpp`](./chapter08/08.07-loop.cpp) 8.7 循环和while语句简介
- [ ] [`08.08-do-while.cpp`](./chapter08/08.08-do-while.cpp) 8.8 Do while语句
- [ ] [`08.09-for.cpp`](./chapter08/08.09-for.cpp) 8.9 for语句
- [ ] [`08.10-break-continue.cpp`](./chapter08/08.10-break-continue.cpp) 8.10 break与continue
- [ ] [`08.11-halt.cpp`](./chapter08/08.11-halt.cpp) 8.11 提前退出程序
- [ ] [`08.12-random-intro.cpp`](./chapter08/08.12-random-intro.cpp) 8.12 随机数生成简介
- [ ] [`08.13-random-ms.cpp`](./chapter08/08.13-random-ms.cpp) 8.13 使用Mersenne Twister生成随机数
- [ ] [`08.14-random-global.cpp`](./chapter08/08.14-random-global.cpp) 8.14 全局随机数
- [ ] [`08.15-summary.cpp`](./chapter08/08.15-summary.cpp) 8.15 第八章总结

### 第九章 错误检查与处理

- [ ] [`09.00-intro.cpp`](./chapter09/09.00-intro.cpp) 9.0 代码测试简介
- [ ] [`09.01-code-coverage.cpp`](./chapter09/09.01-code-coverage.cpp) 9.1 代码覆盖率
- [ ] [`09.02-common-semantic-errors.cpp`](./chapter09/09.02-common-semantic-errors.cpp) 9.2 常见的语义错误
- [ ] [`09.03-detect-handle-error.cpp`](./chapter09/09.03-detect-handle-error.cpp) 9.3 检测和处理错误
- [ ] [`09.04-cin-error-handle.cpp`](./chapter09/09.04-cin-error-handle.cpp) 9.4 std::cin和处理无效输入
- [ ] [`09.05-assert.cpp`](./chapter09/09.05-assert.cpp) 9.5 断言
- [ ] [`09.06-summary.cpp`](./chapter09/09.06-summary.cpp) 9.6 第9章总结

### 第十章 类型转换，类型别名与类型推导

- [ ] [`10.00-implicit-type-convert.cpp`](./chapter10/10.00-implicit-type-convert.cpp) 10.0 隐式类型转换
- [ ] [`10.01-promotion.cpp`](./chapter10/10.01-promotion.cpp) 10.1 数值提升
- [ ] [`10.02-num-convert.cpp`](./chapter10/10.02-num-convert.cpp) 10.2 数值转换
- [ ] [`10.03-narrow-convert-list-constexpr-init.cpp`](./chapter10/10.03-narrow-convert-list-constexpr-init.cpp) 10.3 窄化转换、列表初始化和constexpr初始化
- [ ] [`10.04-arithmetic-convert.cpp`](./chapter10/10.04-arithmetic-convert.cpp) 10.4 算术转换
- [ ] [`10.05-explicit-type-convert-static-cast.cpp`](./chapter10/10.05-explicit-type-convert-static-cast.cpp) 10.5 显式类型转换和static_cast
- [ ] [`10.06-typedef.cpp`](./chapter10/10.06-typedef.cpp) 10.6 typedef和类型别名
- [ ] [`10.07-auto-type-object.cpp`](./chapter10/10.07-auto-type-object.cpp) 10.7 使用auto关键字的对象类型自动推导
- [ ] [`10.08-auto-type-func.cpp`](./chapter10/10.08-auto-type-func.cpp) 10.8 函数的类型推导
- [ ] [`10.09-summary.cpp`](./chapter10/10.09-summary.cpp) 10.9 第10章总结

### 第十一章 函数重载与函数模版

- [ ] [`11.00-func-overload-intro.cpp`](./chapter11/11.00-func-overload-intro.cpp) 11.0 函数重载简介
- [ ] [`11.01-func-overload-diff.cpp`](./chapter11/11.01-func-overload-diff.cpp) 11.1 被重载函数之间互相区分
- [ ] [`11.02-func-overload-resolution.cpp`](./chapter11/11.02-func-overload-resolution.cpp) 11.2 函数重载决议
- [ ] [`11.03-func-del.cpp`](./chapter11/11.03-func-del.cpp) 11.3 函数的delete说明符
- [ ] [`11.04-default-param.cpp`](./chapter11/11.04-default-param.cpp) 11.4 默认参数
- [ ] [`11.05-func-template.cpp`](./chapter11/11.05-func-template.cpp) 11.5 函数模板
- [ ] [`11.06-func-template-instane.cpp`](./chapter11/11.06-func-template-instane.cpp) 11.6 函数模板实例化
- [ ] [`11.07-func-template-mutli-type.cpp`](./chapter11/11.07-func-template-mutli-type.cpp) 11.7 具有多个模板类型的函数模板
- [ ] [`11.08-func-template-none-type-param.cpp`](./chapter11/11.08-func-template-none-type-param.cpp) 11.8 非类型模板参数
- [ ] [`11.09-summary.cpp`](./chapter11/11.09-summary.cpp) 11.9 第11章总结

### 第十二章 复合类型：引用与指针

- [ ] [`12.00-compound-data-intro.cpp`](./chapter12/12.00-compound-data-intro.cpp) 12.0 复合数据类型简介
- [ ] [`12.01-value-category.cpp`](./chapter12/12.01-value-category.cpp) 12.1 值类别（左值 lvalue 和右值 rvalue）
- [ ] [`12.02-lvalue-ref.cpp`](./chapter12/12.02-lvalue-ref.cpp) 12.2 左值引用
- [ ] [`12.03-const-lvalue-ref.cpp`](./chapter12/12.03-const-lvalue-ref.cpp) 12.3 const的左值引用
- [ ] [`12.04-lvalue-ref-func-arg.cpp`](./chapter12/12.04-lvalue-ref-func-arg.cpp) 12.4 通过左值引用传递函数参数
- [ ] [`12.05-const-lvalue-ref-func-arg.cpp`](./chapter12/12.05-const-lvalue-ref-func-arg.cpp) 12.5 通过常量左值引用传递函数参数
- [ ] [`12.06-pointer-intro.cpp`](./chapter12/12.06-pointer-intro.cpp) 12.6 指针简介
- [ ] [`12.07-null-ptr.cpp`](./chapter12/12.07-null-ptr.cpp) 12.7 空指针
- [ ] [`12.08-const-ptr.cpp`](./chapter12/12.08-const-ptr.cpp) 12.8 指针与常量
- [ ] [`12.09-pointer-func-arg.cpp`](./chapter12/12.09-pointer-func-arg.cpp) 12.9 通过指针传递函数参数
- [ ] [`12.10-pointer-func-arg-two.cpp`](./chapter12/12.10-pointer-func-arg-two.cpp) 12.10 通过指针传递函数参数（第2部分）
- [ ] [`12.11-ret-ref-pointer.cpp`](./chapter12/12.11-ret-ref-pointer.cpp) 12.11 引用或指针作为函数返回值
- [ ] [`12.12-io-args.cpp`](./chapter12/12.12-io-args.cpp) 12.12 输入和输出参数
- [ ] [`12.13-auto-type-deduct-ptr-ref-const.cpp`](./chapter12/12.13-auto-type-deduct-ptr-ref-const.cpp) 12.13 指针、引用和常量的类型自动推导
- [ ] [`12.14-summary.cpp`](./chapter12/12.14-summary.cpp) 12.14 第12章总结

### 第十三章 复合类型：枚举与结构体

- [ ] [`13.00-user_define_type.cpp`](./chapter13/13.00-user_define_type.cpp) 13.0 用户自定义类型简介
- [ ] [`13.01-unscoped-enum.cpp`](./chapter13/13.01-unscoped-enum.cpp) 13.1 非限定作用域枚举
- [ ] [`13.02-unscoped-enum-io.cpp`](./chapter13/13.02-unscoped-enum-io.cpp) 13.2 非限定作用域枚举的输入与输出
- [ ] [`13.03-scoped-enum.cpp`](./chapter13/13.03-scoped-enum.cpp) 13.3 限定作用域枚举（枚举类）
- [ ] [`13.04-struct-intro.cpp`](./chapter13/13.04-struct-intro.cpp) 13.4 结构体简介
- [ ] [`13.05-struct-init.cpp`](./chapter13/13.05-struct-init.cpp) 13.5 结构体初始化
- [ ] [`13.06-struct-member-default-init.cpp`](./chapter13/13.06-struct-member-default-init.cpp) 13.6 成员变量的默认初始化
- [ ] [`13.07-struct-arg-ret.cpp`](./chapter13/13.07-struct-arg-ret.cpp) 13.7 结构体作为函数的输入与输出
- [ ] [`13.08-struct-other.cpp`](./chapter13/13.08-struct-other.cpp) 13.8 结构体杂项
- [ ] [`13.09-struct-member-select.cpp`](./chapter13/13.09-struct-member-select.cpp) 13.9 结构体指针和引用的成员选择操作
- [ ] [`13.10-class-template.cpp`](./chapter13/13.10-class-template.cpp) 13.10 类模板
- [ ] [`13.11-class-template-arg-deduct.cpp`](./chapter13/13.11-class-template-arg-deduct.cpp) 13.11 类模板参数推导（CTAD）
- [ ] [`13.12-template-alias.cpp`](./chapter13/13.12-template-alias.cpp) 13.12 模板别名
- [ ] [`13.13-summary.cpp`](./chapter13/13.13-summary.cpp) 13.13 第13章总结
- [ ] [`13.14-use-cpp-ref.cpp`](./chapter13/13.14-use-cpp-ref.cpp) 13.14 如何使用c++语言手册

### 第十四章 class介绍

- [ ] [`14.00-intro-oop.cpp`](./chapter14/14.00-intro-oop.cpp) 14.0 面向对象编程简介
- [ ] [`14.01-intro-class.cpp`](./chapter14/14.01-intro-class.cpp) 14.1 class简介
- [ ] [`14.02-member_func.cpp`](./chapter14/14.02-member_func.cpp) 14.2 成员函数
- [ ] [`14.03-const-obj.cpp`](./chapter14/14.03-const-obj.cpp) 14.3 Const类对象和Const成员函数
- [ ] [`14.04-public-private.cpp`](./chapter14/14.04-public-private.cpp) 14.4 公共和私有成员以及访问说明符
- [ ] [`14.05-access-func.cpp`](./chapter14/14.05-access-func.cpp) 14.5 访问函数
- [ ] [`14.06-member-func-ret-member-data-ref.cpp`](./chapter14/14.06-member-func-ret-member-data-ref.cpp) 14.6 成员函数返回对数据成员的引用
- [ ] [`14.07-data-hide.cpp`](./chapter14/14.07-data-hide.cpp) 14.7 数据隐藏（封装）的好处
- [ ] [`14.08-construct.cpp`](./chapter14/14.08-construct.cpp) 14.8 构造函数简介
- [ ] [`14.09-construct-member-init-list.cpp`](./chapter14/14.09-construct-member-init-list.cpp) 14.9 构造函数成员初始化列表
- [ ] [`14.10-default_construct.cpp`](./chapter14/14.10-default_construct.cpp) 14.10 默认构造函数和默认参数
- [ ] [`14.11-delegate_construct.cpp`](./chapter14/14.11-delegate_construct.cpp) 14.11 委托构造函数
- [ ] [`14.12-tmp_obj.cpp`](./chapter14/14.12-tmp_obj.cpp) 14.12 临时类对象
- [ ] [`14.13-copy-construct.cpp`](./chapter14/14.13-copy-construct.cpp) 14.13 拷贝构造函数简介
- [ ] [`14.14-class-init-copy-elision.cpp`](./chapter14/14.14-class-init-copy-elision.cpp) 14.14 类初始化和拷贝省略
- [ ] [`14.15-convert-construct-explict.cpp`](./chapter14/14.15-convert-construct-explict.cpp) 14.15 转换构造函数和explicit关键字
- [ ] [`14.16-summary.cpp`](./chapter14/14.16-summary.cpp) 14.16 第14章总结

### 第十五章 class第二部分

- [ ] [`15.00-hide-this.cpp`](./chapter15/15.00-hide-this.cpp) 15.0 隐藏的“this”指针和成员函数调用
- [ ] [`15.01-class-header-file.cpp`](./chapter15/15.01-class-header-file.cpp) 15.1 类和头文件
- [ ] [`15.02-nest-type.cpp`](./chapter15/15.02-nest-type.cpp) 15.2 嵌套类型（成员类型）
- [ ] [`15.03-destruct-intro.cpp`](./chapter15/15.03-destruct-intro.cpp) 15.3 析构函数简介
- [ ] [`15.04-class-tmplate-with-member-func.cpp`](./chapter15/15.04-class-tmplate-with-member-func.cpp) 15.4 具有成员函数的类模板
- [ ] [`15.05-static-member-var.cpp`](./chapter15/15.05-static-member-var.cpp) 15.5 静态成员变量
- [ ] [`15.06-static-member-func.cpp`](./chapter15/15.06-static-member-func.cpp) 15.6 静态成员函数
- [ ] [`15.07-friend-no-member-func.cpp`](./chapter15/15.07-friend-no-member-func.cpp) 15.7 友元非成员函数
- [ ] [`15.08-friend-class.cpp`](./chapter15/15.08-friend-class.cpp) 15.8 友元类和友元成员函数
- [ ] [`15.09-ref-qulify.cpp`](./chapter15/15.09-ref-qulify.cpp) 15.9 引用限定符
- [ ] [`15.10-summary.cpp`](./chapter15/15.10-summary.cpp) 15.10 第15章总结

### 第十六章 动态数组：std::vector

- [ ] [`16.00-intro-container-array.cpp`](./chapter16/16.00-intro-container-array.cpp) 16.0 容器和数组简介
- [ ] [`16.01-intro-vector-list-init.cpp`](./chapter16/16.01-intro-vector-list-init.cpp) 16.1 std::vector和列表构造函数简介
- [ ] [`16.02-vec-len.cpp`](./chapter16/16.02-vec-len.cpp) 16.2 vector与无符号长度和下标问题
- [ ] [`16.03-vec-pass.cpp`](./chapter16/16.03-vec-pass.cpp) 16.3 传递std::vector
- [ ] [`16.04-vec-ret-move.cpp`](./chapter16/16.04-vec-ret-move.cpp) 16.4 返回std::vector，移动语义简介
- [ ] [`16.05-vec-loop.cpp`](./chapter16/16.05-vec-loop.cpp) 16.5 数组和循环
- [ ] [`16.06-vec-loop-sign-index.cpp`](./chapter16/16.06-vec-loop-sign-index.cpp) 16.6 数组、循环和有符号下标
- [ ] [`16.07-range-for.cpp`](./chapter16/16.07-range-for.cpp) 16.7 基于范围的for循环（range for / for each）
- [ ] [`16.08-enum-as-index.cpp`](./chapter16/16.08-enum-as-index.cpp) 16.8 使用枚举值来作为数组索引
- [ ] [`16.09-vec-size-capacity.cpp`](./chapter16/16.09-vec-size-capacity.cpp) 16.9 std::vector大小调整和容量
- [ ] [`16.10-vec-stack.cpp`](./chapter16/16.10-vec-stack.cpp) 16.10 std::vector和栈行为
- [ ] [`16.11-vec-bool.cpp`](./chapter16/16.11-vec-bool.cpp) 16.11 std::vector<bool>
- [ ] [`16.12-summary.cpp`](./chapter16/16.12-summary.cpp) 16.12 第16章总结

### 第十七章 固定长度数组：std::array与c样式数组

- [ ] [`17.00-arr-intro.cpp`](./chapter17/17.00-arr-intro.cpp) 17.0 std::array简介
- [ ] [`17.01-arr-len-index.cpp`](./chapter17/17.01-arr-len-index.cpp) 17.1 std::array长度和索引
- [ ] [`17.02-arr-pass-ret.cpp`](./chapter17/17.02-arr-pass-ret.cpp) 17.2 std::array作为函数参数或返回值
- [ ] [`17.03-arr-of-class.cpp`](./chapter17/17.03-arr-of-class.cpp) 17.3 std::array与类类型元素
- [ ] [`17.04-arr-ref.cpp`](./chapter17/17.04-arr-ref.cpp) 17.4 通过std::reference_wrapper创建引用的数组
- [ ] [`17.05-arr-enum.cpp`](./chapter17/17.05-arr-enum.cpp) 17.5 std::array和枚举
- [ ] [`17.06-c-arr.cpp`](./chapter17/17.06-c-arr.cpp) 17.6 C样式数组简介
- [ ] [`17.07-c-arr-decay.cpp`](./chapter17/17.07-c-arr-decay.cpp) 17.7 C样式数组退化
- [ ] [`17.08-pointer-arithmetic.cpp`](./chapter17/17.08-pointer-arithmetic.cpp) 17.8 指针运算和下标
- [ ] [`17.09-c-str.cpp`](./chapter17/17.09-c-str.cpp) 17.9 C样式字符串
- [ ] [`17.10-c-const-str.cpp`](./chapter17/17.10-c-const-str.cpp) 17.10 常量C样式字符串
- [ ] [`17.11-c-multi-arr.cpp`](./chapter17/17.11-c-multi-arr.cpp) 17.11 多维C样式数组
- [ ] [`17.12-std-multi-arr.cpp`](./chapter17/17.12-std-multi-arr.cpp) 17.12 多维std::array
- [ ] [`17.13-summary.cpp`](./chapter17/17.13-summary.cpp) 17.13 第17章总结

### 第十八章 迭代器与算法

- [ ] [`18.00-sort-arr.cpp`](./chapter18/18.00-sort-arr.cpp) 18.0 对数组进行排序
- [ ] [`18.01-iter.cpp`](./chapter18/18.01-iter.cpp) 18.1 迭代器简介
- [ ] [`18.02-std-algorithm.cpp`](./chapter18/18.02-std-algorithm.cpp) 18.2 算法标准库简介
- [ ] [`18.03-time-code.cpp`](./chapter18/18.03-time-code.cpp) 18.3 为代码计时

### 第十九章 动态内存分配

- [ ] [`19.00-new-delete.cpp`](./chapter19/19.00-new-delete.cpp) 19.0 使用new和delete进行动态分配内存
- [ ] [`19.01-new-delete-arr.cpp`](./chapter19/19.01-new-delete-arr.cpp) 19.1 动态分配数组
- [ ] [`19.02-destructor.cpp`](./chapter19/19.02-destructor.cpp) 19.2 再谈析构函数
- [ ] [`19.03-ptr-to-ptr.cpp`](./chapter19/19.03-ptr-to-ptr.cpp) 19.3 指向指针和动态多维数组的指针
- [ ] [`19.04-void-ptr.cpp`](./chapter19/19.04-void-ptr.cpp) 19.4 void指针

### 第二十章 函数

- [ ] [`20.00-func-ptr.cpp`](./chapter20/20.00-func-ptr.cpp) 20.0 函数指针
- [ ] [`20.01-heap-stack.cpp`](./chapter20/20.01-heap-stack.cpp) 20.1 堆和栈
- [ ] [`20.02-recursion.cpp`](./chapter20/20.02-recursion.cpp) 20.2 递归
- [ ] [`20.03-cmd-args.cpp`](./chapter20/20.03-cmd-args.cpp) 20.3 命令行参数
- [ ] [`20.04-ellipsis.cpp`](./chapter20/20.04-ellipsis.cpp) 20.4 省略号与可变参数（以及为什么要避免它们）
- [ ] [`20.05-lambda.cpp`](./chapter20/20.05-lambda.cpp) 20.5 lambda（匿名函数）简介
- [ ] [`20.06-lambda-capture.cpp`](./chapter20/20.06-lambda-capture.cpp) 20.6 Lambda捕获
- [ ] [`20.07-summary.cpp`](./chapter20/20.07-summary.cpp) 20.7 第20章总结

### 第二十一章 操作符重载

- [ ] [`21.00-op-overload-intro.cpp`](./chapter21/21.00-op-overload-intro.cpp) 21.0 操作符重载简介
- [ ] [`21.01-friend-op-overload.cpp`](./chapter21/21.01-friend-op-overload.cpp) 21.1 使用友元函数重载算术运算符
- [ ] [`21.02-normal-op-overload.cpp`](./chapter21/21.02-normal-op-overload.cpp) 21.2 使用普通函数重载运算符
- [ ] [`21.03-overload-io.cpp`](./chapter21/21.03-overload-io.cpp) 21.3 重载I/O运算符
- [ ] [`21.04-member-op-overload.cpp`](./chapter21/21.04-member-op-overload.cpp) 21.4 使用成员函数重载运算符
- [ ] [`21.05-unary-op-overload.cpp`](./chapter21/21.05-unary-op-overload.cpp) 21.5 重载一元运算符+、-和！
- [ ] [`21.06-compare-op-overload.cpp`](./chapter21/21.06-compare-op-overload.cpp) 21.6 重载比较运算符
- [ ] [`21.07-incr-decre-overload.cpp`](./chapter21/21.07-incr-decre-overload.cpp) 21.7 重载递增和递减运算符
- [ ] [`21.08-subscript-overload.cpp`](./chapter21/21.08-subscript-overload.cpp) 21.8 重载下标运算符
- [ ] [`21.09-parenthesis-overload.cpp`](./chapter21/21.09-parenthesis-overload.cpp) 21.9 重载括号运算符
- [ ] [`21.10-type-cast-overload.cpp`](./chapter21/21.10-type-cast-overload.cpp) 21.10 重载类型转换
- [ ] [`21.11-assign-op-overload.cpp`](./chapter21/21.11-assign-op-overload.cpp) 21.11 重载赋值运算符
- [ ] [`21.12-shadow-deep-copy.cpp`](./chapter21/21.12-shadow-deep-copy.cpp) 21.12 浅拷贝与深拷贝
- [ ] [`21.13-op-overload-template.cpp`](./chapter21/21.13-op-overload-template.cpp) 21.13 重载运算符和函数模板
- [ ] [`21.14-summary.cpp`](./chapter21/21.14-summary.cpp) 21.14 第21章总结

### 第二十二章 移动语义与智能指针

- [ ] [`22.00-move-smart-pointer-intro.cpp`](./chapter22/22.00-move-smart-pointer-intro.cpp) 22.0 智能指针和移动语义简介
- [ ] [`22.01-r-value-ref.cpp`](./chapter22/22.01-r-value-ref.cpp) 22.1 右值引用
- [ ] [`22.02-move-construct-assign.cpp`](./chapter22/22.02-move-construct-assign.cpp) 22.2 移动构造函数和移动赋值函数
- [ ] [`22.03-std-move.cpp`](./chapter22/22.03-std-move.cpp) 22.3 std::move
- [ ] [`22.04-unique-ptr.cpp`](./chapter22/22.04-unique-ptr.cpp) 22.4 std::unique_ptr
- [ ] [`22.05-shared-ptr.cpp`](./chapter22/22.05-shared-ptr.cpp) 22.5 std::shared_ptr
- [ ] [`22.06-circle-ref.cpp`](./chapter22/22.06-circle-ref.cpp) 22.6 std::shared_ptr的循环依赖性问题和std::weak_ptr
- [ ] [`22.07-summary.cpp`](./chapter22/22.07-summary.cpp) 22.7 第22章总结

### 第二十三章 对象关系

- [ ] [`23.00-object-relation.cpp`](./chapter23/23.00-object-relation.cpp) 23.0 对象关系
- [ ] [`23.01-composition.cpp`](./chapter23/23.01-composition.cpp) 23.1 对象组合
- [ ] [`23.02-aggregation.cpp`](./chapter23/23.02-aggregation.cpp) 23.2 聚合
- [ ] [`23.03-association.cpp`](./chapter23/23.03-association.cpp) 23.3 关联
- [ ] [`23.04-dependencies.cpp`](./chapter23/23.04-dependencies.cpp) 23.4 依赖关系
- [ ] [`23.05-container-class.cpp`](./chapter23/23.05-container-class.cpp) 23.5 容器类
- [ ] [`23.06-initializer-list.cpp`](./chapter23/23.06-initializer-list.cpp) 23.6 std::initializer_list
- [ ] [`23.07-summary.cpp`](./chapter23/23.07-summary.cpp) 23.7 第23章总结

### 第二十四章 继承

- [ ] [`24.00-inherit-intro.cpp`](./chapter24/24.00-inherit-intro.cpp) 24.0 继承简介
- [ ] [`24.01-inherit-basic.cpp`](./chapter24/24.01-inherit-basic.cpp) 24.1 基本继承
- [ ] [`24.02-derived-class-cons-order.cpp`](./chapter24/24.02-derived-class-cons-order.cpp) 24.2 派生类的构造顺序
- [ ] [`24.03-derived-class-cons-init.cpp`](./chapter24/24.03-derived-class-cons-init.cpp) 24.3 派生类的构造函数与初始化
- [ ] [`24.04-inherit-access-spec.cpp`](./chapter24/24.04-inherit-access-spec.cpp) 24.4 继承和访问说明符
- [ ] [`24.05-add-new-func-to-derived-class.cpp`](./chapter24/24.05-add-new-func-to-derived-class.cpp) 24.5 向派生类添加新功能
- [ ] [`24.06-call-inherit-func-and-overload.cpp`](./chapter24/24.06-call-inherit-func-and-overload.cpp) 24.6 调用继承的函数与重写行为
- [ ] [`24.07-hide-inherit-func.cpp`](./chapter24/24.07-hide-inherit-func.cpp) 24.7 隐藏继承的功能
- [ ] [`24.08-multiple-inherit.cpp`](./chapter24/24.08-multiple-inherit.cpp) 24.8 多重继承
- [ ] [`24.09-summary.cpp`](./chapter24/24.09-summary.cpp) 24.9 第24章总结

### 第二十五章 虚函数

- [ ] [`25.00-base-pointer-ref-to-derived.cpp`](./chapter25/25.00-base-pointer-ref-to-derived.cpp) 25.0 指向派生对象的基类指针和引用
- [ ] [`25.01-virtual-func.cpp`](./chapter25/25.01-virtual-func.cpp) 25.1 虚函数和多态
- [ ] [`25.02-override-final.cpp`](./chapter25/25.02-override-final.cpp) 25.2 override和final说明符
- [ ] [`25.03-virtual-destructor-assign-override.cpp`](./chapter25/25.03-virtual-destructor-assign-override.cpp) 25.3 虚析构函数、虚赋值函数以及虚函数重写
- [ ] [`25.04-early-bind-late-bind.cpp`](./chapter25/25.04-early-bind-late-bind.cpp) 25.4 静态绑定和动态绑定
- [ ] [`25.05-virtual-table.cpp`](./chapter25/25.05-virtual-table.cpp) 25.5 虚函数表
- [ ] [`25.06-abstract-class.cpp`](./chapter25/25.06-abstract-class.cpp) 25.6 纯虚函数、抽象基类和接口类
- [ ] [`25.07-virtual-base-class.cpp`](./chapter25/25.07-virtual-base-class.cpp) 25.7 虚基类
- [ ] [`25.08-object-slice.cpp`](./chapter25/25.08-object-slice.cpp) 25.8 对象切片（Object slicing）
- [ ] [`25.09-dynamic-cast.cpp`](./chapter25/25.09-dynamic-cast.cpp) 25.9 dynamic_cast
- [ ] [`25.10-print-inherit-class.cpp`](./chapter25/25.10-print-inherit-class.cpp) 25.10 使用运算符<<打印继承的类
- [ ] [`25.11-summary.cpp`](./chapter25/25.11-summary.cpp) 25.11 第25章总结

### 第二十六章 模板

- [ ] [`26.00-template-class.cpp`](./chapter26/26.00-template-class.cpp) 26.0 模板类
- [ ] [`26.01-no-type-template-param.cpp`](./chapter26/26.01-no-type-template-param.cpp) 26.1 模板非类型参数
- [ ] [`26.02-func-template-specialization.cpp`](./chapter26/26.02-func-template-specialization.cpp) 26.2 函数模板特化
- [ ] [`26.03-class-template-specialization.cpp`](./chapter26/26.03-class-template-specialization.cpp) 26.3 类模板特化
- [ ] [`26.04-part-template-special.cpp`](./chapter26/26.04-part-template-special.cpp) 26.4 部分模板特化
- [ ] [`26.05-pointer-part-template-special.cpp`](./chapter26/26.05-pointer-part-template-special.cpp) 26.5 指针的部分模板特化
- [ ] [`26.06-summary.cpp`](./chapter26/26.06-summary.cpp) 26.6 第26章总结

### 第二十七章 异常

- [ ] [`27.00-exception-need.cpp`](./chapter27/27.00-exception-need.cpp) 27.0 为什么需要异常机制
- [ ] [`27.01-exception-basic.cpp`](./chapter27/27.01-exception-basic.cpp) 27.1 基本异常处理
- [ ] [`27.02-exception-func-stack-unwind.cpp`](./chapter27/27.02-exception-func-stack-unwind.cpp) 27.2 异常、函数和堆栈展开
- [ ] [`27.03-uncatch-catchall.cpp`](./chapter27/27.03-uncatch-catchall.cpp) 27.3 未捕获的异常和捕获所有异常
- [ ] [`27.04-exception-and-class.cpp`](./chapter27/27.04-exception-and-class.cpp) 27.4 异常、类和继承
- [ ] [`27.05-exception-rethrow.cpp`](./chapter27/27.05-exception-rethrow.cpp) 27.5 重新抛出异常
- [ ] [`27.06-function-try.cpp`](./chapter27/27.06-function-try.cpp) 27.6 函数try块
- [ ] [`27.07-exception-downside.cpp`](./chapter27/27.07-exception-downside.cpp) 27.7 异常的风险和缺点
- [ ] [`27.08-exception-spec-noexcept.cpp`](./chapter27/27.08-exception-spec-noexcept.cpp) 27.8 异常规格和noexcept
- [ ] [`27.09-move-if-noexcept.cpp`](./chapter27/27.09-move-if-noexcept.cpp) 27.9 std::move_if_noexcept
- [ ] [`27.10-summary.cpp`](./chapter27/27.10-summary.cpp) 27.10 第27章总结

### 第二十八章 输入输出（I/O）

- [ ] [`28.00-io-stream.cpp`](./chapter28/28.00-io-stream.cpp) 28.0 输入和输出（I/O）流
- [ ] [`28.01-istream.cpp`](./chapter28/28.01-istream.cpp) 28.1 使用istream处理输入
- [ ] [`28.02-ostream.cpp`](./chapter28/28.02-ostream.cpp) 28.2 使用ostream和ios输出
- [ ] [`28.03-stream-for-string.cpp`](./chapter28/28.03-stream-for-string.cpp) 28.3 针对字符串的stream类
- [ ] [`28.04-stream-state-validate-input.cpp`](./chapter28/28.04-stream-state-validate-input.cpp) 28.4 流的状态和输入验证
- [ ] [`28.05-basic-file-io.cpp`](./chapter28/28.05-basic-file-io.cpp) 28.5 基本文件I/O
- [ ] [`28.06-random-file-io.cpp`](./chapter28/28.06-random-file-io.cpp) 28.6 随机文件I/O

## 重新生成

```bash
python3 tools/studycpp_gen.py all     # 抓取 + 生成（页面缓存在 tools/.cache）
python3 tools/studycpp_gen.py fetch    # 只抓取
python3 tools/studycpp_gen.py gen      # 只生成
```

> 内容版权归 [C++学习网](https://www.studycpp.cn/) 所有，本目录仅用于个人学习。
