cmake_minimum_required(VERSION 3.14)

add_subdirectory(primes)
add_subdirectory(utils)

set(SOURCE_FILES main.c)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main primes)
