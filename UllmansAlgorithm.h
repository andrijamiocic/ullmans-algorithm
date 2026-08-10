#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "DepthFirstSearch.h"
#include "BitVector.h"

class UllmansAlgorithm : public DepthFirstSearch{
    using DepthFirstSearch::DepthFirstSearch;
public:
    int findIsomorphisms() override;
protected:
    void initialize() override;
    int choose_k(int k);
    void M0() override; // we now initiante a bit matrix
    std::vector<std::vector<BitVector>> M; // an array of search matrices, each to be refined before continuation
    std::vector<int> instOrder; // an array holding al G vertices sorted by degree descending
    //void initializeInstOrder(); //initializes instOrder
    int refinementConditionSatisfied(int i, int j);
    virtual int refine(); 
    void generateMd(); // generates a new matrix at current depth
    std::vector<BitVector> M_root;
    std::vector<BitVector> H_adj_matrix;

    class InstantiationOrder {
    public:
        InstantiationOrder(const Graph& G) : G(G){}
        void getOrder(std::vector<int>& order);

    private:
        const Graph& G; 

        class Comparator { // the set of uninserted vertices needs to be heuristicaly ordered
        public:
            Comparator(const Graph& G) : G(G) {}
            bool operator()(int u, int v) const;
            const Graph& G; 
        };
    };
};

