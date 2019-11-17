#include "segment.h"

#include <assert.h>


size_t countSegments(short const *vector, size_t length)
{
    assert(length > 1);  // since we need to compare at least two values.

    // Start from one, as the last segment is not counted below: there are no
    // elements beyond it to compare with.
    size_t count = 1;

    // Count all crossings, that is, points where the next value is not equal
    // to the previous value.
    for (size_t idx = 1; idx != length; ++idx)
        count += vector[idx - 1] != vector[idx];

    return count;
}
