#include "UllmansAlgorithm.h"

void print_matrix1(std::vector<std::vector<int>>& v) {
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
        if ( !paired_verteces[k] && M[depth][depth][k]) {
            return k;
        }
    }
    return -1;
}

int UllmansAlgorithm::refinementConditionSatisfied(int i, int j) {
    //for each neighbour n of i+1 there must be a 1 in the n-1th row so that its column+1 and j+1 are neighbours 
    // AND that column is not used
    std::vector<std::vector<int>>& M_d = M[depth];
    for (int n : G.neighbours(i+1)) {
        int found = 0;
        for (int m = 0; m < h_n; m++) {
            if (M_d[n-1][m] == 1 && H.edge(j+1, m+1)){
                found = 1;
                break;
            }
        }
        if (!found) {return 0;}
    }
    return 1;
}

int UllmansAlgorithm::refine(){
    // this can be implemented in parallel
    std::vector<std::vector<int>>& M_d = M[depth];
    int changed = 1;
    while ( changed ) {
        changed = 0;
        // this can be sped up using column_chosen
        // from 0 to d-1 we can use column_chosen to get the only 1 in the row
        // from d to g_n-1 we have to get them manually
        for ( int i = 0; i < depth; i++) {
            int j = column_chosen[i];
            // check the condition
            //if not satisfied -> terminate
            if ( !refinementConditionSatisfied(i, j)) {
                return 0;
            }
        }
        for (int i = depth; i < g_n; i++) {
            for (int j = 0; j < h_n; j++ ) {
                if ( !M_d[i][j] ) { continue; }
                // check the condition
                // if not satisfied -> M_d[i][j] = 0 and changed = 1
                if ( !refinementConditionSatisfied(i, j)) {
                    M_d[i][j] = 0;
                    changed = 1;
                }
            }
        }
    }
    return 1;
}

void UllmansAlgorithm::generateMd() {
    M[depth] = M[depth-1];
    for (int i = 0; i < h_n; i++) {
        if ( i != column_chosen[depth-1] ) {
            M[depth][depth-1][i] = 0;
        }
    } 
    return;
}

int UllmansAlgorithm::findIsomorphisms(){
    M0();
    M.assign(g_n+1, {});
    M[0] = M_0;
    depth = 0;
    int k = -1;
    paired_verteces.assign(h_n, 0);
    column_chosen.assign(g_n, -1);
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
        //std::cout << "depth: " << depth << std::endl;
        //for (int x = 0; x <= depth; x++){print_matrix1(M[x]);}
        //for (int x = 0; x < g_n; x++) {std::cout << column_chosen[x];}
        //std::cout << std::endl;
    }
}