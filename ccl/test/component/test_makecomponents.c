#include "test_component.h"


void test_makeComponents_3x3_example()
{
    // This is again the familiar 3 x 3 example. It consists of three
    // components, [0], [1, 3], and [2].
    segment segments[4] = {{0, 0, 0, 3},
                           {1, 2, 2, 3},
                           {2, 0, 0, 1},
                           {2, 2, 0, 3}};

    makeSets(segments, 4);
    makeComponents(segments, 4);

    TEST_ASSERT_EQUAL(segments, findSet(segments));          // [0] -> [0]
    TEST_ASSERT_EQUAL(segments + 1, findSet(segments + 1));  // [1] -> [1]
    TEST_ASSERT_EQUAL(segments + 2, findSet(segments + 2));  // [2] -> [2]
    TEST_ASSERT_EQUAL(segments + 1, findSet(segments + 3));  // [3] -> [1]
}

void test_makeComponents_no_neighbours()
{
    // These segments are all not neighbours, either because they do not overlap
    // in the z-dimension for same x and y, or because they don't share a face
    // at (x - 1, y) or (x, y - 1).
    segment segments[4] = {{0, 0, 0, 3},
                           {0, 0, 3, 5},
                           {1, 1, 0, 3},
                           {1, 1, 3, 5}};

    makeSets(segments, 4);
    makeComponents(segments, 4);

    for (size_t idx = 0; idx != 4; ++idx)
        TEST_ASSERT_EQUAL(segments + idx, findSet(segments + idx));
}

void test_makeComponents_x0()
{
    // x == 0 is a boundary condition: makeComponents cannot look back at
    // (x - 1, y) to determine preceding neighbours. The following segments
    // list forms a single component due to neighbours at (x, y - 1).
    segment segments[4] = {{0, 0, 0, 3},
                           {0, 0, 2, 5},
                           {0, 1, 0, 3},
                           {0, 1, 3, 5}};

    makeSets(segments, 4);
    makeComponents(segments, 4);

    for (size_t idx = 0; idx != 4; ++idx)
        TEST_ASSERT_EQUAL(segments, findSet(segments + idx));
}

void test_makeComponents_y0()
{
    // y == 0 is a boundary condition: makeComponents cannot look back at
    // (x, y - 1) to determine preceding neighbours. The following segments
    // list forms a single component due to neighbours at (x - 1, y).
    segment segments[4] = {{0, 0, 0, 3},
                           {0, 0, 2, 5},
                           {1, 0, 0, 3},
                           {1, 0, 3, 5}};

    makeSets(segments, 4);
    makeComponents(segments, 4);

    for (size_t idx = 0; idx != 4; ++idx)
        TEST_ASSERT_EQUAL(segments, findSet(segments + idx));
}
