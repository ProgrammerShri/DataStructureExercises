# 题目7 修理牧场

- [编译说明](#%E7%BC%96%E8%AF%91%E8%AF%B4%E6%98%8E)
- [算法说明](#%E7%AE%97%E6%B3%95%E8%AF%B4%E6%98%8E)
- [输入格式](#%E8%BE%93%E5%85%A5%E6%A0%BC%E5%BC%8F)
- [输出格式](#%E8%BE%93%E5%87%BA%E6%A0%BC%E5%BC%8F)
- [运行示例](#%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B)

## 编译说明

本程序在 `Ubuntu 18.10` 下使用 `g++ (Ubuntu 8.2.0-7ubuntu1) 8.2.0` 编译通过

编译命令为 `g++ -O2 FixFarm.cpp`, 生成可执行文件名为 `a.out`

目录下附有 `Makefile`, 执行 `make` 命令即可构建. 执行 `make test` 可对所有测试用例进行自动测试. 目标可执行文件名可通过其中的 `outfile` 变量进行设置.


## 算法说明

```cpp
priority_queue<int, vector<int>, greater<int>> huffmanTree;

while (huffmanTree.size() > 1) {
    int lvalue = huffmanTree.top();
    huffmanTree.pop();
    int rvalue = huffmanTree.top();
    huffmanTree.pop();
    int sumvalue = lvalue + rvalue;
    huffmanTree.push(sumvalue);
    sum += sumvalue;
}
```

构造一棵哈夫曼树, 此处用 `std::priority_queue` 作为哈夫曼树的容器.

不断取当前最小的两个值相加, 直至容器中只存在一个元素, 即为最优解.

## 输入格式

从 `stdin` 读取题目给定格式的输入内容. 输入第一行给出正整数N (N < 10^4), 表示要将木头锯成N块. 第二行给出N个正整数, 表示每块木头的长度.


## 输出格式

向 `stdout` 输出题目给定格式的内容. 输出一个整数, 即将木头锯成N块的最小花费.


## 运行示例

输入

```
8
4 5 1 2 1 3 1 1
```

输出

```
49
```