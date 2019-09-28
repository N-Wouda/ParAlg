cmake_minimum_required(VERSION 3.14)

# TODO give this something to do. Maybe use CUnit?
set(SOURCE_FILES main.c)

add_executable(test ${SOURCE_FILES})

target_link_libraries(test)
