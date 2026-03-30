#pragma once
#include <vector>
#include <string>
/*
TEST VECTOR INITIALIZATION!! (allocating on initialization)

graph class: 
- file constructor, random graph constructor
- file output function
- adj matrix, adj list (vector/list implementation) - can be const

M_0 construction function (2 graphs)

isomorphism check function (2 graphs and a boolean matrix references)

basic algorithm:
- takes 2 graph references as input (they have to be in order and the size is checked)
- M_0 matrix is constructed M (separate function)
- depth first tree search to a fixed depth
- isomorphism check function on max depth (separate function)
*/

class Graph {
public:

    Graph() = default;
    Graph(std::string filename, int dir); // 0 for undirected, 1 for directed
    Graph(int v_number, double p, int dir); // a random graph with v_number verteces and a probability p of an edge between two vertecees
    bool toFile(const std::string& filename);

    void printAdjMatrix();
    void printAdjList();

    bool is_directed() const {
        return directed;
    }

    int get_v_num() const {return v_num;}
    int get_e_num() const {return e_num;}

    bool edge(int v1, int v2) {
        return adj_matrix[v1-1][v2-1];
    }

    const std::vector<int>& neighbours(int v) {
        return adj_list[v-1];
    }

    //outdegree, indegree ?
    int degree(int v) const {
        return adj_list[v-1].size();
    }

private:
    
    int directed;

    int v_num; // number of verteces
    int e_num; // number of edges

    std::vector<std::vector<int>> adj_matrix;
    std::vector<std::vector<int>> adj_list;

    void insertEdge(int v1, int v2, int directed);

};