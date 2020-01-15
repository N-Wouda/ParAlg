#include "test_component.h"


void test_makeSets()
{
    segment segments[4] = {{0, 0, 1, 3, NULL, 1},
                           {0, 1, 1, 3, NULL, 1},
                           {1, 0, 1, 3, NULL, 1},
                           {2, 0, 1, 3, NULL, 1}};

    makeSets(segments, 4);

    // Tests if each segment is a unique component after running makeSets,
    // that is, it points to itself (is a root), and its rank is zero.
    for (size_t idx = 0; idx != 4; ++idx)
    {
        TEST_ASSERT_EQUAL(segments + idx, segments[idx].parent);
        TEST_ASSERT_TRUE(isRoot(segments + idx));

        TEST_ASSERT_EQUAL(0, segments[idx].rank);
    }
}
