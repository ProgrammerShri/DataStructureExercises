# 题目4 表达式转换

- [编译说明](#%E7%BC%96%E8%AF%91%E8%AF%B4%E6%98%8E)
- [算法说明](#%E7%AE%97%E6%B3%95%E8%AF%B4%E6%98%8E)
  - [函数 `bool isOperator(string ele)`](#%E5%87%BD%E6%95%B0-bool-isoperatorstring-ele)
  - [函数 `bool isOperand(string ele)`](#%E5%87%BD%E6%95%B0-bool-isoperandstring-ele)
  - [函数 `bool isOpenParen(string ele)`](#%E5%87%BD%E6%95%B0-bool-isopenparenstring-ele)
  - [函数 `bool isCloseParen(string ele)`](#%E5%87%BD%E6%95%B0-bool-iscloseparenstring-ele)
  - [函数 `int getPriority(string op)`](#%E5%87%BD%E6%95%B0-int-getprioritystring-op)
  - [函数 `bool hasPriority(string op1, string op2)`](#%E5%87%BD%E6%95%B0-bool-hasprioritystring-op1-string-op2)
  - [函数 `vector<string> toPostfix(vector<string> expr)`](#%E5%87%BD%E6%95%B0-vectorstring-topostfixvectorstring-expr)
- [输入格式](#%E8%BE%93%E5%85%A5%E6%A0%BC%E5%BC%8F)
- [输出格式](#%E8%BE%93%E5%87%BA%E6%A0%BC%E5%BC%8F)
- [运行示例](#%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B)
    - [正常测试6种运算符](#%E6%AD%A3%E5%B8%B8%E6%B5%8B%E8%AF%956%E7%A7%8D%E8%BF%90%E7%AE%97%E7%AC%A6)
    - [嵌套括号](#%E5%B5%8C%E5%A5%97%E6%8B%AC%E5%8F%B7)
    - [运算数超过1位整数且有非整数出现](#%E8%BF%90%E7%AE%97%E6%95%B0%E8%B6%85%E8%BF%871%E4%BD%8D%E6%95%B4%E6%95%B0%E4%B8%94%E6%9C%89%E9%9D%9E%E6%95%B4%E6%95%B0%E5%87%BA%E7%8E%B0)
    - [运算数有正或负号](#%E8%BF%90%E7%AE%97%E6%95%B0%E6%9C%89%E6%AD%A3%E6%88%96%E8%B4%9F%E5%8F%B7)
    - [只有1个数字](#%E5%8F%AA%E6%9C%891%E4%B8%AA%E6%95%B0%E5%AD%97)

## 编译说明

本程序在 `Ubuntu 18.10` 下使用 `g++ (Ubuntu 8.2.0-7ubuntu1) 8.2.0` 编译通过

编译命令为 `g++ -O2 ExpressionConversion.cpp`, 生成可执行文件名为 `a.out`

目录下附有 `Makefile`, 执行 `make` 命令即可构建. 执行 `make test` 可对所有测试用例进行自动测试. 目标可执行文件名可通过其中的 `outfile` 变量进行设置.


## 算法说明

### 函数 `bool isOperator(string ele)`

```cpp
bool isOperator(string ele)
{
    if (ele.size() != 1) {
        return false;
    }
    return (ele == "+" || ele == "-" || ele == "*" || ele == "/");
}
```

判断字符串 `ele` 是否为运算符.

### 函数 `bool isOperand(string ele)`

```cpp
bool isOperand(string ele)
{
    return (!isOperator(ele) && !isOpenParen(ele) && !isCloseParen(ele));
}
```

判断字符串 `ele` 是否为运算数.

### 函数 `bool isOpenParen(string ele)`

```cpp
bool isOpenParen(string ele)
{
    if (ele.size() != 1) {
        return false;
    }
    return (ele == "(");
}
```

判断字符串 `ele` 是否为左括号 `(`.

### 函数 `bool isCloseParen(string ele)`

```cpp
bool isCloseParen(string ele)
{
    if (ele.size() != 1) {
        return false;
    }
    return (ele == ")");
}
```

判断字符串 `ele` 是否为右括号 `)`.

### 函数 `int getPriority(string op)`

```cpp
int getPriority(string op)
{
    switch (op[0]) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
```

返回运算符 `op` 的优先级.

### 函数 `bool hasPriority(string op1, string op2)`

```cpp
bool hasPriority(string op1, string op2)
{
    return (getPriority(op1) >= getPriority(op2));
}
```

判断运算符 `op1` 的优先级是否高于或等于运算符 `op2`.

### 函数 `vector<string> toPostfix(vector<string> expr)`

```cpp
vector<string> toPostfix(vector<string> expr)
{
    Stack<string> ele_stack;
    vector<string> postfix_expr;
    for (size_t i = 0; i < expr.size(); i++) {
        // if element is an operand, just append it
        if (isOperand(expr[i])) {
            postfix_expr.push_back(expr[i]);
        }
        // If element is operator, compare priority with stack top until the first opening bracket, and pop them
        // then push the current operator
        else if (isOperator(expr[i])) {
            while (!ele_stack.empty() && !isOpenParen(ele_stack.top()) && hasPriority(ele_stack.top(), expr[i])) {
                postfix_expr.push_back(ele_stack.top());
                ele_stack.pop();
            }
            ele_stack.push(expr[i]);
        }
        // if opening bracket, push it
        else if (isOpenParen(expr[i])) {
            ele_stack.push(expr[i]);
        }
        // if closing bracket, pop all operators unitl "(", and pop the "("
        else if (isCloseParen(expr[i])) {
            while (!ele_stack.empty() && !isOpenParen(ele_stack.top())) {
                postfix_expr.push_back(ele_stack.top());
                ele_stack.pop();
            }
            ele_stack.pop();
        }
    }
    // finally pop all elements in stack
    while (!ele_stack.empty()) {
        postfix_expr.push_back(ele_stack.top());
        ele_stack.pop();
    }

    return postfix_expr;
}
```

表达式转换函数. 输入原中缀表达式 `vector<string> expr`, 建立操作符栈 `ele_stack`.

从左到右读取表达式中的元素 `expr[i]`.

* 若 `expr[i]` 为运算数, 放入后缀表达式 `postfix_expr` 的末尾.
* 若 `expr[i]` 为运算符, 比较其与栈顶元素的优先级, 如果栈顶元素优先级高则将栈顶元素出栈放入后缀表达式中, 直至遇到第一个左括号. 最后将 `expr[i]` 入栈
* 若 `expr[i]` 为左括号, 将其入栈.
* 若 `expr[i]` 为右括号, 将栈顶元素出栈放入后缀表达式中, 直至第一个左括号, 并将该左括号丢弃.

最后将栈中所有元素出栈, 并返回后缀表达式.


## 输入格式

从 `stdin` 读取题目给定格式的输入内容. 输入在一行中给出以空格分隔不同对象的中缀表达式, 可包含 `+`, `-`, `*`, `/`, `-`, `*`, `/` 以及左右括号. 输入以 `EOF` 结尾

该程序不校验输入是否合法, 输入数据需确保是合法的中缀表达式.


## 输出格式

向 `stdout` 输出题目给定格式的内容. 在一行中输出转换后的后缀表达式, 不同对象 (运算数, 运算符号) 之间以空格分隔, 结尾无多余空格.


## 运行示例

Note: 原测试数据中存中文括号 `（）` 与英文括号 `()` 混用, 中文横线 `–` 与减号 `-` 混用的情况, 此处已作修正.

#### 正常测试6种运算符

输入

```
2 + 3 * ( 7 - 4 ) + 8 / 4
```

输出

```
2 3 7 4 - * + 8 4 / +
```

#### 嵌套括号

输入

```
( ( 2 + 3 ) * 4 - ( 8 + 2 ) ) / 5
```

输出

```
2 3 + 4 * 8 2 + - 5 /
```

#### 运算数超过1位整数且有非整数出现

输入

```
1314 + 25.5 * 12
```

输出

```
1314 25.5 12 * +
```

#### 运算数有正或负号

输入

```
-2 * ( +3 )
```

输出

```
-2 +3 *
```

#### 只有1个数字

输入

```
123
```

输出

```
123
```