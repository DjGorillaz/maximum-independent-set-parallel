# Parallel algorithms for the maximum independent set problem 

[![Travis CI](https://travis-ci.org/DjGorillaz/maximum-independent-set-parallel.svg?branch=develop)](https://travis-ci.org/DjGorillaz/maximum-independent-set-parallel) [![Appveyor](https://ci.appveyor.com/api/projects/status/github/djgorillaz/maximum-independent-set-parallel?branch=develop&svg=true)](https://ci.appveyor.com/project/DjGorillaz/maximum-independent-set-parallel)

This program solves maximum independent set problem[<sup>1</sup>] using parallel algorithms (brute force and greedy).

[<sup>1</sup>]: https://en.wikipedia.org/wiki/Maximal_independent_sethttp://eigen.tuxfamily.org/index.php?title=Main_Page

## Built With

* The Boost Graph Library
* Boost Thread

# Problem
Given an undirected graph ![graph], find the maximum-cardinality subset ![subset] such that no two vertices in ![Qmax] is adjacent.

![Qmax_o], 

where,  ![omega]

[graph]: https://latex.codecogs.com/gif.latex?G=(V,E)
[subset]: https://latex.codecogs.com/gif.latex?Q_{max}&space;\subseteq&space;V
[Qmax]: https://latex.codecogs.com/gif.latex?Q_{max}
[Qmax_o]: https://latex.codecogs.com/gif.latex?\left|Q_{max}\right|=max_{Q\in\Omega}|Q|
[omega]: https://latex.codecogs.com/gif.latex?\Omega=\{Q\subset&space;V\mid\forall&space;u,v\in&space;Q,(u,v)\notin&space;E\}

## Example

![mis-example](/docs/mis_example.png)

Maximal independent set is:

![Qmax_example](https://latex.codecogs.com/gif.latex?Q_{max}=\{2,5,8,9,11,12,18,20\})

# Algorithm

## Brute force algorithm
For each subset (2^n) check adjacency matrix (n^2).

**Complexity:** O(n^2 * 2^n)

Amdahl's law:

![sequential_part_brute](https://latex.codecogs.com/gif.latex?f=\frac{n^2}{n^2\cdot2^n}=\frac{1}{2^n})

![Amdahl_brute](https://latex.codecogs.com/gif.latex?S_p\leqslant\frac{1}{f&plus;\frac{1-f}{p}}=\frac{2^np}{2^n-1&plus;p}\approx&space;p)

where
* f - sequential part of algorithm;
* p - number of processors;
* Sp - theoretical speedup of the whole task.

## Greedy algorithm (approximate solution)
Start from each vertex of graph and make recursive calls for adjacency vertices.

**Complexity**: O(n^2)

Amdahl's law: 

![sequential_part_greedy](https://latex.codecogs.com/gif.latex?f=\frac{n}{n^2}=\frac{1}{n})

![Amdahl_greedy](https://latex.codecogs.com/gif.latex?S_p\leqslant\frac{1}{f&plus;\frac{1-f}{p}}=\frac{np}{n-1&plus;p}\approx&space;p)
