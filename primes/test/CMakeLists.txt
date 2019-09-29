cmake_minimum_required(VERSION 3.2)

find_library(unity REQUIRED)

if (NOT unity)
	message("Could not find Unity!")
endif()

add_subdirectory(primes)
add_subdirectory(utils)
