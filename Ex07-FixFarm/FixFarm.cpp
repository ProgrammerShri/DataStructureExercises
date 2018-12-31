#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int count, value;
    int sum = 0;
    priority_queue<int, vector<int>, greater<int>> huffmanTree;

    cin >> count;
    for (int i = 0; i < count; i++) {
        cin >> value;
        huffmanTree.push(value);
    }

    while (huffmanTree.size() > 1) {
        int lvalue = huffmanTree.top();
        huffmanTree.pop();
        int rvalue = huffmanTree.top();
        huffmanTree.pop();
        int sumvalue = lvalue + rvalue;
        huffmanTree.push(sumvalue);
        sum += sumvalue;
    }

    cout << sum << endl;

    return 0;
}