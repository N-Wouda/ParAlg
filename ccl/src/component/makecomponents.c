#include "component.h"

#include <assert.h>

/**
 * Finds the first segment where x = xKey, and y = yKey, if it exists - else
 * returns NULL.
 */
segment *find(segment *segments, size_t idx, size_t xKey, size_t yKey);

/**
 * Searches for and merges seg with the appropriate segments determined by xKey
 * and yKey.
 */
void findAndMerge(segment *segments, size_t idx, size_t xKey, size_t yKey);

/**
 * Merges appropriate segments in [parent, seg] in the segments array.
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
            findAndMerge(segments, idx, seg.x - 1, seg.y);

        if (seg.y > 0)
            findAndMerge(segments, idx, seg.x, seg.y - 1);
    }
}

void findAndMerge(segment *segments, size_t idx, size_t xKey, size_t yKey)
{
    segment seg = segments[idx];
    segment *offset = find(segments, idx, xKey, yKey);

    if (offset != NULL)
        mergeSegments(&seg, offset);
}

void mergeSegments(segment *seg, segment *parent)
{
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
        // currently considered segment. These must be part of the same
        // component.
        if (parent->zLast > seg->zFirst)
            merge(seg, parent);

        parent++;
    }
}

segment *find(segment *segments, size_t idx, size_t xKey, size_t yKey)
{
    size_t low = 0, high = idx;

    while (high >= low)
    {
        size_t mid = low + (high - low) / 2;

        assert(mid >= low && mid <= high);
        segment const curr = segments[mid];

        // If we're at the lower end we cannot dereference segments[mid - 1],
        // so this check is needed here.
        if (mid == low)
            return curr.x == xKey && curr.y == yKey ? segments + mid : NULL;

        assert(mid - 1 >= low);
        segment const prev = segments[mid - 1];

        // Whether the previous and currently considered segment are smaller
        // than the searched-for segment.
        bool prevSmaller = prev.x < xKey || (prev.x == xKey && prev.y < yKey);
        bool currSmaller = curr.x < xKey || (curr.x == xKey && curr.y < yKey);

        if (prevSmaller)
            return segments + mid;

        if (currSmaller)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return NULL;
}
