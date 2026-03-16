#pragma once
#include "DepthFirstSearch.h"
#include <vector>

class UllmansAlgorithm : public DepthFirstSearch{
    using DepthFirstSearch::DepthFirstSearch;
public:
    int findIsomorphisms() override;
protected:
    int next_k(int k);
    std::vector<std::vector<std::vector<int>>> M;
    int refinementConditionSatisfied(int i, int j);
    int refine();
    void generateMd();
};