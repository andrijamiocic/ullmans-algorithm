#include "UllmansAlgorithm.h"

void print_matrix2(std::vector<std::vector<int>>& v) {
    for ( std::vector<int> v1 : v ) {
        for (int i : v1) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}


int UllmansAlgorithm::choose_k(int k) {
    if ( depth == g_n ) {return -1;}
    int v = instOrder[depth];
    while ( k < h_n - 1 ) {
        k++;
        if (!paired_verteces[k] && M[depth][v].getElement(k)) {
            return k;
        }
    }
    // the bit method implemented below has proven to be slower for a fraction of time for some reason
    /*
    k = M[depth][depth].nextOnePosition(k);
    while (k != -1) {
        if (!paired_verteces[k]){return k;}
        k = M[depth][depth].nextOnePosition(k);
    }*/
    return -1;
}

int UllmansAlgorithm::refinementConditionSatisfied(int i, int j) {
    //for each neighbour n of i+1 there must be a 1 in the n-1th row so that its column+1 and j+1 are neighbours 
    // AND that column is not used

    // we could OR all of the bitvectors and then count the ones -> there should be at least degree(i) of them
    // this would maybe slow down the algorithm and actually is not the part of the original algorithm

    std::vector<BitVector>& M_d = M[depth];
    for (int n : G.neighbours(i+1)) {
        if (!M_d[n-1].intersectionNotEmpty(H_adj_matrix[j])){
            return 0;
        }
    }
    return 1;
}

int UllmansAlgorithm::refine() {
    std::vector<BitVector>& M_d = M[depth];
    int changed = 1;
    while ( changed ) {
        changed = 0;
        // this is sped up using column_chosen
        // from 0 to d-1 we use column_chosen to get the only 1 in the row
        // from d to g_n-1 we have to get them manually
        for (int i = 0; i < depth; i++) {
            int v = instOrder[i];
            int j = column_chosen[v];
            // check the condition
            // if not satisfied -> terminate
            if (!refinementConditionSatisfied(v, j)) {
                return 0;
            }
        }
        for (int i = depth; i < g_n; i++) {
            int v = instOrder[i];
            for (int j = 0; j < h_n; j++ ) {
                if ( !M_d[v].getElement(j) ) { continue; }
                // check the condition
                // if not satisfied -> M_d[i][j] = 0 and changed = 1
                if ( !refinementConditionSatisfied(v, j)) {
                    M_d[v].setZero(j);
                    changed = 1;
                }
            }
            //check if the row is zero (that means no more candidates for the node i)
            if (M_d[v].isZero()) {return 0;}
        }
    }
    return 1;
}

void UllmansAlgorithm::generateMd() {
    M[depth] = M[depth-1];
    int v = instOrder[depth-1];
    M[depth][v].mask(column_chosen[v]);
    // this is not part of the 1976 algorithm, but it speeds it up by ~30%
    /*for (int i = depth; i < g_n; i++) {
        M[depth][i].setZero(column_chosen[depth-1]);
    }*/
    return;
}

void UllmansAlgorithm::M0() {
    // G must have a lesser number of vertices to have an isomorphism subgraph
    M_root.assign(g_n, BitVector(h_n));
    if ( g_n > h_n ) { return; }
    for ( int i = 0; i < g_n; i++ ) {
        for ( int j = 0; j < h_n; j++ ) {
            if ( G.degree(i+1) <= H.degree(j+1) ) {
                M_root[i].setOne(j);
            }
        }
    }
    return;
}

void UllmansAlgorithm::initialize() {
    // initialize adjecency bitmatrices of H
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
    // initialize M_root
    M.assign(g_n+1, {});
    M0();
    M[0] = M_root;
    depth = 0;
    k = -1;
    paired_verteces.assign(h_n, 0);
    column_chosen.assign(g_n, -1);
    return;
}

int UllmansAlgorithm::findIsomorphisms() {
    initialize();
    int v;
    while (1) {
        int refinemet_satisfied = refine();
        k = choose_k(k);
        if (k == -1 || !refinemet_satisfied){
            if (depth == 0) {
                return 0;
            }
            depth--;
            v = instOrder[depth];
            paired_verteces[column_chosen[v]] = 0;
            k = column_chosen[v];
            column_chosen[v] = -1;
        }
        else{
            v = instOrder[depth];
            column_chosen[v] = k;
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

bool UllmansAlgorithm::InstantiationOrder::Comparator::operator()(int u, int v) const {
    if (G.degree(u+1) != G.degree(v+1)) {
        return G.degree(u+1) > G.degree(v+1); // we want the bigger one
    }
    return u < v; // in case of a draw, just return the smaller vertex for determinism
}

void UllmansAlgorithm::InstantiationOrder::getOrder(std::vector<int>& order) {
    Comparator C(G);
    std::set<int, Comparator> vertices(C);
    int g_n = G.get_v_num();
    for (int i = 0; i < g_n; i++){
        vertices.insert(i);
    }
    for (int i = 0; i < g_n; i++){
        int next = *vertices.begin();
        vertices.erase(vertices.begin());
        order.push_back(next);
    }
    return;
}