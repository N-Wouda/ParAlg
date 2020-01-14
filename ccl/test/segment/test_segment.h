#ifndef TEST_SEGMENT_H
#define TEST_SEGMENT_H

#include "segment.h"

#include <unity.h>


void test_isBefore_x();
void test_isBefore_y();
void test_isBefore_z();

void test_isEqual_x();
void test_isEqual_y();
void test_isEqual_z();

void test_makeSegment();
void test_makeSegment_parent();

void test_segCoordCmp_x();
void test_segCoordCmp_y();
void test_segCoordCmp_z();

#endif  // TEST_SEGMENT_H
