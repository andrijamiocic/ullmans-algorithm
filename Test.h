#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "UllmansAlgorithm.h"
#include "FocusSearch.h"
#include "CMAlgorithm.h"
#include "UllmansAlgorithmDirected.h"
#include "FocusSearchDirected.h"
#include "CMAlgorithmDirected.h"

/*
a class to implement tests
- generating and storing random graphs with variables(storing in a file or not?):
    - number of nodes
    - density
    - number of graphs
    - file name
- performing test and storing the results with variables:
    - graph files names
    - runtimes file name
    - special case of graph isomorphism
    
*/

class Test{
public:
    
    void store_graphs();
    int verification(int n);
    int runTest(int g_n, double g_density, double gh_ratio, double h_density, int n, int algorithm); // DFS = 1, Ullman = 2, FS = 3, CM = 4
    int runTestDirected(int g_n, double g_density, double gh_ratio, double h_density, int n, int algorithm); // DFS = 1, Ullman = 2, FS = 3, CM = 4
    void fullTest(int algorithm, std::vector<double>& g_p_list, std::vector<double>& gh_ratio_list, std::vector<double>& h_p_list);
    void fullTestDirected(int algorithm, std::vector<double>& g_p_list, std::vector<double>& gh_ratio_list, std::vector<double>& h_p_list);
private:

    int compare(std::vector<std::vector<int>>& v1, std::vector<std::vector<int>>& v2);

};