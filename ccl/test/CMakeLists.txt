cmake_minimum_required(VERSION 3.2)

find_package(Unity REQUIRED)

add_definitions(-DTEST)

add_subdirectory(algorithm)
add_subdirectory(component)
add_subdirectory(segment)
