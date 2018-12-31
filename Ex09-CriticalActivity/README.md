# 题目9 关键活动

- [编译说明](#%E7%BC%96%E8%AF%91%E8%AF%B4%E6%98%8E)
- [算法说明](#%E7%AE%97%E6%B3%95%E8%AF%B4%E6%98%8E)
- [输入格式](#%E8%BE%93%E5%85%A5%E6%A0%BC%E5%BC%8F)
- [输出格式](#%E8%BE%93%E5%87%BA%E6%A0%BC%E5%BC%8F)
- [运行示例](#%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B)
    - [简单情况测试](#%E7%AE%80%E5%8D%95%E6%83%85%E5%86%B5%E6%B5%8B%E8%AF%95)
    - [一般情况测试, 单个起点和单个终点](#%E4%B8%80%E8%88%AC%E6%83%85%E5%86%B5%E6%B5%8B%E8%AF%95-%E5%8D%95%E4%B8%AA%E8%B5%B7%E7%82%B9%E5%92%8C%E5%8D%95%E4%B8%AA%E7%BB%88%E7%82%B9)
    - [不可行的方案测试](#%E4%B8%8D%E5%8F%AF%E8%A1%8C%E7%9A%84%E6%96%B9%E6%A1%88%E6%B5%8B%E8%AF%95)

## 编译说明

本程序在 `Ubuntu 18.10` 下使用 `g++ (Ubuntu 8.2.0-7ubuntu1) 8.2.0` 编译通过

编译命令为 `g++ -O2 CriticalActivity.cpp`, 生成可执行文件名为 `a.out`

目录下附有 `Makefile`, 执行 `make` 命令即可构建. 执行 `make test` 可对所有测试用例进行自动测试. 目标可执行文件名可通过其中的 `outfile` 变量进行设置.


## 算法说明

```cpp
int n, m;  // n:任务交接点数, m:子任务数
cin >> n >> m;
vector<vector<int>> graph(n + 1, vector<int>(n + 1, INT32_MAX));  // graph[i][j]代表i->j的开销, 初始化整张图为INF(此处INT32_MAX)

int beginPoint, endPoint, cost;
for (int i = 0; i < m; i++) {
    cin >> beginPoint >> endPoint >> cost;
    graph[beginPoint][endPoint] = cost;
}

int count = 0;                         // 用于判断环路
vector<int> earliest(n + 1, 0);        // 最早完成时间
vector<int> latest(n + 1, INT32_MAX);  // 最晚完成时间
vector<int> indegree(n + 1, 0);        // 入度
vector<int> outdegree(n + 1, 0);       // 出度

for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        if (graph[j][i] != INT32_MAX) {  // 初始化入度
            indegree[i]++;
        }
        if (graph[i][j] != INT32_MAX) {  // 初始化出度
            outdegree[i]++;
        }
    }
}

stack<int> s1;
for (int i = 1; i <= n; i++) {
    if (indegree[i] == 0) {  // 判断入度为0的节点, 放入栈
        s1.push(i);
        indegree[i] = -1;  // 避免重复入栈
    }
}
while (!s1.empty()) {
    int temp = s1.top();
    s1.pop();
    count++;
    for (int i = 1; i <= n; i++) {                                            // 遍历所有节点
        if (graph[temp][i] != INT32_MAX) {                                    // 如果有边<temp,i>
            indegree[i]--;                                                    // i的的入度减1
            earliest[i] = max(earliest[i], earliest[temp] + graph[temp][i]);  // 计算节点i的最早完成时间
            if (indegree[i] == 0) {                                           // 判断入度为0的节点, 放入栈
                s1.push(i);
                indegree[i] = -1;
            }
        }
    }
}

int maxtime = 0, index = 0;
for (int i = 1; i <= n; i++) {  // 找出最大的节点和节点编号
    if (maxtime < earliest[i]) {
        maxtime = earliest[i];
        index = i;
    }
}
latest[index] = maxtime;

stack<int> s2;
for (int i = 1; i <= n; i++) {
    if (outdegree[i] == 0) {  // 判断出度为0的节点, 放入栈
        s2.push(i);
        outdegree[i] = -1;  // 避免重复入栈
    }
}
while (!s2.empty()) {
    int temp = s2.top();
    s2.pop();
    for (int i = 1; i <= n; i++) {                                      // 遍历所有节点
        if (graph[i][temp] != INT32_MAX) {                              // 如果有边<temp,i>
            outdegree[i]--;                                             // i的的出度减1
            latest[i] = min(latest[i], latest[temp] - graph[i][temp]);  // 计算节点i的最晚完成时间
            if (outdegree[i] == 0) {                                    // 判断出度为0的节点, 放入栈
                s2.push(i);
                outdegree[i] = -1;
            }
        }
    }
}

if (count == n) {                       // 如果处理了n个节点
    cout << maxtime << endl;            // 输出最长的时间花费
    for (int i = 1; i <= n; i++) {      // 遍历节点
        for (int j = n; j >= 1; j--) {  // 任务开始的交接点编号小者优先
            if (graph[i][j] != INT32_MAX && graph[i][j] == (latest[j] - earliest[i])) {
                cout << i << "->" << j << endl;
            }
        }
    }
}
else {
    cout << 0 << endl;  // 图中有环, 无法实现, 输出0
}
```

使用拓扑排序, 同时使用一个变量判断环路, 并用 `indegree` 和 `outdegree` 两个数组记录每个节点的最晚完成时间和出度. 先把所有入度为0的点入列, 开始循环, 每次弹出一个节点, 找出与这个节点相连的节点, 入度减1, 更新最小花费时间, 再把所有入度为0的节点入列, 继续循环. 对于出度, 采用同样的方法. 最后根据 `graph[i][j] == lastest[j] - earliest[i]` 判断是否为关键节点.

具体实现见代码注释

## 输入格式

从 `stdin` 读取题目给定格式的输入内容. 输入第1行给出两个正整数N (N<=100) 和M, 其中N是任务交接点的数量, 交接点按1~N编号, M是子任务的数量, 依次编号为1~M. 随后M行, 每行给出3个正整数, 分别是该任务开始和完成涉及的交接点编号以及完成该任务所需要的时间, 整数间用空格分隔. 


## 输出格式

向 `stdout` 输出题目给定格式的内容. 如果任务调度不可行, 输出0; 否则第一行输出完成整个项目所需要的时间, 第2行开始输出所有关键活动, 每个关键活动占一行, 按照格式"V->W"输出, 其中V和W为该任务开始和完成涉及的交接点编号. 关键活动输出的顺序规则是: 任务开始的交接点编号小者优先, 起点编号相同时, 与输入时任务的顺序相反. 


## 运行示例

#### 简单情况测试

输入

```
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 2
4 6 6
5 7 5
6 7 2
```

输出

```
17
1->2
2->4
4->6
6->7
```

#### 一般情况测试, 单个起点和单个终点

输入

```
9 11
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4
```

输出

```
18
1->2
2->5
5->8
5->7
7->9
8->9
```

#### 不可行的方案测试

输入

```
4 5
1 2 4
2 3 5
3 4 6
4 2 3
4 1 2
```

输出

```
0
```