#include "test_utils.h"


void test_blockBounds_single_processor()
{
    bounds const interval = {0, 100};
    bounds const subInterval = blockBounds(&interval, 1, 0);

    // When there is only one processor involved, the sub-interval should
    // equal the interval.
    TEST_ASSERT_EQUAL_UINT(
        interval.lowerBound,
        subInterval.lowerBound);

    TEST_ASSERT_EQUAL_UINT(
        interval.upperBound,
        subInterval.upperBound);
}

void test_blockBounds_contiguous_blocks()
{
    bounds const interval = {0, 100};
    bounds const first = blockBounds(&interval, 2, 0);
    bounds const second = blockBounds(&interval, 2, 1);

    // First check if the overall lower and upper bounds match: first should
    // equal [0, 50), and second [50, 100).
    TEST_ASSERT_EQUAL_UINT(
        interval.lowerBound,
        first.lowerBound);

    TEST_ASSERT_EQUAL_UINT(
        interval.upperBound,
        second.upperBound);

    // The sub-intervals must be contiguous. As the interval is half-open, the
    // preceding block's upper bound should equal the next's lower bound.
    TEST_ASSERT_TRUE(first.upperBound == second.lowerBound);
}

// TODO add more test cases
