#include "algorithm/parallel.h"
#include "io.h"

#include <bsp.h>


void stepSendMatrices()
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

    size_t const numItems = NUM_VOXELS / ARGUMENTS.numProcs;
    size_t prev = 0;
    size_t idx = numItems;

    for (size_t proc = 0; proc != bsp_nprocs(); ++proc)
    {
        // This determines the label space available to each processor.
        bsp_send(proc, NULL, &NUM_VOXELS, sizeof(size_t));

        if (idx >= NUM_VOXELS)
            break;

        // Find the first index where there is a break in the x-values.
        while (mat.x[idx - 1] == mat.x[idx] && idx < NUM_VOXELS)
            idx++;

        size_t const numBytes = (idx - prev) * sizeof(size_t);

        // Sends a sub-matrix to the other processor. This matrix is guaranteed
        // to be split between x-values, not within.
        bsp_send(proc, NULL, mat.x + prev, numBytes);
        bsp_send(proc, NULL, mat.y + prev, numBytes);
        bsp_send(proc, NULL, mat.z + prev, numBytes);

        // Ensure the the processors share an x-slice. This looks 'back' to
        // determine the slice's extent.
        while (mat.x[idx - 2] == mat.x[idx - 1] && idx >= 2)
            idx--;

        // idx - 1 rather than idx, as we compare idx - 2 and idx - 1 above.
        prev = idx - 1;
        idx += numItems;
    }

    releaseMatrix(&mat);
}
