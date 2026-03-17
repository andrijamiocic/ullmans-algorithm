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
    int k = 0;
    for (int i = 0; i < 100; i++) {
        Graph G(10, 0.5, 0);
        Graph H(20, 0.15, 0);
        //G.printAdjList();
        //H.printAdjList();
        DepthFirstSearch s(G, H);
        s.measure_time();
        //s.printIsomorphisms();
        UllmansAlgorithm u(G, H);
        u.measure_time();
        //u.printIsomorphisms();
        double ratio = u.time/s.time;
        std::cout << ratio << std::endl;
    }
    std::cout << "krivih: " << k << std::endl;
    return 0;
}