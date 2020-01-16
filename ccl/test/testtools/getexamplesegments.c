#include "testtools.h"


segment *getExampleSegments(char const *location, size_t *numSegments)
{
    bool status;
    matrix mat = readMatrix(location, &status);

    TEST_ASSERT_TRUE(status);

    segment *segments = computeSegments(&mat, numSegments);

    releaseMatrix(&mat);

    return segments;
}
