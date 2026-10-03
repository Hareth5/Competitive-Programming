struct Node {
    int sum, mx, mn;
};

struct segmentTree {
    int sz;
    Node skip = {0, -inf, inf};
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
        if (l > r) swap(l, r);
        return query(0, sz - 1, 0, l, r).sum;
    }

private:
#define mid (l + (r - l) / 2)
#define lNode (node * 2 + 1)
#define rNode (node * 2 + 2)

    bool isLeaf(int node) {
        return node >= sz - 1 && node <= 2 * sz - 2;
    }

    Node merge(Node a, Node b) {
        return {
            a.sum + b.sum,
            max(a.mx, b.mx),
            min(a.mn, b.mn)
        };
    }

    void build(int l, int r, int node, vector<int> &arr) {
        if (l == r) {
            if (l < arr.size()) {
                seg[node] = {arr[l], arr[l], arr[l]};
            }

            return;
        }

        build(l, mid, lNode, arr);
        build(mid + 1, r, rNode, arr);
        seg[node] = merge(seg[lNode], seg[rNode]);
    }

    void update(int l, int r, int node, int idx, int value) {
        if (l == r) {
            seg[node] = {value, value, value};
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
