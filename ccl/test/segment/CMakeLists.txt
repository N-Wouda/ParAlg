cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES
		main.c
		test_computesegments.c
		test_countsegments.c
		test_hasoverlap.c
		test_isbefore.c
		test_isequal.c
		test_isnewsegment.c
		test_makesegment.c
		test_segcoordcmp.c
		test_seglabelcmp.c
		test_segtotalcmp.c)

add_executable(test_segment ${SOURCE_FILES})

target_link_libraries(test_segment segment io unity testtools)
