#include "test_utils.h"


void test_oddCount_interval_0_5()
{
    bounds const bounds = {0, 5};

    // Two, {1, 3}, as the upper bound should be excluded.
    TEST_ASSERT_TRUE(oddCount(&bounds) == 2);
}

void test_oddCount_interval_0_6()
{
    bounds const bounds = {0, 6};

    // Three, {1, 3, 5}, as now 5 is no longer the upper bound.
    TEST_ASSERT_TRUE(oddCount(&bounds) == 3);
}

void test_oddCount_interval_1_6()
{
    bounds const bounds = {1, 6};

    // Three, {1, 3, 5}, as the lower bound should be included.
    TEST_ASSERT_TRUE(oddCount(&bounds) == 3);
}

void test_oddCount_interval_1_1()
{
    bounds const bounds = {1, 1};

    // Since lower bound == upper bound, the interval is empty.
    TEST_ASSERT_TRUE(oddCount(&bounds) == 0);
}

// TODO add more test cases
