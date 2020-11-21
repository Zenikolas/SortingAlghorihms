cmake_minimum_required(VERSION 3.17)
project(sorting-algorithms)

set(CMAKE_CXX_STANDARD 14)

enable_testing()
find_package(GTest REQUIRED)

add_executable(quickSort quickSort.cpp mergeSort.cpp bubbleSort.cpp selectionSort.cpp)
target_link_libraries(quickSort GTest::GTest GTest::Main)

gtest_discover_tests(quickSort)