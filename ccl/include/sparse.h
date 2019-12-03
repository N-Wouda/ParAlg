#ifndef SPARSE_H
#define SPARSE_H

#include <stdbool.h>
#include <stddef.h>

/**
 * 3D matrix type. TODO
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
 * @param location  Location to read the matrix from on the file system.
 * @param status    True if the matrix was correctly read, false otherwise.
 * @return          The matrix read from the passed-in location.
 */
matrix_t readMatrix(char *location, bool *status);

#endif  // SPARSE_H
