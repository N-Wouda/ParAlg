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

    bsp_size_t const numItems = NUM_SEGMENTS / bsp_nprocs();

    for (bsp_pid_t proc = 0; proc != bsp_nprocs(); ++proc)
    {
        // This determines the label space available to each processor.
        bsp_send(proc, NULL, &NUM_VOXELS, sizeof(size_t));

        // This is a nominal slice, but will be adjusted below to account for
        // any breaks in x-values.
        size_t low = proc * numItems;
        size_t high = (proc + 1) * numItems;

        if (proc != 0)
            while (SEGMENTS[low - 1].x == SEGMENTS[low].x && low > 0)
                low--;

        if (proc != bsp_nprocs() - 1)
            while (SEGMENTS[high - 1].x == SEGMENTS[high].x
                   && high < NUM_SEGMENTS)
                high++;
        else
            // numItems rounds down, so this ensures the final few segments all
            // go to the last processor.
            high = NUM_SEGMENTS;

        bsp_size_t const numBytes = (high - low) * sizeof(segment);

        // Sends a sub-matrix of segments to the other processor. This is
        // guaranteed to be split between x-values, not within.
        bsp_send(proc, NULL, SEGMENTS + low, numBytes);
    }

    // Release segments here. In the next superstep, we receive our local
    // segments for P(0).
    free(SEGMENTS);
}
