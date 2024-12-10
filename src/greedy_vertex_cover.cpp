#include "../include/greedy_vertex_cover.h"
#include "../include/connectivity.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> greedyCVC(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> cover(V, 0);
    vector<pair<int, int>> degree(V);

    // Liczymy stopnie wierzchołków i liczbę krawędzi
    int edges_count = 0;
    for (int i = 0; i < V; ++i) {
        degree[i] = {0, i};
        for (int j = 0; j < V; ++j) {
            if (graph[i][j]) {
                degree[i].first++;
                edges_count++;
            }
        }
    }
    edges_count = edges_count / 2;
    
    sort(degree.rbegin(), degree.rend());

    // Kopia grafu, w której będziemy odhaczać krawędzie zaliczone
    vector<vector<int>> graph_copy = graph;

    int u = degree[0].second;
    cover[u] = 1;
    for (int i = 0; i < V; ++i){
        if (graph_copy[u][i]){
            graph_copy[u][i] = 0;
            graph_copy[i][u] = 0;
            edges_count--;
        }
    }
    degree.erase(degree.begin());

    // Główna część
    while (edges_count > 0){
        // for (int i = 0; i < degree.size(); ++i){
        //     cout << degree[i].second << " ";
        // }
        // cout << endl;

        // z degree usuwamy wierzchołki, które już są w pokryciu
        // s = liczba wierzchołków, które jeszcze nie są w pokryciu
        int s = degree.size();

        for (int i = 0; i < s; ++i){
            u = degree[i].second;
            bool connects = false;
            for (int j = 0; j < V; ++j){
                if (graph[u][j] && cover[j]){
                    connects = true;
                }
            }
            if(connects){
                cover[u] = 1;
                for (int j = 0; j < V; ++j){
                    if (graph_copy[u][j]){
                        graph_copy[u][j] = 0;
                        graph_copy[j][u] = 0;
                        edges_count--;
                    }
                }
                degree.erase(degree.begin() + i);

                // Print out the current state of graph_copy
                // cout << "Current \"edges count\": " << edges_count << endl;
                // cout << "Current state of graph_copy:" << endl;
                // for (int i = 0; i < V; ++i) {
                //     for (int j = 0; j < V; ++j) {
                //         cout << graph_copy[i][j] << " ";
                //     }
                //     cout << endl;
                // }

                break;
            }
        }
    }

    return cover;
}