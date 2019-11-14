cmake_minimum_required(VERSION 3.2)

find_path(unity_path
		NAMES unity.h)

if (NOT unity_path)
	message("-- Could not find Unity! Tests are unavailable.")
else()
	# TODO: Add tests
endif()
