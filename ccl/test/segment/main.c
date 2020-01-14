#include "test_segment.h"


void setUp(){};     // we do not use these but the compiler expects
void tearDown(){};  // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_isBefore_x);  // for isbefore.c
    RUN_TEST(test_isBefore_y);
    RUN_TEST(test_isBefore_z);

    RUN_TEST(test_isEqual_x);  // for isequal.c
    RUN_TEST(test_isEqual_y);
    RUN_TEST(test_isEqual_z);

    RUN_TEST(test_makeSegment);  // for makesegment.c
    RUN_TEST(test_makeSegment_parent);

    RUN_TEST(test_segCoordCmp_x);  // for segcoordcmp.c
    RUN_TEST(test_segCoordCmp_y);
    RUN_TEST(test_segCoordCmp_z);

    return UNITY_END();
}
