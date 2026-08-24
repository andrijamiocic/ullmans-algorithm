#include "Directedgraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <random>

DirectedGraph::DirectedGraph(std::string filename) {
    std::ifstream FILE(filename + ".txt");
    std::string line;
    int v1, v2;
    e_num = 0;
    if (getline(FILE, line)) {
        std::stringstream ss(line);
        ss >> v_num;
        adj_matrix = {};
        adj_list_in = {};
        adj_list_out = {};
        for (int i = 0; i < v_num; i++){
            std::vector<int> zero_vector(v_num);
            adj_matrix.push_back(zero_vector);
            adj_list_in.push_back({});            
            adj_list_out.push_back({});

        }
    }
    while (getline(FILE, line)) {
        std::stringstream ss(line);
        ss >> v1 >> v2;
        insertEdge(v1, v2);
    }
}

DirectedGraph::DirectedGraph(int v_number, double p){
    v_num = v_number;
    e_num = 0;
    adj_matrix = {};
    adj_list_in = {};
    adj_list_out = {};
    for (int i = 0; i < v_num; i++){
        std::vector<int> zero_vector(v_num);
        adj_matrix.push_back(zero_vector);
        adj_list_in.push_back({});            
        adj_list_out.push_back({});
    }
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    for (int v1 = 0; v1 < v_num; v1++) {
        for (int v2 = 0; v2 < v_num; v2++) {
            if (v1 == v2) {continue;}
            double random_value = distribution(gen);
            if (random_value <= p){
                insertEdge(v1+1, v2+1);
            }
        }
    }
}

bool DirectedGraph::toFile(const std::string& filename) {
    std::ofstream out_file(filename+".txt");
    
    if (!out_file.is_open()) {return false;}
    
    out_file << get_v_num() << "\n";

    for (int i = 0; i < get_v_num(); i++) {
        for (int j = i+1; j < get_v_num(); j++ ){
            if (edge(i+1, j+1)){
                out_file << i+1 << " " << j+1 << "\n";
            }
        }
    }
    out_file.close();
    return true;
}

void DirectedGraph::printAdjMatrix() {
    for (int i = 0; i < v_num; i++) {
        for (int j = 0; j < v_num; j++) {
            std::cout << adj_matrix [i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}

void DirectedGraph::printAdjList() {
    for (int i = 0; i < v_num; i++) {
        std::cout << i << ": ";
        std::cout << degree(i+1);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}

void DirectedGraph::insertEdge(int v1, int v2) {
    adj_matrix[v1-1][v2-1] = 1;
    adj_list_out[v1-1].push_back(v2);
    adj_list_in[v2-1].push_back(v1);
    e_num++;
    return;
}
