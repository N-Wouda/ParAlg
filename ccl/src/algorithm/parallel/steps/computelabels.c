#include "algorithm.h"
#include "parallel/steps.h"
#include "sparse.h"

#include <assert.h>
#include <bsp.h>
#include <stdio.h>
#include <stdlib.h>


void computeLabels()
{
    unsigned int messages;
    size_t qSize;
    bsp_qsize(&messages, &qSize);

    if (messages > 3)
        bsp_abort("%u: expected 3 messages, got %u.\n", bsp_pid(), messages);

    if (messages < 3)  // This can happen when the x-boundaries are such that
        return;        // some process has no work. Should be rare.

    // Number of bytes per dimension: x, y, z.
    size_t numBytes = qSize / messages;

    // The following is a bit abstract, but constructs a matrix from the
    // received dimension arrays. These are received in order of x, y, z.
    matrix mat = {NULL, NULL, NULL, numBytes / sizeof(size_t)};
    size_t **dimensions[3] = {&mat.x, &mat.y, &mat.z};

    for (size_t idx = 0; idx != 3; ++idx)
    {
        // Allocates some memory for the dimension, and then populates it from
        // the received message.
        *dimensions[idx] = malloc(numBytes);
        assert(*dimensions[idx] != NULL);

        size_t mSize;
        bsp_get_tag(&mSize, NULL);

        assert(mSize == numBytes);
        bsp_move(*dimensions[idx], mSize);
    }

    // Use the sequential algorithm to label the received matrix.
    size_t numSegments;
    segment *segments = sequential(&mat, &numSegments);

    printf("%u: %zu segments.\n", bsp_pid(), numSegments);

    // TODO: put segments in some sort of thread_local variable?
    // TODO: ccl on boundary, communicate, and free mat.
}
