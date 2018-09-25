#include <iostream>
#include <thread>
#include <variant>

#include "finder_greedy.h"
#include "finder_brute.h"
#include "visit_variant.h"

namespace MIS = MaximumIndependentSet;

int main()
{
    try
    {
        std::cout << "Enter number of vertices\n";
        int nVertices = 0;
        std::cin >> nVertices;

        while(std::cin.fail() || nVertices <= 0) 
        {
            std::cout << "Error. Value must be greater than zero\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> nVertices;
        }

        unsigned int nCpu = std::thread::hardware_concurrency(); // Get number of CPUs
        //If value is not defined => return value = 0
        if(nCpu == 0) nCpu = 1;
        std::cout << nCpu << " threads are supported\n\n";

        float connectivity = 0.6f;
        MIS::Graph gm(nVertices, connectivity);
        std::cout << "Generated graph:\n" << gm << "\n";

        std::array<std::variant<MIS::FinderGreedy,
                                MIS::FinderBrute>,
                                2>
                    finders = {MIS::FinderGreedy(gm, nCpu),
                               MIS::FinderBrute(gm, nCpu)};
        
        visit_variant(finders.begin(), finders.end(), [](auto& finder) 
        { 
            finder.run();
            std::cout << "\n" << finder.get_name() << "\n"
                      << "Time: " << finder.get_time() << " ms\n"
                      << "Result:\t(";
                      
            std::string delimiter = "";
            for(const auto& vertex: finder.get_result())
            {
                std::cout << delimiter << vertex;
                delimiter = ", ";
            }
            std::cout << ")\n";
        });
    }
    catch(std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    
    return 0;
}
