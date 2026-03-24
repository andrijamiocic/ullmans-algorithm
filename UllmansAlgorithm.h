#pragma once
#include "DepthFirstSearch.h"
#include <iostream>
#include <vector>
#include "BitVector.h"

class UllmansAlgorithm : public DepthFirstSearch{
    using DepthFirstSearch::DepthFirstSearch;
public:
    int findIsomorphisms() override;
protected:
    void initialize() override;
    int next_k(int k);
    void M0() override; // we now initiante a bit matrix
    std::vector<std::vector<BitVector>> M; // an array of search matrices, each to be refined before continuation
    int refinementConditionSatisfied(int i, int j);
    int refine(); 
    void generateMd(); // generates a new matrix at current depth
    std::vector<BitVector> M_root;
    std::vector<BitVector> G_adj_matrix;
    std::vector<BitVector> H_adj_matrix;
};