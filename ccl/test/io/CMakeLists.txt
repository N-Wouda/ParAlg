cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		main.c)

add_executable(test_io ${SOURCE_FILES})

target_link_libraries(test_io io unity)
