#include "component.h"

#include <assert.h>

_Thread_local segment NOT_FOUND = {};

/**
 * Finds the first segment where x = target.x, y = y.target, if it exists - else
 * returns NOT_FOUND.
 */
static segment *findNeighbour(segment *low, segment *high, segment *target);

/**
 * Merges appropriate segments in [parent, seg] in the segments array. If the
 * parent is NOT_FOUND, nothing is done.
 */
static void mergeSegments(segment *seg, segment *parent);

/**
 * Checks if candidate overlaps with target.
 */
static bool overlaps(segment const *candidate, segment const *target);

void makeComponents(segment *segments, size_t numSegments)
{
    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment seg = segments[idx];

        // If this segment belongs to an existing component, that component
        // must extend to (x - 1, y) or (x, y - 1), and it needs to be a
        // neighbour in the z-dimension: those have been considered before, as
        // the segments array is ordered.
        if (seg.x > 0)
        {
            segment target = {seg.x - 1, seg.y, seg.zFirst};
            mergeSegments(segments + idx,
                          findNeighbour(segments, segments + idx, &target));
        }

        if (seg.y > 0)
        {
            segment target = {seg.x, seg.y - 1, seg.zFirst};
            mergeSegments(segments + idx,
                          findNeighbour(segments, segments + idx, &target));
        }
    }
}

static void mergeSegments(segment *seg, segment *parent)
{
    if (parent == &NOT_FOUND)  // no-op.
        return;

    assert(parent <= seg);

    size_t const x = parent->x;  // x and y to look for. These must remain
    size_t const y = parent->y;  // the same during iteration.

    while (parent != seg)
    {
        // Candidate parent starts beyond the currently considered segment,
        // or the x and y don't match up anymore: these cannot be part of the
        // same component.
        if (parent->zFirst >= seg->zLast || parent->x != x || parent->y != y)
            break;

        // Candidate parent starts before the end (above check), and ends after
        // currently considered segment. Such parents must be part of the same
        // component.
        if (parent->zLast > seg->zFirst)
            merge(seg, parent);

        parent++;
    }
}

static bool overlaps(segment const *candidate, segment const *target)
{
    // clang-format off
    // The x's and y's need to agree, and the current segment must not be
    // before the target.
    return candidate->x == target->x
        && candidate->y == target->y
        && candidate->zLast > target->zFirst;
    // clang-format on
}

static segment *findNeighbour(segment *low, segment *high, segment *target)
{
    while (high >= low)  // high is inclusive.
    {
        segment *mid = low + (high - low) / 2;
        assert(mid >= low && mid <= high);

        if (mid == low)
        {
            if (overlaps(mid, target))
                return mid;
            else
            {
                // If the element exists, it must be near (the range cannot be
                // too large yet). So a simple linear search should be able to
                // find it, and not raise the big-O complexity of the method.
                for (segment *idx = low; idx <= high; ++idx)
                    if (idx->x == target->x && idx->y == target->y
                        && idx->zLast > target->zFirst)
                        return idx;
            }

            return &NOT_FOUND;
        }

        assert(mid - 1 >= low);
        segment const prev = *(mid - 1);

        // We want the first matching target, so the previous segment must be
        // different. It is not sufficient that the current segment matches the
        // target (although that is of course also needed!).
        if (isBefore(&prev, target) && overlaps(mid, target))
            return mid;

        if (isBefore(mid, target))
            low = mid + 1;
        else
            high = mid - 1;
    }

    return &NOT_FOUND;
}
