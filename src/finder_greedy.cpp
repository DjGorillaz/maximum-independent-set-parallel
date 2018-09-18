#include "finder_greedy.h"

namespace MaximumIndependentSet
{
    using namespace boost;

    FinderGreedy::FinderGreedy(const Graph& graph_, int nCpu_):
        Finder(graph_, "Greedy algorithm", nCpu_),
        ind_set_count(nVertices, 0),  //number of independent vertices for each vertex
        matrix(nVertices, std::vector<VertexProperties>(nVertices, {false,false}))
    {
        nTasks = nVertices;
    }

    void FinderGreedy::find_per_thread(int first, int last)
    {
        auto [currVertex, end] = vertices(graphB);
        currVertex += first;

        //The range of vertices is set for each CPU
        for(auto i = first; i <= last; ++currVertex, ++i)
        {
            find_per_vertex(*currVertex, i);
        }
    }

    void FinderGreedy::find_per_vertex(boost::graph_traits<GraphBoost>::vertex_descriptor startVertex, int i)
    {
        if(matrix[startVertex][i].viewed == true) //If the vertex is already viewed
            return;
        matrix[startVertex][i].viewed = true;
        matrix[startVertex][i].in_set = true;
        ++ind_set_count[i]; //Increase size of independent set

        //Look through all neighbors
        for(const auto& adjVertex: make_iterator_range(adjacent_vertices(startVertex, graphB)))
        {
            if(matrix[adjVertex][i].viewed == false) //The vertex isn't viewed
            {
                matrix[adjVertex][i].viewed = true;
                matrix[adjVertex][i].in_set = false;
            }
        }

        //Recursive call for all neighbors of neighbors
        for(const auto& adjVertex: make_iterator_range(adjacent_vertices(startVertex, graphB)))
        {
            for(const auto& adjAdjVertex: make_iterator_range(adjacent_vertices(adjVertex, graphB)))
            {
                find_per_vertex(adjAdjVertex, i);
            }
        }
    }

    void FinderGreedy::calc_result()
    {
        //Find maximal indpendent set
        auto max = std::max_element(ind_set_count.begin(), ind_set_count.end());
        max_independent_set.reserve(*max);
        index_max = static_cast<int>(std::distance(ind_set_count.begin(), max));
        
        for(int i = 0; i < nVertices; ++i)
        {
            if(matrix[i][index_max].in_set == true)
                max_independent_set.push_back(i);
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
