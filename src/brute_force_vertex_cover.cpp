#include "../include/brute_force_vertex_cover.h"
#include "../include/connectivity.h"
#include <cmath>
#include <queue>

using namespace std;

bool isVertexCover(const vector<vector<int>>& graph, const vector<int>& cover) {
    int V = graph.size();
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !cover[u] && !cover[v]) {
                return false;
            }
        }
    }
    return true;
}

vector<int> findMinimalVertexCover(const vector<vector<int>>& graph) {
    int V = graph.size();
    int minCoverSize = V;
    vector<int> minCover;

    for (int i = 0; i < (1 << V); ++i) {
        vector<int> cover(V, 0);
        int coverSize = 0;
        for (int j = 0; j < V; ++j) {
            if (i & (1 << j)) {
                cover[j] = 1;
                ++coverSize;
            }
        }
        if (isVertexCover(graph, cover) && isConnected(graph, cover) && coverSize < minCoverSize) {
            minCoverSize = coverSize;
            minCover = cover;
        }
    }

    return minCover;
}