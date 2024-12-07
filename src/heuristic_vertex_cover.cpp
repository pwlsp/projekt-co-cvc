#include "../include/heuristic_vertex_cover.h"
#include "../include/connectivity.h"
#include <queue>

using namespace std;

vector<int> heuristicCVC(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> cover(V, 0);
    vector<bool> visited(V, false);
    vector<bool> inCover(V, false);

    for (int u = 0; u < V; ++u) {
        if (!visited[u]) {
            for (int v = 0; v < V; ++v) {
                if (graph[u][v] && !visited[v]) {
                    cover[u] = 1;
                    cover[v] = 1;
                    visited[u] = true;
                    visited[v] = true;
                    inCover[u] = true;
                    inCover[v] = true;
                    break;
                }
            }
        }
    }

    if (!isConnected(graph, cover)) {
        for (int u = 0; u < V; ++u) {
            if (!inCover[u]) {
                for (int v = 0; v < V; ++v) {
                    if (inCover[v] && graph[u][v]) {
                        cover[u] = 1;
                        inCover[u] = true;
                        break;
                    }
                }
            }
        }
    }

    return cover;
}