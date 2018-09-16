#include "finder_greedy.h"

namespace MaximumIndependentSet
{
    using namespace boost;

    FinderGreedy::FinderGreedy(const Graph& graph_, int nCpu_):
        Finder(graph_, "Greedy algorithm", nCpu_),
        vSetCount(nVertices, 0)  //number of independent vertices for each vertex
    {
        //Create N-length vector for each vertex
        for(const auto& vertex: make_iterator_range(vertices(graphB)))
        {
            map.emplace(vertex, std::vector<std::pair<bool, bool>>(nVertices, {false, false}));
        }
    }
 
    unsigned long long FinderGreedy::get_nTasks() const
    {
        return static_cast<unsigned long long>(nVertices);
    }

    void FinderGreedy::find_per_thread(unsigned long long first, unsigned long long last)
    {
        auto [currVertex, end] = vertices(graphB);
        currVertex += first;

        //The range of vertices is set for each CPU
        for(auto i = first; i <= last; ++currVertex, ++i)
        {
            find_per_vertex(currVertex, i);
        }
    }

    void FinderGreedy::find_per_vertex(boost::graph_traits<GraphBoost>::vertex_iterator startVertex, unsigned long long i)
    {
        if(get<0>(map[*startVertex][i]) == true) //If the vertex is already viewed
            return;
        get<0>(map[*startVertex][i]) = true; //The vertex is viewed
        get<1>(map[*startVertex][i]) = true; //The vertex is already in set
        vSetCount[i] += 1; //Increase size of independent set by 1

        //Look through all neighbors
        for(const auto& adjVertex: make_iterator_range(adjacent_vertices(*startVertex, graphB)))
        {
            if(get<0>(map[adjVertex][i]) == false) //The vertex isn't viewed
            {
                get<0>(map[adjVertex][i]) = true; //The vertex is viewed
                get<1>(map[adjVertex][i]) = false; //The vertex is not in set
            }
        }

        //Look through all neighbors
        for(const auto& adjVertex: make_iterator_range(adjacent_vertices(*startVertex, graphB)))
        {
            //Look through all neighbors of neighbors
            for(const auto& adjAdjVertex: make_iterator_range(adjacent_vertices(adjVertex, graphB)))
            {
                //Recursive call
                find_per_vertex(graph_traits<GraphBoost>::vertex_iterator(adjAdjVertex), i);
            }
        }
    }

    void FinderGreedy::calc_result()
    {
        //Find maximal indpendent set
        auto max = std::max_element(vSetCount.begin(), vSetCount.end());
        index_max = std::distance(vSetCount.begin(), max);
        
        for(const auto& vertex: make_iterator_range(vertices(graphB)))
        {
            if(get<1>(map[vertex][index_max]) == true) //Is in set
                max_independent_set.push_back(static_cast<int>(vertex));
        }
    }

    decltype(std::chrono::milliseconds().count()) FinderGreedy::get_time() const
    {        
        return ms.count();
    }
    
    std::vector<int> FinderGreedy::get_result() const 
    {
        return max_independent_set;
    }

    std::string FinderGreedy::get_name() const
    {
        return algo_name;
    }
}