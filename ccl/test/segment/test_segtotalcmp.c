#include "test_segment.h"


void test_segTotalCmp_coordinate()
{
    // As the labels are the same, this should behave the same way as
    // segCoordCmp.
    segment a = {1, 0, 0, 1, NULL, 0, 1};
    segment b = {2, 0, 0, 1, NULL, 0, 1};

    // a < b
    TEST_ASSERT_EQUAL(-1, segTotalCmp(&a, &b));
    TEST_ASSERT_EQUAL(segCoordCmp(&a, &b), segTotalCmp(&a, &b));

    // a == b
    b.x = 1;
    TEST_ASSERT_EQUAL(0, segTotalCmp(&a, &b));
    TEST_ASSERT_EQUAL(segCoordCmp(&a, &b), segTotalCmp(&a, &b));

    // a > b
    b.x = 0;
    TEST_ASSERT_EQUAL(1, segTotalCmp(&a, &b));
    TEST_ASSERT_EQUAL(segCoordCmp(&a, &b), segTotalCmp(&a, &b));
}

void test_segTotalCmp_label()
{
    // The coordinates are the same - this should behave the same way as
    // segLabelCmp.
    segment a = {0, 0, 0, 1, NULL, 0, 1};
    segment b = {0, 0, 0, 1, NULL, 0, 1};

    // a == b
    TEST_ASSERT_EQUAL(0, segTotalCmp(&a, &b));
    TEST_ASSERT_EQUAL(segLabelCmp(&a, &b), segTotalCmp(&a, &b));

    // a < b
    a.label = 0;
    TEST_ASSERT_EQUAL(-1, segTotalCmp(&a, &b));
    TEST_ASSERT_EQUAL(segLabelCmp(&a, &b), segTotalCmp(&a, &b));

    // a > b
    a.label = 2;
    TEST_ASSERT_EQUAL(1, segTotalCmp(&a, &b));
    TEST_ASSERT_EQUAL(segLabelCmp(&a, &b), segTotalCmp(&a, &b));
}
