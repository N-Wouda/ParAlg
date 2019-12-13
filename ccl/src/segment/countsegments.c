#include "segment.h"


size_t countSegments(matrix const *mat)
{
    // Since the first segment cannot be compared (there's nothing before it),
    // we start at one, rather than zero.
    size_t count = 1;

    for (size_t idx = 1; idx != mat->length; ++idx)
        count += isNewSegment(mat, idx);

    return count;
}
