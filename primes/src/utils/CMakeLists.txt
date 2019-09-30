cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		blockbounds.c
		countprimes.c
		getprimes.c
		init.c
		oddcount.c
		unmark.c)

add_library(utils
		SHARED STATIC ${SOURCE_FILES})
