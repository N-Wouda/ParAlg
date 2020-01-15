#include "test_component.h"


void setUp(){};     // we do not use these but the compiler expects
void tearDown(){};  // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_findSet_all_roots);
    RUN_TEST(test_findSet_one_component);
    RUN_TEST(test_findSet_two_components);

    RUN_TEST(test_isRoot);

    RUN_TEST(test_labelSegments_all_roots);
    RUN_TEST(test_labelSegments_two_components);

    RUN_TEST(test_makeComponents_3x3_example);
    RUN_TEST(test_makeComponents_no_neighbours);
    RUN_TEST(test_makeComponents_x0);
    RUN_TEST(test_makeComponents_y0);

    RUN_TEST(test_makeSets);

    RUN_TEST(test_merge_same_root);
    RUN_TEST(test_merge_equal_rank);
    RUN_TEST(test_merge_unequal_rank);

    return UNITY_END();
}
