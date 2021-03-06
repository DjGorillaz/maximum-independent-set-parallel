#pragma once

#include "finder.h"

namespace MaximumIndependentSet
{
    class FinderGreedy: public Finder<int>
    {
    public:
        FinderGreedy(const Graph& graph, int nCpu = 1);
        decltype(std::chrono::milliseconds().count()) get_time() const override;
        std::vector<int> get_result() const override;
        std::string get_name() const override;

    private:
        void find_per_thread(int l, int r, int thread_id) override;
        void find_per_vertex(boost::graph_traits<GraphBoost>::vertex_descriptor startVertex, int i);
        void calc_result() override;

        struct VertexProperties
        {
            bool viewed = false;
            bool in_set = false;
        };

        std::vector<int> ind_set_count;
        std::vector<std::vector<VertexProperties>> matrix; //nVertices x nVertices
    };
}
