cmake_minimum_required(VERSION 3.2)

find_package(BSP REQUIRED)

add_subdirectory(algorithm)
add_subdirectory(component)
add_subdirectory(segment)
add_subdirectory(io)

set(SOURCE_FILES
		main.c)

add_executable(ccl ${SOURCE_FILES})

target_link_libraries(ccl
		algorithm
		${BSP}
		pthread)
