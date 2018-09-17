# Parallel algorithms for the maximal independent set problem 

[![Travis CI](https://travis-ci.org/DjGorillaz/maximum-independent-set-parallel.svg?branch=develop)](https://travis-ci.org/DjGorillaz/maximum-independent-set-parallel) [![Appveyor](https://ci.appveyor.com/api/projects/status/github/djgorillaz/maximum-independent-set-parallel?branch=develop&svg=true)](https://ci.appveyor.com/project/DjGorillaz/maximum-independent-set-parallel)

1. Brute force algorithm
2. Greedy algorithm (approximate solution)

This program uses boost/graph and boost/thread for parallelization.

## Complexity

* Brute force algorithm: O(n^2 * 2^n)
* Greedy algorithm: O(n^2)
