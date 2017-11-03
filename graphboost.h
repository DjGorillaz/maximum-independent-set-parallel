#ifndef GRAPHBOOST_H
#define GRAPHBOOST_H

#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_name_t, vector<boost::tuple<bool,bool>> > > Graph;
typedef property_map<Graph, vertex_name_t>::type Map;

class GraphMatrix;

class GraphBoost
{
    int vNumber;            //Number of vertices
    vector<int> vSetCount;  //Number of vertices in each set
    int t;                  //Execution time
    Graph graph;            //Graph
    Map map;                //key = vertex

public:
    GraphBoost(int N);
    GraphBoost(GraphMatrix& graphM);
    void printGraph();
    void run(int proc);
    void printResult();

private:
    void findMaxIndependentSet(graph_traits<Graph>::vertex_iterator startVertex, int i);
    void findThread(int first, int second);

    friend class GraphMatrix;
};

#endif // GRAPHBOOST_H
