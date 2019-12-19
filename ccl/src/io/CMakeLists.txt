cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		readmatrix.c
		writesegments.c
		parsearguments.c)

add_library(io ${SOURCE_FILES})
