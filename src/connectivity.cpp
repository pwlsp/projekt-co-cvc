#include "../include/connectivity.h"
#include <queue>
#include <vector>

using namespace std;

bool isConnected(const vector<vector<int>>& graph, const vector<int>& cover) {
    int V = graph.size();
    vector<bool> visited(V, false);
    queue<int> q;
    for (int i = 0; i < V; ++i) {
        if (cover[i]) {
            q.push(i);
            visited[i] = true;
            break;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && cover[v] && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    for (int i = 0; i < V; ++i) {
        if (cover[i] && !visited[i]) {
            return false;
        }
    }
    return true;
}