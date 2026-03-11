#include <iostream>
#include "graph.h"
#include "SIalgorithms.h"

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
    Graph G(15, 0.3, 0);
    Graph H(30, 0.1, 0);
    G.printAdjList();
    H.printAdjList();
    DepthFirstSearch s(G, H);
    s.findIsomporphisms();
    s.printIsomorphisms();
    return 0;
}