#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

class GraphBoost;

class GraphMatrix
{
    int vNumber;    //Number of vertices
    bool** graph;   //Graph
    int t;          //Execution time
    int proc;       //Number of processors
    int* maxSizes;  //Maximum size of maximal independent set for each processor
    unsigned long long* setNumbers; //Number of set

public:
    GraphMatrix(int N);
    GraphMatrix(GraphBoost& graphB);
    void printGraph();
    void run(int proc);
    void printResult();

private:
    void findMaxIndependentSet(bool* vector, unsigned long long l, unsigned long long r, unsigned long long* setNumber, int* maxSize);


    friend class GraphBoost;
};


#endif // GRAPHMATRIX_H
