#include "test_segment.h"


void test_hasOverlap_true()
{
    segment candidate = {0, 0, 1, 2};
    segment target = {0, 0, 1, 3};

    // Same x and y, and overlapping z.
    TEST_ASSERT_TRUE(hasOverlap(&candidate, &target));
}

void test_hasOverlap_false()
{
    segment candidate = {0, 0, 1, 2};
    segment target = {0, 1, 1, 3};

    // Differing y cannot have overlap
    TEST_ASSERT_FALSE(hasOverlap(&candidate, &target));

    candidate.x = 1;  // same y, different x.
    target.y = 1;

    TEST_ASSERT_FALSE(hasOverlap(&candidate, &target));

    target.x = 1;  // same x and y, but no z overlap.
    target.zFirst = 2;

    TEST_ASSERT_FALSE(hasOverlap(&candidate, &target));
}

void test_hasOverlap_fix_overlap_bug()
{
    // Tests a mistake where the candidate did not overlap with the target, but
    // the function claimed it did.
    segment candidate = {0, 0, 3, 4};
    segment target = {0, 0, 2, 3};

    TEST_ASSERT_FALSE(hasOverlap(&candidate, &target));
}