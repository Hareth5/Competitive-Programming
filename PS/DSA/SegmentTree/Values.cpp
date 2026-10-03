struct Node {
    int sum, mx, mn;
};

struct segmentTree {
    int sz;
    Node skip = {0, -inf, inf};
    vector<Node> seg;

    segmentTree(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        seg.assign(sz << 1, skip);
    }

    void update(int idx, int value) {
        update(0, sz - 1, 0, idx, value);
    }

    int query(int value) {
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
            min(a.mn, b.mn)
        };
    }

    void update(int l, int r, int node, int idx, int value) {
        if (l == r) {
            seg[node].sum += value;
            seg[node].mx = seg[node].sum;
            seg[node].mn = seg[node].sum;
            return;
        }

        if (idx <= mid) update(l, mid, lNode, idx, value);
        else update(mid + 1, r, rNode, idx, value);
        seg[node] = merge(seg[lNode], seg[rNode]);
    }

    int query(int l, int r, int node, int value) {
        if (l == r) return l;

        if (seg[lNode].mx >= value) return query(l, mid, lNode, value);
        return query(mid + 1, r, rNode, value);
    }

#undef mid
#undef lNode
#undef rNode
};
