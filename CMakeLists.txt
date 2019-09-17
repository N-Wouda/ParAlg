cmake_minimum_required(VERSION 3.14)

project(ParAlg VERSION 1.0)

set(CMAKE_C_STANDARD 99)

add_definitions(-Wall)
add_executable(main
		src/test.c
		src/process.c)

# Source directories
target_include_directories(main
		PRIVATE "src/bsp"
		PRIVATE "src")

# This is needed for BSPLib to work properly
target_link_libraries(main
		${CMAKE_SOURCE_DIR}/src/lib/libmcbsp2.0.4.a
		pthread
		rt)
