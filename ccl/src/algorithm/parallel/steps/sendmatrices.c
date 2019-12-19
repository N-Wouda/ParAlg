#include "io.h"
#include "parallel/steps.h"

#include <bsp.h>
#include <stdlib.h>


void sendMatrices()
{
    if (bsp_pid() != 0)
        return;

    bool status;
    matrix const mat = readMatrix(ARGUMENTS.inLocation, &status);

    if (!status)
    {
        free(mat.x);
        free(mat.y);
        free(mat.z);

        bsp_abort("Something went wrong reading the matrix.\n");
    }

    // TODO needs better balancing, and share a slice between processors.
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

        size_t const length = idx - prev;

        // Sends a submatrix to the other processor. This matrix is guaranteed
        // to be split between x-values, not within.
        bsp_send(proc, NULL, mat.x + prev, length * sizeof(size_t));
        bsp_send(proc, NULL, mat.y + prev, length * sizeof(size_t));
        bsp_send(proc, NULL, mat.z + prev, length * sizeof(size_t));

        prev = idx;
        idx += numItems;
    }

    free(mat.x);
    free(mat.y);
    free(mat.z);
}
