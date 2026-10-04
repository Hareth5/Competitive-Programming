struct Node {
    int sum, mx, pref, suff;
    int set;
    bool isLazy;
};

struct segmentTree {
    int sz;
    Node skip = {0, 0, 0, 0, 0, false};
    vector<Node> seg;

    segmentTree(vector<int> &arr) {
        sz = 1;
        int n = arr.size();
        while (sz < n) sz <<= 1;

        seg.assign(sz << 1, skip);
        build(0, sz - 1, 0, arr);
    }

    void update(int idx, int value) {
        int cur = query(idx, idx);
        set(idx, idx, cur + value);
    }

    void set(int l, int r, int value) {
        if (l > r) swap(l, r);
        set(0, sz - 1, 0, l, r, value);
    }

    int query(int l, int r) {
        if (l > r) swap(l, r);
        return query(0, sz - 1, 0, l, r).mx;
    }

private:
#define mid (l + (r - l) / 2)
#define lNode (node * 2 + 1)
#define rNode (node * 2 + 2)

    Node merge(Node a, Node b) {
        Node res;
        res.sum = a.sum + b.sum;
        res.pref = max(a.pref, a.sum + b.pref);
        res.suff = max(b.suff, b.sum + a.suff);
        res.mx = max({a.mx, b.mx, a.suff + b.pref});

        res.set = 0;
        res.isLazy = false;
        return res;
    }

    void applySet(int l, int r, int node, int value) {
        int len = r - l + 1;
        seg[node].sum = len * value;

        if (value > 0) {
            seg[node].mx = seg[node].sum;
            seg[node].pref = seg[node].sum;
            seg[node].suff = seg[node].sum;
        } else {
            seg[node].mx = 0;
            seg[node].pref = 0;
            seg[node].suff = 0;
        }

        seg[node].set = value;
        seg[node].isLazy = true;
    }

    void propagate(int l, int r, int node) {
        if (l == r) return;

        if (seg[node].isLazy) {
            applySet(l, mid, lNode, seg[node].set);
            applySet(mid + 1, r, rNode, seg[node].set);
            seg[node].isLazy = false;
        }
    }

    void build(int l, int r, int node, vector<int> &arr) {
        if (l == r) {
            if (l < arr.size()) {
                seg[node].sum = arr[l];
                seg[node].mx = max(0LL, arr[l]);
                seg[node].pref = max(0LL, arr[l]);
                seg[node].suff = max(0LL, arr[l]);
            }

            return;
        }

        build(l, mid, lNode, arr);
        build(mid + 1, r, rNode, arr);
        seg[node] = merge(seg[lNode], seg[rNode]);
    }

    void set(int l, int r, int node, int lx, int rx, int value) {
        if (l > rx || r < lx) return;
        if (lx <= l && r <= rx) {
            applySet(l, r, node, value);
            return;
        }

        propagate(l, r, node);

        set(l, mid, lNode, lx, rx, value);
        set(mid + 1, r, rNode, lx, rx, value);
        seg[node] = merge(seg[lNode], seg[rNode]);
    }

    Node query(int l, int r, int node, int lx, int rx) {
        if (l > rx || r < lx) return skip;
        if (lx <= l && r <= rx) return seg[node];

        propagate(l, r, node);

        Node left = query(l, mid, lNode, lx, rx);
        Node right = query(mid + 1, r, rNode, lx, rx);
        return merge(left, right);
    }

#undef mid
#undef lNode
#undef rNode
};
