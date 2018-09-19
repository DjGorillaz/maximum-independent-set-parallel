#include <thread>
#include <variant>

#include "gtest/gtest.h"

#include "finder_greedy.h"
#include "finder_brute.h"

namespace 
{
    class TestAlgo : public ::testing::Test
    {
    protected:
        TestAlgo(): nCpu(std::thread::hardware_concurrency()) // Get number of CPUs
        {
            if(nCpu == 0) nCpu = 1;
        }

        unsigned int nCpu;
    };

    namespace MIS = MaximumIndependentSet;

    TEST_F(TestAlgo, OneVertex)
    {
        float connectivity = 0.6f;
        MIS::Graph gm(1, connectivity);

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
                    ASSERT_TRUE(finder->get_result().size() == 1);
                },
                variant_finder);
        }
    }

    TEST_F(TestAlgo, CompareAlgo)
    {
        float connectivity = 0.6f;
        MIS::Graph gm(15, connectivity);

        MIS::FinderGreedy fg(gm, nCpu);
        MIS::FinderBrute fb(gm, nCpu);

        fg.run();
        fb.run();

        //Compare time and size of set
        ASSERT_LE(fg.get_time(), fb.get_time());
        ASSERT_LE(fg.get_result().size(), fb.get_result().size());
    }

    TEST_F(TestAlgo, FixedGraphBrute)
    {
        std::vector<std::pair<int,int>> edges = 
        {{0,1}, {0,4},
         {1,2}, {1,3},
         {2,6}, {2,7},
         {3,4}, {3,6},
         {4,5}, {4,8},
         {5,6}, {5,9},
         {6,7},
         {7,9}, {7,10},
         {8,9},
         {9,10}};

        MIS::Graph gm(edges);
        MIS::FinderBrute fb(gm, nCpu);
        fb.run();

        std::vector<int> answer = {0, 2, 3, 5, 8, 10};
        ASSERT_EQ(fb.get_result(), answer);
    }

    TEST_F(TestAlgo, RandomGraphs)
    {
        for(int i = 0; i < 10; ++i)
        {
            float connectivity = 0.6f;
            MIS::Graph gm(15, connectivity);

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
                        ASSERT_GT(finder->get_result().size(), 1);
                    },
                    variant_finder);
            }
        }
    }

   TEST_F(TestAlgo, MultiThreading)
    {
        if (nCpu == 1) SUCCEED();

        float connectivity = 0.6f;
        MIS::Graph gm(18, connectivity);

        MIS::FinderBrute fb_one_thread(gm, 1);
        MIS::FinderBrute fb_multithread(gm, nCpu);
        
        fb_one_thread.run();
        fb_multithread.run();

        ASSERT_LT(fb_multithread.get_time(), fb_one_thread.get_time());
    }
}  
