#include "SIalgorithms.h"

std::vector<std::vector<int>> SubIsoFinder::M0( const Graph& G, const Graph& H ) {
    int g_n = G.get_v_num();
    int h_n = H.get_v_num();
    // G must have a lesser number of vertices to have an isomorphism subgraph
    if ( g_n > h_n ) {
        return {};
    }
    std::vector<std::vector<int>> M0;
    for ( int i = 0; i < g_n; i++ ) {
        M0.push_back({}); // testirati dobro - koju je bolje prije napuniti
        for ( int j = 0; j < h_n; j++ ) {
            if ( G.degree(i+1) <= H.degree(j+1) ) {
                M0[i].push_back(1);

            }else{
                M0[i].push_back(0);
            }
        }
    }
    return M0;
}

/*int findIsomporphism(const Graph& G, const Graph& H) {
    std::vector<std::vector<int>> m_root = M0(G, H);
    std::vector<int> used_columns(H.v_num); // used_columns[k] = 1 if k-th column is already chosen
    std::vector<int> column(G.v_num);  // column[d] = k if column k is chosen on depth d
    int depth = 0;
    column[0] = 0;
    while ( 1 ) {
        // if there are no more children nodes, go up on the tree
        if ( column[depth]  )
    }

}*/