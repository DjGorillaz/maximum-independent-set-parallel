#include "finder.h"

namespace MaximumIndependentSet
{
    Finder::Finder(const Graph& graph_, const std::string& name,  int nCpu_ ):
        graph(graph_),
        nCpu(nCpu_),
        nVertices(graph_.nVertices),
        graphB(graph.graphB),
        algo_name(name)
    {    }

    void Finder::run2()
    {
        using namespace std::chrono;
        using namespace boost;

        auto start_time = high_resolution_clock::now();

        //todo: rename?
        unsigned long long nTasks = get_nTasks();

        unsigned long long perCpu = nTasks / nCpu;
        unsigned long long l = 0;
        unsigned long long r = perCpu - 1 + (nTasks % nCpu);
    
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

        //todo: rename? find MIS
        calc_result();

        auto end_time = high_resolution_clock::now();
        ms = duration_cast<milliseconds>(end_time-start_time);
    }

    
}
