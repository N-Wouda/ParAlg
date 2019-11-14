cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		arguments.c
		main.c
		readmatrix.c)

add_executable(ccl ${SOURCE_FILES})
