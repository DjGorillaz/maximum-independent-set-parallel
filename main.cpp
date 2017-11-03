#include <iostream>

#include "graphboost.h"
#include "graphmatrix.h"

int main()
{
    cout << "Enter number of vertices ";
    int N;
    cin >> N;

    //Number of processors
    int processorCount = 4;

    //Brute force
    GraphMatrix bruteForce(N);
    bruteForce.printGraph();
    bruteForce.run(processorCount);
    bruteForce.printResult();

    //Greedy, the same graph
    GraphBoost greedy(bruteForce);
    //greedy.printGraph();
    greedy.run(processorCount);
    greedy.printResult();

    return 0;
}
