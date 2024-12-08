#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

int generateRandomNumber(int x, int y)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(x, y);
    return distribution(gen);
}

void generateAdjacencyMatrix(int vertices, double edgePercentage, bool allowSelfLoops)
{
    if (edgePercentage < 0 || edgePercentage > 100)
    {
        cerr << "Error: Edge percentage must be between 0 and 100." << endl;
        return;
    }

    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));

    int maxEdges = vertices * (vertices - 1) / 2 + (allowSelfLoops ? vertices : 0); // Including self-loops if allowed
    int edges = static_cast<int>(maxEdges * edgePercentage / 100.0);

    int currentEdges = 0;
    while (currentEdges < edges)
    {
        int i = generateRandomNumber(0, vertices - 1);
        int j = generateRandomNumber(0, vertices - 1);

        if (graph[i][j] == 0 && (allowSelfLoops || i != j))
        {
            graph[i][j] = 1;
            if (i != j) // Only increment the other side if it's not a self-loop
            {
                graph[j][i] = 1;
            }
            currentEdges++;
        }
    }

    ofstream file("./src/graph.json");
    file << "{\n";
    file << "    \"adjacency_matrix\": [\n";
    for (size_t i = 0; i < graph.size(); ++i)
    {
        file << "        [";
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
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

int main()
{
    int vertices;
    double edgePercentage;
    char selfLoopsOption;
    bool allowSelfLoops;

    cout << "Enter number of vertices: ";
    cin >> vertices;
    cout << "Enter percentage of maximum number of edges: ";
    cin >> edgePercentage;
    cout << "Allow self-loops? (y/n): ";
    cin >> selfLoopsOption;
    allowSelfLoops = (selfLoopsOption == 'y' || selfLoopsOption == 'Y');

    generateAdjacencyMatrix(vertices, edgePercentage, allowSelfLoops);
    return 0;
}