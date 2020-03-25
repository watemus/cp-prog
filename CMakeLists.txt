cmake_minimum_required(VERSION 3.15)
project(cp_prog)

set(CMAKE_CXX_STANDARD 17)

add_executable(cp_prog cf162/D1B.cpp)
add_compile_definitions(LOCAL)