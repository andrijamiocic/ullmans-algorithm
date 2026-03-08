#include <iostream>
#include "graph.h"

int main(){
    //Graph G("graf_probni", 0);
    Graph G(10, 0.1, 1);
    G.printAdjList();
    G.printAdjMatrix();
    return 0;
}