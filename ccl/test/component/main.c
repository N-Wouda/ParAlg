#include "test_component.h"


void setUp(){};     // we do not use these but the compiler expects
void tearDown(){};  // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_findSet_all_roots);  // for findset.c
    RUN_TEST(test_findSet_one_component);
    RUN_TEST(test_findSet_two_components);

    RUN_TEST(test_isRoot);  // for isroot.c

    RUN_TEST(test_labelSegments_all_roots);  // for labelsegments.c
    RUN_TEST(test_labelSegments_two_components);

    RUN_TEST(test_makeSets);  // for makesets.c

    RUN_TEST(test_merge_same_root);  // for merge.c
    RUN_TEST(test_merge_equal_rank);
    RUN_TEST(test_merge_unequal_rank);

    return UNITY_END();
}
