#include "main.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    if (!arguments(argc, argv))
        return EXIT_FAILURE;

    matrix_t mat = readMatrix("somewhere");

    printf("x = %zu, y = %zu, z = %zu\n", mat.xDim, mat.yDim, mat.zDim);

    for (size_t zIdx = 0; zIdx != mat.zDim; ++zIdx)
    {
        printf("z = %zu\n", zIdx);

        for (size_t xIdx = 0; xIdx != mat.xDim; ++xIdx)
        {
            for (size_t yIdx = 0; yIdx != mat.yDim; ++yIdx)
                printf("%d ", mat.data[zIdx][xIdx][yIdx]);

            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
