add_executable(TestSimplexer test_all.cpp)
add_executable(PrintTokenizedFile test_file.cpp)


target_include_directories(TestSimplexer 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

target_include_directories(PrintTokenizedFile 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)


add_test(NAME TestSimplexer COMMAND TestSimplexer)
add_test(NAME PrintTokenizedFile COMMAND PrintTokenizedFile)