#pragma once

#include "finder.h"
#include "graph.h"

namespace MaximumIndependentSet
{
    class FinderGreedy: public Finder
    {
    public:
        FinderGreedy(const Graph& graph, int nCpu = 1);
        void run() override;
        decltype(std::chrono::milliseconds().count()) get_time() const override;
        void get_result() const override;
        void print_result() const override;

    private:
        void find_per_thread(int first, int last);
        void find_per_vertex(boost::graph_traits<GraphBoost>::vertex_iterator startVertex, int i);
        // Map map; //key = vertex
        std::chrono::milliseconds ms;
        std::vector<int> vSetCount; //Number of vertices in each set
        std::map<boost::graph_traits<GraphBoost>::vertex_descriptor, std::vector<std::pair<bool, bool>>> map;
        int index_max = 0;
    };
}