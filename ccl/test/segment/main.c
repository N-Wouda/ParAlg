#include "test_segment.h"


void setUp(){};     // we do not use these but the compiler expects
void tearDown(){};  // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_computeSegments_contiguous);
    RUN_TEST(test_computeSegments_one_voxel);
    RUN_TEST(test_computeSegments_3x3_example);

    RUN_TEST(test_countSegments_contiguous);
    RUN_TEST(test_countSegments_disjoint);
    RUN_TEST(test_countSegments_one_voxel);

    RUN_TEST(test_hasOverlap_true);
    RUN_TEST(test_hasOverlap_false);
    RUN_TEST(test_hasOverlap_fix_overlap_bug);

    RUN_TEST(test_isBefore_x);
    RUN_TEST(test_isBefore_y);
    RUN_TEST(test_isBefore_z);

    RUN_TEST(test_isEqual_x);
    RUN_TEST(test_isEqual_y);
    RUN_TEST(test_isEqual_z);

    RUN_TEST(test_isNewSegment_x);
    RUN_TEST(test_isNewSegment_y);
    RUN_TEST(test_isNewSegment_z);

    RUN_TEST(test_makeSegment);

    RUN_TEST(test_segCoordCmp_x);
    RUN_TEST(test_segCoordCmp_y);
    RUN_TEST(test_segCoordCmp_z);

    RUN_TEST(test_segLabelCmp);

    RUN_TEST(test_segTotalCmp_coordinate);
    RUN_TEST(test_segTotalCmp_label);

    return UNITY_END();
}
