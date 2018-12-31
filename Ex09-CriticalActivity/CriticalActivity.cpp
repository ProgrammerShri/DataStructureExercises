#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    int n, m;  // n:任务交接点数, m:子任务数
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INT32_MAX));  // Graph[i][j]代表i->j的开销, 初始化整张图为INF(此处为INT32_MAX)

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

    return 0;
}