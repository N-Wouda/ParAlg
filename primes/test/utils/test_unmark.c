#include <stdlib.h>
#include <string.h>

#include "test_utils.h"


bool *unmarkArrayHelper(size_t size)
{
    bool *isPrime = malloc(size * sizeof(bool));
    memset(isPrime, true, size * sizeof(bool));

    return isPrime;
}

void test_unmark_all()
{
    bool *isPrime = unmarkArrayHelper(100);

    // This should unmark all values in the array.
    unmark(isPrime, 100, 0, 1);

    for (size_t idx = 0; idx != 100; ++idx)
        TEST_ASSERT_FALSE(isPrime[idx]);

    free(isPrime);
}

void test_unmark_from()
{
    size_t const offsets[] = {25, 50, 75};

    for (size_t offsetIdx = 0; offsetIdx != 3; ++offsetIdx)
    {
        size_t const offset = offsets[offsetIdx];

        bool *isPrime = unmarkArrayHelper(100);

        // This should unmark all numbers starting at offset.
        unmark(isPrime, 100, offset, 1);

        for (size_t idx = 0; idx != offset; ++idx)
            // And so all numbers before offset should be true..
            TEST_ASSERT_TRUE(isPrime[idx]);

        for (size_t idx = offset; idx != 100; ++idx)
            // ..and all numbers after false.
            TEST_ASSERT_FALSE(isPrime[idx]);

        free(isPrime);
    }
}

void test_unmark_step()
{
    size_t const steps[] = {1, 2, 3, 4, 5};

    for (size_t stepIdx = 0; stepIdx != 5; ++stepIdx)
    {
        size_t const step = steps[stepIdx];

        bool *isPrime = unmarkArrayHelper(100);

        // This should unmark every step numbers starting at zero.
        unmark(isPrime, 100, 0, step);

        for (size_t idx = 0; idx != 100; ++idx)
            // And thus every multiple of step should be false, and all other
            // values true.
            TEST_ASSERT_TRUE(isPrime[idx] != (idx % step == 0));

        free(isPrime);
    }
}

void test_unmark_bound()
{
    size_t const bounds[] = {25, 50, 66, 100};

    for (size_t boundsIdx = 0; boundsIdx != 4; ++boundsIdx)
    {
        size_t const bound = bounds[boundsIdx];

        bool *isPrime = unmarkArrayHelper(100);

        // This should unmark all numbers starting at zero, up to bound.
        unmark(isPrime, bound, 0, 1);

        for (size_t idx = 0; idx != bound; ++idx)
            // So all values up to bound should be false..
            TEST_ASSERT_FALSE(isPrime[idx]);

        for (size_t idx = bound; idx != 100; ++idx)
            // ..and all values from bound true.
            TEST_ASSERT_TRUE(isPrime[idx]);

        free(isPrime);
    }
}

// TODO add more test cases
