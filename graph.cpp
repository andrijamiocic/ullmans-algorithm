#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <random>

Graph::Graph(std::string filename) {
    std::ifstream FILE(filename + ".txt");
    std::string line;
    int v1, v2;
    e_num = 0;
    if (getline(FILE, line)) {
        std::stringstream ss(line);
        ss >> v_num;
        adj_matrix = {};
        adj_list = {};
        for (int i = 0; i < v_num; i++){
            std::vector<int> zero_vector(v_num);
            adj_matrix.push_back(zero_vector);
            adj_list.push_back({});
        }
    }
    while (getline(FILE, line)) {
        std::stringstream ss(line);
        ss >> v1 >> v2;
        insertEdge(v1, v2);
    }
}

Graph::Graph(int v_number, double p){
    v_num = v_number;
    e_num = 0;
    adj_matrix = {};
    adj_list = {};
    for (int i = 0; i < v_num; i++){
        std::vector<int> zero_vector(v_num);
        adj_matrix.push_back(zero_vector);
        adj_list.push_back({});
    }
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    for (int v1 = 0; v1 < v_num; v1++) {
        for (int v2 = 0; v2 < v1; v2++) {
            if (v1 == v2) {continue;}
            double random_value = distribution(gen);
            if (random_value <= p){
                insertEdge(v1+1, v2+1);
            }
        }
    }
}

Graph::Graph(Graph& G, int v_number, double p){
    v_num = v_number;
    e_num = 0;
    adj_matrix = {};
    adj_list = {};
    for (int i = 0; i < v_num; i++){
        std::vector<int> zero_vector(v_num);
        adj_matrix.push_back(zero_vector);
        adj_list.push_back({});
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, v_num);
    std::vector<int> isomorphism;
    std::set<int> used;
    int random_int;
    for (int i = 0; i < G.get_v_num(); i++){
        do {
            random_int = distrib(gen);
        }
        while (used.count(random_int));
        isomorphism.push_back(random_int);
        used.insert(random_int);
    }
    for (int i = 0; i < G.get_v_num(); i++){
        for (int j = 0; j < G.adj_list[i].size(); j++){
            insertEdge(isomorphism[i], isomorphism[G.adj_list[i][j]-1]);
        }
    }
    std::random_device rd1;  
    std::mt19937 gen1(rd1());
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    for (int v1 = 0; v1 < v_num; v1++) {
        for (int v2 = 0; v2 < v1; v2++) {
            if (v1 == v2) {continue;}
            double random_value = distribution(gen1);
            if (random_value <= p){
                insertEdge(v1+1, v2+1);
            }
        }
    }
}

bool Graph::toFile(const std::string& filename) {
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

void Graph::printAdjMatrix() {
    for (int i = 0; i < v_num; i++) {
        for (int j = 0; j < v_num; j++) {
            std::cout << adj_matrix [i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}

void Graph::printAdjList() {
    for (int i = 0; i < v_num; i++) {
        std::cout << i << ": ";
        std::cout << degree(i+1);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}

void Graph::insertEdge(int v1, int v2) {
    if (edge(v1, v2)){return;}
    adj_matrix[v1-1][v2-1] = 1;
    adj_list[v1-1].push_back(v2);
    adj_matrix[v2-1][v1-1] = 1;
    adj_list[v2-1].push_back(v1);
    e_num++;
    return;
}