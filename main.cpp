#include <iostream>
#include <thread>
#include <variant>

#include "finder_greedy.h"
#include "finder_brute.h"

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

        std::array<std::variant<std::unique_ptr<MIS::Finder<int>>,
                                std::unique_ptr<MIS::Finder<std::uintmax_t>>>,
                                2>
                    finders =   {std::make_unique<MIS::FinderGreedy>(gm, nCpu),
                                 std::make_unique<MIS::FinderBrute>(gm, nCpu)};

        for(const auto& variant_finder: finders)
        {
            std::visit(
                [](const auto& finder){
                    finder->run();
                    std::cout << "\n" << finder->get_name() << "\n";
                    std::cout << "Time: " << finder->get_time() << " ms\n";
                },
                variant_finder);

            std::cout << "Result:\t(";
            
            auto vertices = std::visit(
                [](const auto& finder){
                    return finder->get_result();
                },
                variant_finder);

            //std::make_ostream_joiner - iterator/experimental
            //std::copy(max_independent_set.begin(), max_independent_set.end(), std::make_ostream_joiner(std::cout, " "));
            std::string delimiter = "";
            for(const auto& vertex: vertices)
            {
                std::cout << delimiter << vertex;
                delimiter = ", ";
            }
            std::cout << ")\n";
        }
    }
    catch(std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    
    return 0;
}
