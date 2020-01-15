#include "io.h"
#include "test_parallel.h"


segment *getExampleSegments(size_t *numSegments)
{
    bool status;
    matrix mat = readMatrix("ccl/examples/3x3_example.mat", &status);

    TEST_ASSERT_TRUE(status);

    return computeSegments(&mat, numSegments);
}

void test_determineSegmentSlice_3x3_example_one_processor()
{
    size_t numSegments;
    segment *segments = getExampleSegments(&numSegments);

    size_t low;
    size_t high;

    determineSegmentSlice(segments, numSegments, 0, 1, &low, &high);

    // Sends all segments to P(0).
    TEST_ASSERT_EQUAL(0, low);
    TEST_ASSERT_EQUAL(numSegments, high);

    // Verifies the bytes computation: the entire array is sent to P(0), so
    // that should result in a message size of numSegments (times the size of
    // a segment, of course!).
    TEST_ASSERT_EQUAL(numSegments, (high - low));
}

void test_determineSegmentSlice_3x3_example_two_processors()
{
    size_t numSegments;
    segment *segments = getExampleSegments(&numSegments);

    size_t low;
    size_t high;

    // First processor.
    determineSegmentSlice(segments, numSegments, 0, 2, &low, &high);

    TEST_ASSERT_EQUAL(0, low);
    TEST_ASSERT_EQUAL(numSegments, high);

    // Sends [0, 1, 2, 3] to P(0), so the message contains three segments.
    // [2, 3] are the overlapping slice.
    TEST_ASSERT_EQUAL(4, (high - low));

    // Second processor.
    determineSegmentSlice(segments, numSegments, 1, 2, &low, &high);

    TEST_ASSERT_EQUAL(2, low);
    TEST_ASSERT_EQUAL(numSegments, high);

    // Sends [2, 3] to P(1), so the message contains three segments. [2, 3] is
    // the overlapping slice, as this is the last processor.
    TEST_ASSERT_EQUAL(2, (high - low));
}

// TODO test larger instances over more processors.
