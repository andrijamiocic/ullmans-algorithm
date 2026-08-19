#include "CMAlgorithm.h"

int CMAlgorithm::choose_k(int k) {
    if ( depth == g_n ) {return -1;}
    int v = instOrder[depth];
    int found = 0;
    int res = -1;
    while ( k < h_n - 1 ) {
        k++;
        if (!paired_verteces[k] && M[v].getElement(k)) {
            found = 1;
            res = k;
            break;
        }
    }while ( k < h_n - 1 ) {
        k++;
        if (M[v].getElement(k)) {
            M[v].setZero(k);
            M_log_stack_xy.push({v, k});
            int n = M_log_stack.top();
            M_log_stack.pop();
            M_log_stack.push(n+1);
        }
    }
    // the bit method implemented below has proven to be slower for a fraction of time for some reason
    /*
    k = M[depth][depth].nextOnePosition(k);
    while (k != -1) {
        if (!paired_verteces[k]){return k;}
        k = M[depth][depth].nextOnePosition(k);
    }*/
    return res;
}

int CMAlgorithm::refinementConditionSatisfied(int i, int j) {
    //for each neighbour n of i+1 there must be a 1 in the n-1th row so that its column+1 and j+1 are neighbours 
    // AND that column is not used

    // we could OR all of the bitvectors and then count the ones -> there should be at least degree(i) of them
    // this would maybe slow down the algorithm and actually is not the part of the original algorithm

    for (int n : G.neighbours(i+1)) {
        if (!M[n-1].intersectionNotEmpty(H_adj_matrix[j])){
            return 0;
        }
    }
    return 1;
}

int CMAlgorithm::refine_full() {
    int changed = 1;
    while ( changed ) {
        changed = 0;
        for (int i = 0; i < g_n; i++) {
            int v = instOrder[i];
            for (int j = 0; j < h_n; j++ ) {
                if ( !M[v].getElement(j) ) { continue; }
                // check the condition
                // if not satisfied -> M_d[i][j] = 0 and changed = 1
                if ( !refinementConditionSatisfied(v, j)) {
                    M[v].setZero(j);
                    changed = 1;
                }
            }
            //check if the row is zero (that means no more candidates for the node i)
            if (M[v].isZero()) {return 0;}
        }
    }
    return 1;
}


int CMAlgorithm::refine(int r, int c){
    for (auto i : G.neighbours(r+1)){
        //M[i-1].intersect(H_adj_matrix[c]); 
        for (int j = 0; j < h_n; j++) {
            if (M[i-1].getElement(j) && !H_adj_matrix[c].getElement(j)){
                M[i-1].setZero(j);
                M_log_stack_xy.push({i-1, j});
                int n = M_log_stack.top();
                M_log_stack.pop();
                M_log_stack.push(n+1);
            }
        }
    }
    int changed = 1;
    while ( changed ) {
        changed = 0;
        for (auto i : G.neighbours(r+1)) {
            int v = i-1;
            for (auto j : H.neighbours(c+1)) {
                if ( !M[v].getElement(j) ) { continue; }
                // check the condition
                // if not satisfied -> M_d[i][j] = 0 and changed = 1
                if ( !refinementConditionSatisfied(v, j)) {
                    M[v].setZero(j);
                    M_log_stack_xy.push({v, j});
                    int n = M_log_stack.top();
                    M_log_stack.pop();
                    M_log_stack.push(n+1);
                    changed = 1;
                }
            }
            //check if the row is zero (that means no more candidates for the node i)
            if (M[v].isZero()) {return 0;}
        }
    }
    return 1;
};

/*void CMAlgorithm::generateMd() {
    M[depth] = M[depth-1];
    int v = instOrder[depth-1];
    M[depth][v].mask(column_chosen[v]);
    // this is not part of the 1976 algorithm, but it speeds it up by ~30%
    for (int i = depth; i < g_n; i++) {
        M[depth][i].setZero(column_chosen[depth-1]);
    }
    return;
}*/

void CMAlgorithm::M0() {
    // G must have a lesser number of vertices to have an isomorphism subgraph
    M.assign(g_n, BitVector(h_n));
    if ( g_n > h_n ) { return; }
    for ( int i = 0; i < g_n; i++ ) {
        for ( int j = 0; j < h_n; j++ ) {
            if ( G.degree(i+1) <= H.degree(j+1) ) {
                M[i].setOne(j);
            }
        }
    }
    return;
}

void CMAlgorithm::initialize() {
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
    M0();
    depth = 0;
    k = -1;
    paired_verteces.assign(h_n, 0);
    column_chosen.assign(g_n, -1);
    return;
}

int CMAlgorithm::findIsomorphisms() {
    initialize();
    int v;
    int refinement_satisfied = refine_full();
    while (1) {
        M_log_stack.push(0);
        k = choose_k(k);
        if (k == -1 || !refinement_satisfied){
            if (depth == 0) {
                return 0;
            }
            depth--;
            v = instOrder[depth];
            paired_verteces[column_chosen[v]] = 0;
            k = column_chosen[v];
            column_chosen[v] = -1;
            restore_M();
        }
        else{
            v = instOrder[depth];
            column_chosen[v] = k;
            paired_verteces[k] = 1;
            if (depth == g_n - 1) {
                isomorphism_found.push_back(column_chosen); //because the refinement procedure verified the solution, we dont need to
            }
            refine(v, k);
            depth++;
            k = -1;
        }
    }
}

void CMAlgorithm::restore_M(){
    int count = M_log_stack.top();
    M_log_stack.pop();
    while(count) {
        auto [x, y] = M_log_stack_xy.top();
        M[x].setOne(y);
        M_log_stack_xy.pop();
        count--;
    }
    return;
}

void CMAlgorithm::InstantiationOrder::getHeuristic() {
    for (int i = 0; i < g_n; i++ ){
        int sum = 0;
        for (int j : G.neighbours(i+1)){
            for (int k : G.neighbours(i+1)){
                if (G.edge(j, k)){sum++;}
            }
        }
        sum/=2;
        sum+=G.degree(i+1);
        heuristic.push_back(sum);
    }
    return;
}

bool CMAlgorithm::InstantiationOrder::Comparator::operator()(int u, int v) const {
    if (prev_neighbours[u] != prev_neighbours[v]) {
        return prev_neighbours[u] > prev_neighbours[v]; // we want the bigger one
    }
    if (heuristic[u] != heuristic[v]) {
        return heuristic[u] > heuristic[v];
    }
    return u < v; // in case of a draw, just return the smaller index for determinism
}

void CMAlgorithm::InstantiationOrder::getOrder(std::vector<int>& order) {
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