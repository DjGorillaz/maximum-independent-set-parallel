#include "finder_brute.h"

namespace MaximumIndependentSet
{
    using namespace boost;

    FinderBrute::FinderBrute(const Graph& graph_, int nCpu_):
        Finder(graph_, "Brute force algorithm", nCpu_)
    {
        nTasks = static_cast<unsigned long long>(pow(2, nVertices));
    }
  
    void FinderBrute::find_per_thread(unsigned long long first, unsigned long long last)
    {
        //The range of subsets is set for each CPU
        for(auto i = first; i <= last; ++i)
        {
            //Convert number of subset to vector<bool>
            std::vector<bool> subset(nVertices, false);
            unsigned long long nSubset = i;
            for (int j = 0; j < nVertices; ++j) 
            {
                subset[j] = (nSubset >> j) & 1;
            }
            find_per_subset(subset, nSubset);
        }
    }

    void FinderBrute::find_per_subset(std::vector<bool>& subset, unsigned long long nSubset)
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
                auto [edge, isEdgeExists] = edge(k, l, graphB);
                if (isEdgeExists == true)
                    return;
            }
            ++curr_set_size;
        }

        //Update max_set_size for current thread
        auto thread_id = boost::this_thread::get_id();
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
                                    [](const auto& v1, const auto& v2){ return v1.second.first < v2.second.first;});
        index_max = max->second.second;

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
