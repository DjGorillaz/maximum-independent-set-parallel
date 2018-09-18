
#include "graph.h"

#include <random>

namespace MaximumIndependentSet
{
    Graph::Graph(int n, float conn): 
        nVertices(n),
        connectivity(conn),
        graphB(n)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(0, 1.0);

        //Generate edges
        for(int i = 0; i < nVertices-1; ++i)
        {
            for(int j = i+1; j < nVertices; ++j)
            {
                if(dist(gen) < connectivity)
                {
                    boost::add_edge(i, j, graphB);
                }
            }
        }
    }

    Graph::Graph(const std::vector<std::pair<int,int>>& edges)
    {
        //Generate edges
        for(const auto& edge: edges)
        {
            boost::add_edge(edge.first, edge.second, graphB);
        }
        nVertices = static_cast<int>(num_vertices(graphB));
    }

    std::ostream& operator<<(std::ostream& os, const Graph& graph)
    {
        using namespace boost;

        //Check if graph is empty
        auto [curr_edge, end_edge] = edges(graph.graphB);
        if (curr_edge == end_edge)
        {
            os << "Graph without edges";
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
        return os;
    } 
}
