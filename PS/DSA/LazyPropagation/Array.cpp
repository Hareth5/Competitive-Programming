struct Node {
    int sum, mx, mn;
    int add, set;
    bool isLazy;
};

struct segmentTree {
    int sz;
    Node skip = {0, -inf, inf, 0, 0, false};
    vector<Node> seg;

    segmentTree(vector<int> &arr) {
        sz = 1;
        int n = arr.size();
        while (sz < n) sz <<= 1;

        seg.assign(sz << 1, skip);
        build(0, sz - 1, 0, arr);
    }

    void update(int l, int r, int value) {
        if (l > r) swap(l, r);
        update(0, sz - 1, 0, l, r, value);
    }

    void set(int l, int r, int value) {
        if (l > r) swap(l, r);
        set(0, sz - 1, 0, l, r, value);
    }

    int query(int l, int r) {
        if (l > r) swap(l, r);
        return query(0, sz - 1, 0, l, r).sum;
    }

private:
#define mid (l + (r - l) / 2)
#define lNode (node * 2 + 1)
#define rNode (node * 2 + 2)

    Node merge(Node a, Node b) {
        return {
            a.sum + b.sum, max(a.mx, b.mx), min(a.mn, b.mn),
            0, 0, false
        };
    }

    void applySet(int l, int r, int node, int value) {
        seg[node].sum = (r - l + 1) * value;
        seg[node].mx = value;
        seg[node].mn = value;

        seg[node].set = value;
        seg[node].add = 0;
        seg[node].isLazy = true;
    }

    void applyUpdate(int l, int r, int node, int value) {
        seg[node].sum += (r - l + 1) * value;
        seg[node].mx += value;
        seg[node].mn += value;

        if (seg[node].isLazy) seg[node].set += value;
        else seg[node].add += value;
    }

    void propagate(int l, int r, int node) {
        if (l == r) return;

        if (seg[node].isLazy) {
            applySet(l, mid, lNode, seg[node].set);
            applySet(mid + 1, r, rNode, seg[node].set);
            seg[node].isLazy = false;
        }

        if (seg[node].add != 0) {
            applyUpdate(l, mid, lNode, seg[node].add);
            applyUpdate(mid + 1, r, rNode, seg[node].add);
            seg[node].add = 0;
        }
    }

    void build(int l, int r, int node, vector<int> &arr) {
        if (l == r) {
            if (l < arr.size()) {
                seg[node] = {
                    arr[l], arr[l], arr[l], 0, 0, false
                };
            }

            return;
        }

        build(l, mid, lNode, arr);
        build(mid + 1, r, rNode, arr);
        seg[node] = merge(seg[lNode], seg[rNode]);
    }

    void update(int l, int r, int node, int lx, int rx, int value) {
        if (l > rx || r < lx) return;
        if (lx <= l && r <= rx) {
            applyUpdate(l, r, node, value);
            return;
        }

        propagate(l, r, node);

        update(l, mid, lNode, lx, rx, value);
        update(mid + 1, r, rNode, lx, rx, value);
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
