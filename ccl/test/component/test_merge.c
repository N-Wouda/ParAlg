#include "test_component.h"


void test_merge_same_root()
{
    segment segments[3] = {{0, 1, 2, 3, NULL, 0, 0},
                           {0, 1, 2, 3, NULL, 0, 1},
                           {0, 1, 2, 3, NULL, 0, 2}};

    for (size_t idx = 0; idx != 3; ++idx)
        segments[idx].parent = segments;

    // The segments already point to the same root, so this should not change
    // anything.
    merge(segments, segments + 1);

    TEST_ASSERT_EQUAL(segments, segments[0].parent);
    TEST_ASSERT_EQUAL(segments, segments[1].parent);
    TEST_ASSERT_EQUAL(0, segments[0].rank);

    // Both segments point to the same root, which is not one of the two
    // segments. Again, merging the same component should not change anything.
    merge(segments + 1, segments + 2);

    TEST_ASSERT_EQUAL(segments, segments[1].parent);
    TEST_ASSERT_EQUAL(segments, segments[2].parent);
    TEST_ASSERT_EQUAL(0, segments[0].rank);
}

void test_merge_equal_rank()
{
    segment segments[2] = {{0, 1, 2, 3, NULL, 0, 0}, {0, 1, 2, 3, NULL, 0, 1}};

    makeSets(segments, 2);

    // Pre-condition, different components.
    TEST_ASSERT_EQUAL(0, segments[0].rank);
    TEST_ASSERT_EQUAL(0, segments[0].rank);

    // This should update the rank of the second argument by one, as the
    // components are currently of the same rank.
    merge(segments, segments + 1);

    TEST_ASSERT_EQUAL(0, segments[0].rank);
    TEST_ASSERT_EQUAL(1, segments[1].rank);

    // And, of course, the first segment now points to the second (whose rank
    // was updated to reflect this change).
    TEST_ASSERT_EQUAL(segments + 1, segments[0].parent);
}

void test_merge_unequal_rank()
{
    segment segments[2] = {{0, 1, 2, 3, NULL, 0, 0}, {0, 1, 2, 3, NULL, 1, 1}};

    makeSets(segments, 2);

    // Pre-condition, different components.
    TEST_ASSERT_EQUAL(0, segments[0].rank);
    TEST_ASSERT_EQUAL(0, segments[0].rank);

    merge(segments, segments + 1);

    // No ranks should have been updated, as the second segment was already of
    // greater rank.
    TEST_ASSERT_EQUAL(0, segments[0].rank);
    TEST_ASSERT_EQUAL(1, segments[1].rank);

    TEST_ASSERT_EQUAL(segments + 1, segments[0].parent);
}
