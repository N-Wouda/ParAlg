#ifndef CCLTYPES_H
#define CCLTYPES_H

#include <stddef.h>

/**
 * A one-dimensional line segment, with a start and end position (inclusive).
 */
struct segment
{
    size_t start;
    size_t end;
};

typedef struct segment segment_t;

/**
 * 3D matrix type. Has members xDim, yDim, and zDim (all size_t), representing
 * the size of the member data (indexed as data[x][y][z]).
 */
struct matrix
{
    size_t xDim;
    size_t yDim;
    size_t zDim;

    short ***data;
};

typedef struct matrix matrix_t;

#endif  // CCLTYPES_H
