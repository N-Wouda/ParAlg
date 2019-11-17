#include "segment.h"


void segment(matrix_t *matrix)
{
    for (size_t zIdx = 0; zIdx != matrix->zDim; ++zIdx)
        for (size_t xIdx = 0; xIdx != matrix->xDim; ++xIdx)
        {
            size_t const numSegments = countSegments(matrix->data[zIdx][xIdx],
                                                     matrix->yDim);

            segment_t *segments = computeSegments(matrix->data[zIdx][xIdx],
                                                  matrix->yDim,
                                                  numSegments);

            // TODO
        }
}
