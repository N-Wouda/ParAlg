cmake_minimum_required(VERSION 3.2)

# TODO all this library finding should be moved to a separate function.
find_library(bsp REQUIRED
		NAMES libbsp.a libbsp)

if (NOT bsp)
	message("-- Could not find BSP! Attempting to recover..")

	find_path(bsp_path
			NAMES bsp.h
			PATHS ~/MulticoreBSP-for-C/
			NO_DEFAULT_PATH)

	if (bsp_path)
		message("-- Recovered.")

		include_directories(${bsp_path}/include)

		find_library(bsp REQUIRED
				NAMES libmcbsp2.0.4.a
				PATHS ${bsp_path}/lib)
	else()
		message("-- Could not recover.")
	endif()
endif()

add_subdirectory(component)
add_subdirectory(segment)
add_subdirectory(sparse)

set(SOURCE_FILES
		main.c
		arguments.c)

add_executable(ccl ${SOURCE_FILES})

target_link_libraries(ccl sparse segment component ${bsp} pthread)
