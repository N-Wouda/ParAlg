cmake_minimum_required(VERSION 3.2)

find_package(Unity)

if (Unity)
	include_directories(testtools)

	add_subdirectory(algorithm)
	add_subdirectory(component)
	add_subdirectory(io)
	add_subdirectory(segment)

	add_subdirectory(testtools)
else()
	message("-- Could not find Unity! Tests are unavailable.")
endif()
