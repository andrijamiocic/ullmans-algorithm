#include "Test.h"

int Test::verification(int n) {
    int krivih = 0;
    double prosjek1 = 0;
    double prosjek2 = 0;
    for (int i = 0; i < n; i++){
        Graph G(7, 0.4, 0);
        Graph H(10, 0.8, 0);
        DepthFirstSearch d(G, H);
        UllmansAlgorithm u(G, H);
        d.measure_time();
        std::cout << i << std::endl;
        u.measure_time();
        std::cout << i << std::endl;
        if (d.isomorphism_found != u.isomorphism_found) {
            krivih++;
        }
        prosjek1 += u.time;
        prosjek2 += d.time;
    }
    prosjek1 /= n;
    prosjek2 /= n;
    std::cout << "krivih:  " << krivih << std::endl;
    std::cout << "Stari: " << prosjek1 << std::endl;
    std::cout << "Novi: " << prosjek2 << std::endl;
    return krivih;
}