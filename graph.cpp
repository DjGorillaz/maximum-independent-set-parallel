
#include <iostream>
//#include <boost/thread.hpp>

#include "graph.h"
#include <boost/config.hpp>
//#include <iostream>
//#include <fstream>
//#include <string>
#include <boost/graph/adjacency_list.hpp>

#include <time.h>
#include <cstdlib>

namespace MaximumIndependentSet
{
    Graph::Graph(int n, float conn): 
        nVertices(n),
        connectivity(conn),
        graphB(n)
    {
        //Generate graph
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

    void Graph::print() const
    {
        using namespace boost;
        
        std::size_t prev_vertex = 0;
        for (auto [curr, end] = edges(graphB); curr != end; ++curr)
        {
            auto curr_vertex = source(*curr, graphB);
            if (curr_vertex != prev_vertex) 
                std::cout << "\n";
            std::cout << *curr << " ";
            prev_vertex = curr_vertex;
        }
        std::cout << std::endl;
    }
}