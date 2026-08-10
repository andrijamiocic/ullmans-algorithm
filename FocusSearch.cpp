#include "FocusSearch.h"
#include <iostream>
#include <chrono>


void FocusSearch::initializeM0() {
    // G must have a lesser number of vertices to have an isomorphism subgraph
    M0.assign(g_n, BitVector(h_n)); // this is valid - there are no candidates for any vertices and no isomorphism will be found
    if ( g_n > h_n ) { return; }
    M0_list.assign(g_n, {});
    for ( int i = 0; i < g_n; i++ ) {
        for ( int j = 0; j < h_n; j++ ) {
            if ( G.degree(i+1) <= H.degree(j+1) ) {
                M0[i].setOne(j);
                M0_list[i].push_back(j);
            }
        }
    }
    M = M0;
    M0_index.assign(g_n, -1);
    return;
}

void FocusSearch::initializeLastNeighbour(){
    lastNeighbour.assign(g_n, -1);
    for (int i = g_n-1; i >= 0; i--) {
        int j = i-1;
        while (j >= 0) {
            if (G.edge(instOrder[i]+1, instOrder[j]+1)){
                lastNeighbour[instOrder[i]] = instOrder[j];
                break;
            }
            j--;
        }
    }
    return;
}

void FocusSearch::initializeNextNeighbours(){
    std::vector<int> position(g_n);
    for (int d = 0; d < g_n; d++) {
        position[instOrder[d]] = d;
    }
    nextNeighbours.assign(g_n, {});
    for (int i = 0; i < g_n; i++){
        for (int j : G.neighbours(i+1)){
            if (position[i] < position[j-1]) {
                nextNeighbours[i].push_back(j-1);
            }
        }
    }
    return;
}

void FocusSearch::initialize(){
    initializeM0();
    H_adj_matrix.assign(h_n, BitVector(h_n));
    for (int i = 0; i < h_n; i++) {
        for (int j = 0; j < h_n; j++) {
            if (H.edge(i+1, j+1)) {
                H_adj_matrix[i].setOne(j);
                H_adj_matrix[j].setOne(i);
            }
        }
    }
    InstantiationOrder I(G);
    I.getOrder(instOrder);
    Isomorphism_function.assign(g_n, -1);
    paired_verteces.assign(h_n, 0);
    initializeLastNeighbour();
    initializeNextNeighbours();
    // initialize all SElists - ~ g_n x h_n of them
    depth = 0;
    k = -1;
    return;
}

int FocusSearch::refine(){
    for (int i : nextNeighbours[instOrder[depth]]){
        BitVector domain = M0[i];
        for (int j = 0; j <= depth; j++){
            int v = instOrder[j];
            if (G.edge(i+1, v+1)){
                domain.intersect(H_adj_matrix[Isomorphism_function[v]]);
            }
        }
        if (domain.isZero()) {
            return 0;
        }
        if (lastNeighbour[i] == instOrder[depth]){
            M[i] = domain; // this is where refining happens
        }
    }
    return 1;
}

void FocusSearch::get_k(){
    if ( depth == g_n ) {
        k = -1;
        return;
    }
    int v = instOrder[depth];
    while ( k+1 < (int)M0_list[v].size() ) {
        k++;
        int candidate = M0_list[v][k];
        // if value hasn't already been taken and it is actually in the domain, it is next
        // the first condition can be removed if we remove values from all domains immediately after instantiation
        if (!paired_verteces[candidate] && M[v].getElement(candidate)) {
            M0_index[v] = k;
            return;
        }
    }
    k = -1;
    M0_index[v] = k;
    return;
}


int FocusSearch::findIsomorphisms(){
    // we need to implement termination when G > H
    initialize();
    int refinemet_satisfied = 1;
    while (1) {
        get_k();
        if (k == -1 || !refinemet_satisfied){
            if (depth == 0) {
                return 0;
            }
            depth--;
            
            int prev_v = instOrder[depth];
            paired_verteces[Isomorphism_function[prev_v]] = 0;
            k = M0_index[instOrder[depth]];
            Isomorphism_function[prev_v] = -1;
            refinemet_satisfied = 1;
        }
        else{
            int v = instOrder[depth];
            int value = M0_list[v][k];
            Isomorphism_function[v] = value;
            paired_verteces[value] = 1;
            if (depth == g_n - 1) {
                isomorphism_found.push_back(Isomorphism_function); //because the refinement procedure verified the solution, we dont need to
            }
            else{refinemet_satisfied = refine();}
            depth++;
            k = -1;
        }
    }
}
void FocusSearch::InstantiationOrder::getHeuristic() {
    std::vector<int> branch;
    for (int i = 0; i < g_n; i++ ){
        int sum = 0;
        for (int j : G.neighbours(i+1)){
            sum += G.degree(j);
        }
        branch.push_back(sum);
    }
    for (int i = 0; i < g_n; i++ ){
        int sum = 0;
        for (int j : G.neighbours(i+1)){
            sum += branch[j-1];
        }
        heuristic.push_back(sum);
    }
    return;
}

bool FocusSearch::InstantiationOrder::Comparator::operator()(int u, int v) const {
    if (prev_neighbours[u] != prev_neighbours[v]) {
        return prev_neighbours[u] > prev_neighbours[v]; // we want the bigger one
    }
    if (heuristic[u] != heuristic[v]) {
        return heuristic[u] > heuristic[v];
    }
    return u < v; // in case of a draw, just return the smaller index for determinism
}

void FocusSearch::InstantiationOrder::getOrder(std::vector<int>& order) {
    getHeuristic();
    prev_neighbours.assign(g_n, 0);
    Comparator C(heuristic, prev_neighbours);
    std::set<int, Comparator> active_nodes(C);
    for (int i = 0; i < g_n; i++){
        active_nodes.insert(i);
    }
    for (int i = 0; i < g_n; i++){
        int next = *active_nodes.begin();
        active_nodes.erase(active_nodes.begin());
        order.push_back(next);
        for (auto v : G.neighbours(next+1)){
            if (active_nodes.count(v-1)){
                active_nodes.erase(v-1); // we have to remove it from the set first before we change the sorting criteria
                prev_neighbours[v-1]++;
                active_nodes.insert(v-1);
            }
        }
    }
    return;
}

void FocusSearch::measure_time(){
    auto start = std::chrono::high_resolution_clock::now();
    findIsomorphisms();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    time = duration.count();
}

void FocusSearch::printIsomorphisms(){
    std::cout << "Isomorphisms:\n";
    for (std::vector<int> isomorphism : isomorphism_found) {
        for (int v : isomorphism) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    return;
}