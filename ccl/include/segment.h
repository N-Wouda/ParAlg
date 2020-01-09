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
    size_t zLast;  // exclusive

    // Determines which component this segment belongs to (parent), and how
    // many jumps are at most required to reach the root (rank).
    struct segment *parent;
    unsigned char rank;

    size_t label;
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
 * Checks if candidate segment precedes the target segment in iteration order.
 *
 * @param candidate Candidate segment.
 * @param target    Target segment.
 * @return          True if candidate precedes target, false otherwise.
 */
bool isBefore(segment const *candidate, segment const *target);

/**
 * Checks if candidate segment is equal to the target segment.
 *
 * @param candidate Candidate segment.
 * @param target    Target segment.
 * @return          True if candidate is equal to target, false otherwise.
 */
bool isEqual(segment const *candidate, segment const *target);

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
 * @param parent    Pointer to the segment's parent.
 * @return          Segment.
 */
segment makeSegment(matrix const *mat, size_t idx, segment *parent);

/**
 * Comparison helper for sorting segments by their coordinates.
 */
int segCmp(void const *a, void const *b);

/**
 * Prints the passed-in segment to stdout, in a human-readable format.
 *
 * @param seg   Segment to print.
 */
void segPrint(segment const *seg);

#endif  // SEGMENT_H
