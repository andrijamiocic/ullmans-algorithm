#pragma once
#include "graph.h"

class DepthFirstSearch{
    
public: 
    DepthFirstSearch( Graph& G, Graph& H ) : G(G), H(H), g_n(G.get_v_num()), h_n(H.get_v_num()){}
    virtual int findIsomporphisms(); // simple depth first search algorithm
    void printIsomorphisms();

protected:
    Graph& G;
    Graph& H;
    int g_n;
    int h_n;

    std::vector<std::vector<int>> isomorphism_found;

    void M0(); // root matrix for search tree (G < H ?) (undirected for now)

    int depth;
    std::vector<std::vector<int>> M_0;
    std::vector<int> paired_verteces; // paired_verteces[v] = 1 iff vertex v of the LARGER graph is paired 
    std::vector<int> column_chosen; // column_chosen[d] = k iff we chose column k at depth d

    int next_k(int k);

    int checkIsomorphism();
};

