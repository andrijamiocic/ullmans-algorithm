#include "Test.h"

int Test::verification(int n) {
    int krivih = 0;
    double prosjek1 = 0;
    double prosjek2 = 0;
    for (int i = 0; i < n; i++){
        Graph G(10, 0.5, 0);
        Graph H(25, 0.25, 0);
        UllmansAlgorithm u(G, H);
        CMAlgorithm f(G, H);
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