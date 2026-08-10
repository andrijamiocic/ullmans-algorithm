#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <thread>
#include <bitset>
#include <cstdint>
#include "graph.h"
#include "BitVector.h"
#include "DepthFirstSearch.h"
#include "UllmansAlgorithm.h"
#include "UllmansAlgorithm_vector.h"
#include "FocusSearch.h"
#include "Test.h"

void print_matrix(std::vector<std::vector<int>>& v) {
    for ( std::vector<int> v1 : v ) {
        for (int i : v1) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}

void store_graphs(int size) {
    for (int i = 0; i < 100; i++) {
        Graph G(int((size)/2), 0.6, 0);
        Graph H(size, 0.2, 0);
        G.toFile("graphs/G_"+std::to_string(i));
        H.toFile("graphs/H_"+std::to_string(i));
    }
    return;
}

void store_test_results_u(const std::string& filename){
    std::ofstream out_file(filename);
    for (int i = 0; i < 100; i++) {
        Graph G("graphs/G_"+std::to_string(i), 0);
        Graph H("graphs/H_"+std::to_string(i), 0);
        UllmansAlgorithm u(G, H);
        u.measure_time();
        out_file << u.time << "\n";
        std::cout << u.time/1000000 << std::endl;
        if (u.time > 1000000) {
            G.printAdjList();
            H.printAdjList();
        }
    }
    out_file.close();
    return;
}

void store_test_results_f(const std::string& filename){
    std::ofstream out_file(filename);
    for (int i = 0; i < 100; i++) {
        Graph G("graphs/G_"+std::to_string(i), 0);
        Graph H("graphs/H_"+std::to_string(i), 0);
        FocusSearch f(G, H);
        f.measure_time();
        out_file << f.time << "\n";
        std::cout << f.time/1000000 << std::endl;
        if (f.time > 1000000) {
            G.printAdjList();
            H.printAdjList();
        }
    }
    out_file.close();
    return;
}

void compare(const std::string& filename1, const std::string& filename2){
    std::ifstream out_file1(filename1);
    std::ifstream out_file2(filename2);
    double zbroj1 = 0;
    double zbroj2 = 0;
    for (int i = 0; i < 100; i++) {
        std::string line1;
        std::getline(out_file1, line1);
        std::stringstream ss1(line1);
        int res1;
        ss1 >> res1;
        zbroj1 += res1*0.01;
        std::string line2;
        std::getline(out_file2, line2);
        std::stringstream ss2(line2);
        int res2;
        ss2 >> res2;
        zbroj2 += res2*0.01;
        std::cout << res1 << " " << res2 << std::endl;
    }
    double prosjek = zbroj2/zbroj1;
    std::cout << "Omjer: " << prosjek << std::endl;
    if (prosjek >= 1){
        std::cout << "Algoritam je u prosjeku " << prosjek << " puta sporiji" << std::endl;
    }
    else{
        std::cout << "Algoritam je u prosjeku " << 1/prosjek << " puta brzi" << std::endl;
    }
    return;
}

int main(){
    /*store_graphs(1500);
    store_test_results_u("results_u.txt");
    store_test_results_f("results_f.txt");
    compare("results_u.txt", "results_f.txt");*/
    Test t;
    t.verification(50);
    return 0;
}