# 题目10 8种排序算法的比较案例

- [编译说明](#%E7%BC%96%E8%AF%91%E8%AF%B4%E6%98%8E)
- [程序说明](#%E7%A8%8B%E5%BA%8F%E8%AF%B4%E6%98%8E)
  - [头文件 `SortAlgorithms.hpp`](#%E5%A4%B4%E6%96%87%E4%BB%B6-sortalgorithmshpp)
    - [函数 `uint64_t bubbleSort(Iter begin, Iter end)`](#%E5%87%BD%E6%95%B0-uint64t-bubblesortiter-begin-iter-end)
    - [函数 `uint64_t selectionSort(Iter begin, Iter end)`](#%E5%87%BD%E6%95%B0-uint64t-selectionsortiter-begin-iter-end)
    - [函数 `uint64_t insertionSort(Iter begin, Iter end)`](#%E5%87%BD%E6%95%B0-uint64t-insertionsortiter-begin-iter-end)
    - [函数 `uint64_t shellSort(Iter begin, Iter end)`](#%E5%87%BD%E6%95%B0-uint64t-shellsortiter-begin-iter-end)
    - [函数 `uint64_t quickSort(Iter begin, Iter end)`](#%E5%87%BD%E6%95%B0-uint64t-quicksortiter-begin-iter-end)
    - [函数 `uint64_t heapSort(Iter begin, Iter end)`](#%E5%87%BD%E6%95%B0-uint64t-heapsortiter-begin-iter-end)
    - [函数 `uint64_t mergeSort(Iter begin, Iter end)`](#%E5%87%BD%E6%95%B0-uint64t-mergesortiter-begin-iter-end)
    - [函数 `uint64_t radixSort(Iter begin, Iter end)`](#%E5%87%BD%E6%95%B0-uint64t-radixsortiter-begin-iter-end)
  - [源文件 `SortComparison.cpp`](#%E6%BA%90%E6%96%87%E4%BB%B6-sortcomparisoncpp)
    - [函数 `std::pair<std::chrono::microseconds::rep, uint64_t> exec(Func f)`](#%E5%87%BD%E6%95%B0-stdpairstdchronomicrosecondsrep-uint64t-execfunc-f)
    - [主函数 `main()`](#%E4%B8%BB%E5%87%BD%E6%95%B0-main)
- [运行示例](#%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B)
  - [调试功能开, 使用 `std::vector`](#%E8%B0%83%E8%AF%95%E5%8A%9F%E8%83%BD%E5%BC%80-%E4%BD%BF%E7%94%A8-stdvector)
  - [调试功能关, 使用 `std::vector`](#%E8%B0%83%E8%AF%95%E5%8A%9F%E8%83%BD%E5%85%B3-%E4%BD%BF%E7%94%A8-stdvector)
  - [调试功能关, 使用 `std::deque`](#%E8%B0%83%E8%AF%95%E5%8A%9F%E8%83%BD%E5%85%B3-%E4%BD%BF%E7%94%A8-stddeque)
- [结论](#%E7%BB%93%E8%AE%BA)

## 编译说明

本程序在 `Ubuntu 18.10` 下使用 `g++ (Ubuntu 8.2.0-7ubuntu1) 8.2.0` 编译通过

编译命令为 `g++ -O2 SortComparison.cpp`, 生成可执行文件名为 `a.out`

目录下附有 `Makefile`, 执行 `make` 命令即可构建. 目标可执行文件名可通过其中的 `outfile` 变量进行设置.

排序的比较可使用 `std::vector` 或 `std::deque` 两种容器执行, 并提供一个显示比较所用容器及显示是否已经正确排序 (使用 `std::is_sorted` 函数) 的调试模式, 编译选项如下.

| 编译选项            | 描述                           |
| ------------------- | ------------------------------ |
| `make`              | 默认选项, 使用 `std::vector`   |
| `make debug`        | 使用 `std::vector`, 有调试信息 |
| `make vector`       | 使用 `std::vector`             |
| `make deque`        | 使用 `std::deque`              |
| `make vector_debug` | 使用 `std::vector`, 有调试信息 |
| `make deque_debug`  | 使用 `std::deque`, 有调试信息  |


## 程序说明

程序由 `SortComparison.cpp` 和 `SortAlgorithms.hpp` 组成. 前者是排序算法比较程序的实现, 后者定义了前者所用到的排序算法的具体实现.

### 头文件 `SortAlgorithms.hpp`

该头文件内包含了冒泡排序、选择排序、插入排序、希尔排序、快速排序、堆排序、归并排序及基数排序8种排序方式的实现

上述排序函数将容器从小到大排列. 参数为2个迭代器, 表示排序的起始元素和终止元素. 返回值为排序的交换次数, 类型为 `uint64_t`.

#### 函数 `uint64_t bubbleSort(Iter begin, Iter end)`

```cpp
template <typename Iter>
uint64_t bubbleSort(Iter begin, Iter end)
{
    uint64_t swap_count = 0;
    Iter i, j;
    for (i = begin; i != end; i++) {
        for (j = begin; j < i; j++) {
            if (*i < *j) {
                std::iter_swap(i, j);
                swap_count++;
            }
        }
    }
    return swap_count;
}
```

冒泡排序是一种简单的排序算法. 它重复地走访过要排序的数列, 一次比较两个元素, 如果他们的顺序错误就把他们交换过来. 走访数列的工作是重复地进行直到没有再需要交换, 也就是说该数列已经排序完成.

#### 函数 `uint64_t selectionSort(Iter begin, Iter end)`

```cpp
template <typename Iter>
uint64_t selectionSort(Iter begin, Iter end)
{
    uint64_t swap_count = 0;
    Iter min;
    while (begin != end) {
        min = std::min_element(begin, end);
        std::iter_swap(begin, min);
        swap_count++;
        ++begin;
    }
    swap_count--;  // iter_swap is counted when begin == min
    return swap_count;
}
```

选择排序是一种简单直观的排序算法. 它首先在未排序序列中找到最小(大)元素, 存放到排序序列的起始位置, 然后, 再从剩余未排序元素中继续寻找最小(大)元素, 然后放到已排序序列的末尾. 以此类推, 直到所有元素均排序完毕. 

#### 函数 `uint64_t insertionSort(Iter begin, Iter end)`

```cpp
template <typename Iter>
uint64_t insertionSort(Iter begin, Iter end)
{
    uint64_t swap_count = 0;
    auto a = begin;
    std::iter_swap(a, std::min_element(a, end));
    swap_count++;
    for (auto b = a; ++b < end; a = b) {
        for (auto c = b; *c < *a; --c, --a) {
            std::iter_swap(a, c);
            swap_count++;
        }
    }
    return swap_count;
}
```

插入排序是一种简单直观的排序算法. 它的工作原理是通过构建有序序列, 对于未排序数据, 在已排序序列中从后向前扫描, 找到相应位置并插入. 插入排序在从后向前扫描过程中, 需要反复把已排序元素逐步向后挪位, 为最新元素提供插入空间.

#### 函数 `uint64_t shellSort(Iter begin, Iter end)`

```cpp
template <typename Iter>
uint64_t shellSort(Iter begin, Iter end)
{
    uint64_t swap_count = 0;
    auto size = end - begin;
    auto h = 1;
    while (h < size / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (auto i = begin + h; i != end; i++) {
            for (auto j = i; (j - begin) >= h && (*j < *(j - h)); j -= h) {
                std::swap(*j, *(j - h));
                swap_count++;
            }
        }
        h = h / 3;
    }
    return swap_count;
}
```

希尔排序, 是插入排序的一种更高效的改进版本. 希尔排序是非稳定排序算法. 希尔排序通过将比较的全部元素分为几个区域来提升插入排序的性能. 这样可以让一个元素可以一次性地朝最终位置前进一大步. 然后算法再取越来越小的步长进行排序, 算法的最后一步就是普通的插入排序.

#### 函数 `uint64_t quickSort(Iter begin, Iter end)`

```cpp
template <typename Iter>
uint64_t quickSort(Iter begin, Iter end)
{
    uint64_t swap_count = 0;
    if (begin != end) {
        auto left = begin;
        auto right = end;
        auto pivot = left++;

        while (left != right) {
            if (*left < *pivot) {
                ++left;
            }
            else {
                while ((left != right) && (*pivot < *right)) {
                    --right;
                }
                std::iter_swap(left, right);
                swap_count++;
            }
        }
        --left;
        std::iter_swap(pivot, left);
        swap_count++;

        swap_count += quickSort(begin, left);
        swap_count += quickSort(right, end);
    }
    return swap_count;
}
```

快速排序使用分治法策略来把一个序列分为两个子序列. 

步骤为: 

1. 从数列中挑出一个元素, 称为"基准".
2. 重新排序数列, 所有比基准值小的元素摆放在基准前面, 所有比基准值大的元素摆在基准后面(相同的数可以到任何一边). 在这个分割结束之后, 该基准就处于数列的中间位置. 这个称为分割操作. 
3. 递归地把小于基准值元素的子数列和大于基准值元素的子数列排序. 

递归到最底部时, 数列的大小是零或一, 也就是已经排序好了. 这个算法一定会结束, 因为在每次的迭代中, 它至少会把一个元素摆到它最后的位置去. 

#### 函数 `uint64_t heapSort(Iter begin, Iter end)`

```cpp
template <typename Iter>
uint64_t heapSort(Iter begin, Iter end)
{
    uint64_t swap_count = 0;
    size_t size = end - begin;
    for (unsigned i = 1; i < size; i++) {
        if (begin[i] > begin[(i - 1) / 2]) {
            int j = i;
            while (begin[j] > begin[(j - 1) / 2]) {
                std::swap(begin[j], begin[(j - 1) / 2]);
                swap_count++;
                j = (j - 1) / 2;
            }
        }
    }
    for (int i = size - 1; i > 0; i--) {
        std::swap(begin[0], begin[i]);
        swap_count++;
        int j = 0, k;
        do {
            k = 2 * j + 1;
            if (k < (i - 1) && begin[k] < begin[k + 1]) {
                k++;
            }
            if (k < i && begin[j] < begin[k]) {
                std::swap(begin[j], begin[k]);
                swap_count++;
            }
            j = k;
        } while (k < i);
    }
    return swap_count;
}
```

堆排序是指利用堆这种数据结构所设计的一种排序算法. 堆是一个近似完全二叉树的结构, 并同时满足堆积的性质: 即子节点的键值或索引总是小于(或者大于)它的父节点. 

#### 函数 `uint64_t mergeSort(Iter begin, Iter end)`

```cpp
template <typename Iter>
uint64_t mergeSort(Iter begin, Iter end)
{
    uint64_t swap_count = 0;
    using T = typename std::iterator_traits<Iter>::value_type;
    size_t size = end - begin;
    std::vector<T> temp(size);
    for (unsigned seg = 1; seg < size; seg += seg) {
        for (unsigned start = 0; start < size; start += seg + seg) {
            int low = start;
            int mid = std::min(start + seg, static_cast<unsigned>(size)) - 1;
            int high = std::min(start + seg + seg, static_cast<unsigned>(size)) - 1;

            std::copy(begin + low, begin + high, temp.begin() + low);

            int i = low, j = mid + 1;
            for (int k = low; k <= high; k++) {
                if (i > mid) {
                    begin[k] = temp.begin()[j++];
                    swap_count++;
                }
                else if (j > high) {
                    begin[k] = temp.begin()[i++];
                }
                else if (temp.begin()[j] < temp.begin()[i]) {
                    begin[k] = temp.begin()[j++];
                    swap_count++;
                }
                else {
                    begin[k] = temp.begin()[i++];
                }
            }
        }
    }
    return swap_count;
}
```

归并排序, 是创建在归并操作上的一种有效的排序算法. 该算法是采用分治法的一个非常典型的应用, 且各层分治递归可以同时进行. 

原理如下(假设序列共有n个元素): 

1. 将序列每相邻两个数字进行归并操作, 形成 (n/2)个序列, 排序后每个序列包含两/一个元素.
2. 若此时序列数不是1个则将上述序列再次归并, 形成n/4个序列, 每个序列包含四/三个元素
3. 重复步骤2, 直到所有元素排序完毕, 即序列数为1.

#### 函数 `uint64_t radixSort(Iter begin, Iter end)`

```cpp
template <typename Iter>
uint64_t radixSort(Iter begin, Iter end)
{
    uint64_t swap_count = 0;
    using T = typename std::iterator_traits<Iter>::value_type;
    T max = *std::max_element(begin, end);
    std::queue<T> bucket[10];
    for (unsigned power = 1; max / power > 0; power *= 10) {
        for (auto it = begin; it != end; it++) {
            bucket[(*it / power) % 10].push(*it);
        }
        auto it = begin;
        for (int i = 0; i < 10; i++) {
            size_t bucketSize = bucket[i].size();
            for (unsigned j = 0; j < bucketSize; j++) {
                *it = bucket[i].front();
                bucket[i].pop();
                it++;
                if (!bucket[i].empty()) {
                    swap_count++;
                }
            }
        }
    }
    return swap_count;
}
```

基数排序是一种非比较型整数排序算法, 其原理是将整数按位数切割成不同的数字, 然后按每个位数分别比较. 由于整数也可以表达字符串(比如名字或日期)和特定格式的浮点数, 所以基数排序也不是只能使用于整数. 

它是这样实现的: 将所有待比较数值(正整数)统一为同样的数字长度, 数字较短的数前面补零. 然后, 从最低位开始, 依次进行一次排序. 这样从最低位排序一直到最高位排序完成以后, 数列就变成一个有序序列. 

### 源文件 `SortComparison.cpp`

#### 函数 `std::pair<std::chrono::microseconds::rep, uint64_t> exec(Func f)`

```cpp
template <typename Func>
std::pair<std::chrono::microseconds::rep, uint64_t> exec(Func f)
{
    uint64_t swap_count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    swap_count = f();
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    return std::make_pair(duration, swap_count);
}
```

该函数传入一个返回值为 `uint64_t` 的函数 `f`, 执行函数 `f` 并计算函数执行所用时间, 返回值类型为 `std::pair<std::chrono::microseconds::rep, uint64_t>`, 前者为函数执行所用时间, 以微秒计算; 后者为程序的返回值.

如果执行的函数 `f` 为头文件 `SortAlgorithms.hpp` 中的任一排序函数, 则其返回值是一个由排序所用时间及排序交换次数所组成的 `std::pair`.

#### 主函数 `main()`

**随机数生成部分**

```cpp
...
#ifdef SORT_VECTOR
    std::vector<int> container(random_count);
#ifdef DEBUG
    std::cout << "sorting vector" << std::endl
              << std::endl;
#endif
#endif
#ifdef SORT_DEQUE
    std::deque<int> container(random_count);
#ifdef DEBUG
    std::cout << "sorting deque" << std::endl
              << std::endl;
#endif
#endif
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis;
    for (size_t i = 0; i < random_count; i++) {
        container[i] = dis(gen);
    }
...
```

该部分根据编译选项选择对应的容器, 生成随机数, 并存放于容器中.

**排序算法执行部分**

```cpp
...
while (true) {
    ...
    auto temp = container;  // Sort the temporary copy instead of the vector
    switch (op) {
        ...
        case $n: {
            auto result = exec([&]() -> uint64_t { return someSort(temp.begin(), temp.end()); });
            std::cout << "某种排序所用时间: \t" << result.first << " 微秒" << std::endl
                      << "某种排序交换次数: \t" << result.second << " 次" << std::endl
#ifdef DEBUG
                      << std::is_sorted(temp.begin(), temp.end())
#endif
                      << std::endl;
        } break;
        ...
    }
}
...
```

该部分每次执行时先拷贝一份随机数容器 `container`, 根据对应选项调用 `exec(Func f)` 函数执行某种排序算法, 其中 `f` 此处为一 lambda 表达式. 以引用捕获容器 `temp`, 使用某一特定的排序函数执行排序, 并返回该函数返回的排序交换次数的值. 将调用 `exec()` 的结果保存至 `result` 中, `result.first`为排序所用时间, 以微秒计算; `result.second` 为排序交换次数. 最后将数值输出

如果编译时启用了调试选项, 将会在交换次数的下一行输出一个数字. `1` 表示 `temp` 容器已经正确排序, 排序算法功能正常; `0` 则表示未正确排序.


## 运行示例

测试所用平台如下

> Hyper-V Gen2 (Windows Server 2019)
> 
> CPU: Intel Xeon E5-2660 v2 @ 4x 2.20GHz
> 
> RAM: 8192 MB
> 
> OS: Ubuntu 18.10 cosmic
> 
> Kernel: x86_64 Linux 4.18.0-1006-azure

Note: 中文字符部分平台下存在无法对齐的情况, 该问题无解

### 调试功能开, 使用 `std::vector`

```
$ ./a.out
**             排序算法比较               **
============================================
**             1 --- 冒泡排序             **
**             2 --- 选择排序             **
**             3 --- 插入排序             **
**             4 --- 希尔排序             **
**             5 --- 快速排序             **
**             6 --- 堆排序               **
**             7 --- 归并排序             **
**             8 --- 基数排序             **
**             9 --- STL排序              **
**             0 --- 退出程序             **
============================================

请输入要产生的随机数的数目: 1000

sorting vector

请选择排序算法:         1
冒泡排序所用时间:       1165 微秒
冒泡排序交换次数:       250647 次
1

请选择排序算法:         2
选择排序所用时间:       1072 微秒
选择排序交换次数:       999 次
1

请选择排序算法:         3
插入排序所用时间:       644 微秒
插入排序交换次数:       249675 次
1

请选择排序算法:         4
希尔排序所用时间:       150 微秒
希尔排序交换次数:       8897 次
1

请选择排序算法:         5
快速排序所用时间:       139 微秒
快速排序交换次数:       3064 次
1

请选择排序算法:         6
堆排序所用时间:         182 微秒
堆排序交换次数:         9547 次
1

请选择排序算法:         7
归并排序所用时间:       125 微秒
归并排序交换次数:       4932 次
1

请选择排序算法:         8
基数排序所用时间:       243 微秒
基数排序交换次数:       11903 次
1

请选择排序算法:         9
STL排序所用时间:        71 微秒
1

请选择排序算法:         0
正在退出...
```

### 调试功能关, 使用 `std::vector`

```
$ ./a.out
**             排序算法比较               **
============================================
**             1 --- 冒泡排序             **
**             2 --- 选择排序             **
**             3 --- 插入排序             **
**             4 --- 希尔排序             **
**             5 --- 快速排序             **
**             6 --- 堆排序               **
**             7 --- 归并排序             **
**             8 --- 基数排序             **
**             9 --- STL排序              **
**             0 --- 退出程序             **
============================================

请输入要产生的随机数的数目: 114514

请选择排序算法:         1
冒泡排序所用时间:       5717084 微秒
冒泡排序交换次数:       3282042177 次

请选择排序算法:         2
选择排序所用时间:       4954769 微秒
选择排序交换次数:       114513 次

请选择排序算法:         3
插入排序所用时间:       3042834 微秒
插入排序交换次数:       3282005634 次

请选择排序算法:         4
希尔排序所用时间:       31468 微秒
希尔排序交换次数:       3444419 次

请选择排序算法:         5
快速排序所用时间:       16238 微秒
快速排序交换次数:       531234 次

请选择排序算法:         6
堆排序所用时间:         28576 微秒
堆排序交换次数:         1886861 次

请选择排序算法:         7
归并排序所用时间:       6097 微秒
归并排序交换次数:       948101 次

请选择排序算法:         8
基数排序所用时间:       15962 微秒
基数排序交换次数:       1374071 次

请选择排序算法:         9
STL排序所用时间:        15609 微秒

请选择排序算法:         0
正在退出...
```

### 调试功能关, 使用 `std::deque`

```
$ ./a.out
**             排序算法比较               **
============================================
**             1 --- 冒泡排序             **
**             2 --- 选择排序             **
**             3 --- 插入排序             **
**             4 --- 希尔排序             **
**             5 --- 快速排序             **
**             6 --- 堆排序               **
**             7 --- 归并排序             **
**             8 --- 基数排序             **
**             9 --- STL排序              **
**             0 --- 退出程序             **
============================================

请输入要产生的随机数的数目: 114514

请选择排序算法:         1
冒泡排序所用时间:       10352401 微秒
冒泡排序交换次数:       3270036773 次

请选择排序算法:         2
选择排序所用时间:       7813161 微秒
选择排序交换次数:       114513 次

请选择排序算法:         3
插入排序所用时间:       6395844 微秒
插入排序交换次数:       3270015721 次

请选择排序算法:         4
希尔排序所用时间:       31753 微秒
希尔排序交换次数:       3545911 次

请选择排序算法:         5
快速排序所用时间:       17125 微秒
快速排序交换次数:       521821 次

请选择排序算法:         6
堆排序所用时间:         20408 微秒
堆排序交换次数:         1887142 次

请选择排序算法:         7
归并排序所用时间:       17645 微秒
归并排序交换次数:       948101 次

请选择排序算法:         8
基数排序所用时间:       28495 微秒
基数排序交换次数:       1374071 次

请选择排序算法:         9
STL排序所用时间:        14608 微秒

请选择排序算法:         0
正在退出...
```

## 结论

冒泡排序在算法上实现最为简便, 而快速排序通常速度最快. 选择排序的交换次数最少, 适合数据不大的时候使用. STL排序调用最为简便, 且效率也较高.

容器类型的不同也导致了排序算法的耗时有较大区别. 示例中大部分排序算法对 `std::deque` 的排序时间明显比对 `std::vector` 的排序来的长. 而STL排序在不同容器下表现类似.

综上所述, 对于C++而言, 调用STL的 `std::sort` 或 `std::stable_sort` (稳定排序) 函数是在排序上最优的选择. 不要重复发明轮子.