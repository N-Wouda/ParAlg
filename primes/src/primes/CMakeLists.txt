cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		boundedsieve.c
		bspsieve.c
		sieve.c)

add_library(primes
		SHARED STATIC ${SOURCE_FILES})

target_link_libraries(primes m bsp)

install(TARGETS primes DESTINATION ${PRIMES_INSTALL_LIB_DIR})
