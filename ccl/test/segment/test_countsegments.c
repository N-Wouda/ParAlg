#include "test_segment.h"


void test_countSegments_one_voxel()
{
    // Single voxel matrix should consist of only one segment.
    matrix const mat = {(size_t[1]){1}, (size_t[1]){2}, (size_t[1]){3}, 1};

    TEST_ASSERT_EQUAL(1, countSegments(&mat));
}

void test_countSegments_disjoint()
{
    // Multiple disjoint segments. [0] is a single-voxel segment, [1-2] are a
    // segment of two voxels, as are [3-4].
    matrix const mat = {(size_t[5]){1, 2, 2, 4, 4},
                        (size_t[5]){2, 2, 2, 4, 4},
                        (size_t[5]){1, 2, 3, 4, 5},
                        5};

    TEST_ASSERT_EQUAL(3, countSegments(&mat));
}

void test_countSegments_contiguous()
{
    // Segments compress the z-dimension. These three voxels should all become
    // a single segment.
    matrix const mat = {(size_t[3]){1, 1, 1},
                        (size_t[3]){2, 2, 2},
                        (size_t[3]){1, 2, 3},
                        3};

    TEST_ASSERT_EQUAL(1, countSegments(&mat));
}
