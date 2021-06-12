cmake_minimum_required(VERSION 3.10)
project(Simplexer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Simplexer INTERFACE)

target_include_directories(Simplexer INTERFACE include/)

add_subdirectory(test)
