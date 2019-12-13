#include "segment.h"


segment makeSegment(matrix const *mat, size_t idx, segment *parent)
{
    return (segment){mat->x[idx],
                     mat->y[idx],
                     mat->z[idx],
                     mat->z[idx] + 1,  // exclusive
                     parent,
                     0};
}
