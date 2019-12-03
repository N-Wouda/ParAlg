#include "sparse.h"

#include <stdio.h>


matrix_t readMatrix(char const *location, bool *status)
{
    matrix_t mat = {NULL, NULL, NULL, 0};

    FILE *file = fopen(location, "r");

    if (file == NULL)
    {
        *status = false;
        return mat;
    }

    // TODO

    fclose(file);
    *status = true;

    return mat;
}
