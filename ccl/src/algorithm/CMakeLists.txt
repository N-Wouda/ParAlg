cmake_minimum_required(VERSION 3.2)

add_subdirectory(parallel)

set(SOURCE_FILES
		parallel.c
		sequential.c)

add_library(algorithm ${SOURCE_FILES})
target_link_libraries(algorithm
		component
		segment
		io
		parallel)
