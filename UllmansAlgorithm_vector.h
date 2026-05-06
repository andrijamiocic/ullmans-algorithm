#pragma once
#include "DepthFirstSearch.h"
#include <iostream>
#include <vector>

// this class implements the Ullman's algorithm with an exception of using regular int vectors instead of bit vectors
// its purpose for now is purely for comparison

class UllmansAlgorithm_vector : public DepthFirstSearch{
    using DepthFirstSearch::DepthFirstSearch;
public:
    int findIsomorphisms() override;
protected:
    void initialize() override;
    int choose_k(int k);
    std::vector<std::vector<std::vector<int>>> M;
    int refinementConditionSatisfied(int i, int j);
    int refine();
    void generateMd();
};