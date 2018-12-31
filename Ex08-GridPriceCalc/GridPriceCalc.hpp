#pragma once
#include <exception>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

class GridPriceCalc
{
public:
    void run();

private:
    void createNode();
    void setLink();
    void build();
    void print();

    vector<string> node;
    vector<vector<int>> map;
    vector<pair<int, int>> tree;
};

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