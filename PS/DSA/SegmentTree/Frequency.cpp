struct Node {
    int val;
    int mp[26]{};
};

struct segmentTree {
    int sz;
    Node skip{0};
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

    Node query(int l, int r) {
        if (l > r) swap(l, r);
        Node res = query(0, sz - 1, 0, l, r);
        return res;
    }

private:
#define mid (l + (r - l) / 2)
#define lNode (node * 2 + 1)
#define rNode (node * 2 + 2)

    Node merge(const Node &a, const Node &b) {
        Node res;
        for (int i = 0; i < 26; i++) {
            res.mp[i] = a.mp[i] + b.mp[i];
        }

        return res;
    }

    void build(int l, int r, int node, vector<int> &arr) {
        if (l == r) {
            if (l < (int) arr.size()) {
                seg[node].mp[arr[l]]++;
                seg[node].val = arr[l];
            }

            return;
        }

        build(l, mid, lNode, arr);
        build(mid + 1, r, rNode, arr);
        seg[node] = merge(seg[lNode], seg[rNode]);
    }

    void update(int l, int r, int node, int idx, int value) {
        if (l == r) {
            seg[node].mp[seg[node].val]--;
            seg[node].val = value;
            seg[node].mp[seg[node].val]++;
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
