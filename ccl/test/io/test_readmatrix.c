#include "test_io.h"


void test_readMatrix_3x3_example()
{
    // The familiar 3 x 3 example from our report.
    size_t x[8] = {0, 0, 0, 1, 2, 2, 2, 2};
    size_t y[8] = {0, 0, 0, 2, 0, 2, 2, 2};
    size_t z[8] = {0, 1, 2, 2, 0, 0, 1, 2};

    matrix const groundTruth = {x, y, z, 8};

    bool status;
    matrix const mat = readMatrix("examples/3x3_example.mat", &status);

    TEST_ASSERT_TRUE(status);
    TEST_ASSERT_EQUAL(groundTruth.length, mat.length);

    for (size_t idx = 0; idx != groundTruth.length; ++idx)
    {
        TEST_ASSERT_EQUAL(groundTruth.x[idx], mat.x[idx]);
        TEST_ASSERT_EQUAL(groundTruth.y[idx], mat.y[idx]);
        TEST_ASSERT_EQUAL(groundTruth.z[idx], mat.z[idx]);
    }

    releaseMatrix(&mat);
}
