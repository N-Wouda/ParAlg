#include "segment.h"


segment makeSegment(matrix const *mat, size_t idx)
{
    return (segment){mat->x[idx],
                     mat->y[idx],
                     mat->z[idx],
                     mat->z[idx] + 1,  // exclusive
                     NULL,
                     0,
                     idx};  // initially, each segment has its own label (index)
}
