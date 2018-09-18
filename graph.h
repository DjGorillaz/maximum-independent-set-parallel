
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
        Graph(const std::vector<std::pair<int,int>>& edges);

    private:
        int nVertices = 0;
        float connectivity = 0;
        GraphBoost graphB = 0; 

        template<typename T>
        friend class Finder;
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    };
}
