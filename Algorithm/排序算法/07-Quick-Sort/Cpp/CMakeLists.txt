cmake_minimum_required(VERSION 3.20)
project(QuickSort)

set(CMAKE_CXX_STANDARD 14)

add_executable(QuickSort main.cpp)


# 修改clion 内存
MATH(EXPR stack_size "100000000")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")