#include "../include/greedy_vertex_cover.h"
#include <algorithm>

using namespace std;

vector<int> greedyVertexCover(const vector<vector<int>>& graph) {
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

    for (auto& d : degree) {
        int u = d.second;
        if (!cover[u]) {
            for (int v = 0; v < V; ++v) {
                if (graph[u][v] && !cover[v]) {
                    cover[u] = 1;
                    cover[v] = 1;
                    break;
                }
            }
        }
    }

    return cover;
}
