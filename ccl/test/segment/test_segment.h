#ifndef TEST_SEGMENT_H
#define TEST_SEGMENT_H

#include "segment.h"

#include <unity.h>


void test_computeSegments_one_segment();
void test_computeSegments_one_voxel();
void test_computeSegments_random();
void test_computeSegments_small();

void test_countSegments_contiguous();
void test_countSegments_disjoint();
void test_countSegments_one_voxel();

void test_isBefore_x();
void test_isBefore_y();
void test_isBefore_z();

void test_isEqual_x();
void test_isEqual_y();
void test_isEqual_z();

void test_isNewSegment_x();
void test_isNewSegment_y();
void test_isNewSegment_z();

void test_makeSegment();
void test_makeSegment_parent();

void test_segCoordCmp_x();
void test_segCoordCmp_y();
void test_segCoordCmp_z();

#endif  // TEST_SEGMENT_H
