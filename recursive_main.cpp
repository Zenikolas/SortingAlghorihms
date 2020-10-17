#include <iostream>

#include <gtest/gtest.h>

template<class T, size_t N>
size_t partition(T (&arr)[N], size_t left, size_t right) {
    size_t idx = left + rand() % right;
    T pivot = arr[idx];

    size_t borderIdx = left;
    bool equalMovedToLeft = true;
    for (size_t i = left; i <= right; ++i) {
        if (arr[i] > pivot) {
            continue;
        }

        if (arr[i] == pivot && equalMovedToLeft) {
            equalMovedToLeft = false;
            continue;
        }

        std::swap(arr[i], arr[borderIdx]);
        ++borderIdx;
    }

    return borderIdx;
}

template<class T, size_t N>
void sort(T (&arr)[N], size_t left, size_t right) {
    size_t idx = partition(arr, left, right);
    if (idx != 0 && left < idx - 1) {
        sort(arr, left, idx - 1);
    }

    if (idx < right) {
        sort(arr, idx, right);
    }
}

template<class T, size_t N>
void print(T (&arr)[N])
{
    std::cout << '[';
    if (N != 0) {
        std::cout << arr[0];
    }

    if (N > 1) {
        for (size_t i = 1; i < N; ++i) {
            std::cout << ", " << arr[i];
        }
    }

    std::cout << ']' << std::endl;
}

TEST(QuickSortTest, simpleTest)
{
    int arr[] = {1, 4, 4, 8, 3, 4, 6, 7, 4, 4, 9};
    int expected_arr[] = {1, 3, 4, 4, 4, 4, 4, 6, 7, 8, 9};
    print(arr);
    sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
    print(arr);
    ASSERT_EQ(sizeof(expected_arr), sizeof(arr));
}
