#include "test_io.h"


void setUp(){};     // we do not use these but the compiler expects
void tearDown(){};  // them, so these are simple stubs.

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_readMatrix_3x3_example);

    return UNITY_END();
}
