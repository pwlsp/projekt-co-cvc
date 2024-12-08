#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
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

void generateAdjacencyMatrix(int vertices, int maximum, int edges_sat)
{
    vector<vector<int>> edgeList;
    vector<int> order(vertices);
    for (int i = 0; i < vertices; ++i)
    {
        order[i] = i;
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(order.begin(), order.end(), g);

    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            auto it = find(order.begin(), order.end(), i);
            auto jt = find(order.begin(), order.end(), j);
            int index_i = it - order.begin();
            int index_j = jt - order.begin();

            if (i != j && (index_i < index_j))
            {
                vector edge({i, j});
                edgeList.push_back(edge);
            }
        }
    }

    int next;

    for (int i = 0; i < vertices - 1; i++)
    {
        next = generateRandomNumber(i + 1, vertices - 1);

        graph[order[i]][order[next]] = 1;
        graph[order[next]][order[i]] = 1;

        vector edge_i({order[i], order[next]});
        edgeList.erase(remove(edgeList.begin(), edgeList.end(), edge_i), edgeList.end());
    }

    int edges = vertices - 1;
    if (edges > edges_sat)
    {
        cout << "\nWARNING: Given saturation is not enough to make a DAG - generating DAG with minimum amount of edges.\n";
    }
    while (edges < edges_sat)
    {
        int i = generateRandomNumber(0, edgeList.size() - 1);
        int start = edgeList[i][0];
        int end = edgeList[i][1];
        vector edge_i({start, end});

        graph[start][end] = 1;
        graph[end][start] = 1;
        edges++;

        edgeList.erase(edgeList.begin() + i);
    }

    json j;
    j["adjacency_matrix"] = graph;

    ofstream file("graph.json");
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
    int vertices, maximum, edges_sat;
    cout << "Enter number of vertices: ";
    cin >> vertices;
    cout << "Enter maximum number of edges: ";
    cin >> maximum;
    cout << "Enter number of edges to saturate the graph: ";
    cin >> edges_sat;

    generateAdjacencyMatrix(vertices, maximum, edges_sat);
    cout << "Graph generated successfully!\n";
    return 0;
}