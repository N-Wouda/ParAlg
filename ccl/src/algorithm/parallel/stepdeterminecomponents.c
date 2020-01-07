#include "algorithm.h"
#include "algorithm/parallel.h"
#include "sparse.h"

#include <assert.h>
#include <bsp.h>
#include <stdlib.h>


void stepDetermineComponents()
{
    unsigned int messages;
    size_t qSize;
    bsp_qsize(&messages, &qSize);

    if (messages != 3)  // should equal the number of dimensions: x, y, z.
        bsp_abort("%u: expected 3 messages, got %u.\n", bsp_pid(), messages);

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
    SEGMENTS = sequential(&mat, &NUM_SEGMENTS);

    free(mat.x);
    free(mat.y);
    free(mat.z);

    // Determines the boundaries for the processor, and labels/sends the
    // appropriate boundary components to the other processors.
    if (bsp_pid() != 0)
    {
        size_t numSegments = 1;

        // Find the last index of the first x-value we have.
        while (SEGMENTS[numSegments - 1].x == SEGMENTS[numSegments].x
               && numSegments < NUM_SEGMENTS)
            numSegments++;

        labelAndSendBoundary(numSegments, 0);
    }

    if (bsp_pid() != bsp_nprocs() - 1)
    {
        size_t idx = NUM_SEGMENTS - 1;

        // Finds the first index of the last x-value we have.
        while (SEGMENTS[idx - 1].x == SEGMENTS[idx].x && idx > 0)
            idx--;

        labelAndSendBoundary(NUM_SEGMENTS - idx, idx);
    }
}
