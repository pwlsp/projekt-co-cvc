#include "../include/heuristic_vertex_cover.h"
#include "../include/connectivity.h"
#include <queue>
#include <iostream>
#include <random>

using namespace std;

vector<int> heuristicCVC(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> cover(V, 0);
    vector<bool> to_visit(V, false);

    // Kopia grafu, w której będziemy odhaczać krawędzie zaliczone
    vector<vector<int>> graph_copy = graph;

    int edges_count = 0;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (graph[i][j]) {
                edges_count++;
            }
        }
    }
    edges_count = edges_count / 2;

    int u = rand() % V;
    to_visit[u] = true;

    cout << "Current \"edges count\": " << edges_count << endl;
    cout << "Current state of graph_copy:" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << graph_copy[i][j] << " ";
        }
        cout << endl;
    }

    while (edges_count > 0){
        for (int i = 0; i <= V; ++i){
            if (to_visit[i]){
                u = i;
                cover[u] = 1;
                to_visit[u] = false;
                break;
            }
        }

        int v;
        for (int i = 0; i < V; ++i){
            if(graph_copy[u][i] == 1){
                v = i;
                cout << "added edge: " << u << "-" << v << endl;
                graph_copy[u][v] = 0;
                graph_copy[v][u] = 0;
                edges_count--;
                cover[v] = 1;
                to_visit[v] = false;
                break;
            }
        }
        for (int i = 0; i < V; ++i){
            if (graph_copy[u][i] == 1){
                to_visit[i] = true;
                graph_copy[u][i] = 0;
                graph_copy[i][u] = 0;
                edges_count--;
            }
            if (graph_copy[i][v] == 1){
                to_visit[i] = true;
                graph_copy[v][i] = 0;
                graph_copy[i][v] = 0;
                edges_count--;
            }
        }
        cout << "Current \"edges count\": " << edges_count << endl;
        // Print out the current state of to_visit
        cout << "Current state of to_visit:" << endl;
        for (int i = 0; i < V; ++i) {
            cout << to_visit[i] << " ";
        }
        cout << endl;
        // Print out the current state of graph_copy
        cout << "Current state of graph_copy:" << endl;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                cout << graph_copy[i][j] << " ";
            }
            cout << endl;
        }
    }

    return cover;
}