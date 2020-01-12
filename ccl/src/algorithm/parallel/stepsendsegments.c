#include "algorithm/parallel.h"
#include "io.h"

#include <bsp.h>
#include <stdlib.h>

void stepSendSegments()
{
    if (bsp_pid() != 0)
        return;

    bool status;
    matrix const mat = readMatrix(ARGUMENTS.inLocation, &status);
    NUM_VOXELS = mat.length;

    if (!status)
    {
        releaseMatrix(&mat);
        bsp_abort("Something went wrong reading the matrix.\n");
    }

    SEGMENTS = computeSegments(&mat, &NUM_SEGMENTS);

    releaseMatrix(&mat);

    bsp_size_t const numItems = NUM_SEGMENTS / ARGUMENTS.numProcs;
    bsp_size_t prev = 0;
    bsp_size_t idx = numItems;

    bsp_size_t const SEG = 0;  // tags.
    bsp_size_t const LABEL = 1;

    for (bsp_pid_t proc = 0; proc != bsp_nprocs(); ++proc)
    {
        // This determines the label space available to each processor.
        bsp_send(proc, &LABEL, &NUM_VOXELS, sizeof(size_t));

        // Find the first index where there is a break in the x-values.
        while (SEGMENTS[idx - 1].x == SEGMENTS[idx].x && idx < NUM_SEGMENTS)
            idx++;

        // numItems rounds down, so this ensures the final few segments all go
        // to the last processor.
        if (proc == bsp_nprocs() - 1)
            idx = NUM_SEGMENTS;

        bsp_size_t const numBytes = (idx - prev) * sizeof(segment);

        // Sends a sub-matrix of segments to the other processor. This is
        // guaranteed to be split between x-values, not within.
        bsp_send(proc, &SEG, SEGMENTS + prev, numBytes);

        // Ensure the the processors share an x-slice. This looks 'back' to
        // determine the slice's extent.
        while (SEGMENTS[idx - 2].x == SEGMENTS[idx - 1].x && idx >= 2)
            idx--;

        // idx - 1 rather than idx, as we compare idx - 2 and idx - 1 above.
        prev = idx - 1;
        idx += numItems;
    }

    free(SEGMENTS);
}
