#include "test_segment.h"


void test_isBefore_x()
{
    segment a = {1, 0, 0, 1};
    segment b = {1, 0, 0, 1};

    TEST_ASSERT_FALSE(isBefore(&a, &b));
    TEST_ASSERT_TRUE(isEqual(&a, &b));

    a.x = 0;

    TEST_ASSERT_TRUE(isBefore(&a, &b));
    TEST_ASSERT_FALSE(isEqual(&a, &b));
}

void test_isBefore_y()
{
    segment a = {0, 1, 0, 1};
    segment b = {0, 1, 0, 1};

    TEST_ASSERT_FALSE(isBefore(&a, &b));
    TEST_ASSERT_TRUE(isEqual(&a, &b));

    a.y = 0;

    TEST_ASSERT_TRUE(isBefore(&a, &b));
    TEST_ASSERT_FALSE(isEqual(&a, &b));
}

void test_isBefore_z()
{
    segment a = {0, 0, 0, 1};
    segment b = {0, 0, 0, 1};

    TEST_ASSERT_FALSE(isBefore(&a, &b));
    TEST_ASSERT_TRUE(isEqual(&a, &b));

    // set b to be the voxel directly after a in the z-dimension. Then a
    // precedes b.
    b.zFirst = 1;
    b.zLast = 2;

    TEST_ASSERT_TRUE(isBefore(&a, &b));

    // a is a segment of [0, 1], and thus contains b. As such, it cannot
    // precede b.
    a.zLast = 2;
    TEST_ASSERT_FALSE(isBefore(&a, &b));
}
