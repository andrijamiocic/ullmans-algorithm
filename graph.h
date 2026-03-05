#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

/*
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

class Graph{
    int v_num;
    int e_num;
    std::vector<std::vector<int>> adj_matrix;
    std::vector<std::vector<int>> adj_list;

    Graph(std::string filename);
    Graph(int v_num, double p);
};

Graph::Graph(std::string filename){
    std::ifstream FILE(filename + ".txt");
    std::string line;
    int v1, v2;
    while (getline(FILE, line)){
        std::stringstream ss(line);
        ss >> v1 >> v2;
    }
}