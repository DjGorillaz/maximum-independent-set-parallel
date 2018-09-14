#pragma once

#include "finder.h"
#include "graph.h"

namespace MaximumIndependentSet
{
    class FinderBrute: public Finder
    {
    public:
        FinderBrute(const Graph& graph, int nCpu = 1);
        void run() override;
        decltype(std::chrono::milliseconds().count()) get_time() const override;
        void get_result() const override;
        void print_result() const override;

    private:
        void find_per_thread(unsigned long long first, unsigned long long last);
        void find_per_subset(std::vector<bool>& subset, unsigned long long& nSubset);
        std::chrono::milliseconds ms;
        std::map<boost::thread::id, std::pair<int, unsigned long long>> vSetCount; //Number of vertices
        // std::map<boost::graph_traits<GraphBoost>::vertex_descriptor, std::vector<bool>> map;
        int index_max = 0;
    };
}