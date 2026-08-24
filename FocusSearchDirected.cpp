#include "FocusSearchDirected.h"
#include <iostream>
#include <chrono>
#include <algorithm>


void FocusSearchDirected::initializeM0() {
    M0.assign(g_n, BitVector(h_n));
    if ( g_n > h_n ) { return; }
    M0_list.assign(g_n, {});
    std::vector<std::vector<int>> G_sorted_neighbor_degrees_out(g_n);
    std::vector<std::vector<int>> G_sorted_neighbor_degrees_in(g_n);
    for (int i = 0; i < g_n; i++) {
        for (int n : G.out_neighbours(i+1)) {
            G_sorted_neighbor_degrees_out[i].push_back(G.degree(n));//we only need the degree of the neighbour
        }
        std::sort(G_sorted_neighbor_degrees_out[i].rbegin(), G_sorted_neighbor_degrees_out[i].rend());
    }
    for (int i = 0; i < g_n; i++) {
        for (int n : G.in_neighbours(i+1)) {
            G_sorted_neighbor_degrees_in[i].push_back(G.degree(n));//we only need the degree of the neighbour
        }
        std::sort(G_sorted_neighbor_degrees_in[i].rbegin(), G_sorted_neighbor_degrees_in[i].rend());
    }
    std::vector<std::vector<int>> H_sorted_neighbor_degrees_out(h_n);
    std::vector<std::vector<int>> H_sorted_neighbor_degrees_in(h_n);
    for (int i = 0; i < h_n; i++) {
        for (int n : H.out_neighbours(i+1)) {
            H_sorted_neighbor_degrees_out[i].push_back(H.degree(n));//we only need the degree of the neighbour
        }
        std::sort(H_sorted_neighbor_degrees_out[i].rbegin(), H_sorted_neighbor_degrees_out[i].rend());
    }
    for (int i = 0; i < h_n; i++) {
        for (int n : H.in_neighbours(i+1)) {
            H_sorted_neighbor_degrees_in[i].push_back(H.degree(n));//we only need the degree of the neighbour
        }
        std::sort(H_sorted_neighbor_degrees_in[i].rbegin(), H_sorted_neighbor_degrees_in[i].rend());
    }
    for ( int i = 0; i < g_n; i++ ) {
        for ( int j = 0; j < h_n; j++ ) {
        
            if ( G.in_degree(i+1) <= H.in_degree(j+1) && G.out_degree(i+1) <= H.out_degree(j+1)) {
                
                bool contender = true;
                
                for (size_t k = 0; k < G_sorted_neighbor_degrees_in[i].size(); k++) {
                    if (G_sorted_neighbor_degrees_in[i][k] > H_sorted_neighbor_degrees_in[j][k] ) {
                        contender = false;
                        break;
                    }
                }
                for (size_t k = 0; k < G_sorted_neighbor_degrees_out[i].size(); k++) {
                    if (G_sorted_neighbor_degrees_out[i][k] > H_sorted_neighbor_degrees_out[j][k] ) {
                        contender = false;
                        break;
                    }
                }

                if (contender) {
                    M0[i].setOne(j);
                    M0_list[i].push_back(j);
                }
            }
        }
    }
    
    M = M0;
    M0_index.assign(g_n, -1);
    return;
}

void FocusSearchDirected::initializeLastNeighbour(){
    lastNeighbour.assign(g_n, -1);
    for (int i = g_n-1; i >= 0; i--) {
        int j = i-1;
        while (j >= 0) {
            if (G.edge(instOrder[i]+1, instOrder[j]+1) || G.edge(instOrder[j]+1, instOrder[i]+1)){
                lastNeighbour[instOrder[i]] = instOrder[j];
                break;
            }
            j--;
        }
    }
    return;
}

void FocusSearchDirected::initializeNextNeighbours(){
    std::vector<int> position(g_n);
    for (int d = 0; d < g_n; d++) {
        position[instOrder[d]] = d;
    }
    nextNeighbours.assign(g_n, {});
    for (int i = 0; i < g_n; i++){
        for (int j : G.out_neighbours(i+1)){
            if (position[i] < position[j-1]) {
                nextNeighbours[i].push_back(j-1);
            }
        }
        for (int j : G.in_neighbours(i+1)){
            if (!G.edge(i+1, j) && (position[i] < position[j-1])) {
                nextNeighbours[i].push_back(j-1);
            }
        }
    }
    return;
}

void FocusSearchDirected::initialize(){
    initializeM0();
    H_adj_matrix_out.assign(h_n, BitVector(h_n));
    for (int i = 0; i < h_n; i++) {
        for (int j = 0; j < h_n; j++) {
            if (H.edge(i+1, j+1)) {
                H_adj_matrix_out[i].setOne(j);
            }
        }
    }
    H_adj_matrix_in.assign(h_n, BitVector(h_n));
    for (int i = 0; i < h_n; i++) {
        for (int j = 0; j < h_n; j++) {
            if (H.edge(j+1, i+1)) {
                H_adj_matrix_in[i].setOne(j);
            }
        }
    }
    InstantiationOrder I(G);
    I.getOrder(instOrder);
    Isomorphism_function.assign(g_n, -1);
    paired_verteces.assign(h_n, 0);
    initializeLastNeighbour();
    initializeNextNeighbours();
    depth = 0;
    k = -1;
    return;
}

int FocusSearchDirected::refine(){
    for (int i : nextNeighbours[instOrder[depth]]){
        BitVector domain = M0[i];
        for (int j = 0; j <= depth; j++){
            int v = instOrder[j];
            if (G.edge(i+1, v+1)){
                domain.intersect(H_adj_matrix_in[Isomorphism_function[v]]);
            }
            if (G.edge(v+1, i+1)){
                domain.intersect(H_adj_matrix_out[Isomorphism_function[v]]);
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

void FocusSearchDirected::get_k(){
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


int FocusSearchDirected::findIsomorphisms(){
    if (g_n > h_n) {return 0;}
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
void FocusSearchDirected::InstantiationOrder::getHeuristic() {
    std::vector<int> branch;
    for (int i = 0; i < g_n; i++ ){
        int sum = 0;
        for (int j : G.in_neighbours(i+1)){
            sum += G.degree(j);
        }
        for (int j : G.out_neighbours(i+1)){
            sum += G.degree(j);
        }
        branch.push_back(sum);
    }
    for (int i = 0; i < g_n; i++ ){
        int sum = 0;
        for (int j : G.in_neighbours(i+1)){
            sum += branch[j-1];
        }
        for (int j : G.out_neighbours(i+1)){
            sum += branch[j-1];
        }
        heuristic.push_back(sum);
    }
    return;
}

bool FocusSearchDirected::InstantiationOrder::Comparator::operator()(int u, int v) const {
    if (prev_neighbours[u] != prev_neighbours[v]) {
        return prev_neighbours[u] > prev_neighbours[v]; // we want the bigger one
    }
    if (heuristic[u] != heuristic[v]) {
        return heuristic[u] > heuristic[v];
    }
    return u < v; // in case of a draw, just return the smaller index for determinism
}

void FocusSearchDirected::InstantiationOrder::getOrder(std::vector<int>& order) {
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
        for (auto v : G.in_neighbours(next+1)){
            if (active_nodes.count(v-1)){
                active_nodes.erase(v-1); // we have to remove it from the set first before we change the sorting criteria
                prev_neighbours[v-1]++;
                active_nodes.insert(v-1);
            }
        }
        for (auto v : G.out_neighbours(next+1)){
            if (active_nodes.count(v-1)){
                active_nodes.erase(v-1); // we have to remove it from the set first before we change the sorting criteria
                prev_neighbours[v-1]++;
                active_nodes.insert(v-1);
            }
        }
    }
    return;
}

void FocusSearchDirected::measure_time(){
    auto start = std::chrono::high_resolution_clock::now();
    findIsomorphisms();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    time = duration.count();
}

void FocusSearchDirected::printIsomorphisms(){
    std::cout << "Isomorphisms:\n";
    for (std::vector<int> isomorphism : isomorphism_found) {
        for (int v : isomorphism) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    return;
}