#include "test_component.h"


void test_isRoot()
{
    segment seg = {0, 1, 2, 3, NULL};

    // A segment is a component root only if it points to itself.
    TEST_ASSERT_FALSE(isRoot(&seg));

    seg.parent = &seg;
    TEST_ASSERT_TRUE(isRoot(&seg));
}
