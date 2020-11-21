#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-generated-matchers.h>

#include "Util.h"

template<class T, size_t N>
size_t partition(T (&arr)[N], size_t left, size_t right) {
    if (left == right) {
        return left;
    }

    size_t idx = left + rand() % (right + 1 - left);
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

#define TRACE
static int DEPTH = 0;

void traceRecursionDepth()
{
#ifdef TRACE
    std::cout << DEPTH++ << std::endl;
#endif
}

template<class T, size_t N>
void sortImpl(T (&arr)[N], size_t left, size_t right) {
    traceRecursionDepth();

    size_t idx = partition(arr, left, right);
    if (idx != 0 && left < idx - 1) {
        sortImpl(arr, left, idx - 1);
    }

    if (idx < right) {
        sortImpl(arr, idx, right);
    }
}

template<class T, size_t N>
void sort(T (&arr)[N]) {
    if (N < 2) {
        return;
    }

    sortImpl(arr, 0, N - 1);
}

template<class T, size_t N>
void sortNotReqursiveImpl(T (&arr)[N], size_t left, size_t right) {
    traceRecursionDepth();

    while (left < right) {
        size_t idx = partition(arr, left, right);
        size_t left_distance = idx - left;
        size_t right_distance = right - idx;

        if (idx != 0 && left < idx - 1 && left_distance < right_distance) {
            sortNotReqursiveImpl(arr, left, idx - 1);
        }

        if (idx < right && right_distance <= left_distance) {
            sortNotReqursiveImpl(arr, idx, right);
        }

        if (left_distance < right_distance) {
            left = idx;

        } else {
            right = idx - 1;
        }
    }

}

template<class T, size_t N>
void sortNotReqursive(T (&arr)[N]) {
    if (N < 2) {
        return;
    }

    sortNotReqursiveImpl(arr, 0, N - 1);
}

TEST(QuickSortTest, simpleTest)
{
    int arr[] = {1, 4, 4, 8, 3, 4, 6, 7, 4, 4, 9};
    int expected_arr[] = {1, 3, 4, 4, 4, 4, 4, 6, 7, 8, 9};
    print(arr);
    sort(arr);
    print(arr);
    ASSERT_THAT(arr, ::testing::ElementsAreArray(expected_arr));
}

TEST(NotReqursiveQuickSortTest, simpleTest)
{
    int arr[] = {1, 4, 4, 8, 3, 4, 6, 7, 4, 4, 9};
    int expected_arr[] = {1, 3, 4, 4, 4, 4, 4, 6, 7, 8, 9};
    print(arr);
    DEPTH = 0;
    sortNotReqursive(arr);
    print(arr);
    ASSERT_THAT(arr, ::testing::ElementsAreArray(expected_arr));
}
