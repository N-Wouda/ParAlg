cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		computesegments.c
		countsegments.c
		segment.c)

add_library(segment
		SHARED STATIC ${SOURCE_FILES})
