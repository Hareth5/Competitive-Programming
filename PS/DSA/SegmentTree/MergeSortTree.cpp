struct Node {
    vector<int> val;
};

struct mergeSortTree {
    int sz;
    Node skip = {{}};
    vector<Node> seg;

    mergeSortTree(vector<int> &arr) {
        sz = 1;
        int n = arr.size();
        while (sz < n) sz <<= 1;

        seg.assign(sz << 1, skip);
        build(0, sz - 1, 0, arr);
    }

    int lessThan(int l, int r, int x) {
        if (l > r) swap(l, r);
        return lessThan(0, sz - 1, 0, l, r, x);
    }

    int lessEqual(int l, int r, int x) {
        if (l > r) swap(l, r);
        return lessEqual(0, sz - 1, 0, l, r, x);
    }

    int greaterThan(int l, int r, int x) {
        if (l > r) swap(l, r);
        return greaterThan(0, sz - 1, 0, l, r, x);
    }

    int greaterEqual(int l, int r, int x) {
        if (l > r) swap(l, r);
        return greaterEqual(0, sz - 1, 0, l, r, x);
    }

private:
#define mid (l + (r - l) / 2)
#define lNode (node * 2 + 1)
#define rNode (node * 2 + 2)

    Node merge(Node &a, Node &b) {
        Node res;
        res.val.resize(a.val.size() + b.val.size());
        std::merge(a.val.begin(), a.val.end(), b.val.begin(), b.val.end(), res.val.begin());
        return res;
    }

    void build(int l, int r, int node, vector<int> &arr) {
        if (l == r) {
            if (l < arr.size()) {
                seg[node].val.push_back(arr[l]);
            }

            return;
        }

        build(l, mid, lNode, arr);
        build(mid + 1, r, rNode, arr);
        seg[node] = merge(seg[lNode], seg[rNode]);
    }

    int lessThan(int l, int r, int node, int lx, int rx, int x) {
        if (l > rx || r < lx) return 0;
        if (lx <= l && r <= rx) {
            return lower_bound(seg[node].val.begin(), seg[node].val.end(), x)
                   - seg[node].val.begin();
        }

        return lessThan(l, mid, lNode, lx, rx, x)
               + lessThan(mid + 1, r, rNode, lx, rx, x);
    }

    int lessEqual(int l, int r, int node, int lx, int rx, int x) {
        if (l > rx || r < lx) return 0;
        if (lx <= l && r <= rx) {
            return upper_bound(seg[node].val.begin(), seg[node].val.end(), x)
                   - seg[node].val.begin();
        }

        return lessEqual(l, mid, lNode, lx, rx, x)
               + lessEqual(mid + 1, r, rNode, lx, rx, x);
    }

    int greaterThan(int l, int r, int node, int lx, int rx, int x) {
        if (l > rx || r < lx) return 0;
        if (lx <= l && r <= rx) {
            return seg[node].val.end() - upper_bound(seg[node].val.begin(), seg[node].val.end(), x);
        }

        return greaterThan(l, mid, lNode, lx, rx, x)
               + greaterThan(mid + 1, r, rNode, lx, rx, x);
    }

    int greaterEqual(int l, int r, int node, int lx, int rx, int x) {
        if (l > rx || r < lx) return 0;
        if (lx <= l && r <= rx) {
            return seg[node].val.end() - lower_bound(seg[node].val.begin(), seg[node].val.end(), x);
        }

        return greaterEqual(l, mid, lNode, lx, rx, x)
               + greaterEqual(mid + 1, r, rNode, lx, rx, x);
    }

#undef mid
#undef lNode
#undef rNode
};
