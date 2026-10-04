class DSU {
private:
    vector<int> par, rank, sz;
    stack<pair<int, pair<int,int> > > history;
    // {type of operation (0 for root change, 1 for rank and 2 for size), {the node that was changed, the last value of the node}}
    stack<int> checkpoint;
    int n, comp, mx;

public:
    DSU(int n) {
        par.resize(n + 1), rank.resize(n + 1), sz.assign(n + 1, 1);
        comp = n, mx = 1;
        for (int i = 0; i <= n; i++) par[i] = i;
    }

    int find_root(int node) {
        if (node == par[node]) return node;
        return find_root(par[node]); // without path compression
    }

    void union_by_rank(int u, int v) {
        int root_u = find_root(u), root_v = find_root(v);
        if (root_u == root_v) return;
        comp--;
        if (rank[root_u] > rank[root_v]) {
            history.push({0, {root_v, par[root_v]}});
            par[root_v] = root_u;
        } else {
            history.push({0, {root_u, par[root_u]}});
            par[root_u] = root_v;
            if (rank[root_u] == rank[root_v]) {
                history.push({1, {root_v, rank[root_v]}});
                rank[root_v]++;
            }
        }
    }

    void union_by_size(int u, int v) {
        int root_u = find_root(u), root_v = find_root(v);
        if (root_u == root_v) return;
        comp--;
        if (sz[root_u] < sz[root_v]) {
            history.push({0, {root_u, par[root_u]}});
            history.push({2, {root_v, sz[root_v]}});
            par[root_u] = root_v;
            sz[root_v] += sz[root_u];
        } else {
            history.push({0, {root_v, par[root_v]}});
            history.push({2, {root_u, sz[root_u]}});
            par[root_v] = root_u;
            sz[root_u] += sz[root_v];
        }
        mx = max({mx, sz[root_u], sz[root_v]});
    }

    void unite(int u, int v) { union_by_size(u, v); }

    void persist() { checkpoint.push(history.size()); }

    void roll_back() {
        if (checkpoint.empty()) return;
        int check = checkpoint.top();
        checkpoint.pop();

        while (history.size() > check) {
            int type = history.top().first, node = history.top().second.first, last_val = history.top().second.second;
            history.pop();
            if (type == 0) {
                // root change
                if (node != par[node]) comp++;
                par[node] = last_val;
            } else if (type == 1) {
                // rank change
                rank[node] = last_val;
            } else {
                // size change
                sz[node] = last_val;
            }
        }
    }

    bool is_connected(int u, int v) { return find_root(u) == find_root(v); }
    int get_size(int node) { return sz[find_root(node)]; }
    int get_comps() { return comp; }
    int get_mx_size() { return mx; }
};

int32_t main() {
    int n, m;
    cin >> n >> m;
    DSU d(n);
    for (int i = 0; i < m; i++) {
        string op;
        cin >> op;
        if (op == "union") {
            int u, v;
            cin >> u >> v;
            d.unite(u, v);
            cout << d.get_comps() << '\n';
        } else if (op == "persist") d.persist();
        else {
            d.roll_back();
            cout << d.get_comps() << '\n';
        }
    }
    return 0;
}