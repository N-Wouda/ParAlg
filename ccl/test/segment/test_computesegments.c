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

    size_t numSegments;
    segment *segments = computeSegments(&mat, &numSegments);

    TEST_ASSERT_EQUAL(1, numSegments);

    TEST_ASSERT_EQUAL(1, segments[0].x);
    TEST_ASSERT_EQUAL(2, segments[0].y);
    TEST_ASSERT_EQUAL(1, segments[0].zFirst);
    TEST_ASSERT_EQUAL(4, segments[0].zLast);  // exclusive, so + 1

    free(segments);
}

void test_computeSegments_one_voxel()
{
    // Single voxel matrix should consist of only one segment.
    matrix const mat = {(size_t[1]){1}, (size_t[1]){2}, (size_t[1]){3}, 1};

    size_t numSegments;
    segment *segments = computeSegments(&mat, &numSegments);

    TEST_ASSERT_EQUAL(1, numSegments);

    TEST_ASSERT_EQUAL(1, segments[0].x);
    TEST_ASSERT_EQUAL(2, segments[0].y);
    TEST_ASSERT_EQUAL(3, segments[0].zFirst);
    TEST_ASSERT_EQUAL(4, segments[0].zLast);  // exclusive, so + 1

    free(segments);
}

void test_computeSegments_3x3_example()
{
    // This COO matrix has four segments. It corresponds to the 3 x 3 example
    // in our report (Figure 1).
    size_t x[8] = {0, 0, 0, 1, 2, 2, 2, 2};
    size_t y[8] = {0, 0, 0, 2, 0, 2, 2, 2};
    size_t z[8] = {0, 1, 2, 2, 0, 0, 1, 2};

    matrix const mat = {x, y, z, 8};

    // Ground truths for the segments in the 3 x 3 example.
    segment groundTruth[4] = {{0, 0, 0, 3},
                              {1, 2, 2, 3},
                              {2, 0, 0, 1},
                              {2, 2, 0, 3}};

    size_t numSegments;
    segment *segments = computeSegments(&mat, &numSegments);

    TEST_ASSERT_EQUAL(4, numSegments);

    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        TEST_ASSERT_EQUAL(groundTruth[idx].x, segments[idx].x);
        TEST_ASSERT_EQUAL(groundTruth[idx].y, segments[idx].y);
        TEST_ASSERT_EQUAL(groundTruth[idx].zFirst, segments[idx].zFirst);
        TEST_ASSERT_EQUAL(groundTruth[idx].zLast, segments[idx].zLast);
    }

    free(segments);
}
