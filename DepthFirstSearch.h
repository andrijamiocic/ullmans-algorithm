#pragma once
#include "graph.h"

class DepthFirstSearch{
    
public: 
    DepthFirstSearch( Graph& G, Graph& H ) : G(G), H(H), g_n(G.get_v_num()), h_n(H.get_v_num()){}
    virtual int findIsomorphisms(); // simple depth first search algorithm
    void printIsomorphisms();
    void measure_time();
    double time = 0;
    std::vector<std::vector<int>> isomorphism_found; // maybe put back to protected

protected:
    Graph& G;
    Graph& H;
    int g_n;
    int h_n;


    virtual void M0(); // root matrix for search tree (G < H ?) (undirected for now)

    int depth;
    int k; // a pointer to the next node to be chosen in the search tree
    virtual void initialize(); //function that initializes all the search variables
    std::vector<std::vector<int>> M_0; // root matrix of all the candidate nodes
    std::vector<int> paired_verteces; // paired_verteces[v] = 1 iff vertex v of the LARGER graph is paired 
    std::vector<int> column_chosen; // column_chosen[d] = k iff we chose column k at depth d

    virtual int choose_k(int k);

    virtual int checkIsomorphism();
};

