#ifndef TEST_PARALLEL_H
#define TEST_PARALLEL_H

#include "algorithm/parallel.h"
#include "component.h"
#include "testtools.h"

#include <unity.h>


void test_determineSegmentSlice_3x3_example_one_processor();
void test_determineSegmentSlice_3x3_example_two_processors();
void test_determineSegmentSlice_hilbert2_two_processors();
void test_determineSegmentSlice_hilbert2_four_processors();

void test_getOwningProcessor_label_trick();

void test_labelBoundary_two_components();
void test_labelBoundary_hilbert2_example();

#endif  // TEST_PARALLEL_H
