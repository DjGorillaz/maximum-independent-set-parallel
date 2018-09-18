#pragma once

#include "finder.h"

namespace MaximumIndependentSet
{
    class FinderBrute: public Finder<std::uintmax_t>
    {
    public:
        FinderBrute(const Graph& graph, int nCpu = 1);
        decltype(std::chrono::milliseconds().count()) get_time() const override;
        std::vector<int> get_result() const override;
        std::string get_name() const override;

    private:
        void find_per_thread(std::uintmax_t first, std::uintmax_t last) override;
        void find_per_subset(std::vector<bool>& subset, std::uintmax_t nSubset);
        void calc_result() override;

        std::map<boost::thread::id, std::pair<int, std::uintmax_t>> ind_set_count;
    };
}
