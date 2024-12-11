#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

int generateRandomNumber(int x, int y){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(x, y);
    return distribution(gen);
}

void generateAdjacencyMatrix(int vertices, double edgePercentage, bool allowSelfLoops){
    if (edgePercentage < 0 || edgePercentage > 100){
        cerr << "Error: Edge percentage must be between 0 and 100." << endl;
        return;
    }

    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));

    // Tworzenie szkieletu grafu w postaci drzewa rozpinającego, aby graf był spójny
    random_device rd;
    mt19937 gen(rd());
    vector<int> connected(vertices, 0);
    connected[0] = 1;
    int connectedCount = 1;

    while (connectedCount < vertices){
        int i = generateRandomNumber(0, vertices - 1);
        int j = generateRandomNumber(0, vertices - 1);

        if (i != j && (connected[i] == 1 && connected[j] == 0 || connected[i] == 0 && connected[j] == 1)){
            graph[i][j] = 1;
            graph[j][i] = 1;
            connected[i] = connected[j] = 1;
            connectedCount++;
        }
    }

    int maxEdges = vertices * (vertices - 1) / 2 + (allowSelfLoops ? vertices : 0);
    int edges = static_cast<int>(maxEdges * edgePercentage / 100.0);

    int currentEdges = vertices - 1;
    while (currentEdges < edges){
        int i = generateRandomNumber(0, vertices - 1);
        int j = generateRandomNumber(0, vertices - 1);

        if (graph[i][j] == 0 && (allowSelfLoops || i != j)){
            graph[i][j] = 1;
            if (i != j){
                graph[j][i] = 1;
            }
            currentEdges++;
        }
    }

    ofstream file("./src/graph.json");
    file << "{\n";
    file << "    \"adjacency_matrix\": [\n";
    for (size_t i = 0; i < graph.size(); ++i){
        file << "        [";
        for (size_t j = 0; j < graph[i].size(); ++j){
            file << graph[i][j];
            if (j < graph[i].size() - 1)
                file << ", ";
        }
        file << "]";
        if (i < graph.size() - 1)
            file << ",";
        file << "\n";
    }
    file << "    ]\n";
    file << "}\n";
    file.close();
}

int main(int argc, char *argv[]){
    if (argc < 3){
        std::cout << "No arguments given\n";
        return 1;
    }

    int vertices = stoi(argv[1]);
    double edgePercentage = stod(argv[2]);
    bool allowSelfLoops = true;

    generateAdjacencyMatrix(vertices, edgePercentage, allowSelfLoops);
    return 0;
}