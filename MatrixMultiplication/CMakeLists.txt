cmake_minimum_required(VERSION 3.10)

project(MatrixMultiplication)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable optimizations by default so the timing comparison is meaningful
# (an unoptimized build would make every loop order look equally slow).
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Tell the compiler where to find header files
include_directories(include)

# --------------------------------------
# Main executable: MatrixMultiplication
# --------------------------------------
add_executable(MatrixMultiplication
    src/main.cpp
    src/ijk.cpp
    src/ikj.cpp
    src/jik.cpp
    src/jki.cpp
    src/kij.cpp
    src/kji.cpp
)