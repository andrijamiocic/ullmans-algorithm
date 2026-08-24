#include "CMAlgorithmDirected.h"

int CMAlgorithmDirected::choose_k(int k) {
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
    }
    if (res != -1) {
        for (int j = 0; j < h_n; j++) {
            if (j != res && M[v].getElement(j)) {
                M[v].setZero(j);
                M_log_stack_xy.push({v, j});
                int n = M_log_stack.top();
                M_log_stack.pop();
                M_log_stack.push(n+1);
            }
        }
    }
    return res;
}

int CMAlgorithmDirected::refinementConditionSatisfied(int i, int j) {

    for (int n : G.out_neighbours(i+1)) {
        if (!M[n-1].intersectionNotEmpty(H_adj_matrix_out[j])){
            return 0;
        }
    }
    for (int n : G.in_neighbours(i+1)) {
        if (!M[n-1].intersectionNotEmpty(H_adj_matrix_in[j])){
            return 0;
        }
    }
    return 1;
}

int CMAlgorithmDirected::refine_full() {
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


int CMAlgorithmDirected::refine(int r, int c){
    for (auto i : G.out_neighbours(r+1)){
        //M[i-1].intersect(H_adj_matrix[c]); // we cant do this now because we have to log any change
        for (int j = 0; j < h_n; j++) {
            if (M[i-1].getElement(j) && !H_adj_matrix_out[c].getElement(j)){
                M[i-1].setZero(j);
                M_log_stack_xy.push({i-1, j});
                int n = M_log_stack.top();
                M_log_stack.pop();
                M_log_stack.push(n+1);
            }
        }
    }
    for (auto i : G.in_neighbours(r+1)){
        //M[i-1].intersect(H_adj_matrix[c]); // we cant do this now because we have to log any change
        for (int j = 0; j < h_n; j++) {
            if (M[i-1].getElement(j) && !H_adj_matrix_in[c].getElement(j)){
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
        for (auto i : G.in_neighbours(r+1)) {
            int v = i-1;
            for (auto j : H.in_neighbours(c+1)) {
                if ( !M[v].getElement(j-1) ) { continue; }
                // check the condition
                // if not satisfied -> M_d[i][j] = 0 and changed = 1
                if ( !refinementConditionSatisfied(v, j-1)) {
                    M[v].setZero(j-1);
                    M_log_stack_xy.push({v, j-1});
                    int n = M_log_stack.top();
                    M_log_stack.pop();
                    M_log_stack.push(n+1);
                    changed = 1;
                }
            }
            //check if the row is zero (that means no more candidates for the node i)
            if (M[v].isZero()) {return 0;}
        }
        for (auto i : G.out_neighbours(r+1)) {
            int v = i-1;
            for (auto j : H.out_neighbours(c+1)) {
                if ( !M[v].getElement(j-1) ) { continue; }
                // check the condition
                // if not satisfied -> M_d[i][j] = 0 and changed = 1
                if ( !refinementConditionSatisfied(v, j-1)) {
                    M[v].setZero(j-1);
                    M_log_stack_xy.push({v, j-1});
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

void CMAlgorithmDirected::M0() {
    // G must have a lesser number of vertices to have an isomorphism subgraph
    M.assign(g_n, BitVector(h_n));
    if ( g_n > h_n ) { return; }
    for ( int i = 0; i < g_n; i++ ) {
        for ( int j = 0; j < h_n; j++ ) {
            if ( G.in_degree(i+1) <= H.in_degree(j+1) && G.out_degree(i+1) <= H.out_degree(j+1) ) {
                M[i].setOne(j);
            }
        }
    }
    return;
}

void CMAlgorithmDirected::initialize() {
    // initialize adjecency bitmatrices of H
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
    // initialize M_root
    M0();
    depth = 0;
    k = -1;
    paired_verteces.assign(h_n, 0);
    column_chosen.assign(g_n, -1);
    return;
}

int CMAlgorithmDirected::findIsomorphisms() {
    initialize();
    int v;
    if (!refine_full()) {
        return 0; 
    }

    while (1) {
        M_log_stack.push(0);
        k = choose_k(k);

        if (k == -1) {
            M_log_stack.pop();
            if (depth == 0) {return 0;}
            depth--;
            v = instOrder[depth];
            paired_verteces[column_chosen[v]] = 0;
            k = column_chosen[v]; 
            column_chosen[v] = -1;
            restore_M(); 
        } 
        else {
            v = instOrder[depth];
            column_chosen[v] = k;
            paired_verteces[k] = 1;
            
            if (refine(v, k)) {
                if (depth == g_n - 1) {
                    isomorphism_found.push_back(column_chosen);
                    
                    paired_verteces[k] = 0;
                    column_chosen[v] = -1;
                    restore_M();
                } else {
                    depth++;
                    k = -1; 
                }
            } 
            else {
                paired_verteces[k] = 0;
                column_chosen[v] = -1;
                restore_M();
            }
        }
    }
}

void CMAlgorithmDirected::restore_M(){
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

void CMAlgorithmDirected::InstantiationOrder::getHeuristic() {
    for (int i = 0; i < g_n; i++ ){
        int sum = 0;
        std::vector<int> G_neighbours;
        G_neighbours.reserve(G.out_neighbours(i+1).size() + G.in_neighbours(i+1).size());
        
        G_neighbours.insert(G_neighbours.end(), G.out_neighbours(i+1).begin(), G.out_neighbours(i+1).end());
        G_neighbours.insert(G_neighbours.end(), G.in_neighbours(i+1).begin(), G.in_neighbours(i+1).end());
        for (int j : G_neighbours){
            for (int k : G_neighbours){
                if (G.edge(j, k)){sum++;}
            }
        }
        sum+=G.degree(i+1);
        heuristic.push_back(sum);
    }
    return;
}

bool CMAlgorithmDirected::InstantiationOrder::Comparator::operator()(int u, int v) const {
    if (prev_neighbours[u] != prev_neighbours[v]) {
        return prev_neighbours[u] > prev_neighbours[v]; // we want the bigger one
    }
    if (heuristic[u] != heuristic[v]) {
        return heuristic[u] > heuristic[v];
    }
    return u < v; // in case of a draw, just return the smaller index for determinism
}

void CMAlgorithmDirected::InstantiationOrder::getOrder(std::vector<int>& order) {
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