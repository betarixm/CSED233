cmake_minimum_required(VERSION 3.15)
project(CSED233)

set(CMAKE_CXX_STANDARD 11)

add_executable(ASSN1 ASSN/ASSN1/pa1.cpp ASSN/ASSN1/utils.cpp)
add_executable(EVAL1 ASSN/ASSN1/evaluate.cpp)