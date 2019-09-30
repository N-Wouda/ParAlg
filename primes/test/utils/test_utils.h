#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <unity.h>

#include "utils.h"


void test_blockBounds_single_processor();

void test_blockBounds_contiguous_blocks();

void test_blockBounds_upper_bound_bug();

void test_oddCount_interval_0_5();

void test_oddCount_interval_0_6();

void test_oddCount_interval_1_6();

void test_oddCount_interval_1_1();

void test_countPrimes_all_false();

void test_countPrimes_all_true();

void test_countPrimes_empty();

void test_countPrimes_varying_values();

void test_getPrimes_empty();

void test_unmark_all();

void test_unmark_from();

void test_unmark_step();

void test_unmark_bound();

#endif // TEST_UTILS_H
