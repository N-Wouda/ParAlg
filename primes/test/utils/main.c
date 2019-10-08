#include "test_utils.h"


void setUp() {};            // we do not use these but the compiler expects
void tearDown() {};         // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_blockBounds_single_processor);    // for blockbounds.c
    RUN_TEST(test_blockBounds_contiguous_blocks);
    RUN_TEST(test_blockBounds_upper_bound_bug);

    RUN_TEST(test_candidateCount_interval_0_5);     // for candidatecount.c
    RUN_TEST(test_candidateCount_interval_0_6);
    RUN_TEST(test_candidateCount_interval_5_7);
    RUN_TEST(test_candidateCount_interval_5_8);
    RUN_TEST(test_candidateCount_interval_5_19);
    RUN_TEST(test_candidateCount_interval_5_6);

    RUN_TEST(test_countPrimes_all_false);           // for countprimes.c
    RUN_TEST(test_countPrimes_all_true);
    RUN_TEST(test_countPrimes_empty);
    RUN_TEST(test_countPrimes_varying_values);

    RUN_TEST(test_getPrimes_empty);                 // for getprimes.c

    RUN_TEST(test_unmark_all);                      // for unmark.c
    RUN_TEST(test_unmark_from);
    RUN_TEST(test_unmark_step);
    RUN_TEST(test_unmark_bound);

    return UNITY_END();
}
