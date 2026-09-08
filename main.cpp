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

int main(){
    Test t;
    int counter = 0;
    int g_n_list[11] = {20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40};
    double gh_ratio_list[3] = {0.75, 0.5, 0.25};
    double g_p_list[4] = {0.5, 0.4, 0.3, 0.2};
    double g_p_list_2[1] = {0.2};
    double h_p_list[4] = {0.05, 0.10, 0.15, 0.2};
    int algorithm = 4;
    for (int g_n : g_n_list){
        for (double gh_ratio : gh_ratio_list){
            for (double g_p : g_p_list_2){
                for (double h_p : h_p_list){
                    t.runTest(g_n, g_p, gh_ratio, h_p, 10, algorithm);
                    t.runTestDirected(g_n, g_p, gh_ratio, h_p, 10, algorithm);
                }
            }
        }
    }
    return 0;
}