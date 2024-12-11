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

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
        }
    }

    while (edges_count > 0){
        for (int i = 0; i <= V; ++i){
            if (to_visit[i]){
                u = i;
                to_visit[u] = false;
                break;
            }
        }

        int v = -1;
        for (int i = 0; i < V; ++i){
            if(graph_copy[u][i] == 1){
                v = i;
                graph_copy[u][v] = 0;
                graph_copy[v][u] = 0;
                edges_count--;
                cover[u] = 1;
                cover[v] = 1;
                to_visit[v] = false;
                break;
            }
        }
        if (v == -1){     
            continue;
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
    }

    return cover;
}