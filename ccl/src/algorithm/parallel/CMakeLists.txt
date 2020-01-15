cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		determinesegmentslice.c
		getowningprocessor.c
		labelboundary.c
		receivesegments.c
		stepdeterminecomponents.c
		stepdeterminesharedcomponents.c
		stepreceiveandwritesegments.c
		stepsendsegments.c
		stepreturnlabelledsegments.c)

add_library(parallel ${SOURCE_FILES})
target_link_libraries(parallel
		component
		algorithm
		segment
		io)
