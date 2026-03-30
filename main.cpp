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

void store_graphs() {
    for (int i = 0; i < 10; i++) {
        Graph G(20, 0.65, 0);
        Graph H(45+i, 0.45, 0);
        G.toFile("graphs/G_"+std::to_string(i));
        H.toFile("graphs/H_"+std::to_string(i));
    }
    return;
}

void store_test_results(const std::string& filename){
    std::ofstream out_file(filename);
    for (int i = 0; i < 100; i++) {
        Graph G("graphs/G_"+std::to_string(i), 0);
        Graph H("graphs/H_"+std::to_string(i), 0);
        UllmansAlgorithm u(G, H);
        u.measure_time();
        out_file << u.time << "\n";
        std::cout << u.time/1000000 << std::endl;
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
    double prosjek = zbroj1/zbroj2;
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
    int k = 0;
    int br_testova = 5;
    for (int velicina = 10; velicina < 50; velicina++){
        /*double coef = 1;
        std::cout << "Velicina od H: " << velicina << std::endl;
        std::vector<Graph> G;
        std::vector<Graph> H;
        std::vector<std::thread> t_u;
        std::vector<std::thread> t_v;
        std::vector<UllmansAlgorithm> u;
        std::vector<UllmansAlgorithm_vector> v;
        G.reserve(5);
        H.reserve(5);
        u.reserve(5);
        v.reserve(5);
        t_u.reserve(5);
        t_v.reserve(5);
        for (int j = 0; j < 5; j++){
            G.push_back(Graph(int(velicina/2), 0.8, 0));
            H.push_back(Graph(velicina, 0.5, 0));
            u.push_back(UllmansAlgorithm(G[j], H[j]));
            v.push_back(UllmansAlgorithm_vector(G[j], H[j]));
            t_u.push_back(std::thread(&UllmansAlgorithm::measure_time, &u[j]));
            t_v.push_back(std::thread(&UllmansAlgorithm::measure_time, &v[j]));
        }
        for (int j = 0; j < 5; j++){
            t_u[j].join();
            t_v[j].join();
        }
        double time_u = 0;
        double time_v = 0;
        for (int j = 0; j < 5; j++){
            time_u += u[j].time;
            time_v += v[j].time;
        }
        time_u/=5;
        time_v/=5;
        */
        
        //G.printAdjList();
        //H.printAdjList();
        //UllmansAlgorithm_vector s(G, H);
        //s.measure_time();
        //s.printIsomorphisms();
        //UllmansAlgorithm_vector v(G, H);
        //UllmansAlgorithm u(G, H);
        //v.measure_time();
        //u.measure_time();
        //std::cout << "stari: " << v.time << " novi: " << u.time << std::endl;
        //std::cout << v.time / u.time << std::endl;
        //Graph G(9, 0.6, 0);
        //Graph H(15, 0.45, 0);
        //UllmansAlgorithm u(G, H);
        //UllmansAlgorithm_vector v(G, H);
        //u.findIsomorphisms();
        //v.findIsomorphisms();
        //if (u.isomorphism_found != v.isomorphism_found) {
            //k++;
            //std::cout << "nije dobar" << std::endl;
            //G.printAdjList();
            //H.printAdjList();
            //u.printIsomorphisms();
            //v.printIsomorphisms();
        }
        //u.printIsomorphisms();
        //std::cout << s.time << " " << u.time << std::endl;
        //std::cout << coef << std::endl;
        //std::cout << s.time/u.time << std::endl;
        
    //}
    //std::cout << "krivih: " << k << std::endl;
    store_graphs();
    //store_test_results("results1.txt");
    store_test_results("results1.txt");
    return 0;
}