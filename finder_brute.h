#pragma once

#include "finder.h"

namespace MaximumIndependentSet
{
    class FinderBrute: public Finder
    {
    public:
        FinderBrute(const Graph& graph, int nCpu = 1);
        decltype(std::chrono::milliseconds().count()) get_time() const override;
        std::vector<int> get_result() const override;
        std::string get_name() const override;

    private:
        unsigned long long get_nTasks() const override;
        void find_per_thread(unsigned long long first, unsigned long long last) override;
        void find_per_subset(std::vector<bool>& subset, unsigned long long& nSubset);
        void calc_result() override;

        std::map<boost::thread::id, std::pair<int, unsigned long long>> vSetCount;
    };
}