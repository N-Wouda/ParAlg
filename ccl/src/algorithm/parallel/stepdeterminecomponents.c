#include "algorithm.h"
#include "algorithm/parallel.h"
#include "io.h"
#include "sparse.h"

#include <assert.h>
#include <bsp.h>
#include <stdlib.h>


void stepDetermineComponents()
{
    bsp_nprocs_t messages;
    bsp_size_t qSize;
    bsp_qsize(&messages, &qSize);

    if (messages != 4)  // dimensions (x, y, and z), and the label space.
        bsp_abort("%u: expected 4 messages, got %u.\n", bsp_pid(), messages);

    // First message is the label space / number of voxels.
    bsp_move(&NUM_VOXELS, sizeof(size_t));

    // Number of bytes per dimension: x, y, z.
    bsp_size_t const numBytes = (qSize - sizeof(size_t)) / 3;

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

        bsp_size_t mSize;
        bsp_get_tag(&mSize, NULL);
        assert(mSize == numBytes);

        bsp_move(*dimensions[idx], mSize);
    }

    // Use the sequential algorithm to label the received matrix.
    SEGMENTS = sequential(&mat, &NUM_SEGMENTS);

    // Guarantees we assign globally unique labels to each component.
    for (size_t idx = 0; idx != NUM_SEGMENTS; ++idx)
        SEGMENTS[idx].label += bsp_pid() * NUM_VOXELS;

    releaseMatrix(&mat);

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
        size_t from = NUM_SEGMENTS - 1;

        // Finds the first index of the last x-value we have.
        while (SEGMENTS[from - 1].x == SEGMENTS[from].x && from > 0)
            from--;

        labelAndSendBoundary(NUM_SEGMENTS - from, from);
    }
}
