#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <vector>
#include "SortAlgorithms.hpp"

#define SORT_VECTOR
#ifdef SORT_DEQUE
#undef SORT_VECTOR
#endif

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

int main()
{
    std::cout << "**             排序算法比较               **" << std::endl
              << "============================================" << std::endl
              << "**             1 --- 冒泡排序             **" << std::endl
              << "**             2 --- 选择排序             **" << std::endl
              << "**             3 --- 插入排序             **" << std::endl
              << "**             4 --- 希尔排序             **" << std::endl
              << "**             5 --- 快速排序             **" << std::endl
              << "**             6 --- 堆排序               **" << std::endl
              << "**             7 --- 归并排序             **" << std::endl
              << "**             8 --- 基数排序             **" << std::endl
              << "**             9 --- STL排序              **" << std::endl
              << "**             0 --- 退出程序             **" << std::endl
              << "============================================" << std::endl
              << std::endl
              << "请输入要产生的随机数的数目：";

    size_t random_count;
    while (true) {
        std::cin >> random_count;
        if (std::cin.good()) {
            break;
        }
        else {
            std::cout << "输入有误，请重新输入：";
        }
        std::cin.ignore(INT32_MAX, '\n');
    }
    std::cout << std::endl;

    // Generate array of random numbers
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

    while (true) {
        int op;
        std::cout << "请选择排序算法：\t";
        std::cin >> op;
        if (!std::cin.good()) {
            std::cin.clear();
            op = -1;  // Set op to -1 to get a warning
        }
        std::cin.ignore(INT32_MAX, '\n');

        auto temp = container;  // Sort the temporary copy instead of the vector
        switch (op) {
            case 1: {
                auto result = exec([&]() -> uint64_t { return bubbleSort(temp.begin(), temp.end()); });
                std::cout << "冒泡排序所用时间：\t" << result.first << " 微秒" << std::endl
                          << "冒泡排序交换次数：\t" << result.second << " 次" << std::endl
#ifdef DEBUG
                          << std::is_sorted(temp.begin(), temp.end()) << std::endl
#endif
                          << std::endl;
            } break;

            case 2: {
                auto result = exec([&]() -> uint64_t { return selectionSort(temp.begin(), temp.end()); });
                std::cout << "选择排序所用时间：\t" << result.first << " 微秒" << std::endl
                          << "选择排序交换次数：\t" << result.second << " 次" << std::endl
#ifdef DEBUG
                          << std::is_sorted(temp.begin(), temp.end()) << std::endl
#endif
                          << std::endl;
            } break;

            case 3: {
                auto result = exec([&]() -> uint64_t { return insertionSort(temp.begin(), temp.end()); });
                std::cout << "插入排序所用时间：\t" << result.first << " 微秒" << std::endl
                          << "插入排序交换次数：\t" << result.second << " 次" << std::endl
#ifdef DEBUG
                          << std::is_sorted(temp.begin(), temp.end()) << std::endl
#endif
                          << std::endl;
            } break;

            case 4: {
                auto result = exec([&]() -> uint64_t { return shellSort(temp.begin(), temp.end()); });
                std::cout << "希尔排序所用时间：\t" << result.first << " 微秒" << std::endl
                          << "希尔排序交换次数：\t" << result.second << " 次" << std::endl
#ifdef DEBUG
                          << std::is_sorted(temp.begin(), temp.end()) << std::endl
#endif
                          << std::endl;
            } break;

            case 5: {
                auto result = exec([&]() -> uint64_t { return quickSort(temp.begin(), temp.end()); });
                std::cout << "快速排序所用时间：\t" << result.first << " 微秒" << std::endl
                          << "快速排序交换次数：\t" << result.second << " 次" << std::endl
#ifdef DEBUG
                          << std::is_sorted(temp.begin(), temp.end()) << std::endl
#endif
                          << std::endl;
            } break;

            case 6: {
                auto result = exec([&]() -> uint64_t { return heapSort(temp.begin(), temp.end()); });
                std::cout << "堆排序所用时间：\t" << result.first << " 微秒" << std::endl
                          << "堆排序交换次数：\t" << result.second << " 次" << std::endl
#ifdef DEBUG
                          << std::is_sorted(temp.begin(), temp.end()) << std::endl
#endif
                          << std::endl;
            } break;

            case 7: {
                auto result = exec([&]() -> uint64_t { return mergeSort(temp.begin(), temp.end()); });
                std::cout << "归并排序所用时间：\t" << result.first << " 微秒" << std::endl
                          << "归并排序交换次数：\t" << result.second << " 次" << std::endl
#ifdef DEBUG
                          << std::is_sorted(temp.begin(), temp.end()) << std::endl
#endif
                          << std::endl;
            } break;

            case 8: {
                auto result = exec([&]() -> uint64_t { return radixSort(temp.begin(), temp.end()); });
                std::cout << "基数排序所用时间：\t" << result.first << " 微秒" << std::endl
                          << "基数排序交换次数：\t" << result.second << " 次" << std::endl
#ifdef DEBUG
                          << std::is_sorted(temp.begin(), temp.end()) << std::endl
#endif
                          << std::endl;
            } break;

            case 9: {
                auto result = exec([&]() -> uint64_t { std::sort(temp.begin(), temp.end()); return 0; });
                std::cout << "STL排序所用时间：\t" << result.first << " 微秒" << std::endl
#ifdef DEBUG
                          << std::is_sorted(temp.begin(), temp.end()) << std::endl
#endif
                          << std::endl;
            } break;

            case 0:
                std::cout << "正在退出..." << std::endl;
                return 0;

            default:
                std::cout << "输入有误，请重新输入" << std::endl;
                continue;
        }
    }

    return 0;
}