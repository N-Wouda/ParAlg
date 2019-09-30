cmake_minimum_required(VERSION 3.2)

project(Primes VERSION 1.0)

set(CMAKE_C_STANDARD 11)

add_definitions(-Wall -O2)

find_library(bsp REQUIRED)

if (NOT bsp)
	message("Could not find BSP! Attempting to recover..")

	find_path(bsp_path
			NAMES bsp.h
			PATHS ~/MulticoreBSP-for-C/
			NO_DEFAULT_PATH)

	if (bsp_path)
		message("Recovered.")

		include_directories(${bsp_path}/include)

		find_library(bsp REQUIRED
				NAMES libmcbsp2.0.4.a
				PATHS ${bsp_path}/lib)
	else()
		message("Could not recover.")
	endif()
endif()

add_executable(main
		src/main.c
		src/sieve.c
		src/bspsieve.c
		src/boundedsieve.c
		src/utils/countprimes.c
		src/utils/getprimes.c
		src/utils/init.c
		src/utils/unmark.c)

# TODO: Include a separate test target?

# Source directories
target_include_directories(main
		PRIVATE "src")

# This is needed for BSPLib to work properly
target_link_libraries(main
		${bsp}
		pthread
		m)
