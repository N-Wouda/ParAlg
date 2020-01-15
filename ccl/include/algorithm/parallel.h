#ifndef STEPS_H
#define STEPS_H

#include "segment.h"

#include <stddef.h>

/**
 * Local segments.
 */
extern _Thread_local segment *SEGMENTS;

/**
 * Number of segments in SEGMENTS.
 */
extern _Thread_local size_t NUM_SEGMENTS;

/**
 * Number of voxels in the target matrix. Doubles as the label space.
 *
 * Note: is made available on all other processors after the first sync.
 */
extern _Thread_local size_t NUM_VOXELS;

/**
 * Reads the matrix file (command-line argument) and sends a slice of segments
 * to each processor.
 */
void stepSendSegments();

/**
 * Has each processor compute local components, and communicate shared
 * components.
 */
void stepDetermineComponents();

/**
 * Has all processors decide, together, on a shared and consistent labelling
 * for shared components.
 */
void stepDetermineSharedComponents();

/**
 * Receive all labelled segments at the first processor, and write them to the
 * out file.
 */
void stepReceiveAndWriteSegments();

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
 * Returns the labelled segments to the first processor.
 */
void stepReturnLabelledSegments();

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

#endif  // STEPS_H
