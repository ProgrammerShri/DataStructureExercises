# 题目2 两个有序链表序列的交集

- [编译说明](#%E7%BC%96%E8%AF%91%E8%AF%B4%E6%98%8E)
- [程序说明](#%E7%A8%8B%E5%BA%8F%E8%AF%B4%E6%98%8E)
  - [类 `ds::LinkedList`](#%E7%B1%BB-dslinkedlist)
- [算法说明](#%E7%AE%97%E6%B3%95%E8%AF%B4%E6%98%8E)
- [输入格式](#%E8%BE%93%E5%85%A5%E6%A0%BC%E5%BC%8F)
- [输出格式](#%E8%BE%93%E5%87%BA%E6%A0%BC%E5%BC%8F)
- [运行示例](#%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B)
    - [一般情况](#%E4%B8%80%E8%88%AC%E6%83%85%E5%86%B5)
    - [交集为空的情况](#%E4%BA%A4%E9%9B%86%E4%B8%BA%E7%A9%BA%E7%9A%84%E6%83%85%E5%86%B5)
    - [完全相交的情况](#%E5%AE%8C%E5%85%A8%E7%9B%B8%E4%BA%A4%E7%9A%84%E6%83%85%E5%86%B5)
    - [其中一个序列完全属于交集的情况](#%E5%85%B6%E4%B8%AD%E4%B8%80%E4%B8%AA%E5%BA%8F%E5%88%97%E5%AE%8C%E5%85%A8%E5%B1%9E%E4%BA%8E%E4%BA%A4%E9%9B%86%E7%9A%84%E6%83%85%E5%86%B5)
    - [其中一个序列为空的情况](#%E5%85%B6%E4%B8%AD%E4%B8%80%E4%B8%AA%E5%BA%8F%E5%88%97%E4%B8%BA%E7%A9%BA%E7%9A%84%E6%83%85%E5%86%B5)

## 编译说明

本程序在 `Ubuntu 18.10` 下使用 `g++ (Ubuntu 8.2.0-7ubuntu1) 8.2.0` 编译通过

编译命令为 `g++ -O2 LinkedListIntersection.cpp`, 生成可执行文件名为 `a.out`

目录下附有 `Makefile`, 执行 `make` 命令即可构建. 执行 `make test` 可对所有测试用例进行自动测试. 目标可执行文件名可通过其中的 `outfile` 变量进行设置.


## 程序说明

### 类 `ds::LinkedList`

一个简单的单链表实现, 与题目1共用.

详见 [Common目录](../Common/)

## 算法说明

```cpp
LinkedList getIntersection(LinkedList& list1, LinkedList& list2)
{
    std::unordered_set<int> hashset;
    LinkedList result;
    Node* node1 = list1.begin();
    Node* node2 = list2.begin();

    while (node1 != nullptr) {
        hashset.insert(node1->data);
        node1 = node1->next;
    }

    while (node2 != nullptr) {
        if (hashset.count(node2->data)) {
            result.push_back(node2->data);
        }
        node2 = node2->next;
    }

    return result;
}
```

建立类型为 `std::unordered_set<int>` 的哈希表. 使用哈希表可以方便的查找重复元素.

先将链表 `list1` 中的元素全部插入哈希表中, 再将链表 `list2` 中的每个元素再在哈希表中查找. 若哈希表中有则证明重复, 放入链表 `result` 中; 若无则跳过.

返回的链表 `result` 即为链表 `list1` 与 `list2` 的交集.


## 输入格式

从 `stdin` 读取题目给定格式的输入内容. 输入分2行, 分别在每行给出由若干个正整数构成的非降序序列, 用-1表示序列的结尾(-1不属于这个序列). 数字用空格间隔.

该程序不校验输入是否合法, 输入数据需确保在 `int32_t` 的范围内. 且链表中无重复元素.


## 输出格式

向 `stdout` 输出题目给定格式的内容. 在一行中输出两个输入序列的交集序列, 数字间用空格分开, 结尾无多余空格; 若新链表为空, 输出NULL.


## 运行示例

#### 一般情况

输入

```
1 2 5 -1
2 4 5 8 10 -1
```

输出

```
2 5
```

#### 交集为空的情况

输入

```
1 3 5 -1
2 4 6 8 10 -1
```

输出

```
NULL
```

#### 完全相交的情况

输入

```
1 2 3 4 5 -1
1 2 3 4 5 -1
```

输出

```
1 2 3 4 5
```

#### 其中一个序列完全属于交集的情况

输入

```
3 5 7 -1
2 3 4 5 6 7 8 -1
```

输出

```
3 5 7
```

#### 其中一个序列为空的情况

输入

```
-1
10 100 1000 -1
```

输出

```
NULL
```