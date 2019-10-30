cmake_minimum_required(VERSION 3.2)

project(Cat
		VERSION 1.0
		LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_definitions(-Wall)

if(CMAKE_BUILD_TYPE MATCHES RELEASE)
	add_definitions(-O3)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)
