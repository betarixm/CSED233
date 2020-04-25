cmake_minimum_required(VERSION 3.15)
project(CSED233)

set(CMAKE_CXX_STANDARD 11)

add_executable(ASSN1 ASSN/ASSN1/pa1.cpp ASSN/ASSN1/utils.cpp)
add_executable(EVAL1 ASSN/ASSN1/evaluate.cpp)

add_executable(TEST test.cpp)
add_executable(ASSN2 ASSN/ASSN2/pa2.cpp ASSN/ASSN2/utils.cpp ASSN/ASSN2/tree.cpp ASSN/ASSN2/heap.cpp)