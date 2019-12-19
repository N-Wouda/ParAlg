#include "io.h"
#include "parallel/steps.h"

#include <bsp.h>
#include <stdlib.h>


void sendMatrices()
{
    if (bsp_pid() != 0)
        return;

    bool status;
    matrix const mat = readMatrix(CCL_ARGUMENTS.inLocation, &status);

    if (!status)
    {
        free(mat.x);
        free(mat.y);
        free(mat.z);

        bsp_abort("Something went wrong reading the matrix.\n");
    }

    // TODO this might need more balancing than it currently has.
    size_t const numItems = mat.length / CCL_ARGUMENTS.numProcs;
    size_t prev = 0;
    size_t idx = numItems;

    for (size_t proc = 0; proc != bsp_nprocs(); ++proc)
    {
        if (idx >= mat.length)
            break;

        while (mat.x[idx - 1] == mat.x[idx] && idx < mat.length)
            idx++;

        matrix submat = {mat.x + prev, mat.y + prev, mat.z + prev, idx - prev};

        enum tag xTag = X;
        bsp_send(proc, &xTag, submat.x, submat.length * sizeof(size_t));

        enum tag yTag = Y;
        bsp_send(proc, &yTag, submat.y, submat.length * sizeof(size_t));

        enum tag zTag = Z;
        bsp_send(proc, &zTag, submat.z, submat.length * sizeof(size_t));

        prev = idx;
        idx = prev + numItems;
    }

    free(mat.x);
    free(mat.y);
    free(mat.z);
}
