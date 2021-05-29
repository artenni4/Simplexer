cmake_minimum_required(VERSION 3.10)

set(BINARY ${CMAKE_PROJECT_NAME}_test)
set(SOURCES main.cpp asttimer.hpp)


add_executable(${BINARY} ${SOURCES})


target_include_directories(${BINARY} 
	PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>/include
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)


add_test(NAME ${BINARY} COMMAND ${BINARY})
