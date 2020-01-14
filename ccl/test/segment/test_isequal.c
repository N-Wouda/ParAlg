#include "test_segment.h"


void test_isEqual_x()
{
    segment a = {1, 0, 0, 0};
    segment b = {1, 0, 0, 0};

    TEST_ASSERT_TRUE(isEqual(&a, &b));

    a.x = 0;
    TEST_ASSERT_FALSE(isEqual(&a, &b));

    b.x = 0;
    TEST_ASSERT_TRUE(isEqual(&a, &b));
}

void test_isEqual_y()
{
    segment a = {0, 1, 0, 0};
    segment b = {0, 1, 0, 0};

    TEST_ASSERT_TRUE(isEqual(&a, &b));

    a.y = 0;
    TEST_ASSERT_FALSE(isEqual(&a, &b));

    b.y = 0;
    TEST_ASSERT_TRUE(isEqual(&a, &b));
}

void test_isEqual_z()
{
    segment a = {0, 0, 1, 1};
    segment b = {0, 0, 1, 1};

    TEST_ASSERT_TRUE(isEqual(&a, &b));

    a.zFirst = 0;
    TEST_ASSERT_FALSE(isEqual(&a, &b));

    b.zFirst = 0;
    TEST_ASSERT_TRUE(isEqual(&a, &b));

    a.zLast = 0;
    TEST_ASSERT_FALSE(isEqual(&a, &b));

    b.zLast = 0;
    TEST_ASSERT_TRUE(isEqual(&a, &b));
}
