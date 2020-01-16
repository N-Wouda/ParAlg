#include "testtools.h"


void compareSegmentCoords(segment const *expected, segment const *actual)
{
    TEST_ASSERT_EQUAL(expected->x, actual->x);
    TEST_ASSERT_EQUAL(expected->y, actual->y);
    TEST_ASSERT_EQUAL(expected->zFirst, actual->zFirst);
    TEST_ASSERT_EQUAL(expected->zLast, actual->zLast);
}
