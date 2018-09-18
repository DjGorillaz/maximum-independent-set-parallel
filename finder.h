#pragma once

#include "graph.h"

#include <chrono>
#include <boost/thread.hpp>

namespace MaximumIndependentSet
{
    template<typename T>
    class Finder
    {
    public:
        Finder(const Graph& graph, const std::string& name, int nCpu = 1);
        virtual decltype(std::chrono::milliseconds().count()) get_time() const = 0;
        virtual std::vector<int> get_result() const = 0;
        virtual std::string get_name() const = 0;
        
        void run();

    private:
        virtual void find_per_thread(T l, T r) = 0;
        virtual void calc_result() = 0;

    protected:
        Graph graph;
        GraphBoost& graphB;
        int nCpu = 0;
        int nVertices = 0;
        T nTasks = 0;
        std::string algo_name;
        std::chrono::milliseconds ms {0};
        std::vector<int> max_independent_set;
        T index_max = 0;
    };

    template<typename T>
    Finder<T>::Finder(const Graph& graph_, const std::string& name, int nCpu_):
        graph(graph_),
        graphB(graph.graphB),
        nCpu(nCpu_),
        nVertices(graph_.nVertices),
        algo_name(name)
    {    }

    template<typename T>
    void Finder<T>::run()
    {
        using namespace std::chrono;
        using namespace boost;

        auto start_time = high_resolution_clock::now();

        T perCpu = nTasks / nCpu;
        T l = 0;
        T r = perCpu - 1 + (nTasks % nCpu);
    
        //Parallelization of task
        thread_group threadGroup;
        while(l < nTasks)
        {
            thread* th = new thread(&Finder::find_per_thread, this, l, r);
            threadGroup.add_thread(th);
            l = r + 1;
            r = r + perCpu;
        }
        threadGroup.join_all();

        calc_result();

        auto end_time = high_resolution_clock::now();
        ms = duration_cast<milliseconds>(end_time-start_time);
    }
}
