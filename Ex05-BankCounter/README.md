# 题目5 银行业务

- [编译说明](#%E7%BC%96%E8%AF%91%E8%AF%B4%E6%98%8E)
- [算法说明](#%E7%AE%97%E6%B3%95%E8%AF%B4%E6%98%8E)
- [输入格式](#%E8%BE%93%E5%85%A5%E6%A0%BC%E5%BC%8F)
- [输出格式](#%E8%BE%93%E5%87%BA%E6%A0%BC%E5%BC%8F)
- [运行示例](#%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B)
    - [正常测试, A窗口人多](#%E6%AD%A3%E5%B8%B8%E6%B5%8B%E8%AF%95-a%E7%AA%97%E5%8F%A3%E4%BA%BA%E5%A4%9A)
    - [正常测试, B窗口人多](#%E6%AD%A3%E5%B8%B8%E6%B5%8B%E8%AF%95-b%E7%AA%97%E5%8F%A3%E4%BA%BA%E5%A4%9A)
    - [正常测试, 最小N](#%E6%AD%A3%E5%B8%B8%E6%B5%8B%E8%AF%95-%E6%9C%80%E5%B0%8Fn)

## 编译说明

本程序在 `Ubuntu 18.10` 下使用 `g++ (Ubuntu 8.2.0-7ubuntu1) 8.2.0` 编译通过

编译命令为 `g++ -O2 BankCounter.cpp`, 生成可执行文件名为 `a.out`

目录下附有 `Makefile`, 执行 `make` 命令即可构建. 执行 `make test` 可对所有测试用例进行自动测试. 目标可执行文件名可通过其中的 `outfile` 变量进行设置.


## 算法说明

```cpp
priority_queue<int, vector<int>, greater<int>> counterA, counterB;

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
```

使用 `std::priority_queue` 作为存放队列的容器. 使用优先队列可以方便的将队列中的数据由小到大排序.

对于某一容器, 判断该容器中首位的元素是否为两个队列中最后一个, 若是则仅输出该元素, 不输出空格, 否则输出该元素和空格, 并丢弃该元素. 

对于A队列, 每回合执行2次; 对于B队列, 每回合执行1次. 直至A, B两容器均为空.


## 输入格式

从 `stdin` 读取题目给定格式的输入内容. 输入为一行正整数, 其中第一数字N (1 <= N <= 1000) 为顾客总数, 后面跟着N位顾客的编号.


## 输出格式

向 `stdout` 输出题目给定格式的内容. 按照业务处理完成的顺序输出顾客的编号. 数字以空格分隔, 最后一个编号无多余空格。


## 运行示例

#### 正常测试, A窗口人多

输入

```
8 2 1 3 9 4 11 13 15
```

输出

```
1 3 2 9 11 4 13 15
```


#### 正常测试, B窗口人多

输入
```
8 2 1 3 9 4 11 13 16
```

输出

```
1 3 2 9 11 4 13 16
```


#### 正常测试, 最小N

输入
```
1 6
```

输出

```
6
```