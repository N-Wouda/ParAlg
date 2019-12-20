#include "algorithm/parallel.h"
#include "io.h"

#include <bsp.h>
#include <stdlib.h>

/**
 * Releases heap-allocated memory for the passed-in matrix.
 */
static void release(matrix const *mat);

void sendMatrices()
{
    if (bsp_pid() != 0)
        return;

    bool status;
    matrix const mat = readMatrix(ARGUMENTS.inLocation, &status);

    if (!status)
    {
        release(&mat);
        bsp_abort("Something went wrong reading the matrix.\n");
    }

    size_t const numItems = mat.length / ARGUMENTS.numProcs;
    size_t prev = 0;
    size_t idx = numItems;

    for (size_t proc = 0; proc != bsp_nprocs(); ++proc)
    {
        if (idx >= mat.length)
            break;

        // Find the first index where there is a break in the x-values.
        while (mat.x[idx - 1] == mat.x[idx] && idx < mat.length)
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

    release(&mat);
}

static void release(matrix const *mat)
{
    free(mat->x);
    free(mat->y);
    free(mat->z);
}
