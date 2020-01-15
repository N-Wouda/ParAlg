#include "test_parallel.h"


void setUp(){};     // we do not use these but the compiler expects
void tearDown(){};  // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_determineSegmentSlice_3x3_example_one_processor);
    RUN_TEST(test_determineSegmentSlice_3x3_example_two_processors);

    RUN_TEST(test_getOwningProcessor_label_trick);

    return UNITY_END();
}
