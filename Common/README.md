# 公用数据结构类

该目录内的命名空间(namespace)为`ds`

- [单链表 `LinkedList.hpp`](#%E5%8D%95%E9%93%BE%E8%A1%A8-linkedlisthpp)
  - [类 `ds::Node`](#%E7%B1%BB-dsnode)
    - [模板参数](#%E6%A8%A1%E6%9D%BF%E5%8F%82%E6%95%B0)
    - [成员对象](#%E6%88%90%E5%91%98%E5%AF%B9%E8%B1%A1)
    - [成员函数](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0)
    - [构造函数 `Node()`](#%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0-node)
  - [类 `ds::LinkedList`](#%E7%B1%BB-dslinkedlist)
    - [模板参数](#%E6%A8%A1%E6%9D%BF%E5%8F%82%E6%95%B0-1)
    - [成员对象](#%E6%88%90%E5%91%98%E5%AF%B9%E8%B1%A1-1)
    - [成员函数](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-1)
    - [构造函数 `LinkedList()`](#%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0-linkedlist)
    - [成员函数 `size_t size()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-sizet-size)
    - [成员函数 `bool empty()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-bool-empty)
    - [成员函数 `Node<T>* begin()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-nodet-begin)
    - [成员函数 `Node<T>* end()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-nodet-end)
    - [成员函数 `Node<T>* locate(size_t pos)`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-nodet-locatesizet-pos)
    - [成员函数 `T& front()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-t-front)
    - [成员函数 `T& back()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-t-back)
    - [成员函数 `T& at(size_t pos)`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-t-atsizet-pos)
    - [成员函数 `T& operator[](size_t pos)`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-t-operatorsizet-pos)
    - [成员函数 `void push_back(T value)`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-pushbackt-value)
    - [成员函数 `void insert(size_t pos, T value)`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-insertsizet-pos-t-value)
    - [成员函数 `void erase(size_t pos)`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-erasesizet-pos)

## 单链表 `LinkedList.hpp`

一个简单的单链表实现, 题目1与题目2共用



### 类 `ds::Node`

#### 模板参数

| 参数 | 定义       |
| ---- | ---------- |
| T    | 元素的类型 |


#### 成员对象

| 成员         | 公有/私有 | 定义                     | 默认值    |
| ------------ | --------- | ------------------------ | --------- |
| `T data`     | 公有      | 链表节点中的元素         | `N/A`     |
| `Node* next` | 公有      | 指向链表下一个节点的指针 | `nullptr` |


#### 成员函数

| 成员     | 公有/私有 | 定义     |
| -------- | --------- | -------- |
| `Node()` | 公有      | 构造函数 |


#### 构造函数 `Node()`

```cpp
template <typename T>
Node<T>::Node() : next(nullptr) {}
```

默认构造函数, `data` 为空, `next` 指向 `nullptr`.

```cpp
template <typename T>
Node<T>::Node(T value, Node* nextptr) : data(value), next(nextptr) {}
```

常用构造函数, `data` 为参数 `value` 的值, `next` 指向参数 `nextptr` 的值.



### 类 `ds::LinkedList`

#### 模板参数

| 参数 | 定义       |
| ---- | ---------- |
| T    | 元素的类型 |


#### 成员对象

| 成员            | 公有/私有 | 定义                 | 默认值    |
| --------------- | --------- | -------------------- | --------- |
| `Node<T>* head` | 私有      | 指向链表头节点的指针 | `nullptr` |
| `Node<T>* tail` | 私有      | 指向链表尾节点的指针 | `nullptr` |
| `size_t _size`  | 私有      | 链表中的节点数量     | `0`       |


#### 成员函数

| 成员                               | 公有/私有 | 定义                                         |
| ---------------------------------- | --------- | -------------------------------------------- |
| `LinkedList()`                     | 公有      | 默认构造函数                                 |
| `size_t size()`                    | 公有      | 返回链表节点数                               |
| `bool empty()`                     | 公有      | 检查链表是否为空                             |
| `Node<T>* begin()`                 | 公有      | 返回指向链表头节点的指针                     |
| `Node<T>* end()`                   | 公有      | 返回指向链表尾节点的指针                     |
| `Node<T>* locate(size_t pos)`      | 公有      | 返回指向链表指定节点的指针, 同时进行越界检查 |
| `T& front()`                       | 公有      | 访问链表第一个元素                           |
| `T& back()`                        | 公有      | 访问链表最后一个元素                         |
| `T& at(size_t pos)`                | 公有      | 访问链表中指定元素, 同时进行越界检查         |
| `T& operator[](size_t pos)`        | 公有      | 访问链表中指定元素, 无越界检查               |
| `void push_back(T value)`          | 公有      | 将元素添加到链表末尾                         |
| `void insert(size_t pos, T value)` | 公有      | 在指定节点前插入元素                         |
| `void erase(size_t pos)`           | 公有      | 擦除节点                                     |


#### 构造函数 `LinkedList()`

```cpp
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), _size(0) {}
```

默认构造函数, 创建一个空链表.


#### 成员函数 `size_t size()`

```cpp
template <typename T>
size_t LinkedList<T>::size() const { return _size; }
```

返回链表中的节点数量.


#### 成员函数 `bool empty()`

```cpp
template <typename T>
bool LinkedList<T>::empty() const { return _size == 0; }
```

检查链表是否为空, 为空则返回 `true`.


#### 成员函数 `Node<T>* begin()`

```cpp
template <typename T>
Node<T>* LinkedList<T>::begin() const { return head; }
```

返回指向链表头节点的指针. 若链表为空, 则返回 `nullptr`.


#### 成员函数 `Node<T>* end()`

```cpp
template <typename T>
Node<T>* LinkedList<T>::end() const { return tail; }
```

返回指向链表尾节点的指针. 若链表为空, 则返回 `nullptr`.


#### 成员函数 `Node<T>* locate(size_t pos)`

```cpp
template <typename T>
Node<T>* LinkedList<T>::locate(size_t pos) const
{
    try {
        if (pos >= _size) {  // range checking
            throw std::out_of_range("out of range");
        }
        Node<T>* elem = head;
        for (size_t i = 0; i < pos; i++) {
            elem = elem->next;
        }
        return elem;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return nullptr;
    }
}
```

返回指向链表中第 `pos` 位节点的指针, 并进行越界检查. 若越界访问则抛出异常, 中止程序执行.


#### 成员函数 `T& front()`

```cpp
template <typename T>
T& LinkedList<T>::front() const
{
    try {
        if (head == nullptr) {
            throw std::out_of_range("head is undefined");
        }
        return head->data;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
```

返回链表中第一个元素的引用. 若链表头节点指向 `nullptr`, 则抛出异常, 中止程序执行.


#### 成员函数 `T& back()`

```cpp
template <typename T>
T& LinkedList<T>::back() const
{
    try {
        if (tail == nullptr) {
            throw std::out_of_range("tail is undefined");
        }
        return tail->data;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
```

返回链表中第一个元素的引用. 若链表尾节点指向 `nullptr`, 则抛出异常, 中止程序执行.


#### 成员函数 `T& at(size_t pos)`

```cpp
template <typename T>
T& LinkedList<T>::at(size_t pos) const
{
    try {
        if (pos >= _size) {  // range checking
            throw std::out_of_range("out of range");
        }
        return operator[](pos);
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
```

返回链表中指定元素的引用, 同时进行越界检查. 若越界访问则抛出异常, 中止程序执行.


#### 成员函数 `T& operator[](size_t pos)`

```cpp
template <typename T>
T& LinkedList<T>::operator[](size_t pos) const
{
    Node<T>* elem = head;
    for (size_t i = 0; i < pos; i++) {
        elem = elem->next;
    }
    return elem->data;
}
```

返回链表中指定元素的引用, 无越界检查. 越界访问会导致未预期的结果.


#### 成员函数 `void push_back(T value)`

```cpp
template <typename T>
void LinkedList<T>::push_back(T value)
{
    try {
        // Allocate memory and assign value
        Node<T>* newNode = new Node<T>(value, nullptr);
        // Handle list order
        if (tail == nullptr) {  // if list is empty
            head = newNode;
        }
        else {
            tail->next = newNode;
        }
        tail = newNode;
        _size++;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
}
```

将元素 `value` 添加到链表末尾. 同时检查内存是否申请成功, 若失败则抛出异常.


#### 成员函数 `void insert(size_t pos, T value)`

```cpp
template <typename T>
void LinkedList<T>::insert(size_t pos, T value)
{
    try {
        if (pos >= _size) {  // range checking
            throw std::out_of_range("out of range");
        }

        // Allocate memory and assign value
        Node<T>* newNode = new Node<T>(value, nullptr);
        // Handle list order
        if (pos == 0) {
            if (_size == 0) {
                tail = newNode;
            }
            newNode->next = head;  // if size == 0, head == nullptr
            head = newNode;
        }
        else {
            Node<T>* prev = locate(pos - 1);
            newNode->next = prev->next;
            prev->next = newNode;
        }
        _size++;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
}
```

将元素 `value` 添加到链表中第 `pos` 号位节点之前. 同时检查内存是否申请成功及是否越界, 若失败或越界则抛出异常.


#### 成员函数 `void erase(size_t pos)`

```cpp
template <typename T>
void LinkedList<T>::erase(size_t pos)
{
    try {
        if (pos >= _size) {  // range checking
            throw std::out_of_range("out of range");
        }
        if (pos == 0) {
            if (_size == 1) {
                tail = nullptr;
            }
            Node<T>* deleteNode = head;
            head = head->next;  // if size == 1, head->next == nullptr
            delete deleteNode;
        }
        else {
            Node<T>* prev = locate(pos - 1);
            Node<T>* deleteNode = prev->next;
            if (tail == deleteNode) {
                tail = prev;
            }
            prev->next = deleteNode->next;
            delete deleteNode;
        }
        _size--;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
}
```

擦除链表中第 `pos` 号位节点. 同时检查内存是否申请成功及是否越界, 若失败或越界则抛出异常.