#include "test_parallel.h"

#include <stdlib.h>


void test_labelBoundary_two_components()
{
    // Simple example of a boundary with two boundary-disjoint components:
    // [0, 1], and [2, 3, 4].
    segment segments[5] = {{0, 0, 0, 3},
                           {1, 0, 0, 2},
                           {1, 1, 3, 5},
                           {2, 0, 3, 6},
                           {2, 1, 0, 4}};

    makeSets(segments, 5);
    makeComponents(segments, 5);

    size_t numRoots;
    segment *roots = labelBoundary(segments, 5, 0, &numRoots);

    TEST_ASSERT_EQUAL(2, numRoots);

    compareSegmentCoords(segments, roots);
    compareSegmentCoords(segments + 2, roots + 1);

    free(roots);
}

void test_labelBoundary_hilbert2_example()
{
    // This is the boundary given to P(3) when running with four processors
    // on the hilbert2 dataset. It should consist only of boundary-disjoint
    // components.
    segment segments[11] = {{111, 1, 1, 2},
                            {111, 1, 43, 44},
                            {111, 43, 1, 2},
                            {111, 43, 43, 44},
                            {111, 43, 85, 86},
                            {111, 85, 1, 2},
                            {111, 85, 43, 44},
                            {111, 85, 85, 86},
                            {111, 85, 127, 128},
                            {111, 127, 1, 2},
                            {111, 127, 43, 44}};

    makeSets(segments, 11);
    makeComponents(segments, 11);

    size_t numRoots;
    segment *roots = labelBoundary(segments, 11, 0, &numRoots);

    TEST_ASSERT_EQUAL(11, numRoots);

    for (size_t idx = 0; idx != 11; ++idx)
        compareSegmentCoords(segments + idx, roots + idx);

    free(roots);
}
