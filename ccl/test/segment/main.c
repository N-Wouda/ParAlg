#include "test_segment.h"


void setUp(){};     // we do not use these but the compiler expects
void tearDown(){};  // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_computeSegments_one_segment);  // for computesegments.c
    RUN_TEST(test_computeSegments_one_voxel);
    RUN_TEST(test_computeSegments_random);
    RUN_TEST(test_computeSegments_small);

    RUN_TEST(test_countSegments_contiguous);  // for countsegments.c
    RUN_TEST(test_countSegments_disjoint);
    RUN_TEST(test_countSegments_one_voxel);

    RUN_TEST(test_isBefore_x);  // for isbefore.c
    RUN_TEST(test_isBefore_y);
    RUN_TEST(test_isBefore_z);

    RUN_TEST(test_isEqual_x);  // for isequal.c
    RUN_TEST(test_isEqual_y);
    RUN_TEST(test_isEqual_z);

    RUN_TEST(test_isNewSegment_x);  // for isnewsegment.c
    RUN_TEST(test_isNewSegment_y);
    RUN_TEST(test_isNewSegment_z);

    RUN_TEST(test_makeSegment);  // for makesegment.c
    RUN_TEST(test_makeSegment_parent);

    RUN_TEST(test_segCoordCmp_x);  // for segcoordcmp.c
    RUN_TEST(test_segCoordCmp_y);
    RUN_TEST(test_segCoordCmp_z);

    return UNITY_END();
}
