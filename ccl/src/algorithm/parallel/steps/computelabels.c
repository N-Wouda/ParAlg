#include "algorithm.h"
#include "parallel/steps.h"
#include "sparse.h"

#include <assert.h>
#include <bsp.h>
#include <stdlib.h>


void computeLabels()
{
    unsigned int messages;
    size_t qSize;
    bsp_qsize(&messages, &qSize);

    if (messages > 3)
        bsp_abort("%u: expected 3 messages, got %u.\n", bsp_pid(), messages);

    if (messages < 3)  // this can happen when the x-boundaries are such that
        return;        // some process has no work. Should be rare.

    size_t numBytes = qSize / messages;

    matrix mat = {NULL, NULL, NULL, numBytes / sizeof(size_t)};
    size_t **fields[3] = {&mat.x, &mat.y, &mat.z};

    for (size_t idx = 0; idx != 3; ++idx)
    {
        *fields[idx] = malloc(numBytes);
        assert(*fields[idx] != NULL);

        size_t mSize;
        bsp_get_tag(&mSize, NULL);

        assert(mSize == numBytes);
        bsp_move(*fields[idx], mSize);
    }

    size_t numSegments;
    segment *segments = sequential(&mat, &numSegments);

    // TODO
}
