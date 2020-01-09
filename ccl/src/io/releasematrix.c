#include "io.h"

#include <stdlib.h>


void releaseMatrix(matrix const *mat)
{
    free(mat->x);
    free(mat->y);
    free(mat->z);
}
