#include "sparse.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


matrix_t readMatrix(char const *location, bool *status)
{
    matrix_t mat = {NULL, NULL, NULL, 0};

    FILE *file = fopen(location, "r");

    if (file == NULL)
    {
        *status = false;
        return mat;
    }

    // TODO: this is a bit too large for a single function - should be factored
    // into multiple smaller ones. Is 20 characters sufficient for a buffer?
    char buffer[20];
    size_t idx = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (buffer[strlen(buffer) - 1] != '\n')
        {
            printf("Read line %zu: insufficient buffer space.\n", idx);

            *status = false;
            return mat;
        }

        char *line = buffer;
        int x, y, z;

        int numRead = sscanf(line, "%d %d %d", &x, &y, &z);

        assert(numRead == (idx == 0) ? 1 : 3);

        if (idx == 0)
        {
            // Only the first number was read (as there is just one), which is
            // stored in 'x'. This is the number of non-zeroes.
            mat.length = x;

            mat.x = malloc(mat.length * sizeof(size_t));
            mat.y = malloc(mat.length * sizeof(size_t));
            mat.z = malloc(mat.length * sizeof(size_t));
        }
        else
        {
            mat.x[idx - 1] = x;
            mat.y[idx - 1] = y;
            mat.z[idx - 1] = z;
        }

        idx++;
    }

    assert(idx == mat.length + 1);

    fclose(file);
    *status = true;

    return mat;
}
