#include <iostream>
#include "graph.h"
#include "BitVector.h"
#include "DepthFirstSearch.h"
#include "UllmansAlgorithm.h"
#include "UllmansAlgorithm_vector.h"

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
    for (int i = 0; i < 1000; i++) {
        Graph G(5, 0.8, 0);
        Graph H(10, 0.5, 0);
        //G.printAdjList();
        //H.printAdjList();
        //DepthFirstSearch s(G, H);
        //s.measure_time();
        //s.printIsomorphisms();
        UllmansAlgorithm_vector v(G, H);
        UllmansAlgorithm u(G, H);
        v.measure_time();
        u.measure_time();
        std::cout << "stari: " << v.time << " novi: " << u.time << std::endl;
        if (u.isomorphism_found != v.isomorphism_found) {
            k++;
            std::cout << "nije dobar" << std::endl;
            G.printAdjList();
            H.printAdjList();
            v.printIsomorphisms();
            u.printIsomorphisms();
        }
        //u.measure_time();
        //u.printIsomorphisms();
        //std::cout << u.time << std::endl;
    }
    std::cout << "krivih: " << k << std::endl;
    return 0;
}