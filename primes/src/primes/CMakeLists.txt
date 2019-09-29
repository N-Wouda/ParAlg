cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		boundedsieve.c
		bspsieve.c
		sieve.c)

add_library(primes_lib
		SHARED STATIC ${SOURCE_FILES})

target_link_libraries(primes_lib m utils_lib)
