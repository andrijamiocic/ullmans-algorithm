#pragma once
#include <vector>
#include "graph.h"
#include "BitVector.h"

class FocusSearch {
public:
FocusSearch( Graph& G, Graph& H ) : G(G), H(H), g_n(G.get_v_num()), h_n(H.get_v_num()){}
    int findIsomorphisms();
    void printIsomorphisms();
    void measure_time();
    double time = 0;
    std::vector<std::vector<int>> isomorphism_found;
private:
    // input graphs
    Graph& G;
    Graph& H;
    // numbers of their vertices
    int g_n;
    int h_n;
    std::vector<BitVector> H_adj_matrix; // only bit-representation of H is needed
    int depth; // current depth in search tree
    int k; // pointer to the next instantiation of variable
    std::vector<BitVector> M0; // bit-matrix that stores inital domain of each pattern graph vertex as a bitset
    std::vector<BitVector> M; // same as M0, but used to keep
    std::vector<int> instOrder; // a list of G vertices, ordered by instantiation priority
    int choose_k();
    void initializeM0();
    void initialize();
    void instantiationOrder();
    std::vector<int> getHeuristic();
    int refine();

};