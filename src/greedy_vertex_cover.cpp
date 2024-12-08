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
    int count_visited = 0;

    cout << "\n------------------\n\n";

    int u = degree[0].second;
    cout << u << endl;
    cover[u] = 1;
    visited[u] = true;
    count_visited++;
    for (int i = 0; i < V; ++i){
        if (graph[u][i] && !visited[i]){
            visited[i] = true;
            count_visited++;
        }
    }
    degree.erase(degree.begin());

    while (count_visited < V){
        for (int i = 0; i < degree.size(); ++i){
            cout << degree[i].second << " ";
        }
        cout << endl;

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
                cout << u << endl;
                cover[u] = 1;
                for (int j = 0; j < V; ++j){
                    if (graph[u][j] && !visited[j]){
                        visited[j] = true;
                        count_visited++;
                    }
                }
                degree.erase(degree.begin() + i);
                break;
            }
        }
    }

    cout << "\n------------------\n\n";

    return cover;
}