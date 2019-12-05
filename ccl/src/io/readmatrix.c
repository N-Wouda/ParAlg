#include "io.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


matrix_t readMatrix(char const *location, bool *status)
{
    matrix_t mat = {NULL, NULL, NULL, 0};
    *status = false;

    FILE *file = fopen(location, "r");

    if (file == NULL)
        return mat;

    // TODO: this is a bit too large for a single function - should perhaps be
    // factored into multiple smaller ones.
    char buffer[20];  // is this sufficient for a buffer?
    size_t idx = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // The buffer size is insufficient.
        assert(buffer[strlen(buffer) - 1] == '\n');

        char *line = buffer;
        int x, y, z;

        int const numRead = sscanf(line, "%d %d %d", &x, &y, &z);

        // First line contains only the number of non-zeroes; all others x y z
        // triplets.
        assert(numRead == ((idx == 0) ? 1 : 3));

        if (idx == 0)
        {
            // Only the first number was read (as there is just one), which is
            // stored in 'x'.
            mat.length = x;

            mat.x = malloc(mat.length * sizeof(size_t));
            mat.y = malloc(mat.length * sizeof(size_t));
            mat.z = malloc(mat.length * sizeof(size_t));

            assert(mat.x != NULL && mat.y != NULL && mat.z != NULL);
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
