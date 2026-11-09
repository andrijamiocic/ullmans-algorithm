#include "Test.h"
#include <future>
#include <chrono>

int Test::verification(int n) {
    int krivih = 0;
    double prosjek1 = 0;
    double prosjek2 = 0;
    for (int i = 0; i < n; i++){
        Graph G(5, 0.35);
        Graph H(10, 0.2);
        CMAlgorithm u(G, H);
        FocusSearch f(G, H);
        u.findIsomorphisms();
        std::cout << i << std::endl;
        f.findIsomorphisms();
        std::cout << i << std::endl;
        std::cout << "isomorphisms: " << f.isomorphism_found.size() << " " << u.isomorphism_found.size()<< std::endl;  
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

void Test::store_graphs(std::vector<double>& g_p_list, std::vector<double>& gh_ratio_list, std::vector<double>& h_p_list, int n) {
    for (int g_n = 200; g_n < 301; g_n ++){
        for (auto g_p : g_p_list){
            for (auto gh_ratio : gh_ratio_list){
                int h_n = int(g_n/gh_ratio);
                for (auto h_p : h_p_list){
                    for (int i = 0; i < n; i++){
                        std::cout << g_n << " " << g_p << " " << gh_ratio << " " << h_p << std::endl;
                        int g_e = int(g_n*(g_n-1)*g_p/2);
                        Graph G(g_n, g_e);
                        std::cout << "G\n";
                        Graph H(G, h_n, h_p);
                        std::cout << "H\n";
                        G.toFile("test_graphs/G_"
                            +std::to_string(g_n)
                            +"_"+std::to_string(g_p)
                            +"_"+std::to_string(gh_ratio)
                            +"_"+std::to_string(h_p)
                            +"_"+std::to_string(i));
                        H.toFile("test_graphs/H_"
                            +std::to_string(g_n)
                            +"_"+std::to_string(g_p)
                            +"_"+std::to_string(gh_ratio)
                            +"_"+std::to_string(h_p)
                            +"_"+std::to_string(i));
                    }
                }
            }
        }
        std::cout << g_n << " generated \n";
    }
    return;
}

void Test::store_graphs_directed(std::vector<double>& g_p_list, std::vector<double>& gh_ratio_list, std::vector<double>& h_p_list, int n) {
    for (int g_n = 5; g_n < 16; g_n ++){
        for (auto g_p : g_p_list){
            for (auto gh_ratio : gh_ratio_list){
                int h_n = int(g_n/gh_ratio);
                for (auto h_p : h_p_list){
                    for (int i = 0; i < n; i++){
                        int g_e = int(g_n*(g_n-1)*g_p);
                        DirectedGraph G(g_n, g_e);
                        //DirectedGraph H(G, h_n, h_p);
                        G.toFile("test_graphs_directed/G_"
                            +std::to_string(g_n)
                            +"_"+std::to_string(g_p)
                            +"_"+std::to_string(gh_ratio)
                            +"_"+std::to_string(h_p)
                            +"_"+std::to_string(i));
                        /*H.toFile("test_graphs_directed/H_"
                            +std::to_string(g_n)
                            +"_"+std::to_string(g_p)
                            +"_"+std::to_string(gh_ratio)
                            +"_"+std::to_string(h_p)
                            +"_"+std::to_string(i));*/
                    }
                }
            }
        }
        std::cout << g_n << " directed generated \n";
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

int Test::runTest(int g_n, double g_density, double gh_ratio, double h_density, int n, int algorithm){
    std::ofstream out_file("rezultati/undirected_"+std::to_string(algorithm)+ "_"+std::to_string(g_n) + "_"+std::to_string(gh_ratio)+"_"+std::to_string(g_density)+"_"+std::to_string(h_density));
    int timeout = 0;
    int h_n = int(g_n/gh_ratio); /*
    std::cout << "undirected: g_n=" << g_n << " g_density= " 
    << g_density << " h_n= " << h_n << " h_density= " 
    << h_density << " alg=" << algorithm << std::endl;*/
    for (int i = 0; i < n; i++) {
        
        Graph G("test_graphs/G_"
                +std::to_string(g_n)
                +"_"+std::to_string(g_density)
                +"_"+std::to_string(gh_ratio)
                +"_"+std::to_string(h_density)
                +"_"+std::to_string(i));

        Graph H("test_graphs/H_"
                +std::to_string(g_n)
                +"_"+std::to_string(g_density)
                +"_"+std::to_string(gh_ratio)
                +"_"+std::to_string(h_density)
                +"_"+std::to_string(i));

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
            return 0;
        }
    }
    out_file.close();
    if (timeout) {return 0;}
    return 1;
}

int Test::runTestDirected(int g_n, double g_density, double gh_ratio, double h_density, int n, int algorithm){
    std::ofstream out_file("rezultati/directed_"+std::to_string(algorithm)+ "_"+std::to_string(g_n) + "_"+std::to_string(gh_ratio)+"_"+std::to_string(g_density)+"_"+std::to_string(h_density));
    int timeout = 0;
    int h_n = int(g_n/gh_ratio);    
    /*std::cout << "directed: g_n=" << g_n << " g_density= " 
    << g_density << " h_n= " << h_n << " h_density= " 
    << h_density << " alg=" << algorithm << std::endl;*/
    
    for (int i = 0; i < n; i++) {

        DirectedGraph G("test_graphs_directed/G_"
                +std::to_string(g_n)
                +"_"+std::to_string(g_density)
                +"_"+std::to_string(gh_ratio)
                +"_"+std::to_string(h_density)
                +"_"+std::to_string(i));

        DirectedGraph H("test_graphs_directed/H_"
                +std::to_string(g_n)
                +"_"+std::to_string(g_density)
                +"_"+std::to_string(gh_ratio)
                +"_"+std::to_string(h_density)
                +"_"+std::to_string(i));

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
            return 0;
        }
    }
    out_file.close();
    if (timeout) {return 0;}
    return 1;
}

void Test::fullTest(int algorithm, std::vector<double>& g_p_list, std::vector<double>& gh_ratio_list, std::vector<double>& h_p_list, int n, int max){
    for (auto g_p : g_p_list){
        for (auto gh_ratio : gh_ratio_list){
            for (auto h_p : h_p_list){
                int g_n = 200;
                while(g_n <= max){
                    if(!runTest(g_n, g_p, gh_ratio, h_p, n, algorithm)){break;}
                    std::cout << g_n << std::endl;
                    g_n++;
                }
            }
        }
        std::cout << "undirected, algoritam: " << algorithm << ", g_p: " << g_p << std::endl;
    }
    return;
} 

void Test::fullTestDirected(int algorithm, std::vector<double>& g_p_list, std::vector<double>& gh_ratio_list, std::vector<double>& h_p_list, int n, int max){
    for (auto g_p : g_p_list){
        for (auto gh_ratio : gh_ratio_list){
            for (auto h_p : h_p_list){
                int g_n = 76;
                while(g_n <= max){
                    if(!runTestDirected(g_n, g_p, gh_ratio, h_p, n, algorithm)){break;}
                    std::cout << g_n << std::endl;
                    g_n++;
                }
            }
        }
        std::cout << "directed, algoritam: " << algorithm << ", g_p: " << g_p << std::endl;;
    }
    return;
}