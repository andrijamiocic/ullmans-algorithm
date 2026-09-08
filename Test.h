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
    void runTest(int g_n, double g_density, double gh_ratio, double h_density, int n, int algorithm); // DFS = 1, Ullman = 2, FS = 3, CM = 4
    void runTestDirected(int g_n, double g_density, double gh_ratio, double h_density, int n, int algorithm); // DFS = 1, Ullman = 2, FS = 3, CM = 4

private:

    int compare(std::vector<std::vector<int>>& v1, std::vector<std::vector<int>>& v2);

};