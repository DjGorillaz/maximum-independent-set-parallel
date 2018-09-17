
#pragma once

#include <boost/graph/adjacency_list.hpp>

namespace MaximumIndependentSet
{
    using GraphBoost =  boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::undirectedS
    >;

    class Graph
    {
    public:
        Graph(int n, float conn);

    private:
        int nVertices;
        float connectivity;
        GraphBoost graphB; 

        friend class Finder;
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    };
}
