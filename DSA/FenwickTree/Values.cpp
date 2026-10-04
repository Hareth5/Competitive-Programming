struct fenwickTree {
    vector<ll> bit;
    int sz;

    fenwickTree(int n) {
        sz = n;
        bit = vector<ll>(sz + 1);
    }

    void update(int idx, ll val) {
        idx++;
        while (idx <= sz) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    void rangeUpdate(int l, int r, ll val) {
        update(l, val);
        if (r + 1 < sz) update(r + 1, -val);
    }

    ll query(int idx) {
        if (idx < 0) return 0;

        idx++;
        ll res = 0;
        while (idx > 0) {
            res += bit[idx];
            idx -= idx & -idx;
        }

        return res;
    }

    ll range(int l, int r) {
        if (l > r) swap(l, r);
        return query(r) - query(l - 1);
    }

    ll getValue(int idx) {
        return range(idx, idx);
    }

    void set(int idx, ll val) {
        ll old = getValue(idx);
        update(idx, val - old);
    }

    int lower_bound(ll sum) {
        if (sum <= 0) return 0;
        if (query(sz - 1) < sum) return -1;

        int idx = 0;
        int step = 1;
        while (step << 1 <= sz) {
            step <<= 1;
        }

        for (; step > 0; step >>= 1) {
            int nxt = idx + step;
            if (nxt <= sz && bit[nxt] < sum) {
                idx = nxt;
                sum -= bit[nxt];
            }
        }

        return idx;
    }

    int upper_bound(ll sum) {
        return lower_bound(sum + 1);
    }

    void clear() {
        fill(bit.begin(), bit.end(), 0);
    }
};
