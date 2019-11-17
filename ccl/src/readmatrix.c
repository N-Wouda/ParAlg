#include "ccltypes.h"

#include <stdlib.h>


matrix_t readMatrix(char *location)
{
    // TODO read from file location, maybe add status return-by-argument.

    short ***data = (short ***) malloc(3 * sizeof(short **));

    short init[3][3][3] = {{{1, 0, 1}, {0, 0, 0}, {1, 0, 0}},
                           {{1, 0, 0}, {0, 0, 0}, {1, 0, 0}},
                           {{1, 0, 0}, {0, 0, 0}, {1, 1, 0}}};

    for (size_t zIdx = 0; zIdx != 3; ++zIdx)  // z indexes the layers.
    {
        data[zIdx] = (short **) malloc(3 * sizeof(short *));

        // For each layer, x is top to bottom.
        for (size_t xIdx = 0; xIdx != 3; ++xIdx)
        {
            data[zIdx][xIdx] = (short *) malloc(3 * sizeof(short));

            // And y left to right.
            for (size_t yIdx = 0; yIdx != 3; ++yIdx)
                data[zIdx][xIdx][yIdx] = init[zIdx][xIdx][yIdx];
        }
    }

    return (struct matrix){3, 3, 3, data};
}
