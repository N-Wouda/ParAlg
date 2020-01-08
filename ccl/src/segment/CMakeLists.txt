cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		computesegments.c
		countsegments.c
		isbefore.c
		isequal.c
		isnewsegment.c
		makesegment.c)

add_library(segment ${SOURCE_FILES})
