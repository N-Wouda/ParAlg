# ParAlg19

[![Build Status](https://travis-ci.com/N-Wouda/ParAlg.svg?branch=master)](https://travis-ci.com/N-Wouda/ParAlg)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c839ab5541964bf381063e3101657d6a)](https://www.codacy.com/manual/N-Wouda/ParAlg)

Assignments for the Parallel Algorithms course, taken in Fall 2019. This
repository consists of two parts, an initial assignment `primes` where we 
develop a parallel prime number sieve, and a larger project of our own 
choosing. TODO

## Primes

In `/primes`, we provide a sequential and parallel implementation of the
sieve of Eratosthenes. Several branches relate to this, as follows,

  * `baseline` contains the initial implementation of our sequential and
    parallel sieves, without any further enhancements.
      
  * `odd-k2` contains an initial search-space reduction, by considering only 
    odd primes (and two, the only even prime).
      
  * `six-k` contains an optimisation where we limit the search space even
    further.  
      
  * `twin-primes` contains code for generating only twin primes, that is,
    primes that surround an even number `k` as (`k - 1`, `k + 1`).
      
  * `goldbach` contains code for verifying the Goldbach conjecture in
    parallel.

Finally, we refer the reader to the paper in `primes/report.pdf`, which
explains the various algorithms in considerably more detail.

## Project

TODO

## Developing

Regarding development,

  * There is not really any one code style, but be reasonable. You might want
    to consider adopting the `Qt` style.
      
  * `CMake` is used as a build tool.
    
  * [`Unity`](http://www.throwtheswitch.org/unity) is our testing framework.

Finally, you will also need on your machine,

  * [`MulticoreBSP-for-C`](http://www.multicorebsp.com/download/) as it handles
    the nitty-gritty details of parallel communication.

## How to use

### Primes

First run _e.g._ `cmake primes` and `make`. This produces an executable, which
must be called with positive integer argument: the upper bound for the sieve 
(exclusive). Additionally, several optional arguments are available:

  * `l`, a value for the lower bound. When specified, the sieve operates over the
    interval `[lower bound, upper bound)`, rather than `[0, upper bound)`.
  * `p`, a value for the number of processors to use. When left unspecified, this
    defaults to the maximal number available.

Thus, ```bin/primes 100 -l 20 -p 3``` would run the parallel sieve over the 
interval `[20, 100)`, dividing the work between three processors.

### Project

TODO
