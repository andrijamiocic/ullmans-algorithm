#include "FocusSearch.h"

void FocusSearch::initialize(){
    
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