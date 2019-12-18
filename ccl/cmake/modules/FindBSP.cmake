find_library(BSP REQUIRED
		NAMES libbsp.a libbsp)

if (NOT BSP)
	message("-- Could not find BSP! Attempting to recover..")

	find_path(BSP_PATH
			NAMES bsp.h
			PATHS ~/MulticoreBSP-for-C/
			NO_DEFAULT_PATH)

	if (BSP_PATH)
		message("-- Recovered.")

		include_directories(${BSP_PATH}/include)

		find_library(BSP REQUIRED
				NAMES libmcbsp2.0.4.a
				PATHS ${BSP_PATH}/lib)
	else()
		message("-- Could not recover.")
	endif()
endif()
