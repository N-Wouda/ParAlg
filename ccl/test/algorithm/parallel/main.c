#include "test_parallel.h"


void setUp(){};     // we do not use these but the compiler expects
void tearDown(){};  // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_getOwningProcessor_label_trick);  // for getowningprocessor.c

    return UNITY_END();
}
