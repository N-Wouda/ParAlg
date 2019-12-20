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
 * Reads the matrix file (command-line argument) and sends sub-matrices to each
 * processor.
 */
void sendMatrices();

/**
 * Has each processor compute local components, and communicate shared
 * components.
 */
void determineComponents();

/**
 * Has all processors decide, together, on a shared and consistent labelling.
 */
void determineLabels();

#endif  // STEPS_H
