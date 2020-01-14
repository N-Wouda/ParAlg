#include "test_segment.h"

void test_makeSegment()
{
    matrix const mat = {(size_t[2]){1, 2},
                        (size_t[2]){3, 4},
                        (size_t[2]){5, 6},
                        2};

    for (size_t idx = 0; idx != mat.length; ++idx)
    {
        segment seg = makeSegment(&mat, idx, NULL);

        TEST_ASSERT_EQUAL(mat.x[idx], seg.x);
        TEST_ASSERT_EQUAL(mat.y[idx], seg.y);
        TEST_ASSERT_EQUAL(mat.z[idx], seg.zFirst);
        TEST_ASSERT_EQUAL(mat.z[idx] + 1, seg.zLast);

        TEST_ASSERT_EQUAL(idx, seg.label);
    }
}

void test_makeSegment_parent()
{
    matrix const mat = {(size_t[1]){1}, (size_t[1]){2}, (size_t[1]){3}, 1};
    segment parent = {};

    segment seg = makeSegment(&mat, 0, &parent);
    TEST_ASSERT_EQUAL(&parent, seg.parent);

    seg = makeSegment(&mat, 0, NULL);
    TEST_ASSERT_EQUAL(NULL, seg.parent);
}
