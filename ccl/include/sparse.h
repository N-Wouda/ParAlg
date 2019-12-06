#ifndef SPARSE_H
#define SPARSE_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Binary sparse 3D matrix. Has three indexed data members that together
 * represent all non-zero elements: x, y, and z. These are all of the same
 * length, indicated by the data member length. The n'th index is given by the
 * triplet (x[n], y[n], z[n]), where n in {0, 1, ..., length - 1}.
 */
struct matrix
{
    size_t *x;
    size_t *y;
    size_t *z;

    size_t length;
};

typedef struct matrix matrix;

#endif  // SPARSE_H
