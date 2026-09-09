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
    std::vector<double> gh_ratio_list = {0.5, 0.25, 0.1};
    std::vector<double> g_p_list = {0.4, 0.3, 0.2, 0.5};
    std::vector<double> h_p_list = {0.05, 0.1, 0.2, 0.3};
    int algorithm = std::stoi(argv[1])
    ;
    t.fullTest(algorithm, g_p_list, gh_ratio_list, h_p_list);
    std::cout << "Undirected done!";
    /*t.fullTestDirected(algorithm, g_p_list, gh_ratio_list, h_p_list);
    std::cout << "Directed done!";*/
    return 0;
}