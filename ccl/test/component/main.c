#include "test_component.h"


void setUp(){};     // we do not use these but the compiler expects
void tearDown(){};  // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_findSet_all_roots);  // for findset.c
    RUN_TEST(test_findSet_linked_list);
    RUN_TEST(test_findSet_two_roots);

    RUN_TEST(test_isRoot);  // for isroot.c

    RUN_TEST(test_makeSets);  // for makesets.c

    return UNITY_END();
}
