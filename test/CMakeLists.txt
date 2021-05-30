add_executable(TestAll main.cpp)
add_executable(PrintTokenizedFile test_file.cpp)


target_include_directories(TestAll 
	PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>/include
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

target_include_directories(PrintTokenizedFile 
	PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>/include
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)


add_test(NAME TestAll COMMAND TestAll)
add_test(NAME PrintTokenizedFile COMMAND PrintTokenizedFile)