#pragma once
#include <vector>
#include <string>

class Graph {
public:

    Graph() = default;
    Graph(std::string filename); 
    Graph(int v_number, double p); // a random graph with v_number verteces and a probability p of an edge between two vertecees
    bool toFile(const std::string& filename);

    void printAdjMatrix();
    void printAdjList();

    int get_v_num() const {return v_num;}
    int get_e_num() const {return e_num;}

    bool edge(int v1, int v2) {
        return adj_matrix[v1-1][v2-1];
    }

    const std::vector<int>& neighbours(int v) {
        return adj_list[v-1];
    }

    int degree(int v) const {
        return adj_list[v-1].size();
    }

private:

    int v_num; // number of verteces
    int e_num; // number of edges

    std::vector<std::vector<int>> adj_matrix;
    std::vector<std::vector<int>> adj_list;

    void insertEdge(int v1, int v2);

};