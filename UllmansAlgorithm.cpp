#include "UllmansAlgorithm.h"
#include <thread>

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

int UllmansAlgorithm::next_k(int k) {
    if ( depth == g_n ) {return -1;}
    while ( k < h_n - 1 ) {
        k++;
        if (!paired_verteces[k] && M[depth][depth].getElement(k)) {
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
    std::vector<BitVector>& M_d = M[depth];
    for (int n : G.neighbours(i+1)) {
        if (!M_d[n-1].intersect(H_adj_matrix[j])){
            return 0;
        }
    }
    return 1;
}

int UllmansAlgorithm::refine(){
    // this can be implemented in parallel
    std::vector<BitVector>& M_d = M[depth];
    int changed = 1;
    while ( changed ) {
        changed = 0;
        // this can be sped up using column_chosen
        // from 0 to d-1 we can use column_chosen to get the only 1 in the row
        // from d to g_n-1 we have to get them manually
        for (int i = 0; i < depth; i++) {
            int j = column_chosen[i];
            // check the condition
            // if not satisfied -> terminate
            if (!refinementConditionSatisfied(i, j)) {
                return 0;
            }
        }
        for (int i = depth; i < g_n; i++) {
            for (int j = 0; j < h_n; j++ ) {
                if ( !M_d[i].getElement(j) ) { continue; }
                // check the condition
                // if not satisfied -> M_d[i][j] = 0 and changed = 1
                if ( !refinementConditionSatisfied(i, j)) {
                    M_d[i].setZero(j);
                    changed = 1;
                }
            }
        }
    }
    return 1;
}

void UllmansAlgorithm::refineRow(int i, int& changed) {
    for (int j = 0; j < h_n; j++ ) {
        if ( ! M[depth][i].getElement(j) ) { continue; }
        // check the condition
        // if not satisfied -> M_d[i][j] = 0 and changed = 1
        if ( !refinementConditionSatisfied(i, j)) {
            M[depth][i].setZero(j);
            changed = 1;
        }
    }
}

int UllmansAlgorithm::refineParallel(){
    std::vector<BitVector>& M_d = M[depth];
    int changed = 1;
    while ( changed ) {
        changed = 0;
        // this can be sped up using column_chosen
        // from 0 to d-1 we can use column_chosen to get the only 1 in the row
        // from d to g_n-1 we have to get them manually
        for (int i = 0; i < depth; i++) {
            int j = column_chosen[i];
            // check the condition
            // if not satisfied -> terminate
            if (!refinementConditionSatisfied(i, j)) {
                return 0;
            }
        }
        std::vector<std::thread> t;
        t.reserve(g_n);
        for (int i = depth; i < g_n; i++) {
            t.push_back(std::thread(&UllmansAlgorithm::refineRow, this,  i, std::ref(changed)));
        }
        for (int i = depth; i < g_n; i++) {
            t[i-depth].join();
        }
    }
    return 1;
}

void UllmansAlgorithm::generateMd() {
    // this should maybe be implemented as a vector of stacks - each row in its own stack
    // would save memory and time that is wasted on copying rows
    M[depth] = M[depth-1];
    M[depth][depth-1].mask(column_chosen[depth-1]);
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
            }else {
                M_root[i].setZero(j);
            }
        }
    }
    return;
}

void UllmansAlgorithm::initialize() {
    // initialize adjecency bitmatrices of G and H
    G_adj_matrix.assign(g_n, BitVector(g_n));
    for (int i = 0; i < g_n; i++) {
        for (int j = 0; j < g_n; j++) {
            if (G.edge(i+1, j+1)) {
                G_adj_matrix[i].setOne(j);
                G_adj_matrix[j].setOne(i);
            }
        }
    }
    H_adj_matrix.assign(h_n, BitVector(h_n));
    for (int i = 0; i < h_n; i++) {
        for (int j = 0; j < h_n; j++) {
            if (H.edge(i+1, j+1)) {
                H_adj_matrix[i].setOne(j);
                H_adj_matrix[j].setOne(i);
            }
        }
    }
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
    while (1) {
        int refinemet_satisfied = refine();
        k = next_k(k);
        if (k == -1 || !refinemet_satisfied){
            if (depth == 0) {
                return 0;
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
            //generate matrix M[d] (first d rows need to be chosen)
            generateMd();
            k = -1;
        }
    }
}