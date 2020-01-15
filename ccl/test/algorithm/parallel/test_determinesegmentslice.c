#include "io.h"
#include "test_parallel.h"

#include <stdlib.h>


segment *getExampleSegments(size_t *numSegments, char const *location)
{
    bool status;
    matrix mat = readMatrix(location, &status);

    TEST_ASSERT_TRUE(status);

    segment *segments = computeSegments(&mat, numSegments);

    releaseMatrix(&mat);

    return segments;
}

void test_determineSegmentSlice_3x3_example_one_processor()
{
    size_t numSegments;
    segment *segments = getExampleSegments(&numSegments,
                                           "ccl/examples/3x3_example.mat");

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

    free(segments);
}

void test_determineSegmentSlice_3x3_example_two_processors()
{
    size_t numSegments;
    segment *segments = getExampleSegments(&numSegments,
                                           "ccl/examples/3x3_example.mat");

    size_t low;
    size_t high;

    // First processor.
    determineSegmentSlice(segments, numSegments, 0, 2, &low, &high);

    TEST_ASSERT_EQUAL(0, low);
    TEST_ASSERT_EQUAL(numSegments, high);

    // Sends [0, 1, 2, 3] to P(0), so the message contains four segments.
    // [2, 3] are the overlapping slice.
    TEST_ASSERT_EQUAL(4, (high - low));

    // Second processor.
    determineSegmentSlice(segments, numSegments, 1, 2, &low, &high);

    TEST_ASSERT_EQUAL(2, low);
    TEST_ASSERT_EQUAL(numSegments, high);

    // Sends [2, 3] to P(1), so the message contains two segments. [2, 3] is
    // the overlapping slice, as this is the last processor.
    TEST_ASSERT_EQUAL(2, (high - low));

    free(segments);
}

void test_determineSegmentSlice_hilbert2_two_processors()
{
    size_t numSegments;
    segment *segments = getExampleSegments(&numSegments,
                                           "ccl/examples/hilbert2.mat");

    size_t low;
    size_t high;

    determineSegmentSlice(segments, numSegments, 0, 2, &low, &high);

    TEST_ASSERT_EQUAL(0, low);
    TEST_ASSERT_EQUAL(862, high);

    determineSegmentSlice(segments, numSegments, 1, 2, &low, &high);

    TEST_ASSERT_EQUAL(861, low);
    TEST_ASSERT_EQUAL(numSegments, high);

    free(segments);
}

void test_determineSegmentSlice_hilbert2_four_processors()
{
    size_t numSegments;
    segment *segments = getExampleSegments(&numSegments,
                                           "ccl/examples/hilbert2.mat");

    // These offsets were carefully vetted to ensure the boundaries are correct.
    size_t procOffsets[4][2] = {{0, 434},
                                {423, 861},
                                {860, 1300},
                                {1289, numSegments}};

    for (size_t proc = 0; proc != 4; ++proc)
    {
        size_t low;
        size_t high;

        determineSegmentSlice(segments, numSegments, proc, 4, &low, &high);

        TEST_ASSERT_EQUAL(procOffsets[proc][0], low);
        TEST_ASSERT_EQUAL(procOffsets[proc][1], high);
    }

    free(segments);
}
