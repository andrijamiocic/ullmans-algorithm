#include "DepthFirstSearch.h"
#include <iostream>
#include <chrono>

void DepthFirstSearch::M0() {
    // G must have a lesser number of vertices to have an isomorphism subgraph
    if ( g_n > h_n ) { return; }
    for ( int i = 0; i < g_n; i++ ) {
        M_0.push_back({});
        for ( int j = 0; j < h_n; j++ ) {
            if ( G.degree(i+1) <= H.degree(j+1) ) {
                M_0[i].push_back(1);
            }else {
                M_0[i].push_back(0);
            }
        }
    }
    return;
}

int DepthFirstSearch::choose_k(int k) {
    if ( depth == g_n ) {return -1;}
    while ( k < h_n - 1 ) {
        k++;
        if ( !paired_verteces[k] && M_0[depth][k]) {
            return k;
        }
    }
    return -1;
}

int DepthFirstSearch::checkIsomorphism(){
    for ( int i = 0; i < g_n;  i++ ){
        for ( int j = i + 1; j < g_n; j++ ){
            if ( G.edge(i+1, j+1) && !H.edge(column_chosen[i]+1, column_chosen[j]+1) ){return 0;}
        }
    }
    isomorphism_found.push_back(column_chosen);
    return 1;
}

void DepthFirstSearch::printIsomorphisms(){
    std::cout << "Isomorphisms:\n";
    for (std::vector<int> isomorphism : isomorphism_found) {
        for (int v : isomorphism) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    return;
}

void DepthFirstSearch::initialize(){
    M0();
    depth = 0;
    k = -1;
    paired_verteces.assign(h_n, 0);
    column_chosen.assign(g_n, -1); 
    return;
}

int DepthFirstSearch::findIsomorphisms(){
    int timeout = 0;
    int counter = 0;
    auto start = std::chrono::high_resolution_clock::now();
    initialize();
    while (1) {
        k = choose_k(k);
        if (k == -1){
            if (depth == 0) {
                break;
            }
            depth --;
            paired_verteces[column_chosen[depth]] = 0;
            k = column_chosen[depth];
            column_chosen[depth] = -1;
        }
        else{
            column_chosen[depth] = k;
            paired_verteces[k] = 1;
            if (depth == g_n - 1) {
                checkIsomorphism();
            }
            depth ++;
            k = -1;
        }
        counter++;
        if (counter == 10000){
            auto now = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
            if (duration.count()>60000000){
                timeout = 1;
                break;
            }
            counter = 0;
        }
        
    }
    if(timeout) {
        time = -1;
        return -1;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    time = duration.count();
    return 0;
}

void DepthFirstSearch::measure_time(){
    auto start = std::chrono::high_resolution_clock::now();
    findIsomorphisms();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    time = duration.count();
}