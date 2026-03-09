#include <iostream>
#include "graph.h"

void print_matrix(std::vector<std::vector<int>>& v) {
    for ( std::vector<int> v1 : v ) {
        for (int i : v1) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}

int main(){
    //Graph G("graf_probni", 0);
    Graph G(10, 0.2, 0);
    Graph H(20, 0.1, 0);
    G.printAdjList();
    //G.printAdjMatrix();
    H.printAdjList();
    std::vector<std::vector<int>> M = M0(G, H);
    print_matrix(M);
    return 0;
}