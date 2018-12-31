// Sorting Algorithms
// Elements will be compared using operator< by default

#pragma once
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

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

/*
template <typename Iter>
uint64_t heapSort(Iter begin, Iter end)
{
    uint64_t swap_count = 0;
    std::make_heap(begin, end);
    std::sort_heap(begin, end);
    return swap_count;
}
*/

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

/*
template <typename Iter>
uint64_t mergeSort(Iter begin, Iter end)
{
    uint64_t swap_count = 0;
    if (last - first> 1) {
        auto middle =  first + (last - first) / 2;
        merge_sort(begin, middle, cmp);
        merge_sort(middle, end, cmp);
        std::inplace_merge(begin, middle, end);
    }
    return swap_count;
}
*/

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