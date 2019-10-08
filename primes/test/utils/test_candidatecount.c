#include "test_utils.h"


void test_candidateCount_interval_0_5()
{
    bounds const bounds = {0, 5};

    // 0, as {5} is not included in the interval.
    TEST_ASSERT_EQUAL_UINT(0, candidateCount(&bounds));
}

void test_candidateCount_interval_0_6()
{
    bounds const bounds = {0, 6};

    // Only {5}, as it is now in the half-open interval proper.
    TEST_ASSERT_EQUAL_UINT(1, candidateCount(&bounds));
}

void test_candidateCount_interval_5_7()
{
    bounds const bounds = {5, 7};

    // Only {5}, as the upper bound is not included.
    TEST_ASSERT_EQUAL_UINT(1, candidateCount(&bounds));
}

void test_candidateCount_interval_5_8()
{
    bounds const bounds = {5, 8};

    // {5, 7}, as {7} is now included.
    TEST_ASSERT_EQUAL_UINT(2, candidateCount(&bounds));
}

void test_candidateCount_interval_5_19()
{
    bounds const bounds = {5, 19};

    // {5, 7, 11, 13, 17}, as {19} is excluded.
    TEST_ASSERT_EQUAL_UINT(5, candidateCount(&bounds));
}

void test_candidateCount_interval_5_6()
{
    bounds const bounds = {5, 6};

    // This should only contain {5}.
    TEST_ASSERT_EQUAL_UINT(1, candidateCount(&bounds));
}

// TODO add more test cases
