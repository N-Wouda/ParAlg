#ifndef STEPS_H
#define STEPS_H

#include "segment.h"

#include <stddef.h>

/**
 * Segments computed at determineComponents.
 */
extern _Thread_local segment *SEGMENTS;

/**
 * Number of segments in SEGMENTS.
 */
extern _Thread_local size_t NUM_SEGMENTS;

/**
 * Number of voxels in the target matrix.
 *
 * Note: this is only available on P(0)!
 */
extern _Thread_local size_t NUM_VOXELS;

/**
 * Reads the matrix file (command-line argument) and sends sub-matrices to each
 * processor.
 */
void stepSendMatrices();

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
 * long, and starting at from in the SEGMENTS variable.
 *
 * @param numSegments   Number of segments on the boundary.
 * @param from          Boundary index in the SEGMENTS array (first element).
 */
void labelAndSendBoundary(size_t numSegments, size_t from);

#endif  // STEPS_H
