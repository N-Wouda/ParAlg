cmake_minimum_required(VERSION 3.14)

set(SOURCE_FILES
		main.c
		test_countprimes.c
		test_getprimes.c
		test_oddcount.c
		test_unmark.c)

add_executable(test_utils ${SOURCE_FILES})

target_link_libraries(test_utils utils unity)
