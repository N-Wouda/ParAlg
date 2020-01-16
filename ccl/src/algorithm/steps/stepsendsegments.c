#include "algorithm/parallel.h"
#include "algorithm/steps.h"

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

    for (bsp_pid_t proc = 0; proc != bsp_nprocs(); ++proc)
    {
        // This determines the label space available to each processor.
        bsp_send(proc, NULL, &NUM_VOXELS, sizeof(size_t));

        size_t low;
        size_t high;
        determineSegmentSlice(SEGMENTS,
                              NUM_SEGMENTS,
                              proc,
                              bsp_nprocs(),
                              &low,
                              &high);

        bsp_size_t const numBytes = (high - low) * sizeof(segment);

        // Sends a sub-matrix of segments to the other processor. This is
        // guaranteed to be split between x-values, not within.
        bsp_send(proc, NULL, SEGMENTS + low, numBytes);
    }

    // Release segments and matrix here. In the next superstep, we receive our
    // local segments for P(0).
    releaseMatrix(&mat);
    free(SEGMENTS);
}
