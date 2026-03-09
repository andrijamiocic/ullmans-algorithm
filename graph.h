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
    Graph(std::string filename, int directed); // 0 for undirected, 1 for directed
    Graph(int v_number, double p, int directed); // a random graph with v_number verteces and a probability p of an edge between two vertecees

    void printAdjMatrix();
    void printAdjList();

private:
    
    int v_num; // number of verteces
    int e_num; // number of edges

    std::vector<std::vector<int>> adj_matrix;
    std::vector<std::vector<int>> adj_list;

    void insertEdge(int v1, int v2, int directed); 

    friend std::vector<std::vector<int>> M0(const Graph& G, const Graph& H); // root matrix for search tree (G < H ?) (undirected for now)

    friend void findIsomporphism(const Graph& G, const Graph& H);

};