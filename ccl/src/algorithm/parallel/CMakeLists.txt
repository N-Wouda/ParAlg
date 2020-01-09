cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		stepdeterminecomponents.c
		stepdeterminesharedcomponents.c
		labelandsendboundary.c
		stepreceiveandwritesegments.c
		stepsendmatrices.c
		returnlabelledsegments.c)

add_library(parallel ${SOURCE_FILES})
target_link_libraries(parallel
		component
		algorithm
		segment
		io)
