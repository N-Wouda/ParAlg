#ifndef SEGMENT_H
#define SEGMENT_H

#include "sparse.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * Segment type. TODO
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
 * TODO
 *
 * @param mat
 * @param numSegments
 * @return
 */
segment_t *computeSegments(matrix_t const *mat, size_t *numSegments);

/**
 * TODO
 *
 * @param mat
 * @return
 */
size_t countSegments(matrix_t const *mat);

/**
 * TODO
 *
 * @param mat
 * @param idx
 * @return
 */
bool isNewSegment(matrix_t const *mat, size_t idx);

#endif  // SEGMENT_H
