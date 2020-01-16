#ifndef STEPS_H
#define STEPS_H

#include "io.h"
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
 * Wrapper around <code>bsp_move</code> and queue handling. Receives passed-in
 * segments from the other processors.
 *
 * @param numSegments   Number of segments received.
 * @return              Array of segments.
 */
segment *receiveSegments(size_t *numSegments);

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
 * Returns the labelled segments to the first processor.
 */
void stepReturnLabelledSegments();

#endif  // STEPS_H
