#include <gtest/gtest.h>
#include <gmock/gmock-generated-matchers.h>

#include "Util.h"

template <size_t N> void bubbleSort(int (&arr)[N]) {
    for (size_t k = N - 1; k > 0; --k) {
        bool swapped = false;
        for (size_t i = 0; i < k; ++i) {
            if (arr[i + 1] < arr[i]) {
                swapped = true;
                std::swap(arr[i], arr[i + 1]);
            }
        }

        if (!swapped) {
            std::cout << "already sorted on " << N - k << " iteration!" << std::endl;
            break;
        } else {
            swapped = false;
        }
    }
}


TEST(BubbleSortTest, simpleTest) {
    int arr[] = {1, 4, 4, 8, 3, 4, 6, 7, 4, 4, 2};
    int expected_arr[] = {1, 2, 3, 4, 4, 4, 4, 4, 6, 7, 8};
    print(arr);
    bubbleSort(arr);
    print(arr);
    ASSERT_THAT(arr, ::testing::ElementsAreArray(expected_arr));
}