cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		comparesegmentcoords.c
		getexamplesegments.c)

add_library(testtools ${SOURCE_FILES})
target_link_libraries(testtools segment io component unity)
