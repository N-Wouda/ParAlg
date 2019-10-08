cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		main.c
		test_blockbounds.c
		test_countprimes.c
		test_getprimes.c
		test_candidatecount.c
		test_unmark.c)

add_executable(test_utils ${SOURCE_FILES})

target_link_libraries(test_utils utils unity)
