cmake_minimum_required(VERSION 3.17)
project(QuickSort)

set(CMAKE_CXX_STANDARD 14)

enable_testing()
find_package(GTest REQUIRED)

add_executable(QuickSort recursive_main.cpp)
target_link_libraries(QuickSort GTest::GTest GTest::Main)

add_test(QuickSortTest QuickSort)