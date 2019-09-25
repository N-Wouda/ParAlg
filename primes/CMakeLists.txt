cmake_minimum_required(VERSION 3.14)

project(Primes VERSION 1.0)

set(CMAKE_C_STANDARD 11)

add_definitions(-Wall -O2)

add_executable(main
		src/main.c
		src/sieve.c
		src/bspsieve.c
		src/boundedsieve.c
		src/utils/countprimes.c
		src/utils/getprimes.c
		src/utils/init.c
		src/utils/unmark.c)

# TODO: Include a separate test target

# Source directories
target_include_directories(main
		PRIVATE "external"
		PRIVATE "src")

# This is needed for BSPLib to work properly
target_link_libraries(main
		${CMAKE_SOURCE_DIR}/lib/libmcbsp2.0.4.a
		pthread
		rt
		m)
