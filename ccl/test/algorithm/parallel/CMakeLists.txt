cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		main.c
		test_determinesegmentslice.c
		test_getowningprocessor.c
		test_labelboundary.c)

add_executable(test_parallel ${SOURCE_FILES})

target_link_libraries(test_parallel parallel io unity)
