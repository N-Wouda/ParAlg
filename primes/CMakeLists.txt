cmake_minimum_required(VERSION 3.14)

project(Primes VERSION 1.0)

set(CMAKE_C_STANDARD 11)
add_definitions(-Wall -O2)

set(PRIMES_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PRIMES_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PRIMES_INSTALL_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
