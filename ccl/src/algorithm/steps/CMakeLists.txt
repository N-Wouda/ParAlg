cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		receivesegments.c
		stepdeterminecomponents.c
		stepdeterminesharedcomponents.c
		stepreceiveandwritesegments.c
		stepsendsegments.c
		stepreturnlabelledsegments.c)

add_library(steps ${SOURCE_FILES})
target_link_libraries(steps
		component
		algorithm
		segment
		io)
