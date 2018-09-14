#pragma once

#include "graph.h"

#include <chrono>
#include <boost/thread.hpp>


namespace MaximumIndependentSet
{
    class Finder
    {
    public:
        Finder(const Graph& graph, int nCpu = 1);
        virtual void run() = 0;
        virtual decltype(std::chrono::milliseconds().count()) get_time() const = 0;
        virtual void get_result() const = 0;
        virtual void print_result() const = 0;

    protected:
        Graph graph;
        int nCpu = 0;
        std::chrono::milliseconds ms;
        int nVertices = 0;
        GraphBoost& graphB;
    };
}