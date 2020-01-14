#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "component.h"

#include <unity.h>


void test_findSet_all_roots();
void test_findSet_one_component();
void test_findSet_two_components();

void test_isRoot();

void test_labelSegments_all_roots();
void test_labelSegments_two_components();

void test_makeSets();

void test_merge_same_root();
void test_merge_equal_rank();
void test_merge_unequal_rank();

#endif  // TEST_COMPONENT_H
