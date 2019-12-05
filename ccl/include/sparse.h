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

typedef struct matrix matrix_t;

/**
 * Reads a binary, sparse 3D matrix from the file system.
 *
 * @param location  File system location to read the matrix from.
 * @param status    True if the matrix was correctly read, false otherwise.
 * @return          The matrix read from the passed-in location.
 */
matrix_t readMatrix(char const *location, bool *status);

#endif  // SPARSE_H
