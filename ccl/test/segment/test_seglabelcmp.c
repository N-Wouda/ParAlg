#include "test_segment.h"


void test_segLabelCmp()
{
    segment a = {1, 0, 0, 1, NULL, 0, 1};
    segment b = {2, 0, 0, 1, NULL, 0, 1};

    // a == b
    TEST_ASSERT_EQUAL(0, segLabelCmp(&a, &b));

    // a < b
    a.label = 0;
    TEST_ASSERT_EQUAL(-1, segLabelCmp(&a, &b));

    // a > b
    a.label = 2;
    TEST_ASSERT_EQUAL(1, segLabelCmp(&a, &b));
}
