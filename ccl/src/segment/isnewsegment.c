#include "segment.h"


bool isNewSegment(matrix_t const *mat, size_t idx)
{
    // We have a new segment every time we either jump on the x or y axis,
    // or the current z value is not contiguous with the previous z value.

    // clang-format off
    return mat->x[idx - 1] != mat->x[idx]
        || mat->y[idx - 1] != mat->y[idx]
        || mat->z[idx - 1] + 1 != mat->z[idx];
    // clang-format on
}
