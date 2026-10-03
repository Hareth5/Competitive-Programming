#include<bits/stdc++.h>
using namespace std;
#define ll long long

int dx[8] = {1, -1, 0, 0, -1, -1, 1, 1};
int dy[8] = {0, 0, 1, -1, -1, 1, -1, 1};
char dir[4]{'D', 'L', 'R', 'U'};
const int N = 5e3 + 5;
vector<int> adj[n + 1];
vector<bool> vis(n + 1, false);

auto dfs = [&](auto &self, int node) -> void {
    vis[node] = true;
    for (auto x: adj[node]) {
        if (!vis[x]) {
            self(self, x);
        }
    }
};

auto bfs = [&](int start) -> void {
    queue<int> q;
    q.emplace(start);
    vis[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto x: adj[node]) {
            if (!vis[x]) {
                vis[x] = true;
                q.emplace(x);
            }
        }
    }
};

auto bfs = [&](int start, int end) -> int {
    queue<pair<int, int> > q;
    q.emplace(start, 0);
    vis[start] = true;

    while (!q.empty()) {
        auto [node, cost] = q.front();
        q.pop();

        if (node == end) return cost;

        for (auto x: adj[node]) {
            if (!vis[x]) {
                vis[x] = true;
                q.emplace(x, cost + 1);
            }
        }
    }
    return -1;
};

auto dijkstra = [&](int start) -> void {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq;
    vector<int> dist(n + 1, inf);
    vector<bool> visited(n + 1, false);

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (visited[node]) continue;
        visited[node] = true;

        for (auto [next, weight]: adj[node]) {
            if (!visited[next] && cost + weight < dist[next]) {
                dist[next] = cost + weight;
                pq.emplace(dist[next], next);
            }
        }
    }
};

auto dijkstra = [&](int start, int end) -> int {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq;
    vector<int> dist(n + 1, inf);
    vector<bool> visited(n + 1, false);

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (visited[node]) continue;
        visited[node] = true;
        if (node == end) return cost;

        for (auto [next, weight]: adj[node]) {
            if (!visited[next] && dist[next] > cost + weight) {
                dist[next] = cost + weight;
                pq.emplace(dist[next], next);
            }
        }
    }

    return -1;
};