# 题目1 考试报名系统

- [编译说明](#%E7%BC%96%E8%AF%91%E8%AF%B4%E6%98%8E)
- [程序说明](#%E7%A8%8B%E5%BA%8F%E8%AF%B4%E6%98%8E)
  - [类 `ds::LinkedList`](#%E7%B1%BB-dslinkedlist)
  - [类 `Student`](#%E7%B1%BB-student)
    - [成员对象](#%E6%88%90%E5%91%98%E5%AF%B9%E8%B1%A1)
    - [成员函数](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0)
    - [非成员函数](#%E9%9D%9E%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0)
    - [构造函数 `Student()`](#%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0-student)
    - [非成员函数 `friend std::istream& operator>>(std::istream& is, Student& stu)`](#%E9%9D%9E%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-friend-stdistream-operatorstdistream-is-student-stu)
    - [非成员函数 `friend std::ofstream& operator<<(std::ofstream& ofs, const Student& stu)`](#%E9%9D%9E%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-friend-stdofstream-operatorstdofstream-ofs-const-student-stu)
    - [非成员函数 `friend std::ofstream& operator<<(std::ofstream& ofs, const Student& stu)`](#%E9%9D%9E%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-friend-stdofstream-operatorstdofstream-ofs-const-student-stu-1)
  - [类 `StudentManager`](#%E7%B1%BB-studentmanager)
    - [成员对象](#%E6%88%90%E5%91%98%E5%AF%B9%E8%B1%A1-1)
    - [成员函数](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-1)
    - [成员函数 `void run()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-run)
    - [成员函数 `void init()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-init)
    - [成员函数 `void insert()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-insert)
    - [成员函数 `void delete()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-delete)
    - [成员函数 `void find()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-find)
    - [成员函数 `void modify()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-modify)
    - [成员函数 `void stat()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-stat)
    - [成员函数 `void exportToCSV()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-exporttocsv)
    - [成员函数 `bool duplicate(unsigned id)`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-bool-duplicateunsigned-id)
    - [成员函数 `void printTable()`](#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0-void-printtable)
- [运行示例](#%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B)

## 编译说明

本程序在 `Ubuntu 18.10` 下使用 `g++ (Ubuntu 8.2.0-7ubuntu1) 8.2.0` 编译通过

编译命令为 `g++ -O2 GridPriceCalc.cpp`, 生成可执行文件名为 `a.out`

目录下附有 `Makefile`, 执行 `make` 命令即可构建. 目标可执行文件名可通过其中的 `outfile` 变量进行设置.


## 程序说明

程序由 `StudentManager.cpp`、`StudentManager.hpp` 和 `Student.hpp`组成. `StudentManager.cpp`仅定义了程序的入口点, `StudentManager.hpp` 和 `Student.hpp` 定义了程序中所用到的类和具体实现.

### 类 `ds::LinkedList`

一个简单的单链表实现, 与题目2共用.

详见 [Common目录](../Common/)

### 类 `Student`

该类表示某一条学生信息.

#### 成员对象

| 成员                    | 公有/私有 | 定义                        | 默认值 |
| ----------------------- | --------- | --------------------------- | ------ |
| `unsigned id`           | 公有      | 学生的考号(0~4,294,967,295) | `N/A`  |
| `std::string name`      | 公有      | 学生的姓名                  | `N/A`  |
| `std::string gender`    | 公有      | 学生的性别                  | `N/A`  |
| `unsigned age`          | 公有      | 学生的年龄(0~255)           | `N/A`  |
| `std::string exam_type` | 公有      | 学生的报考类别              | `N/A`  |

#### 成员函数

| 成员        | 公有/私有 | 定义     |
| ----------- | --------- | -------- |
| `Student()` | 公有      | 构造函数 |

#### 非成员函数

| 函数         | 定义     |
| ------------ | -------- |
| `operator>>` | 输入数据 |
| `operator<<` | 输出数据 |

#### 构造函数 `Student()`

```cpp
Student() {}
```

默认构造函数.

```cpp
Student(uint32_t _id, std::string _name, std::string _gender, uint8_t _age, std::string _exam_type)
        : id(_id), name(_name), gender(_gender), age(_age), exam_type(_exam_type) {}
```

常用构造函数.

#### 非成员函数 `friend std::istream& operator>>(std::istream& is, Student& stu)`

```cpp
std::istream& operator>>(std::istream& is, Student& stu)
{
    is >> stu.id >> stu.name >> stu.gender >> stu.age >> stu.exam_type;
    return is;
}
```

从 `stdin` 输入数据, 输入依次为考号, 姓名, 性别, 年龄, 考试类型.

#### 非成员函数 `friend std::ofstream& operator<<(std::ofstream& ofs, const Student& stu)`

```cpp
std::ostream& operator<<(std::ostream& os, const Student& stu)
{
    os << stu.id << "\t" << stu.name << "\t" << stu.gender << "\t" << stu.age << "\t" << stu.exam_type;
    return os;
}
```

向 `stdout` 输出数据, 输出依次为考号, 姓名, 性别, 年龄, 考试类型, 以 `\t` 分隔.

#### 非成员函数 `friend std::ofstream& operator<<(std::ofstream& ofs, const Student& stu)`

```cpp
std::ofstream& operator<<(std::ofstream& ofs, const Student& stu)
{
    ofs << stu.id << "," << stu.name << "," << stu.gender << "," << stu.age << "," << stu.exam_type;
    return ofs;
}
```
向文件输出数据, 输出依次为考号, 姓名, 性别, 年龄, 考试类型, 以逗号分隔.


### 类 `StudentManager`

该类为程序的主要实现.

#### 成员对象

| 成员                            | 公有/私有 | 定义                               | 默认值 |
| ------------------------------- | --------- | ---------------------------------- | ------ |
| `ds::LinkedList<Student> table` | 私有      | 存放考生数据表的容器, 基于链表实现 | `N/A`  |

#### 成员函数

| 成员                          | 公有/私有 | 定义                                   |
| ----------------------------- | --------- | -------------------------------------- |
| `void run()`                  | 公有      | 运行程序的入口, 唯一可被外部调用的方法 |
| `void init()`                 | 私有      | 初始化功能(交互式)                     |
| `void insert()`               | 私有      | 插入功能(交互式)                       |
| `void remove()`               | 私有      | 删除功能(交互式)                       |
| `void find()`                 | 私有      | 查找功能(交互式)                       |
| `void modify()`               | 私有      | 修改功能(交互式)                       |
| `void stat()`                 | 私有      | 统计功能(交互式)                       |
| `void exportToCSV()`          | 私有      | 导出功能(交互式)                       |
| `bool duplicate(unsigned id)` | 私有      | 检查是否有重复的考号                   |
| `void printTable()`           | 私有      | 列出考试报名表                         |

#### 成员函数 `void run()`

```cpp
void StudentManager::run()
{
    while (table.empty()) {
        init();
    }
    while (true) {
        printTable();
        int op;
        std::cout << "[1]插入\t[2]删除\t[3]查找\t[4]修改" << std::endl
                  << "[5]统计\t[6]导出\t\t[0]退出" << std::endl
                  << std::endl
                  << "请选择你要进行的操作：";
        std::cin >> op;
        if (!std::cin.good()) {
            std::cin.clear();
            op = -1;  // set op to UINT32_MAX to get a warning
        }
        std::cin.ignore(INT32_MAX, '\n');
        switch (op) {
            case 0:
                std::cout << "正在退出..." << std::endl;
                return;
            case 1:
                insert();
                break;
            case 2:
                remove();
                break;
            case 3:
                find();
                break;
            case 4:
                modify();
                break;
            case 5:
                stat();
                break;
            case 6:
                exportToCSV();
                break;
            default:
                std::cerr << "[警告] 输入有误，请重新输入" << std::endl;
                continue;
        }
    }
}
```

该成员函数检查考生数据表是否为空, 若为空, 则进行初始化操作. 此后列出当前数据表及选单, 接着获取用户输入, 根据用户输入执行相应功能.

#### 成员函数 `void init()`

```cpp
void StudentManager::init()
{
    size_t stu_count;
    Student temp;
    std::cout << "首先请建立考生信息系统！" << std::endl
              << "请输入考生人数：";
    std::cin >> stu_count;
    if (!std::cin.good()) {
        std::cin.clear();
        stu_count = 0;
    }
    std::cin.ignore(INT32_MAX, '\n');
    if (stu_count <= 0) {
        std::cout << "[错误] 考生人数需为大于0的整数" << std::endl
                  << std::endl;
        return;
    }
    std::cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别:" << std::endl;
    for (unsigned i = 0; i < stu_count; i++) {
        try {
            std::cin >> temp;
            std::cin.ignore(INT32_MAX, '\n');
            if (duplicate(temp.id)) {
                throw std::invalid_argument("重复的考号");
            }
            table.push_back(temp);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "[警告] " << e.what() << "，该条目将会被忽略" << std::endl
                      << "[信息] 考号必须唯一！" << std::endl;
        }
    }
}
```

该成员函数提供初始化考生信息功能的实现, 交互式地请求输入考生信息. 对输入的考生信息校验是否有考号重复的情况, 有重复则抛出异常, 无重复则输入数据表中.

#### 成员函数 `void insert()`

```cpp
void StudentManager::insert()
{
    try {
        size_t position;
        std::cout << "提示：插入功能为向前插入，若要向末尾添加，请输入最大序号的下一个数字" << std::endl
                  << "请输入你要插入的考生的位置：";
        std::cin >> position;
        std::cin.ignore(INT32_MAX, '\n');
        if (position == 0 || position > (table.size() + 1)) {
            throw std::out_of_range("输入超出范围");
        }
        Student newStu;
        std::cout << "请依次输入要插入的考生的考号、姓名、性别、年龄及报考类别:" << std::endl;
        std::cin >> newStu;
        std::cin.ignore(INT32_MAX, '\n');
        if (duplicate(newStu.id)) {
            throw std::invalid_argument("重复的考号");
        }
        if (position == (table.size() + 1)) {
            table.push_back(newStu);
        }
        else {
            table.insert((position - 1), newStu);
        }
    }
    catch (const std::out_of_range& e) {
        std::cout << "[错误] " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "[警告] " << e.what() << "，该条目将会被忽略" << std::endl
                  << "[信息] 考号必须唯一！" << std::endl;
    }
}
```

该成员函数提供插入功能的实现, 交互式地请求输入考生信息. 先检查所输入的插入位置是否正确, 若位置非法则抛出异常. 否则接着请求输入要插入的考生信息, 并对其校验是否有考号重复的情况, 有重复则抛出异常, 无重复则继续执行, 将该条目插入数据表中.

#### 成员函数 `void delete()`

```cpp
void StudentManager::remove()
{
    try {
        size_t position;
        std::cout << "请输入你要删除的考生的序号：";
        std::cin >> position;
        std::cin.ignore(INT32_MAX, '\n');
        if (position == 0 || position > table.size()) {
            throw std::out_of_range("输入超出范围");
        }
        std::cout << "你删除的考生信息是：" << std::endl
                  << "考号\t姓名\t性别\t年龄\t报考类别" << std::endl
                  << table.at(position - 1) << std::endl;
        table.erase(position - 1);
    }
    catch (const std::out_of_range& e) {
        std::cout << "[错误] " << e.what() << std::endl;
    }
}
```

该成员函数提供删除功能的实现, 交互式地请求输入要删除的考生的序号. 先检查所输入的要删除的考生的序号是否正确, 若位置非法则抛出异常, 否则继续执行, 删除该条目.

#### 成员函数 `void find()`

```cpp
void StudentManager::find()
{
    unsigned id;
    std::cout << "请输入你要查找的考生的考号：";
    std::cin >> id;
    std::cin.ignore(INT32_MAX, '\n');
    auto node = table.begin();
    while (node != nullptr) {
        if (id == node->data.id) {
            std::cout << "考号\t姓名\t性别\t年龄\t报考类别" << std::endl
                      << node->data << std::endl;
            return;  // since id is unique, return when found one
        }
        node = node->next;
    }
    std::cout << "未找到，请确认输入信息是否正确" << std::endl;
}
```

该成员函数提供查找功能的实现, 交互式地请求要查找的考生的考号, 然后在链表中从头至尾搜索. 由于考号字段确保了唯一性, 一旦找到一个结果, 就中止查找, 并输出查找结果.

#### 成员函数 `void modify()`

```cpp
void StudentManager::modify()
{
    try {
        size_t position;
        std::cout << "请输入你要修改的考生的序号：";
        std::cin >> position;
        std::cin.ignore(INT32_MAX, '\n');
        if (position == 0 || position > table.size()) {
            throw std::out_of_range("输入超出范围");
        }
        Student newStu;
        std::cout << "请依次输入修改后的考生的考号、姓名、性别、年龄及报考类别:" << std::endl;
        std::cin >> newStu;
        std::cin.ignore(INT32_MAX, '\n');
        if (duplicate(newStu.id)) {
            throw std::invalid_argument("重复的考号");
        }
        table.at(position - 1) = newStu;
    }
    catch (const std::out_of_range& e) {
        std::cout << "[错误] " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "[警告] " << e.what() << "，该条目将会被忽略" << std::endl
                  << "[信息] 考号必须唯一！" << std::endl;
    }
}
```

该成员函数提供修改功能的实现, 交互式地请求输入要修改的考生的序号. 先检查所输入的要删除的行的序号是否正确, 若位置非法则抛出异常. 否则接着请求输入修改后的考生信息, 对其校验是否有考号重复的情况, 有重复则抛出异常, 无重复则继续执行, 修改该条目.

#### 成员函数 `void stat()`

```cpp
void StudentManager::stat()
{
    std::cout << "共有" << table.size() << "条数据" << std::endl;
}
```

该成员函数提供统计功能的实现. 由于需求未明确给出, 此处仅输出统计的考生信息条目总数.

#### 成员函数 `void exportToCSV()`

```cpp
void StudentManager::exportToCSV()
{
    std::string filename;
    std::cout << "请输入导出文件名(不需要扩展名)：";
    std::cin >> filename;
    std::cin.ignore(INT32_MAX, '\n');
    filename.append(".csv");
    std::ofstream file(filename, std::ios::out);
    file << "考号,姓名,性别,年龄,报考类别" << std::endl;
    auto node = table.begin();
    while (node != nullptr) {
        file << node->data << std::endl;
        node = node->next;
    }
    file.close();
    std::cout << filename <<" 导出成功" << std::endl;
}
```

该成员函数提供输出功能的实现, 输出的文件满足逗号分隔值 `.csv` 格式. 该函数交互式地请求输入要输出的文件名, 并将考生信息表中的数据输出至文件中.

#### 成员函数 `bool duplicate(unsigned id)`

```cpp
bool StudentManager::duplicate(unsigned id)
{
    if (table.empty()) {
        return false;
    }
    auto node = table.begin();
    while (node != nullptr) {
        if (id == node->data.id) {
            return true;
        }
        node = node->next;
    }
    return false;
}
```

该成员函数检查链表中是否有考号与 `id` 一样的元素, 若有则返回 `true`, 无则返回 `false`.

#### 成员函数 `void printTable()`

```cpp
void StudentManager::printTable()
{
    std::cout << std::endl
              << "序号\t考号\t姓名\t性别\t年龄\t报考类别" << std::endl;
    auto node = table.begin();
    int i = 1;
    while (node != nullptr) {
        std::cout << i << "\t" << node->data << std::endl;
        node = node->next;
        i++;
    }
    std::cout << std::endl;
}
```

该成员函数提供打印数据表功能, 用于每次进入选单前数据表的显示.


## 运行示例

Note: 中文字符部分平台下存在无法对齐的情况, 该问题无解

```
$ ./a.out
首先请建立考生信息系统！
请输入考生人数：3
请依次输入考生的考号、姓名、性别、年龄及报考类别:
1 stu1 女 20 软件设计师
2 stu2 男 21 软件开发师
3 stu3 男 20 软件设计师

序号    考号    姓名    性别    年龄    报考类别
1       1       stu1    女      20      软件设计师
2       2       stu2    男      21      软件开发师
3       3       stu3    男      20      软件设计师

[1]插入 [2]删除 [3]查找 [4]修改
[5]统计 [6]导出         [0]退出

请选择你要进行的操作：1
提示：插入功能为向前插入，若要向末尾添加，请输入最大序号的下一个数字
请输入你要插入的考生的位置：4
请依次输入要插入的考生的考号、姓名、性别、年龄及报考类别:
4 stu4 女 21 软件测试师

序号    考号    姓名    性别    年龄    报考类别
1       1       stu1    女      20      软件设计师
2       2       stu2    男      21      软件开发师
3       3       stu3    男      20      软件设计师
4       4       stu4    女      21      软件测试师

[1]插入 [2]删除 [3]查找 [4]修改
[5]统计 [6]导出         [0]退出

请选择你要进行的操作：2
请输入你要删除的考生的序号：2
你删除的考生信息是：
考号    姓名    性别    年龄    报考类别
2       stu2    男      21      软件开发师

序号    考号    姓名    性别    年龄    报考类别
1       1       stu1    女      20      软件设计师
2       3       stu3    男      20      软件设计师
3       4       stu4    女      21      软件测试师

[1]插入 [2]删除 [3]查找 [4]修改
[5]统计 [6]导出         [0]退出

请选择你要进行的操作：3
请输入你要查找的考生的考号：3
考号    姓名    性别    年龄    报考类别
3       stu3    男      20      软件设计师

序号    考号    姓名    性别    年龄    报考类别
1       1       stu1    女      20      软件设计师
2       3       stu3    男      20      软件设计师
3       4       stu4    女      21      软件测试师

[1]插入 [2]删除 [3]查找 [4]修改
[5]统计 [6]导出         [0]退出

请选择你要进行的操作：4
请输入你要修改的考生的序号：3
请依次输入修改后的考生的考号、姓名、性别、年龄及报考类别:
114514 田所浩二 男 24 传统艺能

序号    考号    姓名    性别    年龄    报考类别
1       1       stu1    女      20      软件设计师
2       3       stu3    男      20      软件设计师
3       114514  田所浩二 男      24      传统艺能

[1]插入 [2]删除 [3]查找 [4]修改
[5]统计 [6]导出         [0]退出

请选择你要进行的操作：5
共有3条数据

序号    考号    姓名    性别    年龄    报考类别
1       1       stu1    女      20      软件设计师
2       3       stu3    男      20      软件设计师
3       114514  田所浩二 男      24      传统艺能

[1]插入 [2]删除 [3]查找 [4]修改
[5]统计 [6]导出         [0]退出

请选择你要进行的操作：6
请输入导出文件名(不需要扩展名)：考试报名表
考试报名表.csv 导出成功

序号    考号    姓名    性别    年龄    报考类别
1       1       stu1    女      20      软件设计师
2       3       stu3    男      20      软件设计师
3       114514  田所浩二 男      24      传统艺能

[1]插入 [2]删除 [3]查找 [4]修改
[5]统计 [6]导出         [0]退出

请选择你要进行的操作：0
正在退出...
```