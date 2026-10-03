struct Node {
    int sum, mx, mn;
    int add, set;
    bool isLazy;
};

struct segmentTree {
    int sz;
    Node skip = {0, -inf, inf, 0, 0, false};
    vector<Node> seg;

    segmentTree(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;

        seg.assign(sz << 1, skip);
        build(0, sz - 1, 0, n);
    }

    void update(int l, int r, int value) {
        if (l > r) swap(l, r);
        update(0, sz - 1, 0, l, r, value);
    }

    void set(int l, int r, int value) {
        if (l > r) swap(l, r);
        set(0, sz - 1, 0, l, r, value);
    }

    int query(int value) {
        if (seg[0].mx < value) return -1;
        return query(0, sz - 1, 0, value);
    }

private:
#define mid (l + (r - l) / 2)
#define lNode (node * 2 + 1)
#define rNode (node * 2 + 2)

    Node merge(Node a, Node b) {
        return {
            a.sum + b.sum,
            max(a.mx, b.mx),
            min(a.mn, b.mn),
            0, 0, false
        };
    }

    void build(int l, int r, int node, int n) {
        if (l == r) {
            if (l < n) {
                seg[node] = {0, 0, 0, 0, 0, false};
            }

            return;
        }

        build(l, mid, lNode, n);
        build(mid + 1, r, rNode, n);
        seg[node] = merge(seg[lNode], seg[rNode]);
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

    int query(int l, int r, int node, int value) {
        if (l == r) return l;

        propagate(l, r, node);

        if (seg[lNode].mx >= value) return query(l, mid, lNode, value);
        return query(mid + 1, r, rNode, value);
    }

#undef mid
#undef lNode
#undef rNode
};
