cmake_minimum_required(VERSION 3.2)

add_subdirectory(parallel)

set(SOURCE_FILES
		main.c
		test_sequential.c)

add_executable(test_algorithm ${SOURCE_FILES})

target_link_libraries(test_algorithm algorithm io unity testtools)
