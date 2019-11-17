#ifndef SEGMENT_H
#define SEGMENT_H

#include "ccltypes.h"

#include <stddef.h>


segment_t *computeSegments(short const *vector,
                           size_t length,
                           size_t numSegments);

size_t countSegments(short const *vector, size_t length);

void segment(matrix_t *matrix);

#endif  // SEGMENT_H
