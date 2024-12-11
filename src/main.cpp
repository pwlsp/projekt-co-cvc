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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <mode: b|h|g>" << endl;
        return 1;
    }

    char mode = argv[1][0];
    string filename = "./src/graph.json";
    vector<vector<int>> graph = readAdjacencyMatrix(filename);

    switch (mode) {
        case 'b':
            // cout << "Brute-force Connected Vertex Cover" << endl;
            {
                vector<int> bruteForceCover = bruteForceCVC(graph);
                // printVertexCover(bruteForceCover);
            }
            break;
        case 'h':
            // cout << "Heuristic Connected Vertex Cover" << endl;
            {
                vector<int> heuristicCover = heuristicCVC(graph);
                // printVertexCover(heuristicCover);
            }
            break;
        case 'g':
            // cout << "Greedy Connected Vertex Cover" << endl;
            {
                vector<int> greedyCover = greedyCVC(graph);
                // printVertexCover(greedyCover);
            }
            break;
        default:
            cerr << "Invalid mode. Use 'b' for brute-force, 'h' for heuristic, or 'g' for greedy." << endl;
            return 1;
    }

    return 0;
}