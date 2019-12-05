#include "segment.h"


segment_t makeSegment(matrix_t const *mat, size_t idx, size_t parent)
{
    return (segment_t){mat->x[idx],
                       mat->y[idx],
                       mat->z[idx],
                       mat->z[idx],
                       parent,
                       0};
}
