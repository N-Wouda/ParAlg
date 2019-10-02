#include <stdlib.h>

#include "test_sieve.h"


size_t *boundTestHelper(size_t lowerBound, size_t upperBound, size_t *numPrimes)
{
    bounds const bounds = {lowerBound, upperBound};
    return boundedSieve(&bounds, numPrimes);
}

void test_boundedSieve_interval_5_10()
{
    size_t primes[] = {5, 7};       // there are two primes in [5, 10).

    size_t numPrimes = 0;
    size_t *candPrimes = boundTestHelper(5, 10, &numPrimes);

    TEST_ASSERT_TRUE(numPrimes == 2)
    TEST_ASSERT_EQUAL_UINT_ARRAY(primes, candPrimes, 2);

    free(candPrimes);
}

void test_boundedSieve_interval_50_100()
{
    size_t numPrimes = 0;
    free(boundTestHelper(50, 100, &numPrimes));

    // There are 10 primes in [50, 100) according to WolframAlpha.
    TEST_ASSERT_TRUE(numPrimes == 10)
}

void test_boundedSieve_interval_48_97()
{
    size_t numPrimes = 0;
    free(boundTestHelper(48, 97, &numPrimes));

    // There are 9 primes in [48, 97) according to WolframAlpha.
    TEST_ASSERT_TRUE(numPrimes == 9)
}

void test_boundedSieve_interval_53_97()
{
    size_t numPrimes = 0;
    free(boundTestHelper(53, 97, &numPrimes));

    // There are 9 primes in [53, 97) according to WolframAlpha. The first is
    // 53, which should be included.
    TEST_ASSERT_TRUE(numPrimes == 9)
}

void test_boundedSieve_interval_53_98()
{
    size_t numPrimes = 0;
    free(boundTestHelper(53, 98, &numPrimes));

    // There are 10 primes in [53, 98) according to WolframAlpha. The last is
    // 97, which should be included.
    TEST_ASSERT_TRUE(numPrimes == 10)
}

void test_boundedSieve_interval_1000_10000()
{
    size_t numPrimes = 0;
    free(boundTestHelper(1000, 10000, &numPrimes));

    // There are 1061 primes in [1000, 10000) according to WolframAlpha.
    TEST_ASSERT_TRUE(numPrimes == 1061)
}

void test_boundedSieve_same_output_sieve_from_zero()
{
    size_t const upperBounds[] = {10, 100, 1000, 10000};

    for (size_t idx = 0; idx != 4; ++idx)
    {
        bounds const bounds = {0, upperBounds[idx]};

        size_t boundedNumPrimes = 0;
        size_t sieveNumPrimes = 0;

        size_t *boundedPrimes = boundedSieve(&bounds, &boundedNumPrimes);
        size_t *sievePrimes = sieve(&bounds, &sieveNumPrimes);

        // These should be equivalent, as the lowerBound is zero for both.
        TEST_ASSERT_TRUE(boundedNumPrimes == sieveNumPrimes);

        // And they should, of course, both return the same primes.
        TEST_ASSERT_EQUAL_UINT_ARRAY(
            sievePrimes,
            boundedPrimes,
            sieveNumPrimes);

        free(boundedPrimes);
        free(sievePrimes);
    }
}

// TODO add more test cases
