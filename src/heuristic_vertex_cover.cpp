#include "../include/heuristic_vertex_cover.h"

using namespace std;

vector<int> heuristicVertexCover(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> cover(V, 0);
    vector<bool> visited(V, false);

    for (int u = 0; u < V; ++u) {
        if (!visited[u]) {
            for (int v = 0; v < V; ++v) {
                if (graph[u][v] && !visited[v]) {
                    cover[u] = 1;
                    cover[v] = 1;
                    visited[u] = true;
                    visited[v] = true;
                    break;
                }
            }
        }
    }

    return cover;
}
