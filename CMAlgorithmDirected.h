#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <utility>
#include "DepthFirstSearchDirected.h"
#include "BitVector.h"

class CMAlgorithmDirected : public DepthFirstSearchDirected{
    using DepthFirstSearchDirected::DepthFirstSearchDirected;
public:
    int findIsomorphisms() override;
protected:
    void initialize() override;
    int choose_k(int k);
    void M0() override; // we now initiante a bit matrix
    std::vector<BitVector> M; // Matrix of all the candidates
    std::vector<int> instOrder; // an array holding al G vertices sorted by degree descending
    //void initializeInstOrder(); //initializes instOrder
    int refinementConditionSatisfied(int i, int j);
    int refine_full(); 
    int refine(int r, int c);
    void generateMd(); // generates a new matrix at current depth
    std::vector<BitVector> H_adj_matrix_out;
    std::vector<BitVector> H_adj_matrix_in;

    std::stack<int> M_log_stack;
    std::stack<std::pair<int, int>> M_log_stack_xy;
    void restore_M();

    class InstantiationOrder {
    public:

        InstantiationOrder( DirectedGraph& G) : G(G), g_n(G.get_v_num()){}
        void getOrder(std::vector<int>& order);

    private:

        std::vector<int> heuristic;
        std::vector<int> prev_neighbours;
        void getHeuristic();

        class Comparator { // the set of uninserted vertices needs to be heuristicaly ordered
        public:
            Comparator(const std::vector<int>& h, const std::vector<int>& p) : heuristic(h), prev_neighbours(p) {}
            const std::vector<int>& heuristic;
            const std::vector<int>& prev_neighbours;
            bool operator()(int u, int v) const;
        };

        DirectedGraph& G;
        int g_n;
    };
};

