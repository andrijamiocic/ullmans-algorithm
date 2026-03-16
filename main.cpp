#include <iostream>
#include "graph.h"
#include "DepthFirstSearch.h"
#include "UllmansAlgorithm.h"

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
    Graph G(10, 0.45, 0);
    Graph H(30, 0.1, 0);
    G.printAdjList();
    H.printAdjList();
    DepthFirstSearch s(G, H);
    s.findIsomorphisms();
    s.printIsomorphisms();
    UllmansAlgorithm u(G, H);
    u.findIsomorphisms();
    u.printIsomorphisms();
    return 0;
}