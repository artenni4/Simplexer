cmake_minimum_required(VERSION 3.10)
project(Simplexer)

set(CMAKE_CXX_STANDARD 17)

add_library(${CMAKE_PROJECT_NAME} INTERFACE)

target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE include/)

add_subdirectory(test)
