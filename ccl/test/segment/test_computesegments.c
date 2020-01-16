#include "io.h"
#include "test_segment.h"

#include <stdlib.h>


void test_computeSegments_contiguous()
{
    // Segments compress the z-dimension. These three voxels should all become
    // a single segment.
    matrix const mat = {(size_t[3]){1, 1, 1},
                        (size_t[3]){2, 2, 2},
                        (size_t[3]){1, 2, 3},
                        3};

    segment const groundTruth = {1, 2, 1, 4};

    size_t numSegments;
    segment *segments = computeSegments(&mat, &numSegments);

    TEST_ASSERT_EQUAL(1, numSegments);

    compareSegmentCoords(&groundTruth, segments);

    free(segments);
}

void test_computeSegments_one_voxel()
{
    // Single voxel matrix should consist of only one segment.
    matrix const mat = {(size_t[1]){1}, (size_t[1]){2}, (size_t[1]){3}, 1};

    segment const groundTruth = {1, 2, 3, 4};

    size_t numSegments;
    segment *segments = computeSegments(&mat, &numSegments);

    TEST_ASSERT_EQUAL(1, numSegments);

    compareSegmentCoords(&groundTruth, segments);

    free(segments);
}

void test_computeSegments_3x3_example()
{
    bool status;
    matrix const mat = readMatrix("ccl/examples/3x3_example.mat", &status);

    TEST_ASSERT_TRUE(status);

    // Ground truths for the segments in the 3 x 3 example.
    segment groundTruth[4] = {{0, 0, 0, 3},
                              {1, 2, 2, 3},
                              {2, 0, 0, 1},
                              {2, 2, 0, 3}};

    size_t numSegments;
    segment *segments = computeSegments(&mat, &numSegments);

    TEST_ASSERT_EQUAL(4, numSegments);

    for (size_t idx = 0; idx != numSegments; ++idx)
        compareSegmentCoords(groundTruth + idx, segments + idx);

    releaseMatrix(&mat);
    free(segments);
}
