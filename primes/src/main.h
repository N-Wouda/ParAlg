#ifndef MAIN_H
#define MAIN_H

#include "primes.h"


/**
 * Converts command-line arguments (if given) to the appropriate passed-in
 * variables. If an argument or option is found, it is converted without
 * consideration to the argument's validity, which remains the user's
 * responsibility.
 *
 * @param argc      Number of arguments.
 * @param argv      Array of argument values.
 * @param bounds    Will be populated with a lower and upper bound. If the
 *                  lower bound is missing, it is set to zero. If the upper
 *                  bound is missing, the program terminates.
 * @param numProcs  Will be populated with the number of processor cores to
 *                  use. If the option is missing, this will be set to the
 *                  maximum number of cores available.
 */
void arguments(int argc, char **argv, bounds *bounds, size_t *numProcs);

#endif // MAIN_H
