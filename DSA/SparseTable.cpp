struct sparseTable {
    vector<int> logs;
    vector<vector<int> > table;
    function<int(int, int)> merge;

    sparseTable(vector<int> &arr, function<int(int, int)> f) {
        merge = f;
        int n = arr.size();
        logs.assign(n + 1, 0);
        for (int i = 2; i <= n; i++)
            logs[i] = logs[i / 2] + 1;

        table.assign(logs[n] + 1, vector<int>(n));
        table[0] = arr;
        for (int i = 1; i <= logs[n]; i++) {
            int len = 1 << i;
            for (int j = 0; j + len <= n; j++) {
                table[i][j] = merge(table[i - 1][j], table[i - 1][j + (len >> 1)]);
            }
        }
    }

    int get(int l, int r) {
        if (l > r) swap(l, r);
        int level = logs[r - l + 1];
        return merge(table[level][l], table[level][r - (1 << level) + 1]);
    }

    int query(int l, int r) {
        if (l > r) swap(l, r);
        bool first = true;
        int res = 0;
        int sz = r - l + 1;
        for (int i = logs[sz]; i >= 0; i--) {
            if (1 << i <= sz) {
                if (first) res = table[i][l], first = false;
                else res = merge(res, table[i][l]);

                l += 1 << i;
                sz -= 1 << i;
            }
        }

        return res;
    }
};

sparseTable sp(v, [](int a, int b) {
    return max(a, b);
});
