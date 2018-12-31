# 题目3 勇闯迷宫游戏

- [编译说明](#%E7%BC%96%E8%AF%91%E8%AF%B4%E6%98%8E)
- [程序说明](#%E7%A8%8B%E5%BA%8F%E8%AF%B4%E6%98%8E)
  - [类 `Point`](#%E7%B1%BB-point)
    - [成员函数](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0)
    - [成员对象](#%E6%88%90%E5%91%98%E5%AF%B9%E8%B1%A1)
- [算法说明](#%E7%AE%97%E6%B3%95%E8%AF%B4%E6%98%8E)
- [输入格式](#%E8%BE%93%E5%85%A5%E6%A0%BC%E5%BC%8F)
- [输出格式](#%E8%BE%93%E5%87%BA%E6%A0%BC%E5%BC%8F)
- [运行示例](#%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B)
    - [带边界的迷宫](#%E5%B8%A6%E8%BE%B9%E7%95%8C%E7%9A%84%E8%BF%B7%E5%AE%AB)
    - [横纵大小不相等的迷宫](#%E6%A8%AA%E7%BA%B5%E5%A4%A7%E5%B0%8F%E4%B8%8D%E7%9B%B8%E7%AD%89%E7%9A%84%E8%BF%B7%E5%AE%AB)
    - [没有路径的迷宫](#%E6%B2%A1%E6%9C%89%E8%B7%AF%E5%BE%84%E7%9A%84%E8%BF%B7%E5%AE%AB)
    - [无边界的迷宫](#%E6%97%A0%E8%BE%B9%E7%95%8C%E7%9A%84%E8%BF%B7%E5%AE%AB)

## 编译说明

本程序在 `Ubuntu 18.10` 下使用 `g++ (Ubuntu 8.2.0-7ubuntu1) 8.2.0` 编译通过

编译命令为 `g++ -O2 Maze.cpp`, 生成可执行文件名为 `a.out`

目录下附有 `Makefile`, 执行 `make` 命令即可构建. 执行 `make test` 可对所有测试用例进行自动测试. 目标可执行文件名可通过其中的 `outfile` 变量进行设置.


## 程序说明

### 类 `Point`

该类表示迷宫中的点

#### 成员函数

| 成员                  | 公有/私有 | 定义                       |
| --------------------- | --------- | -------------------------- |
| `Point()`             | 公有      | 缺省构造函数, 构造点(0, 0) |
| `Point(int x, int y)` | 公有      | 构造函数, 构造点(x, y)     |
| `int x() const`       | 公有      | 访问器, 返回横坐标         |
| `int y() const`       | 公有      | 访问器, 返回纵坐标         |

#### 成员对象

| 成员     | 公有/私有 | 定义       | 默认值 |
| -------- | --------- | ---------- | ------ |
| `int _x` | 私有      | 点的横坐标 | `N/A`  |
| `int _y` | 私有      | 点的纵坐标 | `N/A`  |


## 算法说明

```cpp
int start_x, start_y;
int end_x, end_y;
vector<vector<int>> maze(size_x, vector<int>(size_y, 0));
stack<Point> route;

route.push(Point(start_x, start_y));
maze[start_x][start_y] = 0;

Point current = Point(start_x, start_y);

while (true) {
    if (current.x() == end_x && current.y() == end_y) {
        break;
    }
    if (current.x() != (size_x - 1) && maze[current.x() + 1][current.y()]) {  // going down
        maze[current.x() + 1][current.y()] = 0;
        current = Point(current.x() + 1, current.y());
        route.push(current);
        continue;
    }
    if (current.x() != 0 && maze[current.x() - 1][current.y()]) {  // going up
        maze[current.x() - 1][current.y()] = 0;
        current = Point(current.x() - 1, current.y());
        route.push(current);
        continue;
    }
    if (current.y() != (size_y - 1) && maze[current.x()][current.y() + 1]) {  // going right
        maze[current.x()][current.y() + 1] = 0;
        current = Point(current.x(), current.y() + 1);
        route.push(current);
        continue;
    }
    if (current.y() != 0 && maze[current.x()][current.y() - 1]) {  // going left
        maze[current.x()][current.y() - 1] = 0;
        current = Point(current.x(), current.y() - 1);
        route.push(current);
        continue;
    }
    route.pop();
    if (route.empty()) {
        cout << "没有路径!" << endl;
        return -1;
    }
    current = route.top();
}
```

采用回溯法, 对于某一点所有可走的方向进行尝试, 将走过的点压入栈中, 若该点无路可走则回退至上一点, 将该点弹出栈, 并标记该点为不可通过. 直至走到终点, 输出路径. 或是直至栈为空, 输出没有路径.


## 输入格式

从 `stdin` 获取输入, 第1行为2个正整数, 表示迷宫的长和宽. 第2行开始为迷宫, 其中 `0` 代表不可通过的点, `1` 代表可以通过的点. 迷宫后1行为2个正整数, 表示迷宫的起点. 迷宫后2行为2个正整数, 表示迷宫终点.

该程序不校验输入是否合法, 输入数据需确保在 `int32_t` 的范围内, 且为正整数.

为了方便测试, 测试数据已经置于同目录下名为 `test_*` 的文件中, 可使用输入重定向 `<` 从文件获取输入


## 输出格式

向 `stdout` 输出题目给定格式的内容. 先输出带路径的迷宫地图, 其中 `#` 代表不可通过的点, `0` 代表可以通过的点, `x` 代表所求的路径上的点. 再输出所求的路径.

## 运行示例

测试输入见同 `test` 目录下名为 `case_*` 的文件.

#### 带边界的迷宫

输入 `test/case_1`, 输出如下:

```
$ ./a.out < test/case_1
迷宫地图:
        0列     1列     2列     3列     4列     5列     6列
0行     #       #       #       #       #       #       #
1行     #       x       #       0       0       0       #
2行     #       x       #       0       #       #       #
3行     #       x       x       x       #       0       #
4行     #       #       #       x       x       x       #
5行     #       #       #       #       #       x       #
6行     #       #       #       #       #       #       #

迷宫路径:
(1,1) ---> (2,1) ---> (3,1) ---> (3,2) ---> (3,3) ---> (4,3) ---> (4,4) ---> (4,5) ---> (5,5)
```

#### 横纵大小不相等的迷宫

输入 `test/case_2`, 输出如下:

```
$ ./a.out < test/case_2
迷宫地图:
        0列     1列     2列     3列     4列     5列     6列
0行     #       #       #       #       #       #       #
1行     #       x       #       0       #       #       #
2行     #       x       x       x       #       0       #
3行     #       #       #       x       x       x       #
4行     #       #       #       #       #       x       #
5行     #       #       #       #       #       #       #

迷宫路径:
(1,1) ---> (2,1) ---> (2,2) ---> (2,3) ---> (3,3) ---> (3,4) ---> (3,5) ---> (4,5)
```

#### 没有路径的迷宫

输入 `test/case_3`, 输出如下:

```
$ ./a.out < test/case_3
没有路径!
```

#### 无边界的迷宫

输入 `test/case_4`, 输出如下:

```
$ ./a.out < test/case_4
迷宫地图:
        0列     1列     2列     3列     4列
0行     x       #       0       0       0
1行     x       #       0       #       #
2行     x       x       x       #       0
3行     #       #       x       x       x
4行     #       #       #       #       x

迷宫路径:
(0,0) ---> (1,0) ---> (2,0) ---> (2,1) ---> (2,2) ---> (3,2) ---> (3,3) ---> (3,4) ---> (4,4)
```

