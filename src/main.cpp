#include <iostream>
#include <vector>
#include "../include/read_graph.h"
#include "../include/brute_force_vertex_cover.h"
#include "../include/heuristic_vertex_cover.h"
#include "../include/greedy_vertex_cover.h"

using namespace std;

void printVertexCover(const vector<int>& cover) {
    cout << "Vertex Cover: ";
    for (int i = 0; i < cover.size(); ++i) {
        if (cover[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    string filename = "graph.json";
    vector<vector<int>> graph = readAdjacencyMatrix(filename);

    cout << "Brute-force Vertex Cover:" << endl;
    vector<int> bruteForceCover = bruteForceCVC(graph);
    printVertexCover(bruteForceCover);

    cout << "Heuristic Vertex Cover:" << endl;
    vector<int> heuristicCover = heuristicCVC(graph);
    printVertexCover(heuristicCover);

    cout << "Greedy Vertex Cover:" << endl;
    vector<int> greedyCover = greedyCVC(graph);
    printVertexCover(greedyCover);

    return 0;
}