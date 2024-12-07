#include "../include/read_graph.h"
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

vector<vector<int>> readAdjacencyMatrix(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Could not open the file!" << endl;
        exit(1);
    }

    json j;
    inputFile >> j;

    auto adjacencyMatrix = j["adjacency_matrix"];
    int size = adjacencyMatrix.size();
    vector<vector<int>> matrix(size, vector<int>(size));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = adjacencyMatrix[i][j];
        }
    }

    return matrix;
}
