#include "test_utils.h"


void setUp() {};            // we do not use these but the compiler expects
void tearDown() {};         // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_blockBounds_single_processor);    // for blockbounds.c
    RUN_TEST(test_blockBounds_contiguous_blocks);
    RUN_TEST(test_blockBounds_upperBound_bug);

    RUN_TEST(test_oddCount_interval_0_5);           // for oddcount.c
    RUN_TEST(test_oddCount_interval_0_6);
    RUN_TEST(test_oddCount_interval_1_6);
    RUN_TEST(test_oddCount_interval_1_1);

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
