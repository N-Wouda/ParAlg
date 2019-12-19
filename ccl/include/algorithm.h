#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "segment.h"
#include "sparse.h"

/**
 * TODO.
 *
 * @param mat
 * @param numSegments
 * @return
 */
segment *sequential(matrix const *mat, size_t *numSegments);

/**
 * TODO.
 */
void parallel();

#endif  // ALGORITHM_H
