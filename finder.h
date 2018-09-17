#pragma once

#include "graph.h"

#include <chrono>
#include <boost/thread.hpp>

namespace MaximumIndependentSet
{
    class Finder
    {
    public:
        Finder(const Graph& graph, const std::string& name, int nCpu = 1);
        virtual decltype(std::chrono::milliseconds().count()) get_time() const = 0;
        virtual std::vector<int> get_result() const = 0;
        virtual std::string get_name() const = 0;
       
        void run();

    private:
        virtual void find_per_thread(unsigned long long l, unsigned long long r) = 0;
        virtual void calc_result() = 0;

    protected:
        Graph graph;
        GraphBoost& graphB;
        int nCpu = 0;
        int nVertices = 0;
        unsigned long long nTasks = 0;
        std::string algo_name;
        std::chrono::milliseconds ms {0};
        std::vector<int> max_independent_set;
        unsigned long long index_max = 0;
    };
}
