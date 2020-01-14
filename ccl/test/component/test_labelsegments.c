#include "test_component.h"


void test_labelSegments_all_roots()
{
    segment segments[3] = {{0, 1, 2, 3, NULL, 0, 0},
                           {0, 1, 2, 3, NULL, 0, 1},
                           {0, 1, 2, 3, NULL, 0, 2}};

    makeSets(segments, 3);
    labelSegments(segments, 3);

    // These segments are unique components. As such, no labels should have been
    // updated.
    for (size_t idx = 0; idx != 3; ++idx)
        TEST_ASSERT_EQUAL(idx, segments[idx].label);
}

void test_labelSegments_two_components()
{
    segment segments[3] = {{0, 1, 2, 3, NULL, 0, 0},
                           {0, 1, 2, 3, NULL, 0, 1},
                           {0, 1, 2, 3, NULL, 0, 2}};

    makeSets(segments, 3);

    // This creates two components: [0, 1] ([0] is root), and [2].
    segments[1].parent = segments;

    labelSegments(segments, 3);

    // Since [0, 1] are in a component with [0] as root, [1] should take [0]'s
    // label.
    TEST_ASSERT_EQUAL(0, segments[0].label);
    TEST_ASSERT_EQUAL(0, segments[1].label);

    // [2] is a component, so its label should remain unchanged.
    TEST_ASSERT_EQUAL(2, segments[2].label);
}
