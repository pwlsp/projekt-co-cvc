#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp> // Include the JSON library

using json = nlohmann::json;

int main() {
    // Read the JSON file
    std::ifstream inputFile("./src/graph.json");
    json graphJson;
    inputFile >> graphJson;

    // Extract the adjacency matrix
    std::vector<std::vector<int>> adjacencyMatrix = graphJson["adjacency_matrix"];

    // Convert and print the adjacency matrix in the specified format
    for (const auto& row : adjacencyMatrix) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
