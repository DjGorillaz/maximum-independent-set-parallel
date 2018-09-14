#include "finder_greedy.h"

#include <iostream>
#include <chrono>
#include <algorithm>

#include <boost/thread.hpp>

namespace MaximumIndependentSet
{
    using namespace boost;

    FinderGreedy::FinderGreedy(const Graph& graph_, int nCpu_):
        Finder(graph_, nCpu_)
    {
        //Create N-length vector for each vertex
        for(auto [curr, end] = vertices(graphB); curr != end; ++curr)
        {
            map.emplace(*curr, std::vector<std::pair<bool, bool>>(nVertices, {false, false}));
        }

        vSetCount.resize(nVertices, 0); //This vector contains number of independent vertices for each vertex
    }
    
    void FinderGreedy::run()
    {
        using namespace std::chrono;
        auto t0 = high_resolution_clock::now();
       
        int perCpu = nVertices / nCpu;

        int l = 0;
        int r = perCpu - 1 + (nVertices % nCpu);


        thread_group threadGroup;
        //Parallelization of task
        while(l < nVertices)
        {
            thread* th = new thread(&FinderGreedy::find_per_thread, this, l, r);
            threadGroup.add_thread(th);
            l = r + 1;
            r = r + perCpu;
        }
        
        threadGroup.join_all();

        //Find maximal indpendent set
        int maxCount = 0, index = 0;

        auto max = std::max_element(vSetCount.begin(), vSetCount.end());
        index_max = std::distance(vSetCount.begin(), max);
        /*
        for(int i = 0; i < vSetCount.size(); ++i)
        {
            if(vSetCount[i] > maxCount)
            {
                maxCount = vSetCount[i];
                index = i;
            }
        }
        */

        auto t1 = high_resolution_clock::now();
        ms = duration_cast<milliseconds>(t1-t0);
    }

    void FinderGreedy::find_per_thread(int first, int last)
    {
        // auto start = vertex(first, boost_graph);
        //The range of vertices is set for each processor
        auto [currVertex, end] = vertices(graphB);
        currVertex += first;

        for(int i = first; i <= last; ++currVertex, ++i)
        {
            find_per_vertex(currVertex, i);
        }
    }

    void FinderGreedy::find_per_vertex(boost::graph_traits<GraphBoost>::vertex_iterator startVertex, int i)
    {
        //hello
        if(get<0>(map[*startVertex][i]) == true) //If the vertex is already viewed
            return;
        get<0>(map[*startVertex][i]) = true; //The vertex is viewed
        get<1>(map[*startVertex][i]) = true; //The vertex is already in set
        vSetCount[i] += 1; //Increase size of independent set by 1

        auto [adjStart, adjEnd] = adjacent_vertices(*startVertex, graphB);
        //Look through all neighbors
        for(; adjStart != adjEnd; ++adjStart)
        {
            if(get<0>(map[*adjStart][i]) == false) //The vertex isn't viewed
            {
            get<0>(map[*adjStart][i]) = true; //The vertex is viewed
            get<1>(map[*adjStart][i]) = false; //The vertex is not in set
            }
        }

        //Look through all neighbors
        boost::tie(adjStart, adjEnd) = adjacent_vertices(*startVertex, graphB);
        for(; adjStart != adjEnd; ++adjStart)
        {
            //Look through all neighbors of neighbors
            graph_traits<GraphBoost>::adjacency_iterator adj2Start, adj2End;
            boost::tie(adj2Start, adj2End) = adjacent_vertices(*adjStart, graphB);
            for(; adj2Start != adj2End; ++adj2Start)
            {
                //Recursive call
                find_per_vertex(graph_traits<GraphBoost>::vertex_iterator(*adj2Start), i);
            }
        }
    }

    void FinderGreedy::print_result() const
    {
        std::cout << "Greedy algorithm\n";
        // std::cout << "Size: " << index_max << " vertices\n";
        std::cout << "Result: ( ";
        // auto [start, end] = vertices(graphB);

        for(int i = 0; i < nVertices; ++i)
        {
                if(std::get<1>(map.at(index_max).at(i)))
                    std::cout << i << " ";
        }
            std::cout << ")\n\n";
    }
        
    decltype(std::chrono::milliseconds().count()) FinderGreedy::get_time() const
    {        
        return ms.count();
    }
    
    void FinderGreedy::get_result() const 
    {
        std::cout << "result\n";
    }
}