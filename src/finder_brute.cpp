#include "finder_brute.h"

namespace MaximumIndependentSet
{
    using namespace boost;

    FinderBrute::FinderBrute(const Graph& graph_, int nCpu_):
        Finder(graph_, "Brute force algorithm", nCpu_),
        ind_set_count(nCpu_, {0,0})
    {
        nTasks = static_cast<std::uintmax_t>(pow(2, nVertices));
    }
  
    void FinderBrute::find_per_thread(std::uintmax_t first, std::uintmax_t last, int thread_id)
    {
        //The range of subsets is set for each CPU
        for(auto i = first; i <= last; ++i)
        {
            //Convert number of subset to vector<bool>
            std::vector<bool> subset(nVertices, false);
            std::uintmax_t nSubset = i;
            for (int j = 0; j < nVertices; ++j) 
            {
                subset[j] = (nSubset >> j) & 1;
            }
            find_per_subset(subset, nSubset, thread_id);
        }
    }

    void FinderBrute::find_per_subset(std::vector<bool>& subset, std::uintmax_t nSubset, int thread_id)
    {
        int curr_set_size = 0;

        //Check vertices from vector pairwise
        for(int k = 0; k < nVertices; ++k)
        {
            if(subset[k] == false) continue; //Skip if vertex is not in subset

            for(int l = k+1; l < nVertices; ++l)
            {
                if (subset[l] == false) continue;

                //If edge is in the matrix => set is not independent
                auto [some_edge, isEdgeExists] = edge(k, l, get_graphB());
                if (isEdgeExists == true)
                    return;
            }
            ++curr_set_size;
        }

        //Update max_set_size for current thread
        auto& [max_set_size, nSubset_old] = ind_set_count[thread_id];
        if (curr_set_size > max_set_size) 
        {
            max_set_size = curr_set_size;
            nSubset_old = nSubset;
        }
    }

    void FinderBrute::calc_result()
    {
        //Find maximal indpendent set
        auto max = std::max_element(ind_set_count.begin(), ind_set_count.end(), 
                                    [](const auto& v1, const auto& v2){ return v1.first < v2.first;});
        index_max = max->second;

        for (int j = 0; j < nVertices; ++j) 
        {
            if (index_max >> j & 1)
                max_independent_set.emplace_back(j);
        }
    }
        
    decltype(std::chrono::milliseconds().count()) FinderBrute::get_time() const
    {        
        return ms.count();
    }
    
    std::vector<int> FinderBrute::get_result() const 
    {
        return max_independent_set;
    }

    std::string FinderBrute::get_name() const
    {
        return algo_name;
    }
}
