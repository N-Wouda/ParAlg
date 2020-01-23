#include "io.h"
#include "test_algorithm.h"

#include <stdlib.h>


void test_sequential_3x3_example()
{
    bool status;
    matrix const mat = readMatrix("ccl/examples/3x3_example.mat", &status);

    TEST_ASSERT_TRUE(status);

    // Ground truths for the segments in the 3 x 3 example. They form three
    // components, as [0], [2], and [1, 3].
    segment groundTruth[4] = {{0, 0, 0, 3, NULL, 0, 0},
                              {1, 2, 2, 3, NULL, 0, 1},
                              {2, 0, 0, 1, NULL, 0, 2},
                              {2, 2, 0, 3, NULL, 0, 3}};

    size_t numSegments;
    segment *segments = sequential(&mat, &numSegments);

    TEST_ASSERT_EQUAL(4, numSegments);

    for (size_t idx = 0; idx != 4; ++idx)  // tests the segmentation.
        compareSegmentCoords(groundTruth + idx, segments + idx);

    // Test components. The initial labelling is based on the root segment's
    // first voxel's index in mat, which is 0 for [0], 4 for [2], and
    // 3 for [1, 3] (based on the component root [1]). This is less complicated
    // than it seems.
    TEST_ASSERT_EQUAL(segments, segments[0].parent);
    TEST_ASSERT_EQUAL(0, segments[0].label);

    TEST_ASSERT_EQUAL(segments + 2, segments[2].parent);
    TEST_ASSERT_EQUAL(4, segments[2].label);

    TEST_ASSERT_EQUAL(segments + 1, segments[1].parent);
    TEST_ASSERT_EQUAL(3, segments[1].label);

    TEST_ASSERT_EQUAL(segments + 1, segments[3].parent);
    TEST_ASSERT_EQUAL(3, segments[3].label);

    releaseMatrix(&mat);
    free(segments);
}
