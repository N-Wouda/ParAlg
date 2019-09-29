#include "test_primes.h"


size_t *sieveTestHelper(size_t upperBound, size_t *numPrimes)
{
    bounds const bounds = {0, upperBound};
    return sieve(&bounds, numPrimes);
}

void test_sieve_100()
{
    size_t numPrimes = 0;
    sieveTestHelper(100, &numPrimes);

    // There are 25 primes in [0, 100) according to WolframAlpha.
    TEST_ASSERT_TRUE(numPrimes == 25);
}

void test_sieve_1000()
{
    size_t numPrimes = 0;
    sieveTestHelper(1000, &numPrimes);

    // There are 168 primes in [0, 1000) according to WolframAlpha.
    TEST_ASSERT_TRUE(numPrimes == 168);
}

void test_sieve_primes_10()
{
    size_t numPrimes = 0;
    size_t *candPrimes = sieveTestHelper(10, &numPrimes);

    // There are four primes in [0, 10): [2, 3, 5, 7]
    size_t primes[] = {2, 3, 4, 7};

    TEST_ASSERT_TRUE(numPrimes == 4);
    TEST_ASSERT_EQUAL_UINT_ARRAY(primes, candPrimes, 4);
}
