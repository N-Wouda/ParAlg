#ifndef CCLTYPES_H
#define CCLTYPES_H

#include <stddef.h>


/**
 * A 3D coordinate, with members x, y, z (all size_t). These together index
 * some 3D matrix.
 */
struct coordinate
{
    size_t x;
    size_t y;
    size_t z;
};

typedef struct coordinate coordinate_t;

/**
 * A one-dimensional line segment, with a start and end coordinate.
 */
struct segment
{
    coordinate_t start;
    coordinate_t end;
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
