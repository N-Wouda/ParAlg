#include <stdlib.h>

#include "test_utils.h"


void test_getPrimes_empty()
{
    bool const isPrime[] = {};
    bounds const bounds = {0, 0};

    size_t *primes = getPrimes(isPrime, &bounds, 0);

    TEST_ASSERT_EQUAL_PTR(NULL, primes);

    free(primes);
}

// TODO add more test cases
