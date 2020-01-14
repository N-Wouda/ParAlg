#include "test_component.h"


void test_findSet_all_roots()
{
    segment segments[3] = {{0, 1, 2, 3, NULL},
                           {0, 1, 2, 3, NULL},
                           {0, 1, 2, 3, NULL}};

    makeSets(segments, 3);

    for (size_t idx = 0; idx != 3; ++idx)
    {
        // The segments are each component roots, so findSet should return
        // these as well.
        TEST_ASSERT_TRUE(isRoot(segments + idx));
        TEST_ASSERT_EQUAL(segments + idx, findSet(segments + idx));
    }
}

void test_findSet_one_component()
{
    segment segments[3] = {{0, 1, 2, 3, NULL},
                           {0, 1, 2, 3, NULL},
                           {0, 1, 2, 3, NULL}};

    // [0] is the component root, all other segments are made to point to the
    // preceding segment, such that the segments array forms a linked list.
    segments[0].parent = segments;

    for (size_t idx = 1; idx != 3; ++idx)
        segments[idx].parent = segments + idx - 1;

    // For each segment, the component root is at idx 0, and findSet should
    // return this.
    for (size_t idx = 0; idx != 3; ++idx)
        TEST_ASSERT_EQUAL(segments, findSet(segments + idx));
}

void test_findSet_two_components()
{
    segment segments[5] = {{0, 1, 2, 3, NULL},
                           {0, 1, 2, 3, NULL},
                           {0, 1, 2, 3, NULL},
                           {0, 1, 2, 3, NULL},
                           {0, 1, 2, 3, NULL}};

    // First we construct a linked list like we have before, with [0] as the
    // component root.
    segments[0].parent = segments;

    for (size_t idx = 1; idx != 5; ++idx)
        segments[idx].parent = segments + idx - 1;

    // This makes [2] a component root. The component structure is now as
    // follows: [0, 1] ([0] root), [2, 3, 4] ([2] root).
    segments[2].parent = segments + 2;

    for (size_t idx = 0; idx != 2; ++idx)  // first component
        TEST_ASSERT_EQUAL(segments, findSet(segments + idx));

    for (size_t idx = 2; idx != 5; ++idx)  // second component
        TEST_ASSERT_EQUAL(segments + 2, findSet(segments + idx));
}
