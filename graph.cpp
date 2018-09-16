
#include "graph.h"

#include <time.h>
// #include <cstdlib>

namespace MaximumIndependentSet
{
    Graph::Graph(int n, float conn): 
        nVertices(n),
        connectivity(conn),
        graphB(n)
    {
        //Generate graph
        //todo
        srand(time(NULL));
        for(int i = 0; i < nVertices; ++i)
        {
            for(int j = i+1; j < nVertices; ++j)
            {
                if((static_cast<float>(rand() % 101) / 100) < connectivity)
                {
                    boost::add_edge(i, j, graphB);
                }
            }
        }
    }

    std::ostream& operator<<(std::ostream& os, const Graph& graph)
    {
        using namespace boost;

        auto [curr_edge, end_edge] = edges(graph.graphB);
        //No edges
        if (curr_edge == end_edge)
        {
            os << "Graph without edges\n";
            return os;
        }

        //Print edges
        auto prev_vertex = source(*curr_edge, graph.graphB);
        for (; curr_edge != end_edge; ++curr_edge)
        {
            auto curr_vertex = source(*curr_edge, graph.graphB);
            if (curr_vertex != prev_vertex) 
                os << "\n";
            os << *curr_edge << " ";
            prev_vertex = curr_vertex;
        }
        os << std::endl;
        return os;
    } 
}