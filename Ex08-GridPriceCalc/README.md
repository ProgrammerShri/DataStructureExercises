# 题目8 电网建设造价模拟系统

- [编译说明](#%E7%BC%96%E8%AF%91%E8%AF%B4%E6%98%8E)
- [程序说明](#%E7%A8%8B%E5%BA%8F%E8%AF%B4%E6%98%8E)
  - [类 `GridPriceCalc`](#%E7%B1%BB-gridpricecalc)
    - [成员函数](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0)
    - [成员对象](#%E6%88%90%E5%91%98%E5%AF%B9%E8%B1%A1)
- [系统设计及实现](#%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1%E5%8F%8A%E5%AE%9E%E7%8E%B0)
    - [成员函数 `void run()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-run)
  - [创建电网顶点功能](#%E5%88%9B%E5%BB%BA%E7%94%B5%E7%BD%91%E9%A1%B6%E7%82%B9%E5%8A%9F%E8%83%BD)
    - [成员函数 `void createNode()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-createnode)
  - [添加电网的边功能](#%E6%B7%BB%E5%8A%A0%E7%94%B5%E7%BD%91%E7%9A%84%E8%BE%B9%E5%8A%9F%E8%83%BD)
    - [成员函数 `void setLink()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-setlink)
  - [构造最小生成树功能](#%E6%9E%84%E9%80%A0%E6%9C%80%E5%B0%8F%E7%94%9F%E6%88%90%E6%A0%91%E5%8A%9F%E8%83%BD)
    - [成员函数 `void build()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-build)
  - [显示最小生成树功能](#%E6%98%BE%E7%A4%BA%E6%9C%80%E5%B0%8F%E7%94%9F%E6%88%90%E6%A0%91%E5%8A%9F%E8%83%BD)
    - [成员函数 `void print()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-print)
- [运行示例](#%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B)

## 编译说明

本程序在 `Ubuntu 18.10` 下使用 `g++ (Ubuntu 8.2.0-7ubuntu1) 8.2.0` 编译通过

编译命令为 `g++ -O2 GridPriceCalc.cpp`, 生成可执行文件名为 `a.out`

目录下附有 `Makefile`, 执行 `make` 命令即可构建. 目标可执行文件名可通过其中的 `outfile` 变量进行设置.


## 程序说明

程序由 `GridPriceCalc.cpp` 和 `GridPriceCalc.hpp` 组成. 前者仅定义了程序的入口点, 后者定义了程序中所用到的类和具体实现.

### 类 `GridPriceCalc`

该类为程序的主要实现

#### 成员函数

| 成员                | 公有/私有 | 定义                                   |
| ------------------- | --------- | -------------------------------------- |
| `void run()`        | 公有      | 运行程序的入口, 唯一可被外部调用的方法 |
| `void createNode()` | 私有      | 创建电网的节点                         |
| `void setLink()`    | 私有      | 设置电网的路径信息                     |
| `void build()`      | 私有      | 构造最小生成树                         |
| `void print()`      | 私有      | 列出最小生成树的顶点及边               |

#### 成员对象

| 成员                          | 公有/私有 | 定义                 | 默认值 |
| ----------------------------- | --------- | -------------------- | ------ |
| `vector<string> node`         | 私有      | 存放节点名称         | `N/A`  |
| `vector<vector<int>> map`     | 私有      | 存放节点间距离       | `N/A`  |
| `vector<pair<int, int>> tree` | 私有      | 存放最小生成树的路径 | `N/A`  |


## 系统设计及实现

该程序先创建一个隶属于`GridPriceCalc`类的对象, 调用成员函数`run()`执行程序.

#### 成员函数 `void run()`

```cpp
void GridPriceCalc::run()
{
    cout << "**            电网造价模拟系统            **" << endl
         << "============================================" << endl
         << "**           A --- 创建电网顶点           **" << endl
         << "**           B --- 添加电网的边           **" << endl
         << "**           C --- 构造最小生成树         **" << endl
         << "**           D --- 显示最小生成树         **" << endl
         << "**           E --- 退出程序               **" << endl
         << "============================================" << endl
         << endl;
    while (true) {
        char op;
        cout << "请选择操作: ";
        cin >> op;
        if (!cin.good()) {
            cin.clear();
            op = -1;  // get a warning
        }
        cin.ignore(INT32_MAX, '\n');
        switch (op) {
            case 'A':
            case 'a':
                createNode();
                break;
            case 'B':
            case 'b':
                setLink();
                break;
            case 'C':
            case 'c':
                build();
                break;
            case 'D':
            case 'd':
                print();
                break;
            case 'E':
            case 'e':
                std::cout << "正在退出..." << std::endl;
                return;
            default:
                cerr << "[警告] 输入有误，请重新输入" << endl;
                continue;
        }
    }
}
```

该成员函数先列出菜单, 并获取用户输入, 根据用户输入执行相应功能.

### 创建电网顶点功能

#### 成员函数 `void createNode()`

```cpp
void GridPriceCalc::createNode()
{
    try {
        if (!tree.empty()) {
            throw logic_error("已生成最小生成树");
        }
        if (!map.empty()) {
            throw logic_error("已添加路径，无法调整节点");
        }

        int count;
        string name;
        cout << "请输入顶点的个数: ";
        cin >> count;
        cout << "请依次输入各顶点的名称:" << endl;
        for (int i = 0; i < count; i++) {
            cin >> name;
            node.push_back(name);
        }
    }
    catch (const logic_error& e) {
        cout << "[错误] " << e.what() << endl;
    }
    cout << endl;
}
```

该成员函数先检查是否已经生成过最小生成树或已经添加过路径, 若为是则抛出异常, 中止执行. 否则提示用户输入顶点个数和顶点名称, 将顶点名称存入 `vector<string> node` 中.

### 添加电网的边功能

#### 成员函数 `void setLink()`

```cpp
void GridPriceCalc::setLink()
{
    try {
        if (!tree.empty()) {
            throw logic_error("已生成最小生成树");
        }
        if (node.empty()) {
            throw logic_error("无节点信息. 尝试选择A选项");
        }
        if (node.size() < 2) {
            throw logic_error("节点数量过少");
        }

        map.resize(node.size());
        for (int i = 0; i < node.size(); i++) {
            map.at(i).resize(node.size());
        }

        for (int i = 0; i < node.size() - 1; i++) {
            map[i][i] = 0;
            for (int j = i + 1; j < node.size(); j++) {
                cout << "请输入节点\"" << node[i] << "\"与节点\"" << node[j] << "\"间的距离,不存在连接请输入-1: ";
                cin >> map[i][j];
                if (!cin.good()) {
                    cin.clear();
                }
                cin.ignore(INT32_MAX, '\n');
                if (map[i][j] == -1) {
                    map[i][j] = INT32_MAX;
                }
            }
        }

        for (int i = 0; i < node.size(); i++) {
            for (int j = 0; j < i; j++) {
                map[i][j] = map[j][i];
            }
        }
    }
    catch (const logic_error& e) {
        cout << "[错误] " << e.what() << endl;
    }
    cout << endl;
}
```

该成员函数先检查是否已经生成过最小生成树, 若为是则抛出异常, 中止执行. 否则提示用户依次输入各个顶点间的距离, 将距离保存至 `vector<vector<int>> map` 中.

### 构造最小生成树功能

#### 成员函数 `void build()`

```cpp
void GridPriceCalc::build()
{
    try {
        if (node.empty()) {
            throw logic_error("无节点信息. 尝试选择A选项");
        }
        if (map.empty()) {
            throw logic_error("无节点间的路径信息. 尝试选择B选项");
        }

        tree.clear();
        vector<pair<int, string>> linkedNode;  // Here stores the nodes linked
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pqueue;
        string start;
        cout << "请输入起始顶点：";
        cin >> start;
        for (int i = 0; i < node.size(); i++) {
            if (start == node[i]) {
                linkedNode.push_back(make_pair(i, node[i]));
                break;
            }
        }
        while (linkedNode.size() < node.size()) {
            // add every node can be linked to tree
            for (int i = 0; i < linkedNode.size(); i++) {
                for (int j = 0; j < node.size(); j++) {
                    if (j != linkedNode[i].first) {
                        pqueue.push(make_tuple(map[linkedNode[i].first][j], linkedNode[i].first, j));
                    }
                }
            }
            // add the link with minimum cost to tree
            for (int i = 0; i < node.size(); i++) {
                if (get<2>(pqueue.top()) == i) {
                    linkedNode.push_back(make_pair(i, node[i]));
                    tree.push_back(make_pair(get<1>(pqueue.top()), get<2>(pqueue.top())));
                }
            }
            // clear the priority queue
            while (!pqueue.empty()) {
                pqueue.pop();
            }
        }
        cout << "生成Prim最小生成树！" << endl;
    }
    catch (const logic_error& e) {
        cout << "[错误] " << e.what() << endl;
    }
    cout << endl;
}
```

该成员函数先检查是否存在节点及路径信息, 若无则抛出异常, 中止执行. 否则提示用户输入起始节点, 采用Prim算法构造最小生成树, 并保存至 `vector<pair<int, int>> tree` 中.

### 显示最小生成树功能

#### 成员函数 `void print()`

```cpp
void GridPriceCalc::print()
{
    try {
        if(tree.empty()){
            throw logic_error("未构造最小生成树. 尝试选择C选项");
        }
        cout << "最小生成树的顶点及边为:" << endl;
        string name1, name2;
        for (int i = 0; i < tree.size(); i++) {
            for (int j = 0; j < node.size(); j++) {
                if (tree[i].first == j) {
                    name1 = node[j];
                }
                if (tree[i].second == j) {
                    name2 = node[j];
                }
            }
            cout << name1 << "-<" << map[tree[i].first][tree[i].second] << ">->" << name2 << "\t";
        }
        cout << endl;
    }
    catch (const logic_error& e) {
        cout << "[错误] " << e.what() << endl;
    }
    cout << endl;
}
```

该成员函数先检查是否已构造最小生成树, 若未构造则抛出异常, 中止执行. 否则依据题目要求所给格式输出最小生成树的顶点及边.

## 运行示例

Note: 中文字符部分平台下存在无法对齐的情况, 该问题无解

```
$ ./a.out
**            电网造价模拟系统            **
============================================
**           A --- 创建电网顶点           **
**           B --- 添加电网的边           **
**           C --- 构造最小生成树         **
**           D --- 显示最小生成树         **
**           E --- 退出程序               **
============================================

请选择操作: A
请输入顶点的个数: 4
请依次输入各顶点的名称:
a b c d

请选择操作: B
请输入节点"a"与节点"b"间的距离,不存在连接请输入-1: 8
请输入节点"a"与节点"c"间的距离,不存在连接请输入-1: 18
请输入节点"a"与节点"d"间的距离,不存在连接请输入-1: 11
请输入节点"b"与节点"c"间的距离,不存在连接请输入-1: 7
请输入节点"b"与节点"d"间的距离,不存在连接请输入-1: 12
请输入节点"c"与节点"d"间的距离,不存在连接请输入-1: 5

请选择操作: C
请输入起始顶点：a
生成Prim最小生成树！

请选择操作: D
最小生成树的顶点及边为:
a-<8>->b        b-<7>->c        c-<5>->d

请选择操作: E
正在退出...
```