#include "component.h"

#include <assert.h>

/**
 * Finds the first segment where x = xKey, and y = yKey, if it exists - else
 * returns NULL.
 */
segment *find(segment *low, segment *high, size_t xKey, size_t yKey);

/**
 * Merges appropriate segments in [parent, seg] in the segments array. If any
 * pointer is NULL, nothing is done.
 */
void mergeSegments(segment *seg, segment *parent);

void makeComponents(segment *segments, size_t numSegments)
{
    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment seg = segments[idx];

        // If this segment belongs to a component, that component must extend
        // to (x - 1, y) or (x, y - 1): those have been considered before, as
        // the segments array is ordered.
        if (seg.x > 0)
            mergeSegments(&seg,
                          find(segments, segments + idx, seg.x - 1, seg.y));

        if (seg.y > 0)
            mergeSegments(&seg,
                          find(segments, segments + idx, seg.x, seg.y - 1));
    }
}

void mergeSegments(segment *seg, segment *parent)
{
    if (parent == NULL || seg == NULL)  // no-op.
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

segment *find(segment *low, segment *high, size_t xKey, size_t yKey)
{
    while (high >= low)
    {
        segment *mid = low + (high - low) / 2;

        assert(mid >= low && mid <= high);
        segment const curr = *mid;

        // Does curr equal the target segment?
        bool currIsTarget = curr.x == xKey && curr.y == yKey;

        // If we're at the lower end we cannot dereference mid - 1, so this
        // check is needed here.
        if (mid == low)
            return currIsTarget ? mid : NULL;

        assert(mid - 1 >= low);
        segment const prev = *(mid - 1);

        // Whether the previous and currently considered segments precede the
        // searched-for segment.
        bool prevBefore = prev.x < xKey || (prev.x == xKey && prev.y < yKey);
        bool currBefore = curr.x < xKey || (curr.x == xKey && curr.y < yKey);

        // We want the first matching target, so the previous segment must be
        // different. It is not sufficient that the current segment matches the
        // target (although that is of course also needed!).
        if (prevBefore && currIsTarget)
            return mid;

        if (currBefore)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return NULL;
}
