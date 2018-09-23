#include <thread>
#include <variant>

#include "gtest/gtest.h"

#include "finder_greedy.h"
#include "finder_brute.h"
#include "visit_variant.h"

namespace 
{
    namespace MIS = MaximumIndependentSet;
    
    using variant_array = std::array<
                                     std::variant<
                                                    MIS::FinderGreedy,
                                                    MIS::FinderBrute>,
                                     2>;

    class TestAlgo : public ::testing::Test
    {
    protected:
        TestAlgo(): nCpu(std::thread::hardware_concurrency()) // Get number of CPUs
        {
            if(nCpu == 0) nCpu = 1;
        }

        unsigned int nCpu;
    };

    TEST_F(TestAlgo, OneVertex)
    {
        float connectivity = 0.6f;
        MIS::Graph gm(1, connectivity);

        variant_array finders = {MIS::FinderGreedy(gm, nCpu),
                                 MIS::FinderBrute(gm, nCpu)};

        visit_variant(finders.begin(), finders.end(), [](auto& finder)
        {
            finder.run();
            ASSERT_EQ(finder.get_result().size(), 1);
        });
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
        for(int i = 0; i < 30; ++i)
        {
            float connectivity = 0.6f;
            MIS::Graph gm(15, connectivity);

            variant_array finders = {MIS::FinderGreedy(gm, nCpu),
                                     MIS::FinderBrute(gm, nCpu)};

            visit_variant(finders.begin(), finders.end(), [](auto& finder)
            {
                finder.run();
                ASSERT_GE(finder.get_result().size(), 1);
            });
        }
    }

   TEST_F(TestAlgo, MultiThreading)
    {
        if (nCpu == 1) SUCCEED();

        float connectivity = 0.6f;
        MIS::Graph gm(20, connectivity);

        MIS::FinderBrute fb_one_thread(gm, 1);
        MIS::FinderBrute fb_multithread(gm, nCpu);
        
        fb_one_thread.run();
        fb_multithread.run();

        ASSERT_LT(fb_multithread.get_time(), fb_one_thread.get_time());
    }
}  
