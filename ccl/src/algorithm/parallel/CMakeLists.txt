cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		determinecomponents.c
		determinelabels.c
		sendmatrices.c)

add_library(parallel ${SOURCE_FILES})
target_link_libraries(parallel
		component
		algorithm
		segment
		io)
