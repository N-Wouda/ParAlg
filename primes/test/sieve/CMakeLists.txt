cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		main.c
		test_boundedsieve.c
		test_sieve.c)

add_executable(test_sieve ${SOURCE_FILES})

target_link_libraries(test_sieve sieve unity)
