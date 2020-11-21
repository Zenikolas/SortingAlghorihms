#pragma once

#include <iostream>

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
