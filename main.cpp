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
#include "FocusSearch.h"
#include "CMAlgorithm.h"
#include "UllmansAlgorithmDirected.h"
#include "FocusSearchDirected.h"
#include "CMAlgorithmDirected.h"

#include "Test.h"

int main(int argc, char* argv[]){
    Test t;
    int n = 10;
    //std::vector<double> gh_ratio_list = {0.5, 0.25, 0.1};
    //std::vector<double> g_p_list = {0.5, 0.4, 0.3, 0.2};
    //std::vector<double> h_p_list = {0.01, 0.05, 0.1, 0.2, 0.3};
    std::vector<double> gh_ratio_list = {0.5};
    std::vector<double> g_p_list = {0.05};
    std::vector<double> h_p_list = {0.01};

    std::vector<std::vector<double>> parameters = {
        {0.1, 0.2, 0.01, 3},
        {0.1, 0.3, 0.01, 3},
        {0.1, 0.3, 0.05, 3},
        {0.1, 0.4, 0.05, 3},
        {0.1, 0.4, 0.1, 3},
        {0.1, 0.5, 0.2, 3},

        {0.1, 0.3, 0.01, 4},
        {0.1, 0.3, 0.05, 4},
        {0.1, 0.4, 0.05, 4},
        {0.1, 0.4, 0.1, 4},
        {0.1, 0.5, 0.2, 4},

        {0.5, 0.2, 0.1, 2},
        {0.5, 0.3, 0.2, 2},

        {0.5, 0.2, 0.1, 3},

        {0.5, 0.2, 0.1, 2},
        {0.5, 0.3, 0.2, 2},

        {0.25, 0.2, 0.01, 3},
        {0.25, 0.2, 0.05, 3},
        {0.25, 0.3, 0.1, 3},
        {0.25, 0.4, 0.3, 3},

        {0.25, 0.2, 0.01, 4},
        {0.25, 0.2, 0.05, 4},
        {0.25, 0.3, 0.1, 4},
        {0.25, 0.4, 0.2, 4},
        {0.25, 0.5, 0.3, 4}
    };
    std::vector<std::vector<double>> parameters2 = {
        {0.1, 0.3, 0.01, 2},
        {0.1, 0.3, 0.01, 3},
        {0.1, 0.3, 0.01, 4},
        {0.1, 0.4, 0.1, 4},

        {0.5, 0.2, 0.05, 2},
        {0.5, 0.3, 0.3, 2},
        {0.5, 0.2, 0.05, 4},
        {0.5, 0.3, 0.3, 4},

        {0.25, 0.2, 0.01, 2},
        {0.25, 0.3, 0.05, 2},
        {0.25, 0.3, 0.2, 2},
        {0.25, 0.2, 0.01, 3},
        {0.25, 0.2, 0.01, 4},
        {0.25, 0.3, 0.05, 4},
        {0.25, 0.3, 0.2, 4},
    };
    
    t.store_graphs(g_p_list, gh_ratio_list, h_p_list, n);
    //t.store_graphs_directed(g_p_list, gh_ratio_list, h_p_list, n);
    
    t.fullTest(3, g_p_list, gh_ratio_list, h_p_list, n, 300);
    t.fullTest(4, g_p_list, gh_ratio_list, h_p_list, n, 300);
    //t.fullTest(2, g_p_list, gh_ratio_list, h_p_list, n, 100);
    //t.fullTest(1, g_p_list, gh_ratio_list, h_p_list, n, 15);

   

    //std::cout << "Undirected done!";
    /*int a = 1;
    for (auto x : parameters){
        double gh_ratio = x[0];
        double g_p = x[1];
        double h_p = x[2];
        int algorithm = x[3];
        int g_n = 15;
        while(g_n <= 100){
            if(!t.runTest(g_n, g_p, gh_ratio, h_p, n, algorithm)){break;}
            std::cout << g_n << std::endl;
            g_n++;
        }
        std::cout << a << " završio" << std::endl;
        a++; 
    }*/
    //t.fullTestDirected(3, g_p_list, gh_ratio_list, h_p_list, n, 15);
    //t.fullTestDirected(4, g_p_list, gh_ratio_list, h_p_list, n, 15);
    //t.fullTestDirected(2, g_p_list, gh_ratio_list, h_p_list, n, 100);
    //t.fullTestDirected(1, g_p_list, gh_ratio_list, h_p_list, n, 15);

    std::cout << "Undirected done!";

    /*for (auto x : parameters2){
        double gh_ratio = x[0];
        double g_p = x[1];
        double h_p = x[2];
        int algorithm = x[3];
        int g_n = 15;
        while(g_n <= 100){
            if(!t.runTestDirected(g_n, g_p, gh_ratio, h_p, n, algorithm)){break;}
            std::cout << g_n << std::endl;
            g_n++;
        }
        std::cout << a << " završio" << std::endl;
        a++; 
    }*/

    std::cout << "Directed done!";
    
    return 0;
}
/*
int main() {
    Graph G(7, 5);
    G.printAdjMatrix();
    return 0;
}*/
