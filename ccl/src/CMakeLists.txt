cmake_minimum_required(VERSION 3.2)

add_subdirectory(segment)

set(SOURCE_FILES
		arguments.c
		main.c
		readmatrix.c)

add_executable(ccl ${SOURCE_FILES})
target_link_libraries(ccl segment)
