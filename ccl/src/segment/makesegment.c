#include "segment.h"


segment makeSegment(matrix const *mat, size_t idx, size_t parent)
{
    return (segment){mat->x[idx],
                     mat->y[idx],
                     mat->z[idx],
                     mat->z[idx] + 1,  // exclusive
                     parent,
                     0,
                     -1,    // dummy value
                     idx};  // default value
}
