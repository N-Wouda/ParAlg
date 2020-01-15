#include "test_segment.h"


void test_isNewSegment_x()
{
    matrix mat = {(size_t[2]){1, 1}, (size_t[2]){3, 3}, (size_t[2]){5, 6}, 2};

    // Same x and y as the previous index, and contiguous z.
    TEST_ASSERT_FALSE(isNewSegment(&mat, 1));

    mat.x[1] = 2;  // same y and contiguous z, but not same x
    TEST_ASSERT_TRUE(isNewSegment(&mat, 1));
}

void test_isNewSegment_y()
{
    matrix mat = {(size_t[2]){1, 1}, (size_t[2]){3, 3}, (size_t[2]){5, 6}, 2};

    TEST_ASSERT_FALSE(isNewSegment(&mat, 1));

    mat.y[1] = 4;  // same x and contiguous z, but not same y.
    TEST_ASSERT_TRUE(isNewSegment(&mat, 1));
}

void test_isNewSegment_z()
{
    matrix mat = {(size_t[2]){1, 1}, (size_t[2]){3, 3}, (size_t[2]){5, 6}, 2};

    TEST_ASSERT_FALSE(isNewSegment(&mat, 1));

    mat.z[1] = 7;  // z-values are not contiguous.
    TEST_ASSERT_TRUE(isNewSegment(&mat, 1));
}
