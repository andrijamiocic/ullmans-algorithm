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

void Test::store_graphs() {
    for (int i = 0; i < 100; i++) {
        Graph G(int((50)/2), 0.6);
        Graph H(50, 0.2);
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

void Test::runTest(std::string filename, int g_n, double g_density, int h_n, double h_density, int n){
    std::ofstream out_file(filename);
    for (int i = 0; i < n; i++) {
        Graph G(g_n, g_density);
        Graph H(h_n, h_density);
        //UllmansAlgorithm u(G, H);
        CMAlgorithm c(G, H);
        FocusSearch f(G, H);
        //u.measure_time();
        c.measure_time();
        f.measure_time();
        //out_file << u.time << " ";
        out_file << c.time << " ";
        out_file << f.time << "\n";
        std::cout << i << std::endl;
    }
    out_file.close();
    return;
}

void Test::runTestDirected(std::string filename, int g_n, double g_density, int h_n, double h_density, int n){
    std::ofstream out_file(filename);
    for (int i = 0; i < n; i++) {
        DirectedGraph G(g_n, g_density);
        DirectedGraph H(h_n, h_density);
        UllmansAlgorithmDirected u(G, H);
        CMAlgorithmDirected c(G, H);
        FocusSearchDirected f(G, H);
        u.measure_time();
        c.measure_time();
        f.measure_time();
        out_file << u.time << " ";
        out_file << c.time << " ";
        out_file << f.time << "\n";
    }
    out_file.close();
    return;
}