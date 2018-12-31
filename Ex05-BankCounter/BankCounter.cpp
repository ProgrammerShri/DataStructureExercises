#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int count, input;
    priority_queue<int, vector<int>, greater<int>> counterA, counterB;
    cin >> count;
    for (int i = 0; i < count; i++) {
        cin >> input;
        if (input % 2) {  // if odd
            counterA.push(input);
        }
        else {
            counterB.push(input);
        }
    }

    while (!counterA.empty() || !counterB.empty()) {
        for (int i = 0; i < 2; i++) {
            if (!counterA.empty()) {
                if (counterB.empty() && counterA.size() == 1) {
                    cout << counterA.top();
                }
                else {
                    cout << counterA.top() << " ";
                }
                counterA.pop();
            }
        }
        if (!counterB.empty()) {
            if (counterA.empty() && counterB.size() == 1) {
                cout << counterB.top();
            }
            else {
                cout << counterB.top() << " ";
            }
            counterB.pop();
        }
    }
    cout << endl;

    return 0;
}