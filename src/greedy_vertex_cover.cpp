#include "../include/greedy_vertex_cover.h"
#include "../include/connectivity.h"
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

vector<int> greedyCVC(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> cover(V, 0);
    vector<pair<int, int>> degree(V);

    for (int i = 0; i < V; ++i) {
        degree[i] = {0, i};
        for (int j = 0; j < V; ++j) {
            if (graph[i][j]) {
                degree[i].first++;
            }
        }
    }
    
    sort(degree.rbegin(), degree.rend());

    vector<bool> visited(V, false);

    for (const auto& d : degree) {
        int u = d.second;
        if (!visited[u]) {
            cover[u] = 1;
            visited[u] = true;
            for (int v = 0; v < V; ++v) {
                if (graph[u][v] && !visited[v]) {
                    cover[v] = 1;
                    visited[v] = true;
                }
            }
        }
    }

    return cover;
}