#include <gtest/gtest.h>
#include <gmock/gmock-generated-matchers.h>

#include <algorithm>

#include "Util.h"

void merge(int* arr, size_t mid, size_t size) { // 1 1 3 mid 1 size 3 // 2 5 7 3
    int input[size];// 1 1 3 // 2 5 3 7
    std::copy(arr, arr + size, input);

    int* left = input; //1 // 1    // 2       // 5
    int* right = input + mid; // 1 // 3       // 7
    int* right_end = input + size; // after 7
    int* left_end = right;  // 1   // 3
    int* current = arr; // 1       // 2       // 3 // 5
    while (left < left_end && right < right_end) {
        if (*left <= *right) {
            *current = *left;
            ++left;
        } else {
            *current = *right;
            ++right;
        }
        ++current;
    }

    if (left < left_end) {
        std::copy(left, left_end, current);
    }

    if (right < right_end) {
        std::copy(right, right_end, current);
    }
}

// 1 3 1 2 5 7 3 // 2 5 7 3
void mergeSort(int* arr, size_t size) { // 7 // 3 // 4
    if (size < 2) {
        return;
    }

    if (size == 2) {
        if (arr[1] < arr[0]) {
            std::swap(arr[0], arr[1]);
        }
        return;
    }

    size_t mid = size / 2; // 3 // 1
    mergeSort(arr, mid);
    mergeSort(arr + mid, size - mid); // 3,1 -> 1,3 //
    merge(arr, mid, size);
}

template<class T>
void print(T* arr, size_t N) {
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

void mergeSortNoRecursive(int* arr, size_t size) {
    if (size < 2) {
        return;
    }

    if (size == 2) {
        if (arr[1] < arr[0]) {
            std::swap(arr[0], arr[1]);
        }
        return;
    }

    size_t currentStep = 1;
    while (2 * currentStep < size) {
        size_t i = 0;
        while (i + currentStep < size) {
            size_t currentSize = 2 * currentStep;
            if (i + currentSize >=  size) {
                currentSize = size - i;
            }

            merge(arr + i, currentStep, currentSize);
            i += currentSize;
        }

        currentStep *= 2;
    }

    if (currentStep < size) {
        merge(arr, currentStep, size);
    }
}

TEST(MergeSortTest, simpleTest) {
    int arr[] = {1, 4, 4, 8, 3, 4, 6, 7, 4, 4, 2};
    int expected_arr[] = {1, 2, 3, 4, 4, 4, 4, 4, 6, 7, 8};
    print(arr);
    mergeSort(arr, sizeof(arr) / sizeof(int));
    print(arr);
    ASSERT_THAT(arr, ::testing::ElementsAreArray(expected_arr));
}

TEST(MergeSortTestNotRecursive, simpleTest) {
    int arr[] = {1, 4, 4, 8, 3, 4, 6, 7, 4, 4, 2};
    int expected_arr[] = {1, 2, 3, 4, 4, 4, 4, 4, 6, 7, 8};
    print(arr);
    mergeSortNoRecursive(arr, sizeof(arr) / sizeof(int));
    print(arr);
    ASSERT_THAT(arr, ::testing::ElementsAreArray(expected_arr));
}

