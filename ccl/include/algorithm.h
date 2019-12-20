#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "segment.h"
#include "sparse.h"

/**
 * Applies the sequential algorithm to compute and label segments from the
 * passed-in matrix.
 *
 * @param mat           Sparse binary 3D matrix.
 * @param numSegments   Number of segments (RBA).
 * @return              Segments, where each is assigned to a connected
 *                      component.
 */
segment *sequential(matrix const *mat, size_t *numSegments);

/**
 * Applies the parallel algorithm to read, label, and write a 3D binary
 * matrix. All relevant arguments are taken from the command line.
 */
void parallel();

#endif  // ALGORITHM_H
