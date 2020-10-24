cmake_minimum_required(VERSION 3.15)
project(cp_prog)

set(CMAKE_CXX_STANDARD 11)


add_executable(cp_prog tinkoff2020/distur3/D.cpp)
add_compile_definitions(LOCAL)