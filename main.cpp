#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <thread>
#include <bitset>
#include <cstdint>
#include "graph.h"
#include "BitVector.h"
#include "DepthFirstSearch.h"
#include "UllmansAlgorithm.h"
#include "FocusSearch.h"
#include "CMAlgorithm.h"
#include "UllmansAlgorithmDirected.h"
#include "FocusSearchDirected.h"
#include "CMAlgorithmDirected.h"

#include "Test.h"

int main(int argc, char* argv[]){
    Test t;
    int n = 10;
    std::vector<double> gh_ratio_list = {0.5, 0.25, 0.1};
    std::vector<double> g_p_list = {0.5, 0.4, 0.3, 0.2};
    std::vector<double> h_p_list = {0.01, 0.05, 0.1, 0.2, 0.3};

    t.store_graphs(g_p_list, gh_ratio_list, h_p_list, n);
    t.store_graphs_directed(g_p_list, gh_ratio_list, h_p_list, n);
    
    t.fullTest(3, g_p_list, gh_ratio_list, h_p_list, n, 300);
    t.fullTest(4, g_p_list, gh_ratio_list, h_p_list, n, 300);
    t.fullTest(2, g_p_list, gh_ratio_list, h_p_list, n, 100);
    t.fullTest(1, g_p_list, gh_ratio_list, h_p_list, n, 15);

   

    std::cout << "Undirected done!";

    t.fullTestDirected(3, g_p_list, gh_ratio_list, h_p_list, n, 15);
    t.fullTestDirected(4, g_p_list, gh_ratio_list, h_p_list, n, 15);
    t.fullTestDirected(2, g_p_list, gh_ratio_list, h_p_list, n, 100);
    t.fullTestDirected(1, g_p_list, gh_ratio_list, h_p_list, n, 15);

    std::cout << "Undirected done!";

    
    
    return 0;
}
