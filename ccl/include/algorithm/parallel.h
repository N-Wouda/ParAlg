#ifndef PARALLEL_H
#define PARALLEL_H

#include "segment.h"

#include <stddef.h>

/**
 * Labels components on the boundary. The boundary is assumed to be numSegments
 * long, and starting at from in the segments array. This method returns an
 * array of boundary component root segments, of length numRoots.
 *
 * @param segments      Segments array.
 * @param numSegments   Number of segments on the boundary.
 * @param from          Boundary index in the SEGMENTS array (first element).
 * @param numRoots      Number of boundary component roots.
 * @return              Boundary component root segments.
 */
segment *labelBoundary(segment const *segments,
                       size_t numSegments,
                       size_t from,
                       size_t *numRoots);

/**
 * Wrapper around <code>bsp_move</code> and queue handling. Receives passed-in
 * segments from the other processors.
 *
 * @param numSegments   Number of segments received.
 * @return              Array of segments.
 */
segment *receiveSegments(size_t *numSegments);

/**
 * Determines the processor that owns this segment, using the 'label trick'.
 *
 * @param candidate     Candidate segment.
 * @param labelSpace    Size of the label space for each processor.
 * @return              Owning processor ID.
 */
size_t getOwningProcessor(segment const *candidate, size_t labelSpace);

/**
 * Determines the segment slice indices [low, high) to allocate to processor
 * proc, given that there are numSegments segments and numProcs processors.
 *
 * @param segments      Segments array.
 * @param numSegments   Number of segments.
 * @param proc          Candidate processor.
 * @param numProcs      Number of processors.
 * @param low           Lower bound index, inclusive.
 * @param high          Upper bound index, exclusive.
 */
void determineSegmentSlice(segment const *segments,
                           size_t numSegments,
                           size_t proc,
                           size_t numProcs,
                           size_t *low,
                           size_t *high);

#endif  // PARALLEL_H
