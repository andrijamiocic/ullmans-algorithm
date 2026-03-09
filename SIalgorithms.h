#pragma once
#include "graph.h"

class SubIsoFinder{
    
public: 

    virtual int findIsomporphism(); // simple depth first search algorithm

private:
    std::vector<std::vector<int>> M0( const Graph& G, const Graph& H ); // root matrix for search tree (G < H ?) (undirected for now)
};

