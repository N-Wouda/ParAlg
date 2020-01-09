cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		findset.c
		isroot.c
		labelsegments.c
		link.c
		makecomponents.c
		merge.c)

add_library(component ${SOURCE_FILES})
target_link_libraries(component segment)
