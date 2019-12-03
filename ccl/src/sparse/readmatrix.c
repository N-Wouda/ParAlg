#include "sparse.h"

#include <stdio.h>


matrix_t readMatrix(char *location, bool *status)
{
    matrix_t mat = {NULL, NULL, NULL, 0};

    FILE *file = fopen(location, "r");

    if (file == NULL)
    {
        *status = false;
        return mat;
    }

    // TODO

    return mat;
}
