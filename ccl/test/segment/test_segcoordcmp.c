#include "test_segment.h"


void test_segCoordCmp_x()
{
    segment a = {1, 0, 0, 1};
    segment b = {2, 0, 0, 1};

    // a < b
    TEST_ASSERT_EQUAL(-1, segCoordCmp(&a, &b));

    // a == b
    b.x = 1;
    TEST_ASSERT_EQUAL(0, segCoordCmp(&a, &b));

    // a > b
    b.x = 0;
    TEST_ASSERT_EQUAL(1, segCoordCmp(&a, &b));
}

void test_segCoordCmp_y()
{
    segment a = {0, 1, 0, 1};
    segment b = {0, 2, 0, 1};

    // a < b
    TEST_ASSERT_EQUAL(-1, segCoordCmp(&a, &b));

    // a == b
    b.y = 1;
    TEST_ASSERT_EQUAL(0, segCoordCmp(&a, &b));

    // a > b
    b.y = 0;
    TEST_ASSERT_EQUAL(1, segCoordCmp(&a, &b));
}

void test_segCoordCmp_z()
{
    segment a = {0, 0, 3, 4};
    segment b = {0, 0, 5, 6};

    // a < b
    TEST_ASSERT_EQUAL(-1, segCoordCmp(&a, &b));

    // a == b
    b.zFirst = 3;
    b.zLast = 4;
    TEST_ASSERT_EQUAL(0, segCoordCmp(&a, &b));

    // a > b
    b.zFirst = 1;
    b.zLast = 2;
    TEST_ASSERT_EQUAL(1, segCoordCmp(&a, &b));
}
