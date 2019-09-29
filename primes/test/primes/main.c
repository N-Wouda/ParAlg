#include "test_primes.h"


void setUp() {};            // we do not use these but the compiler expects
void tearDown() {};         // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_sieve_upperBound_100);            // for sieve.c
    RUN_TEST(test_sieve_upperBound_1000);
    RUN_TEST(test_sieve_primes_upperBound_10);

    RUN_TEST(test_boundedSieve_interval_5_10);      // for boundedsieve.c
    RUN_TEST(test_boundedSieve_interval_50_100);
    RUN_TEST(test_boundedSieve_interval_48_97);
    RUN_TEST(test_boundedSieve_interval_53_97);
    RUN_TEST(test_boundedSieve_interval_53_98);
    RUN_TEST(test_boundedSieve_interval_1000_10000);
    RUN_TEST(test_boundedSieve_same_output_sieve_from_zero);

    return UNITY_END();
}
