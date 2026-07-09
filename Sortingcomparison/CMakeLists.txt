cmake_minimum_required(VERSION 3.10)

project(SortingComparison)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(SortingComparison
    src/main.cpp
    src/BubbleSort.cpp
    src/MergeSort.cpp
    src/QuickSort.cpp
)

add_executable(RunTests
    test/test.cpp
    src/BubbleSort.cpp
    src/MergeSort.cpp
    src/QuickSort.cpp
)