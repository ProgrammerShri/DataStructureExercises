# 题目6 家谱管理系统

- [编译说明](#%E7%BC%96%E8%AF%91%E8%AF%B4%E6%98%8E)
- [程序说明](#%E7%A8%8B%E5%BA%8F%E8%AF%B4%E6%98%8E)
  - [结构体 `Member`](#%E7%BB%93%E6%9E%84%E4%BD%93-member)
  - [类 `GenealogyBook`](#%E7%B1%BB-genealogybook)
    - [成员对象](#%E6%88%90%E5%91%98%E5%AF%B9%E8%B1%A1)
    - [成员函数](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0)
- [系统设计及实现](#%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1%E5%8F%8A%E5%AE%9E%E7%8E%B0)
    - [成员函数 `void run()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-run)
  - [完善家庭功能](#%E5%AE%8C%E5%96%84%E5%AE%B6%E5%BA%AD%E5%8A%9F%E8%83%BD)
    - [成员函数 `void createFamily()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-createfamily)
  - [添加家庭成员](#%E6%B7%BB%E5%8A%A0%E5%AE%B6%E5%BA%AD%E6%88%90%E5%91%98)
    - [成员函数 `void addChild()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-addchild)
  - [解散局部成员](#%E8%A7%A3%E6%95%A3%E5%B1%80%E9%83%A8%E6%88%90%E5%91%98)
    - [成员函数 `void removeFamily()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-removefamily)
  - [更改家庭成员姓名](#%E6%9B%B4%E6%94%B9%E5%AE%B6%E5%BA%AD%E6%88%90%E5%91%98%E5%A7%93%E5%90%8D)
    - [成员函数 `void editName()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-editname)
  - [一些其他的辅助功能](#%E4%B8%80%E4%BA%9B%E5%85%B6%E4%BB%96%E7%9A%84%E8%BE%85%E5%8A%A9%E5%8A%9F%E8%83%BD)
    - [成员函数 `void init()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-init)
    - [成员函数 `Member* find(std::string name, Member* node)`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-member-findstdstring-name-member-node)
    - [成员函数 `void printChild(Member* node)`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-printchildmember-node)
    - [成员函数 `void freeNode(Member* node)`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-freenodemember-node)
- [运行示例](#%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B)

## 编译说明

本程序在 `Ubuntu 18.10` 下使用 `g++ (Ubuntu 8.2.0-7ubuntu1) 8.2.0` 编译通过

编译命令为 `g++ -O2 GenealogyBook.cpp`, 生成可执行文件名为 `a.out`

目录下附有 `Makefile`, 执行 `make` 命令即可构建. 目标可执行文件名可通过其中的 `outfile` 变量进行设置.


## 程序说明

程序由 `GenealogyBook.cpp` 和 `GenealogyBook.hpp` 组成. 前者仅定义了程序的入口点, 后者定义了程序中所用到的类和具体实现.

### 结构体 `Member`

该结构体表示家谱树中的某一成员节点.

| 成员                  | 定义                   | 默认值    |
| --------------------- | ---------------------- | --------- |
| `std::string _name`   | 家庭成员的姓名         | `N/A`     |
| `Member* parent`      | 指向父节点的指针       | `nullptr` |
| `Member* child`       | 指向子节点的指针       | `nullptr` |
| `Member* siblingPrev` | 指向上一兄弟节点的指针 | `nullptr` |
| `Member* siblingNext` | 指向下一兄弟节点的指针 | `nullptr` |

### 类 `GenealogyBook`

该类为程序的主要实现.

#### 成员对象

| 成员               | 公有/私有 | 定义           | 默认值    |
| ------------------ | --------- | -------------- | --------- |
| `Member* ancestor` | 私有      | 指向家谱的祖先 | `nullptr` |

#### 成员函数

| 成员                                           | 公有/私有 | 定义                                   |
| ---------------------------------------------- | --------- | -------------------------------------- |
| `void run()`                                   | 公有      | 运行程序的入口, 唯一可被外部调用的方法 |
| `void init()`                                  | 私有      | 初始化家谱, 创建祖先节点               |
| `void createFamily()`                          | 私有      | 创建新的家庭成员                       |
| `void addChild()`                              | 私有      | 向已有的家庭成员添加子女信息           |
| `void removeFamily()`                          | 私有      | 删除某一家庭成员                       |
| `void editName()`                              | 私有      | 修改某一家庭成员的姓名                 |
| `Member* find(std::string name, Member* node)` | 私有      | 在家谱树中查找名为 `name` 的成员       |
| `void printChild(Member* node)`                | 私有      | 列出某一成员的第一代子女               |
| `void freeNode(Member* node)`                  | 私有      | 释放某一节点的内存空间                 |

## 系统设计及实现

该程序先创建一个隶属于`GenealogyBook`类的对象, 调用成员函数`run()`执行程序.

#### 成员函数 `void run()`

```cpp
void GenealogyBook::run()
{
    cout << "**              家谱管理系统              **" << endl
         << "============================================" << endl
         << "**          请选择要执行的操作:           **" << endl
         << "**          A --- 完善家庭                **" << endl
         << "**          B --- 添加家庭成员            **" << endl
         << "**          C --- 解散局部成员            **" << endl
         << "**          D --- 更改家庭成员姓名        **" << endl
         << "**          E --- 退出系统                **" << endl
         << "============================================" << endl;

    init();

    while (true) {
        char op;
        cout << "请选择要执行的操作: ";
        cin >> op;
        if (!cin.good()) {
            cin.clear();
            op = -1;  // get a warning
        }
        cin.ignore(INT32_MAX, '\n');
        switch (op) {
            case 'A':
            case 'a':
                createFamily();
                break;
            case 'B':
            case 'b':
                addChild();
                break;
            case 'C':
            case 'c':
                removeFamily();
                break;
            case 'D':
            case 'd':
                editName();
                break;
            case 'E':
            case 'e':
                cout << "正在退出..." << endl;
                return;
            default:
                cout << "[错误] 输入有误，请重新输入" << endl
                     << endl;
                continue;
        }
    }
}
```

该成员函数先列出菜单, 然后调用成员函数`init()`对家谱进行初始化, 即添加根节点. 此后获取用户输入, 根据用户输入执行相应功能.

### 完善家庭功能

#### 成员函数 `void createFamily()`

```cpp
void GenealogyBook::createFamily()
{
    try {
        string name;
        cout << "请输入要建立家庭的人的姓名: ";
        cin >> name;
        Member* node = find(name, ancestor);
        if (node == nullptr) {
            throw invalid_argument("找不到" + name);
        }
        if (node->child != nullptr) {
            throw invalid_argument(name + "已建立过家庭");
        }

        int childNum;
        cout << "请输入" << node->_name << "的子女人数: ";
        cin >> childNum;
        if (!cin.good()) {
            cin.clear();
            throw invalid_argument("输入不合法");
        }
        if (childNum == 0) {
            return;
        }
        cout << "请依次输入" << node->_name << "的子女的姓名: ";
        node->child = new Member();
        Member* temp = node->child;
        cin >> temp->_name;
        temp->parent = node;
        for (int i = 1; i < childNum; i++) {
            Member* sibling = new Member();
            cin >> sibling->_name;
            sibling->parent = node;
            sibling->siblingPrev = temp;
            temp->siblingNext = sibling;
            temp = temp->siblingNext;
        }

        printChild(node);
    }
    catch (const invalid_argument& e) {
        cout << "[错误] " << e.what() << ", 请检查输入" << endl;
    }
    cout << endl;
}
```

该成员函数先提示用户输入所要建立家庭的人的姓名字符串 `name`, 调用成员函数 `find()` 查找根节点下名为 `name` 的节点. 若未找到则抛出异常, 中止执行. 若找到则校验该节点是否有子节点, 若有也抛出异常, 中止执行. 此后提示用户输入 `name` 的子女人数 `childNum`. 若输入的 `childName` 有误则抛出异常, 为 `0` 则执行完成返回, 非 `0` 则提示用户输入子女姓名, 将输入的第1个子女姓名的节点作为 `name` 的 `child` 指针所指向的节点, 并处理兄弟节点的关系. 最后列出 `name` 的第一代子女.

### 添加家庭成员

#### 成员函数 `void addChild()`

```cpp
void GenealogyBook::addChild()
{
    try {
        string name;
        cout << "请输入要添加子女的人的姓名: ";
        cin >> name;
        Member* node = find(name, ancestor);
        if (node == nullptr) {
            throw invalid_argument("找不到" + name);
        }

        cout << "请输入" << node->_name << "新添加的子女的姓名: ";
        Member* newChild = new Member();
        cin >> newChild->_name;
        newChild->parent = node;
        if (node->child == nullptr) {
            node->child = newChild;
        }
        else {
            Member* temp = node->child;
            while (temp != nullptr) {
                temp = temp->siblingNext;
            }
            newChild->siblingPrev = temp;
            temp->siblingNext = newChild;
        }

        printChild(node);
    }
    catch (const invalid_argument& e) {
        cout << "[错误] " << e.what() << ", 请检查输入" << endl;
    }
    cout << endl;
}
```

该成员函数先提示用户输入所要添加子女的人的姓名字符串 `name`, 调用成员函数 `find()` 查找根节点下名为 `name` 的节点. 若未找到则抛出异常, 中止执行. 此后创建一个新节点 `newChild`, 并提示用户输入 `name` 的新添加的子女的姓名 `newChild->_name`. 若 `name` 无子节点, 将该节点作为 `name` 的 `child` 指针所指向的节点, 若有则处理子节点间的关系. 最后列出 `name` 的第一代子女.

### 解散局部成员

#### 成员函数 `void removeFamily()`

```cpp
void GenealogyBook::removeFamily()
{
    try {
        string name;
        cout << "请输入要解散家庭的人的姓名: ";
        cin >> name;
        Member* node = find(name, ancestor);
        if (node == nullptr) {
            throw invalid_argument("找不到" + name);
        }
        if (node == ancestor) {
            throw invalid_argument("根节点不允许被删除");
        }

        cout << "要解散家庭的人是: " << node->_name << endl;
        printChild(node);

        if (node->child != nullptr) {
            freeNode(node->child);
        }

        if (node->siblingPrev != nullptr && node->siblingNext != nullptr) {
            node->siblingPrev->siblingNext = node->siblingNext;
            node->siblingNext->siblingPrev = node->siblingPrev;
        }
        else if (node->siblingPrev != nullptr && node->siblingNext == nullptr) {
            node->siblingPrev->siblingNext = nullptr;
        }
        else if (node->siblingPrev == nullptr && node->siblingNext != nullptr) {
            node->siblingNext->siblingPrev = nullptr;
            node->parent->child = node->siblingNext;
        }
        else if (node->siblingPrev == nullptr && node->siblingNext == nullptr) {
            node->parent->child = nullptr;
        }
        delete node;
    }
    catch (const invalid_argument& e) {
        cout << "[错误] " << e.what() << ", 请检查输入" << endl;
    }
    cout << endl;
}
```

该成员函数先提示用户输入所要解散家庭的人的姓名字符串 `name`, 调用成员函数 `find()` 查找根节点下名为 `name` 的节点. 若未找到或 `name` 为根节点则抛出异常, 中止执行. 此后列出 `name` 的第一代子女, 释放 `name` 的子节点所占用的内存, 处理 `name` 的兄弟节点间的关系. 最后回收 `name` 节点.

### 更改家庭成员姓名

#### 成员函数 `void editName()`

```cpp
void GenealogyBook::editName()
{
    try {
        string name;
        cout << "请输入要更改姓名的人的目前姓名: ";
        cin >> name;
        Member* node = find(name, ancestor);
        if (node == nullptr) {
            throw invalid_argument("找不到" + name);
        }
        cout << "请输入更改后的姓名: ";
        cin >> node->_name;
        cout << name << "已更名为" << node->_name << endl;
    }
    catch (const invalid_argument& e) {
        cout << "[错误] " << e.what() << ", 请检查输入" << endl;
    }
    cout << endl;
}
```

该成员函数先提示用户输入所要更改姓名的人的目前姓名字符串 `name`, 调用成员函数 `find()` 查找根节点下名为 `name` 的节点. 若未找到则抛出异常, 中止执行. 此后提示用户输入 `name` 的新姓名, 并写入. 最后列出 `name` 的第一代子女.

### 一些其他的辅助功能

#### 成员函数 `void init()`

```cpp
void GenealogyBook::init()
{
    ancestor = new Member;
    cout << "首先建立一个家谱！" << endl
         << "请输入祖先的姓名: ";
    cin >> ancestor->_name;
    cout << "此家谱的祖先是: " << ancestor->_name << endl;
    cout << endl;
}
```

该成员函数交互式地创建家谱树的祖先节点.

#### 成员函数 `Member* find(std::string name, Member* node)`

```cpp
Member* GenealogyBook::find(string name, Member* node)
{
    if (node->_name == name) {
        return node;
    }
    Member* temp = node;
    Member* result = nullptr;
    while (temp->siblingNext != nullptr) {
        result = find(name, temp->siblingNext);
        if (result != nullptr) {
            return result;
        }
    }
    if (node->child != nullptr) {
        result = find(name, node->child);
    }
    return result;
}
```

该成员函数在查找家谱树中 `node` 节点下名为 `name` 的节点, 并返回一个指向该节点的的指针. 若查找无结果则返回 `nullptr`.

算法上, 采用递归实现树的广度优先遍历. 先查找 `node` 的兄弟节点, 再查找子节点.

#### 成员函数 `void printChild(Member* node)`

```cpp
void GenealogyBook::printChild(Member* node)
{
    if (node->child == nullptr) {
        cout << node->_name << "没有子女" << endl;
    }
    else {
        Member* temp = node->child;
        cout << node->_name << "的第一代子女是: ";
        while (temp != nullptr) {
            cout << temp->_name << " ";
            temp = temp->siblingNext;
        }
        cout << endl;
    }
}
```

该成员函数提供打印 `node` 的子节点及子节点的兄弟节点的姓名的功能, 用于每个操作后"xx的第一代子女是"的显示.

#### 成员函数 `void freeNode(Member* node)`

```cpp
void GenealogyBook::freeNode(Member* node)
{
    Member* temp = node;
    while (temp->siblingNext != nullptr) {
        temp = temp->siblingNext;
    }
    while (temp->siblingPrev != nullptr) {
        temp = temp->siblingPrev;
        temp->siblingNext->siblingPrev = nullptr;
        temp->siblingNext->siblingNext = nullptr;
        freeNode(temp->siblingNext);
    }
    if (temp->child) {
        freeNode(temp->child);
    }
    delete node;
}
```

该成员函数用于释放 `node` 及其兄弟节点, 以及这些节点下的所有子节点.

算法上, 采用递归实现树的广度优先遍历. 先回收 `node` 的兄弟节点, 再回收子节点.


## 运行示例

Note: 中文字符部分平台下存在无法对齐的情况, 该问题无解

```
$ ./a.out
**              家谱管理系统              **
============================================
**          请选择要执行的操作:           **
**          A --- 完善家庭                **
**          B --- 添加家庭成员            **
**          C --- 解散局部成员            **
**          D --- 更改家庭成员姓名        **
**          E --- 退出系统                **
============================================
首先建立一个家谱！
请输入祖先的姓名: P0
此家谱的祖先是: P0

请选择要执行的操作: A
请输入要建立家庭的人的姓名: P0
请输入P0的子女人数: 2
请依次输入P0的子女的姓名: P1 P2
P0的第一代子女是: P1 P2

请选择要执行的操作: A
请输入要建立家庭的人的姓名: P1
请输入P1的子女人数: 3
请依次输入P1的子女的姓名: P11 P12 P13
P1的第一代子女是: P11 P12 P13

请选择要执行的操作: B
请输入要添加子女的人的姓名: P2
请输入P2新添加的子女的姓名: P21
P2的第一代子女是: P21

请选择要执行的操作: C
请输入要解散家庭的人的姓名: P2
要解散家庭的人是: P2
P2的第一代子女是: P21

请选择要执行的操作: D
请输入要更改姓名的人的目前姓名: P13
请输入更改后的姓名: P14
P13已更名为P14

请选择要执行的操作: E
正在退出...
```