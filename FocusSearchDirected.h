#pragma once
#include <vector>
#include <set>
#include "DirectedGraph.h"
#include "BitVector.h"

class FocusSearchDirected {
public:
    FocusSearchDirected( DirectedGraph& G, DirectedGraph& H ) : G(G), H(H), g_n(G.get_v_num()), h_n(H.get_v_num()) {}
    int findIsomorphisms();
    void printIsomorphisms();
    void measure_time();
    double time = 0;
    std::vector<std::vector<int>> isomorphism_found;
private:
    // input Directedgraphs
    DirectedGraph& G;
    DirectedGraph& H;
    // numbers of their vertices
    int g_n;
    int h_n;
    std::vector<BitVector> H_adj_matrix_out; // only bit-representation of H is needed
    std::vector<BitVector> H_adj_matrix_in;
    int depth; // current depth in search tree
    int current_vertex; // = instOrder[depth]. Because of vetrex oredering this is not the same as depth.
    std::vector<BitVector> M0; // bit-matrix that stores inital domain of each pattern Directedgraph vertex as a bitset
    std::vector<BitVector> M; // same as M, but used for searc tree and is changed constantly : TEMPORARY SIMPLIFIED SOLUTION!!
    std::vector<std::vector<int>> M0_list; // M0 as a vector, used for iteration
    std::vector<int> M0_index; // M0_index[i] = index of the current instantiation in M0_list[i]
    int k; // index of the last instantiated variable within M0_list
    std::vector<int> instOrder; // a list of G vertices, ordered by instantiation priority
    std::vector<int> lastNeighbour; // lastNeigbour[u]=v <=> v is the last adjacent vertex to u before u
    std::vector<std::vector<int>> nextNeighbours; //nextNeigbours[u] = {v; lastNeighbour[v]=u}
    std::vector<std::vector<std::vector<int>>> seList;
    std::vector<int> paired_verteces; // paired_verteces[v] = 1 iff some vetrex of G has been instantiated to vertex v of Directedgraph H
    std::vector<int> Isomorphism_function; // the main isomporphism function
    void get_k();
    void initializeLastNeighbour();
    void initializeNextNeighbours();
    void initializeM0();
    void initialize();
    int refine();

    
    // we implement a new class just for static ordering before the search
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


