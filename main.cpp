#include <iostream>

#include "graphboost.h"
#include "finder_greedy.h"
#include "finder_brute.h"

namespace MIS = MaximumIndependentSet;

int main()
{
    cout << "Enter number of vertices ";
    int N;
    cin >> N;

    //Number of processors
    int p = 4;

    MIS::Graph gm(N, 0.6);
    gm.print();
    
    MIS::FinderGreedy fg(gm, p);
    fg.run();
    std::cout << fg.get_time() << " ms\n";
    fg.print_result();
    std::cout << "\n";

    MIS::FinderBrute fb(gm, p);
    fb.run();
    std::cout << fb.get_time() << " ms\n";
    fb.print_result();

    return 0;
}
