#include <gtest/gtest.h>
#include <gmock/gmock-generated-matchers.h>

#include "Util.h"

size_t findMaxIdx(int* arr, size_t left, size_t right) {
    size_t ret = left;
    int max = arr[left];

    for (size_t i = left + 1; i <= right; ++i) {
        if (arr[i] > max) {
            max = arr[i];
            ret = i;
        }
    }

    return ret;
}

template <size_t N> void selectionSort(int (&arr)[N]) {
    if (N < 2) {
        return;
    }

    for (size_t i = 0; i < N - 1; ++i) {
        size_t rightCurrentIdx = N - 1 - i;
        size_t  maxIdx = findMaxIdx(arr, 0, rightCurrentIdx);
        if (maxIdx != rightCurrentIdx) {
            std::swap(arr[maxIdx], arr[rightCurrentIdx]);
        }
    }
}

TEST(SelectionSortTest, simpleTest) {
    int arr[] = {1, 4, 4, 8, 3, 4, 6, 7, 4, 4, 2};
    int expected_arr[] = {1, 2, 3, 4, 4, 4, 4, 4, 6, 7, 8};
    print(arr);
    selectionSort(arr);
    print(arr);
    ASSERT_THAT(arr, ::testing::ElementsAreArray(expected_arr));
}
