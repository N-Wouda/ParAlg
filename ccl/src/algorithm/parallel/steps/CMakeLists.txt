cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		sendmatrices.c
		computelabels.c)

add_library(steps ${SOURCE_FILES})
target_link_libraries(steps
		component
		segment
		io)
