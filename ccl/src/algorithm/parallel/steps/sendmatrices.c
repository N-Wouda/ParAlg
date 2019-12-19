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

    // TODO this might need more balancing than it currently has.
    size_t const numItems = mat.length / ARGUMENTS.numProcs;
    size_t prev = 0;
    size_t idx = numItems;

    for (size_t proc = 0; proc != bsp_nprocs(); ++proc)
    {
        if (idx >= mat.length)
            break;

        while (mat.x[idx - 1] == mat.x[idx] && idx < mat.length)
            idx++;

        matrix submat = {mat.x + prev, mat.y + prev, mat.z + prev, idx - prev};

        bsp_send(proc, NULL, submat.x, submat.length * sizeof(size_t));
        bsp_send(proc, NULL, submat.y, submat.length * sizeof(size_t));
        bsp_send(proc, NULL, submat.z, submat.length * sizeof(size_t));

        prev = idx;
        idx = prev + numItems;
    }

    free(mat.x);
    free(mat.y);
    free(mat.z);
}
