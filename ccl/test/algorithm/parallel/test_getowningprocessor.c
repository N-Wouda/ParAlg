#include "test_parallel.h"


void test_getOwningProcessor_label_trick()
{
    segment candidate = {0, 0, 0, 0, NULL, 0, 1};

    // Label is one, so we have 1 / 1 and 1 / 2.
    TEST_ASSERT_EQUAL(1, getOwningProcessor(&candidate, 1));
    TEST_ASSERT_EQUAL(0, getOwningProcessor(&candidate, 2));

    candidate.label = 100;
    TEST_ASSERT_EQUAL(1, getOwningProcessor(&candidate, 100));
    TEST_ASSERT_EQUAL(0, getOwningProcessor(&candidate, 101));

    // Same as above, but now the label space is halved. We have 100 / 49,
    // 100 / 50, and 100 / 51.
    TEST_ASSERT_EQUAL(2, getOwningProcessor(&candidate, 49));
    TEST_ASSERT_EQUAL(2, getOwningProcessor(&candidate, 50));
    TEST_ASSERT_EQUAL(1, getOwningProcessor(&candidate, 51));
}
