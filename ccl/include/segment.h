#ifndef SEGMENT_H
#define SEGMENT_H

#include "sparse.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * segment type. TODO
 */
struct segment
{
    size_t x;
    size_t y;
    size_t z1;
    size_t z2;
};

typedef struct segment segment_t;


/**
 * Reads a sparse 3D matrix, and outputs all segments in it.
 *
 * @param matrix    Input matrix: must be sorted.
 * @return          a segment? which? TODO.
 */
segment_t getSegments(matrix_t mat);

#endif  // SEGMENT_H
