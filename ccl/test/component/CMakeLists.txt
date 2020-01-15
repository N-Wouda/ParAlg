cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		main.c
		test_findset.c
		test_isroot.c
		test_labelsegments.c
		test_makecomponents.c
		test_makesets.c
		test_merge.c)

add_executable(test_component ${SOURCE_FILES})

target_link_libraries(test_component component unity)
