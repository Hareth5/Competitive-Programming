#include<bits/stdc++.h>
using namespace std;
#define ll long long

auto topo_sort = [&]() -> vector<int> {
    vector<int> indegree(n + 1, 0);
    for (int u = 1; u <= n; u++) {
        for (int v: adj[u]) indegree[v]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        topo.push_back(u);
        for (int v: adj[u]) {
            if (--indegree[v] == 0) q.push(v);
        }
    }

    return topo;
};

auto cycleUndirected = [&](auto self, int node, int parent) {
    vis[node] = true;

    for (int neighbor: adj[node]) {
        if (!vis[neighbor]) {
            if (self(self, neighbor, node)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;
        }
    }

    return false;
};

auto cycleDirected = [&](auto self, int node, vector<int> &pathVisited) {
    visited[node] = 1;
    pathVisited[node] = 1;

    for (int neighbor: adj[node]) {
        if (!visited[neighbor]) {
            if (self(self, neighbor, adj)) {
                return true;
            }
        } else if (pathVisited[neighbor]) {
            return true;
        }
    }

    pathVisited[node] = 0;
    return false;
};
