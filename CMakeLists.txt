cmake_minimum_required(VERSION 3.15)
project(CSED233)

set(CMAKE_CXX_STANDARD 11)

add_executable(ASSN1 ASSN/ASSN1/pa1.cpp ASSN/ASSN1/utils.cpp)
add_executable(EVAL1 ASSN/ASSN1/evaluate.cpp)

add_executable(TEST test.cpp)
add_executable(ASSN2 ASSN/ASSN2/pa2.cpp ASSN/ASSN2/utils.cpp ASSN/ASSN2/tree.cpp ASSN/ASSN2/heap.cpp)
add_executable(EVAL2 ASSN/ASSN2/chck/evaluate.cpp)

FILE(GLOB ASSN3_CPP ASSN/ASSN3/*.cpp)
add_executable(ASSN3 ${ASSN3_CPP})

FILE(GLOB ASSN4_H ASSN/ASSN4/*.h)
FILE(GLOB ASSN4_CPP ASSN/ASSN4/*.cpp)
add_executable(ASSN4 ${ASSN4_CPP} ${ASSN4_H})


FILE(GLOB ASSN5_H ASSN/ASSN5/*.h)
FILE(GLOB ASSN5_CPP ASSN/ASSN5/*.cpp)
add_executable(ASSN5 ${ASSN5_CPP} ${ASSN5_H})