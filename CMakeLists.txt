cmake_minimum_required(VERSION 3.10)

project(Simplexer)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES test/main.cpp test/asttimer.hpp Simplexer.hpp Simplexer.cpp)

add_executable(Simplexer ${SOURCES})
