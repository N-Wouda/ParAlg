cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		computesegments.c
		countsegments.c
		isbefore.c
		isequal.c
		isnewsegment.c
		makesegment.c
		hasoverlap.c
		segcoordcmp.c
		seglabelcmp.c
		segprint.c
		segtotalcmp.c)

add_library(segment ${SOURCE_FILES})
