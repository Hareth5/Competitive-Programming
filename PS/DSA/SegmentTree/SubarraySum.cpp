struct Node {
    int mx, sum, pref, suff;
};

struct segmentTree {
    int sz;
    Node skip = {0, 0, 0, 0};
    vector<Node> seg;

    segmentTree(vector<int> &arr) {
        sz = 1;
        int n = arr.size();
        while (sz < n) sz <<= 1;

        seg.assign(sz << 1, skip);
        build(0, sz - 1, 0, arr);
    }

    void update(int idx, int value) {
        update(0, sz - 1, 0, idx, value);
    }

    int query(int l, int r) {
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
        return res;
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

    void update(int l, int r, int node, int idx, int value) {
        if (l == r) {
            seg[node].sum = value;
            seg[node].mx = max(0LL, value);
            seg[node].pref = max(0LL, value);
            seg[node].suff = max(0LL, value);
            return;
        }

        if (idx <= mid) update(l, mid, lNode, idx, value);
        else update(mid + 1, r, rNode, idx, value);
        seg[node] = merge(seg[lNode], seg[rNode]);
    }

    Node query(int l, int r, int node, int lx, int rx) {
        if (l > rx || r < lx) return skip;
        if (lx <= l && r <= rx) return seg[node];

        Node left = query(l, mid, lNode, lx, rx);
        Node right = query(mid + 1, r, rNode, lx, rx);
        return merge(left, right);
    }

#undef mid
#undef lNode
#undef rNode
};
