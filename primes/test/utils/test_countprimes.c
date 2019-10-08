#include <stdlib.h>
#include <string.h>

#include "test_utils.h"


void test_countPrimes_all_false()
{
    bool isPrime[] = {false, false, false};

    // There are no 'primes' in isPrime, so the count should return zero.
    TEST_ASSERT_EQUAL_UINT(0, countPrimes(isPrime, 3));
}

void test_countPrimes_all_true()
{
    bool isPrime[] = {true, true, true};

    // There are only 'primes' in isPrime, so the count should equal the
    // length.
    TEST_ASSERT_EQUAL_UINT(3, countPrimes(isPrime, 3));
}

void test_countPrimes_empty()
{
    bool isPrime[] = {};

    // There are no values, so the count should return zero.
    TEST_ASSERT_EQUAL_UINT(0,  countPrimes(isPrime, 0));
}

void test_countPrimes_varying_values()
{
    // Initially, create an all false array.
    bool *isPrime = malloc(100 * sizeof(bool));
    memset(isPrime, false, 100 * sizeof(bool));

    for (size_t idx = 0; idx != 100; ++idx)
    {
        isPrime[idx] = true;

        // There are now idx + 1 'primes' in the array, so the count should
        // reflect this.
        TEST_ASSERT_EQUAL_UINT(idx + 1, countPrimes(isPrime, 100));
    }

    free(isPrime);
}

// TODO add more test cases
