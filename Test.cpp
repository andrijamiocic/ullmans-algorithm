#include "Test.h"

int Test::verification(int n) {
    int krivih = 0;
    double prosjek1 = 0;
    double prosjek2 = 0;
    for (int i = 0; i < n; i++){
        DirectedGraph G(10, 0.3);
        DirectedGraph H(25, 0.5);
        FocusSearchDirected u(G, H);
        CMAlgorithmDirected f(G, H);
        u.measure_time();
        std::cout << i << std::endl;
        f.measure_time();
        std::cout << i << std::endl;
        /*if (!compare(u.isomorphism_found, f.isomorphism_found)) {
            krivih++;
            f.printIsomorphisms();
        }*/
        prosjek1 += u.time;
        prosjek2 += f.time;
    }
    prosjek1 /= n;
    prosjek2 /= n;
    std::cout << "krivih:  " << krivih << std::endl;
    std::cout << "Stari: " << prosjek1 << std::endl;
    std::cout << "Novi: " << prosjek2 << std::endl;
    return krivih;
}

void Test::store_graphs(int size) {
    for (int i = 0; i < 100; i++) {
        Graph G(int((size)/2), 0.6);
        Graph H(size, 0.2);
        G.toFile("graphs/G_"+std::to_string(i));
        H.toFile("graphs/H_"+std::to_string(i));
    }
    return;
}

int Test::compare(std::vector<std::vector<int>>& v1, std::vector<std::vector<int>>& v2){
        if (v1.size() != v2.size()){return 0;}
        int n = v2.size();
        for (int i = 0; i < n; i++){
            int ok = 0;
            for (int j = 0; j < n; j++){
                if (v1[i] == v2[j]){
                    ok = 1;
                    break;
                }
            }
            if (!ok) {return 0;}
        }
        return 1;
}