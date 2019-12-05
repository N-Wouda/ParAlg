#ifndef SEGMENT_H
#define SEGMENT_H

#include "sparse.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * Segment structure. A segment is a single contiguous block of ones in the
 * z-dimension of the matrix. The contained elements are [zFirst, zLast]
 * (inclusive).
 */
struct segment
{
    size_t x;
    size_t y;

    size_t zFirst;
    size_t zLast;

    // Determines which component this segment belongs to. TODO
    size_t parent;
};

typedef struct segment segment_t;


/**
 * Computes all segments in the given sparse matrix.
 *
 * @param mat           Sparse 3D matrix.
 * @param numSegments   Once computeSegments returns, this stores the number of
 *                      segments.
 * @return              Pointer to an array of segments of length numSegments.
 */
segment_t *computeSegments(matrix_t const *mat, size_t *numSegments);

/**
 * Counts the number of segments in the given sparse matrix.
 *
 * @param mat   Sparse 3D matrix.
 * @return      Number of segments.
 */
size_t countSegments(matrix_t const *mat);

/**
 * Determines if idx marks the start of a new segment, relative to idx - 1.
 * Assumes the matrix has at least two elements.
 *
 * @param mat   Sparse 3D matrix.
 * @param idx   Index into the matrix.
 * @return      True if idx marks a new segment, false if not.
 */
bool isNewSegment(matrix_t const *mat, size_t idx);

#endif  // SEGMENT_H
