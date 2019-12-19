#ifndef STEPS_H
#define STEPS_H

#include <stddef.h>

struct bspSteps
{
    size_t numSteps;
    void (*steps[])(void);
};

/**
 * TODO.
 */
void sendMatrices();

/**
 * TODO.
 */
void computeLabels();

/**
 * Tracks the BSP super-steps.
 */
extern struct bspSteps BSP_STEPS;

#endif  // STEPS_H
