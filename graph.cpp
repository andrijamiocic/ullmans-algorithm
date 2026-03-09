#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <random>

Graph::Graph(std::string filename, int dir) {
    directed = dir;
    std::ifstream FILE(filename + ".txt");
    std::string line;
    int v1, v2;
    e_num = 0;
    //treba staviti try i izbaciti odgovarajucu gresku
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
        insertEdge(v1, v2, directed);
    }
}

Graph::Graph(int v_number, double p, int dir){
    directed = dir;
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
        int max = directed ? v_num : v1;
        for (int v2 = 0; v2 < max; v2++) {
            if (v1 == v2) {continue;}
            double random_value = distribution(gen);
            if (random_value <= p){
                insertEdge(v1+1, v2+1, directed);
            }
        }
    }
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
        std::cout << i + 1 << ": ";
        for (int j = 0; j < adj_list[i].size(); j++) {
            std::cout << adj_list [i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}

void Graph::insertEdge(int v1, int v2, int directed) {
    adj_matrix[v1-1][v2-1] = 1;
    adj_list[v1-1].push_back(v2);
    //insert simetrical edge for undirected graphs
    if (directed == 0) {
        adj_matrix[v2-1][v1-1] = 1;
        adj_list[v2-1].push_back(v1);
    }
    e_num++;
    return;
}

