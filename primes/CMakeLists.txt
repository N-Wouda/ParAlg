cmake_minimum_required(VERSION 3.14)

project(Primes VERSION 1.0)

set(CMAKE_C_STANDARD 11)

add_definitions(-Wall)
add_executable(main
		src/primes.c
		src/sieve.c)

# Source directories
target_include_directories(main
		PRIVATE "external"
		PRIVATE "src")

# This is needed for BSPLib to work properly
target_link_libraries(main
		${CMAKE_SOURCE_DIR}/lib/libmcbsp2.0.4.a
		pthread
		rt)
