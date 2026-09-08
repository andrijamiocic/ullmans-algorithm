#include "Test.h"
#include <future>

int Test::verification(int n) {
    int krivih = 0;
    double prosjek1 = 0;
    double prosjek2 = 0;
    for (int i = 0; i < n; i++){
        Graph G(40, 0.3);
        Graph H(80, 0.2);
        UllmansAlgorithm u(G, H);
        FocusSearch f(G, H);
        u.findIsomorphisms();
        std::cout << i << std::endl;
        f.findIsomorphisms();
        std::cout << i << std::endl;
        std::cout << "isomorphisms: " << u.isomorphism_found.size() << std::endl;  
        if (!compare(u.isomorphism_found, f.isomorphism_found)) {
            krivih++;
            //f.printIsomorphisms();
        }
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

void Test::runTest(int g_n, double g_density, double gh_ratio, double h_density, int n, int algorithm){
    std::ofstream out_file("rezultati/undirected_"+std::to_string(algorithm)+ "_"+std::to_string(g_n) + "_"+std::to_string(gh_ratio)+"_"+std::to_string(g_density)+"_"+std::to_string(h_density));
    int timeout = 0;
    int h_n = int(g_n/gh_ratio); 
    std::cout << "undirected: g_n=" << g_n << " g_density= " 
    << g_density << " h_n= " << h_n << " h_density= " 
    << h_density << " alg=" << algorithm << std::endl;
    for (int i = 0; i < n; i++) {
        Graph G(g_n, g_density);
        Graph H(h_n, h_density);
        long long measured_time = -1;

        if (algorithm == 1) {
            DepthFirstSearch d(G, H);
            d.findIsomorphisms();
            measured_time = d.time;
        } else if (algorithm == 2) {
            UllmansAlgorithm u(G, H);
            u.findIsomorphisms();
            measured_time = u.time;
        } else if (algorithm == 3) {
            FocusSearch f(G, H);
            f.findIsomorphisms();
            measured_time = f.time;
        } else if (algorithm == 4) {
            CMAlgorithm c(G, H);
            c.findIsomorphisms();
            measured_time = c.time;
        }

        out_file << measured_time << "\n";
        
        if (measured_time == -1) {
            timeout++;
        }
        if (timeout == 4) {
            break;
        }
    }
    std::cout << "done!" << std::endl;
    out_file.close();
    return;
}

void Test::runTestDirected(int g_n, double g_density, double gh_ratio, double h_density, int n, int algorithm){
    std::ofstream out_file("rezultati/directed_"+std::to_string(algorithm)+ "_"+std::to_string(g_n) + "_"+std::to_string(gh_ratio)+"_"+std::to_string(g_density)+"_"+std::to_string(h_density));
    int timeout = 0;
    int h_n = int(g_n/gh_ratio);    
    std::cout << "directed: g_n=" << g_n << " g_density= " 
    << g_density << " h_n= " << h_n << " h_density= " 
    << h_density << " alg=" << algorithm << std::endl;
    
    for (int i = 0; i < n; i++) {
        DirectedGraph G(g_n, g_density);
        DirectedGraph H(h_n, h_density);
        long long measured_time = -1;

        if (algorithm == 1) {
            DepthFirstSearchDirected d(G, H);
            d.findIsomorphisms();
            measured_time = d.time;
        } else if (algorithm == 2) {
            UllmansAlgorithmDirected u(G, H);
            u.findIsomorphisms();
            measured_time = u.time;
        } else if (algorithm == 3) {
            FocusSearchDirected f(G, H);
            f.findIsomorphisms();
            measured_time = f.time;
        } else if (algorithm == 4) {
            CMAlgorithmDirected c(G, H);
            c.findIsomorphisms();
            measured_time = c.time;
        }

        out_file << measured_time << "\n";
        
        if (measured_time == -1) {
            timeout++;
        }
        if (timeout == 2) {
            break;
        }
    }
    std::cout << "done!" << std::endl;
    out_file.close();
    return;
}