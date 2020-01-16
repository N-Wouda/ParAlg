cmake_minimum_required(VERSION 3.2)

add_subdirectory(parallel)
add_subdirectory(steps)

set(SOURCE_FILES
		parallel.c
		sequential.c)

add_library(algorithm ${SOURCE_FILES})
target_link_libraries(algorithm
		parallel
		steps)
