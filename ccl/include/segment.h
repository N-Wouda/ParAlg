#ifndef SEGMENT_H
#define SEGMENT_H

#include "sparse.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * Segment structure. A segment is a single contiguous block of ones in the
 * z-dimension of the matrix. The contained elements are [zFirst, zLast)
 * (exclusive).
 */
struct segment
{
    size_t x;
    size_t y;

    size_t zFirst;
    size_t zLast;

    // Determines which component this segment belongs to, and how many jumps
    // are required to reach the root.
    size_t parent;
    size_t rank;

    long prevX;  // index to the start of x - 1 in the segments array.
    long currX;  // index to the start of x in the segments array.
};

typedef struct segment segment;


/**
 * Computes all segments in the given sparse matrix.
 *
 * @param mat           Sparse 3D matrix.
 * @param numSegments   Once computeSegments returns, this stores the number of
 *                      segments.
 * @return              Pointer to an array of segments of length numSegments.
 */
segment *computeSegments(matrix const *mat, size_t *numSegments);

/**
 * Counts the number of segments in the given sparse matrix.
 *
 * @param mat   Sparse 3D matrix.
 * @return      Number of segments.
 */
size_t countSegments(matrix const *mat);

/**
 * Determines if idx marks the start of a new segment, relative to idx - 1.
 * Assumes the matrix has at least two elements.
 *
 * @param mat   Sparse 3D matrix.
 * @param idx   Index into the matrix.
 * @return      True if idx marks a new segment, false if not.
 */
bool isNewSegment(matrix const *mat, size_t idx);

/**
 * Construct a new segment pointing to the indexed element in the 3D matrix.
 *
 * @param mat       Sparse 3D matrix.
 * @param idx       Index into the matrix.
 * @param parent    Index to the segment's parent.
 * @return          Segment.
 */
segment makeSegment(matrix const *mat, size_t idx, size_t parent);

#endif  // SEGMENT_H
