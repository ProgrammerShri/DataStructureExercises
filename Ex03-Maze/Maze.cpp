#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Point
{
public:
    Point() : _x(0), _y(0) {}
    Point(int x, int y) : _x(x), _y(y) {}

    int x() const { return _x; }
    int y() const { return _y; }

private:
    int _x;
    int _y;
};

/*
 * Maze:
 * 0: Point cannot pass
 * 1: Point can pass
 */
int main()
{
    int size_x, size_y;
    cin >> size_x >> size_y;
    vector<vector<int>> maze(size_x, vector<int>(size_y, 0));
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            cin >> maze[i][j];
        }
    }

    int start_x, start_y;
    int end_x, end_y;
    cin >> start_x >> start_y;
    cin >> end_x >> end_y;
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
            return 0;
        }
        current = route.top();
    }

    /* 
     * Reverse stack<Point> route and draw route on maze
     * Maze:
     * 0: Point cannot pass
     * 1: Point can pass
     * 2: Point passed
     */
    stack<Point> reversed_route;
    while (!route.empty()) {
        maze[route.top().x()][route.top().y()] = 2;
        reversed_route.push(route.top());
        route.pop();
    }
    route = reversed_route;

    // Print maze
    cout << "迷宫地图:" << endl;

    for (int j = 0; j < size_y; j++) {
        cout << "\t" << j << "列";
    }
    cout << endl;

    for (int i = 0; i < size_x; i++) {
        cout << i << "行";
        for (int j = 0; j < size_y; j++) {
            switch (maze[i][j]) {
                default:
                case 0:
                    cout << "\t#";
                    break;
                case 1:
                    cout << "\t0";
                    break;
                case 2:
                    cout << "\tx";
                    break;
            }
        }
        cout << endl;
    }
    cout << endl;

    // Print route
    cout << "迷宫路径:" << endl
         << "(" << start_x << "," << start_y << ")";
    route.pop();
    while (!route.empty()) {
        cout << " ---> "
             << "(" << route.top().x() << "," << route.top().y() << ")";
        route.pop();
    }
    cout << endl;

    return 0;
}