#include "finder.h"

#include "graph.h"

namespace MaximumIndependentSet
{
    Finder::Finder(const Graph& graph_, int nCpu_):
        nCpu(nCpu_),
        graph(graph_),
        nVertices(graph_.nVertices),
        graphB(graph.graphB)
    {    }
}