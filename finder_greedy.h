#pragma once

#include "finder.h"

namespace MaximumIndependentSet
{
    class FinderGreedy: public Finder
    {
    public:
        FinderGreedy(const Graph& graph, int nCpu = 1);
        decltype(std::chrono::milliseconds().count()) get_time() const override;
        std::vector<int> get_result() const override;
        std::string get_name() const override;

    private:
        unsigned long long get_nTasks() const override;
        void find_per_thread(unsigned long long first, unsigned long long last) override;
        void find_per_vertex(boost::graph_traits<GraphBoost>::vertex_iterator startVertex, unsigned long long i);
        void calc_result() override;

        std::vector<int> vSetCount; //Number of vertices in each set
        std::map<boost::graph_traits<GraphBoost>::vertex_descriptor, std::vector<std::pair<bool, bool>>> map; //Key = vertex
    };
}