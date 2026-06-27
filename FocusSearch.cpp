#include "FocusSearch.h"

void FocusSearch::instantiationOrder() {
    /*std::vector<int> heuristic = getHeuristic();
    std::vector<int> num_neighbours;
    num_neighbours.assign(g_n, 0);*/
    for (int i = 0; i < g_n; i++) {
        instOrder.push_back(i);
    }
    return;
}

std::vector<int> FocusSearch::getHeuristic() {
    std::vector<int> branch;
    for (int i = 0; i < g_n; i++ ){
        int sum = 0;
        for (int j : G.neighbours(i+1)){
            sum += G.degree(j);
        }
        branch.push_back(sum);
    }
    std::vector<int> heuristic;
    for (int i = 0; i < g_n; i++ ){
        int sum = 0;
        for (int j : G.neighbours(i+1)){
            sum += branch[j-1];
        }
        heuristic.push_back(sum);
    }
    return heuristic;
}

void FocusSearch::initializeM0() {
    // G must have a lesser number of vertices to have an isomorphism subgraph
    M0.assign(g_n, BitVector(h_n));
    if ( g_n > h_n ) { return; }
    for ( int i = 0; i < g_n; i++ ) {
        for ( int j = 0; j < h_n; j++ ) {
            if ( G.degree(i+1) <= H.degree(j+1) ) {
                M0[i].setOne(j);
            }
        }
    }
    return;
}

void FocusSearch::initialize(){
    initializeM0();
    instantiationOrder();
    depth = 0;
    return;
}

int FocusSearch::refine(){

}

int FocusSearch::findIsomorphisms(){
    initialize();
    while (1) {
        int refinemet_satisfied = refine();
        k = choose_k(k);
        if (k == -1 || !refinemet_satisfied){
            if (depth == 0) {
                return 0;
            }
            depth--;
            paired_verteces[column_chosen[depth]] = 0;
            k = column_chosen[depth];
            column_chosen[depth] = -1;
        }
        else{
            column_chosen[depth] = k;
            paired_verteces[k] = 1;
            if (depth == g_n - 1) {
                isomorphism_found.push_back(column_chosen); //because the refinement procedure verified the solution, we dont need to
            }
            depth++;
            //generate matrix M[d] (first d rows need to be chosen)
            generateMd();
            k = -1;
        }
    }
}