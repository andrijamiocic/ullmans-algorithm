#pragma once
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
    
    void store_graphs(int size);
    int verification(int n);
    int Ullmans(int number, std::string filename);
    int UllmansDirected(int number, std::string filename);

private:

    int compare(std::vector<std::vector<int>>& v1, std::vector<std::vector<int>>& v2);

};