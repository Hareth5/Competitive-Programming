#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef long long L;
const L INF = (L) (1e18) + 1;
const L MOD = 1e9 + 7;

// ================================================================
// SECTION: I/O & shorthand macros
// ================================================================
#define pb(x) push_back(x)                                             // vector push_back
#define _pb() pop_back()                                                // vector pop_back
#define pf(x) push_front(x)                                             // deque push_front
#define _pf() pop_front()                                               // deque pop_front
#define lb(a, x) lower_bound(a.begin(), a.end(), x)                     // first >= x
#define ub(a, x) upper_bound(a.begin(), a.end(), x)                     // first > x
#define minx(x, y) x = min(x, y)                                        // x = min(x, y) in place
#define maxx(x, y) x = max(x, y)                                        // x = max(x, y) in place
#define scan(a, n, s) for (int i = s; i < n+s; i++) cin >> a[i];                              // read n values starting at index s

#define scan_pair(a, n, s) for (int i = s; i < n+s; i++) cin >> a[i].first, cin >> a[i].second; // read n pairs starting at index s

#define scan_arr(a, n, s, sub, subs) for (int i = s; i < n+s; i++) for (int j = subs; j < sub+subs; j++) cin >> a[i][j]; // read a 2D grid

#define freq(a, m, n, s) for (int i = s; i < n+s; i++) cin >> a[i], m[a[i]]++;                 // read n values and build frequency map

#define pref(a, p) for (int i = 1; i < a.size(); i++) p[i] = p[i-1] + a[i];                    // build prefix-sum array p from a

#define suff(a, s) for (int i = 1; i < a.size(); i++) s[i] = p[i-1] + a[a.size()-1-i];         // build suffix-sum array s from a

#define modSub(a, b) (a-b+MOD)%MOD                                      // (a - b) mod MOD, safe for negatives
#define MOD_SUB(a, b) ((a - b) % MOD + MOD) % MOD;                      // same as modSub, statement form
#define MXE(a) max_element(a.begin(), a.end())                          // iterator to max element
#define YN(b) cout << (b ? "YES":"NO") << '\n';                         // print YES/NO
#define fastio ios::sync_with_stdio(false);cin.tie(nullptr);            // fast cin/cout

// ================================================================
// SECTION: PBDS ordered containers
// ================================================================
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// order_of_key / find_by_order, unique keys
template<class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// same, allows duplicates

// ================================================================
// SECTION: Data structures
// ================================================================

// Disjoint Set Union with path compression + union by rank
class DSU {
public:
    vector<int> parent, rnk;

    DSU(int n) {
        parent.resize(n + 1);
        rnk.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int f(int x) {
        // find root with path compression
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void unite(int x, int y) {
        // union by rank
        int rx = f(x), ry = f(y);
        if (rx == ry) return;
        if (rnk[rx] < rnk[ry]) parent[rx] = ry;
        else if (rnk[rx] > rnk[ry]) parent[ry] = rx;
        else {
            parent[ry] = rx;
            rnk[rx]++;
        }
    }

    bool connected(int x, int y) { return f(x) == f(y); }
};

// Iterative-build sum segment tree over a fixed array (point update, range sum query)
class SegTree {
public:
    vector<L> ST, a;
    L n;

    SegTree(L n) {
        this->n = n, a = vector<L>(n), ST = vector<L>(4 * n);
        B(1, 0, n - 1);
    }

    SegTree(vector<L> V) {
        a = V, n = (L) V.size(), ST = vector<L>(4 * n);
        B(1, 0, n - 1);
    }

    void B(L x, L s, L e) {
        // build
        if (s == e)
            ST[x] = a[s];
        else {
            L m = (s + e) / 2;
            B(2 * x, s, m);
            B(2 * x + 1, m + 1, e);
            ST[x] = ST[2 * x] + ST[2 * x + 1];
        }
    }

    void U(L x, L s, L e, L i, L v) {
        // point update (fixed: recurse on node x, not size n)
        if (s == e) ST[x] = v;
        else {
            L m = (s + e) / 2;
            if (i <= m) U(2 * x, s, m, i, v);
            else U(2 * x + 1, m + 1, e, i, v);
            ST[x] = ST[2 * x] + ST[2 * x + 1];
        }
    }

    L Q(L x, L s, L e, L l, L r) {
        // range sum query
        if (s > r || e < l) return 0;
        if (s >= l && e <= r)
            return ST[x];
        L m = (s + e) / 2;
        return Q(2 * x, s, m, l, r) + Q(2 * x + 1, m + 1, e, l, r);
    }

    L Q(L l, L r) { return Q(1, 0, n - 1, l, r); }
    void U(L i, L v) { U(1, 0, n - 1, i, v); }
};

// Generic point-update / range-max segment tree
template<typename T>
class SegTreeMax {
private:
    vector<T> tree, arr;
    int n;
    int left(int node) { return 2 * node + 1; }
    int right(int node) { return 2 * node + 2; }
    int mid(int l, int r) { return l + (r - l) / 2; }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int m = mid(start, end);
        build(left(node), start, m);
        build(right(node), m + 1, end);
        tree[node] = max(tree[left(node)], tree[right(node)]);
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            arr[idx] = val;
            tree[node] = val;
            return;
        }
        int m = mid(start, end);
        if (idx <= m) update(left(node), start, m, idx, val);
        else update(right(node), m + 1, end, idx, val);
        tree[node] = max(tree[left(node)], tree[right(node)]);
    }

    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return numeric_limits<T>::lowest(); // out of range
        if (l <= start && end <= r) return tree[node]; // fully covered
        int m = mid(start, end);
        return max(query(left(node), start, m, l, r), query(right(node), m + 1, end, l, r));
    }

public:
    SegTreeMax(const vector<T> &a) : arr(a), n(a.size()) {
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    void update(int idx, T val) { update(0, 0, n - 1, idx, val); }
    T query(int l, int r) { return query(0, 0, n - 1, l, r); }
};

// Range-add / range-max lazy segment tree
template<typename T>
class LazySegmentTree {
private:
    vector<T> tree, lazy, arr;
    int n;
    int left(int node) { return 2 * node + 1; }
    int right(int node) { return 2 * node + 2; }
    int mid(int l, int r) { return l + (r - l) / 2; }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int m = mid(start, end);
        build(left(node), start, m);
        build(right(node), m + 1, end);
        tree[node] = max(tree[left(node)], tree[right(node)]);
    }

    void push(int node, int start, int end) {
        // apply pending update and propagate to children
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[left(node)] += lazy[node];
                lazy[right(node)] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void updateRange(int node, int start, int end, int l, int r, T val) {
        push(node, start, end);
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        int m = mid(start, end);
        updateRange(left(node), start, m, l, r, val);
        updateRange(right(node), m + 1, end, l, r, val);
        tree[node] = max(tree[left(node)], tree[right(node)]);
    }

    T queryRange(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (r < start || end < l) return numeric_limits<T>::lowest();
        if (l <= start && end <= r) return tree[node];
        int m = mid(start, end);
        return max(queryRange(left(node), start, m, l, r), queryRange(right(node), m + 1, end, l, r));
    }

public:
    LazySegmentTree(const vector<T> &a) : arr(a), n(a.size()) {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    void updateRange(int l, int r, T val) { updateRange(0, 0, n - 1, l, r, val); }
    T queryRange(int l, int r) { return queryRange(0, 0, n - 1, l, r); }
};

// Node holding min/max/sum together
struct Node {
    long long min_val, max_val, sum_val;
};

// Lazy tag for an affine transform x -> scale * x + shift (scale is 1 or -1)
struct LazyTag {
    long long scale = 1;
    long long shift = 0;
};

// Segment tree supporting min/max/sum with affine range updates (e.g. range "negate + offset")
class LazyMultiSegmentTree {
private:
    vector<Node> tree;
    vector<LazyTag> lazy;
    vector<long long> arr;
    int n;
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    int mid(int l, int r) { return l + (r - l) / 2; }

    Node merge(const Node &a, const Node &b) {
        return {min(a.min_val, b.min_val), max(a.max_val, b.max_val), a.sum_val + b.sum_val};
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = {arr[start], arr[start], arr[start]};
            return;
        }
        int m = mid(start, end);
        build(left(node), start, m);
        build(right(node), m + 1, end);
        tree[node] = merge(tree[left(node)], tree[right(node)]);
    }

    void applyTag(int node, int start, int end, long long scale, long long shift) {
        // apply x -> scale*x + shift to a node
        long long len = end - start + 1;
        if (scale == -1) {
            long long new_min = -tree[node].max_val + shift;
            long long new_max = -tree[node].min_val + shift;
            tree[node].min_val = new_min;
            tree[node].max_val = new_max;
            tree[node].sum_val = -tree[node].sum_val + (len * shift);
        } else {
            tree[node].min_val += shift;
            tree[node].max_val += shift;
            tree[node].sum_val += (len * shift);
        }
        lazy[node].scale *= scale;
        lazy[node].shift = lazy[node].shift * scale + shift;
    }

    void push(int node, int start, int end) {
        if (lazy[node].scale != 1 || lazy[node].shift != 0) {
            if (start != end) {
                int m = mid(start, end);
                applyTag(left(node), start, m, lazy[node].scale, lazy[node].shift);
                applyTag(right(node), m + 1, end, lazy[node].scale, lazy[node].shift);
            }
            lazy[node] = {1, 0};
        }
    }

    void updateRangeAffine(int node, int start, int end, int l, int r, long long scale, long long shift) {
        push(node, start, end);
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            applyTag(node, start, end, scale, shift);
            return;
        }
        int m = mid(start, end);
        updateRangeAffine(left(node), start, m, l, r, scale, shift);
        updateRangeAffine(right(node), m + 1, end, l, r, scale, shift);
        tree[node] = merge(tree[left(node)], tree[right(node)]);
    }

    Node query(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (r < start || end < l) return {numeric_limits<long long>::max(), numeric_limits<long long>::lowest(), 0};
        if (l <= start && end <= r) return tree[node];
        int m = mid(start, end);
        return merge(query(left(node), start, m, l, r), query(right(node), m + 1, end, l, r));
    }

public:
    LazyMultiSegmentTree(const vector<long long> &a) : arr(a), n(a.size()) {
        tree.resize(4 * n);
        lazy.resize(4 * n, {1, 0});
        build(0, 0, n - 1);
    }

    void updateTransform(int l, int r) {
        // A[i] = M - A[i] for i in [l,r], M = range max
        Node res = query(0, 0, n - 1, l, r);
        long long M = res.max_val;
        updateRangeAffine(0, 0, n - 1, l, r, -1, M);
    }

    Node query(int l, int r) { return query(0, 0, n - 1, l, r); }
};

// Segment tree over a char array: OR of bitmasks, query returns count of distinct letters in range
template<typename T>
class SegTreeBitmaskOR {
private:
    vector<T> tree, arr;
    int n;
    int left(int node) { return 2 * node + 1; }
    int right(int node) { return 2 * node + 2; }
    int mid(int l, int r) { return l + (r - l) / 2; }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = 1 << (arr[start] - 'a');
            return;
        }
        int m = mid(start, end);
        build(left(node), start, m);
        build(right(node), m + 1, end);
        tree[node] = tree[left(node)] | tree[right(node)];
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            arr[idx] = val;
            tree[node] = 1 << (val - 'a');
            return;
        }
        int m = mid(start, end);
        if (idx <= m) update(left(node), start, m, idx, val);
        else update(right(node), m + 1, end, idx, val);
        tree[node] = tree[left(node)] | tree[right(node)];
    }

    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int m = mid(start, end);
        return query(left(node), start, m, l, r) | query(right(node), m + 1, end, l, r);
    }

public:
    SegTreeBitmaskOR(const vector<T> &a) : arr(a), n(a.size()) {
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    void update(int idx, T val) { update(0, 0, n - 1, idx, val); }
    T query(int l, int r) { return __builtin_popcount(query(0, 0, n - 1, l, r)); } // distinct letter count
};

// Segment tree over a char array: per-letter count vector, combine by summing
template<typename T>
class SegTreeCharCount {
private:
    using CountVec = array<int, 26>;
    vector<CountVec> tree;
    vector<T> arr;
    int n;
    int left(int node) { return 2 * node + 1; }
    int right(int node) { return 2 * node + 2; }
    int mid(int l, int r) { return l + (r - l) / 2; }

    CountVec combine(const CountVec &a, const CountVec &b) {
        CountVec result;
        for (int i = 0; i < 26; i++) result[i] = a[i] + b[i];
        return result;
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node].fill(0);
            tree[node][arr[start] - 'a'] = 1;
            return;
        }
        int m = mid(start, end);
        build(left(node), start, m);
        build(right(node), m + 1, end);
        tree[node] = combine(tree[left(node)], tree[right(node)]);
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            arr[idx] = val;
            tree[node].fill(0);
            tree[node][arr[idx] - 'a'] = 1;
            return;
        }
        int m = mid(start, end);
        if (idx <= m) update(left(node), start, m, idx, val);
        else update(right(node), m + 1, end, idx, val);
        tree[node] = combine(tree[left(node)], tree[right(node)]);
    }

    CountVec query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            CountVec empty;
            empty.fill(0);
            return empty;
        }
        if (l <= start && end <= r) return tree[node];
        int m = mid(start, end);
        return combine(query(left(node), start, m, l, r), query(right(node), m + 1, end, l, r));
    }

public:
    SegTreeCharCount(const vector<T> &a) : arr(a), n(a.size()) {
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    void update(int idx, T val) { update(0, 0, n - 1, idx, val); }
    CountVec query(int l, int r) { return query(0, 0, n - 1, l, r); }
};

// ================================================================
// SECTION: Searching & sorting
// ================================================================

L ceil_(L n, L d) { return n / d + (n % d > 0 ? 1 : 0); } // ceil division

L BS(vector<L> &arr, L t, L l, L r) {
    // exact binary search, returns index of t or -1
    L m = l + (r - l) / 2;
    if (l > r) return -1;
    if (arr[m] == t) return m;
    else if (arr[m] > t) return BS(arr, t, l, m - 1);
    else return BS(arr, t, m + 1, r);
}

L BSs(vector<L> &arr, L t, L l, L r) {
    // boundary search: largest index with arr[idx] <= t
    if (r - l <= 1) return l;
    L m = (r + l) / 2;
    if (arr[m] <= t) return BSs(arr, t, m, r);
    else return BSs(arr, t, l, m);
}

void M(vector<L> &arr, L l, L m, L r) {
    // merge step for merge sort
    L n1 = m - l + 1, n2 = r - m, k = l, i = 0, j = 0;
    L L_[n1], R[n2];
    for (int y = 0; y < n1; y++) L_[y] = arr[l + y];
    for (int y = 0; y < n2; y++) R[y] = arr[m + 1 + y];
    for (i = 0, j = 0; i < n1 && j < n2; k++) {
        if (L_[i] <= R[j]) arr[k] = L_[i], i++;
        else arr[k] = R[j], j++;
    }
    for (; i < n1; i++, k++) arr[k] = L_[i];
    for (; j < n2; j++, k++) arr[k] = R[j];
}

void MS(vector<L> &arr, L l, L r) {
    // merge sort entry point
    if (l < r) {
        L m = l + (r - l) / 2;
        MS(arr, l, m);
        MS(arr, m + 1, r);
        M(arr, l, m, r);
    }
}

void Mm(vector<array<L, 2> > &arr, L l, L m, L r) {
    // merge step for pairs: sort by [0] asc, tie-break [1] desc
    L n1 = m - l + 1, n2 = r - m, k = l, i = 0, j = 0;
    L L_[n1][2], R[n2][2];
    for (int y = 0; y < n1; y++) L_[y][0] = arr[l + y][0], L_[y][1] = arr[l + y][1];
    for (int y = 0; y < n2; y++) R[y][0] = arr[m + 1 + y][0], R[y][1] = arr[m + 1 + y][1];
    for (i = 0, j = 0; i < n1 && j < n2; k++) {
        if (L_[i][0] < R[j][0]) arr[k][0] = L_[i][0], arr[k][1] = L_[i][1], i++;
        else if (L_[i][0] > R[j][0]) arr[k][0] = R[j][0], arr[k][1] = R[j][1], j++;
        else {
            if (L_[i][1] > R[j][1]) arr[k][0] = L_[i][0], arr[k][1] = L_[i][1], i++;
            else arr[k][0] = R[j][0], arr[k][1] = R[j][1], j++;
        }
    }
    for (; i < n1; i++, k++) arr[k][0] = L_[i][0], arr[k][1] = L_[i][1];
    for (; j < n2; j++, k++) arr[k][0] = R[j][0], arr[k][1] = R[j][1];
}

void MSm(vector<array<L, 2> > &arr, L l, L r) {
    // merge sort entry point for pairs
    if (l < r) {
        L m = l + (r - l) / 2;
        MSm(arr, l, m);
        MSm(arr, m + 1, r);
        Mm(arr, l, m, r);
    }
}

// ================================================================
// SECTION: Graph / tree
// ================================================================

void BFS(vector<vector<L> > &a, L r, vector<bool> &V, vector<L> res) {
    // BFS from r, collects visit order in res
    queue<L> q;
    V[r] = true;
    q.push(r);
    while (q.size()) {
        L c = q.front();
        q.pop(), res.pb(c);
        for (L i: a[c])
            if (!V[i])
                V[i] = true, q.push(i);
    }
}

void DFS(L x, L p, vector<vector<L> > &t, vector<vector<L> > &o, L tech, bool md) {
    // re-orients tree edges into o, alternating direction by depth parity
    bool d = md;
    for (L i: t[x]) {
        if (i != p) {
            if (!md) {
                if (tech) o[x].pb(i);
                else o[i].pb(x);
            } else {
                if (tech) o[i].pb(x);
                else o[x].pb(i);
            }
            DFS(i, x, t, o, (tech ^ 1), true);
        }
    }
}

L mex(map<L, L> &exist) {
    // smallest non-negative integer not present as a key
    L num = 0;
    while (exist.count(num)) num++;
    return num;
}

// ================================================================
// SECTION: Number theory
// ================================================================

L gcd(L a, L b) {
    if (b == 0) return a;
    return gcd(b, a % b);
} // greatest common divisor
L lcm(L a, L b) { return (a * b) / gcd(a, b); } // least common multiple

const int MAX = 1000000; // 10^6
vector<L> P;
vector<bool> isPrime1(MAX + 1, true);

void Sieve() {
    // sieve of Eratosthenes, fills isPrime1[] and prime list P
    isPrime1[0] = isPrime1[1] = false;
    for (int i = 2; i * i <= MAX; i++)
        if (isPrime1[i])
            for (int j = i * i; j <= MAX; j += i)
                isPrime1[j] = false;
    for (int i = 2; i <= MAX; i++)
        if (isPrime1[i])
            P.push_back(i);
}

const L MAXN = 5000000;
vector<L> SPF(MAXN + 1), N_OF_F(MAXN + 1), p(MAXN + 1);

void SPF_Sieve() {
    // smallest prime factor sieve
    for (int i = 1; i <= MAXN; i++) SPF[i] = i;
    for (int i = 2; i * i <= MAXN; i++)
        if (SPF[i] == i)
            for (int j = i * i; j <= MAXN; j += i)
                if (SPF[j] == j) SPF[j] = i;
}

void numOfFactors() {
    // number of prime factors (with multiplicity) via SPF, needs SPF_Sieve() first
    N_OF_F[1] = 0;
    for (int i = 2; i <= MAXN; i++)
        N_OF_F[i] = N_OF_F[i / SPF[i]] + 1;
}

bool isPrime(int n) {
    // trial division primality test
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

vector<L> prime_factors(L n) {
    // prime factorization using sieve-built prime list P
    vector<L> factors;
    for (L pr: P) {
        if (pr * pr > n) break;
        while (n % pr == 0)
            factors.push_back(pr), n /= pr;
    }
    if (n > 1) factors.push_back(n); // remaining prime
    return factors;
}

L getPhi(L m) {
    // Euler's totient of m
    L result = m;
    for (L i = 2; i * i <= m; i++) {
        if (m % i == 0) {
            while (m % i == 0) m /= i;
            result -= result / i;
        }
    }
    if (m > 1) result -= result / m;
    return result;
}

L pow_(L b, int e) {
    // fast power, no mod
    if (e == 0) return 1;
    L h = pow_(b, e / 2);
    if (e % 2) return b * h * h;
    else return h * h;
}

L Bpow(L b, L e) {
    // fast power mod MOD
    L a = 1;
    while (e) {
        if (e % 2) a = (a * b) % MOD;
        b = (b * b) % MOD;
        e /= 2;
    }
    return a;
}

L mod_mul(L a, L b, L mod) { return (L) ((__int128) a * b % mod); } // overflow-safe modular multiply
L Mpow(L a, L e, L mod) {
    // fast power with arbitrary mod, overflow-safe
    L res = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1) res = mod_mul(res, a, mod);
        a = mod_mul(a, a, mod);
        e >>= 1;
    }
    return res;
}

L pos(L x, L p) {
    x %= p;
    if (x < 0) x += p;
    return x;
} // normalize x into [0, p)

L log_(L n, L b) {
    // integer log base b of n, via binary search on the exponent
    if (n < -1) return -1;
    L l = 0, h = 35;
    while (l <= h) {
        L m = (l + h) / 2, pw = 1;
        for (int i = 0; i < m; i++) {
            pw *= b;
            if (pw > n) break;
        }
        if (pw == n) return m;
        else if (pw < n) l = m + 1;
        else h = m - 1;
    }
    return h;
}

L sqrt_(L t, L l, L r) {
    // integer sqrt of t via binary search in [l, r)
    L m = (r + l) / 2;
    if (r - l == 1) return l;
    if (m * m > t) return sqrt_(t, l, m);
    else return sqrt_(t, m, r);
}

// ================================================================
// SECTION: Combinatorics / matrix
// ================================================================

vector<L> F(200001), F_(200001); // factorial / inverse-factorial tables for nCr mod MOD
// F[0] = F[1] = 1;
// for (int i = 2; i <= 200000; i++)
//   F[i] = (i*F[i-1])%MOD;
// F_[200000] = Bpow(F[200000], MOD-2);
// for (int i = 200000; i >= 1; i--)
//   F_[i - 1] = F_[i]*i % MOD;

typedef vector<vector<L> > Matrix;

Matrix multiply(const Matrix &A, const Matrix &B, int size) {
    // matrix multiplication mod MOD
    Matrix C(size, vector<L>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            if (A[i][k] == 0) continue;
            for (int j = 0; j < size; ++j) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

Matrix power(Matrix A, L p, int size) {
    // matrix exponentiation: computes A^p mod MOD
    Matrix res(size, vector<L>(size, 0));
    for (int i = 0; i < size; ++i) res[i][i] = 1;
    while (p > 0) {
        if (p & 1) res = multiply(res, A, size);
        A = multiply(A, A, size);
        p >>= 1;
    }
    return res;
}

// ================================================================
// SECTION: Reference snippets (paste & adapt, not compiled live)
// ================================================================

// DP ON DIGITS: count n-digit sequences where adjacent digits d1,d2 satisfy d1+d2<=9, raised to k sets
// L n, k; cin >> n >> k;
// vector<vector<L>> dp(n+1, vector<L>(10));
// for (int i = 0; i <= 9; i++)
//     dp[1][i] = 1;
// for (int i = 2; i <= n; i++)
//     for (int d = 0; d <= 9; d++)
//         for (int p = 0; p <= 9-d; p++)
//             (dp[i][d] += dp[i-1][p]) %= MOD;
// L ans = 0;
// for (int i = 0; i <= 9; i++)
//     (ans += dp[n][i]) %= MOD;
// cout << Bpow(ans, k) << endl;

// TREE DIAMETER AFTER REMOVING EDGE (u,v): paste inside main() / a function where `vector<vector<L>> t` (adjacency list) exists
// function<void(L, L, L, L&, L&, L, L)> dfs = [&](L u, L p, L dist, L& mx, L& b, L _u, L _v) {
//     if (dist > mx) { mx = dist; b = u; }
//     for (int v : t[u]) {
//         if (v == p) continue;
//         if ((u == _u && v == _v) || (u == _v && v == _u)) continue; // treat edge (u,v) as removed
//         dfs(v, u, dist + 1, mx, b, _u, _v);
//     }
// };
// function<L(L, L, L)> d = [&](L i, L u, L v) -> L { // diameter of the tree rooted at i after removing edge (u,v)
//     L mx = -1, j = i;
//     dfs(i, -1, 0, mx, j, u, v);
//     mx = -1;
//     L k = j;
//     dfs(j, -1, 0, mx, k, u, v);
//     return mx;
// };

// PREFIX SUM ON ANSWERS: build a 2n x 2n transition matrix for a circular +-d shift, with identity passthrough rows
// Matrix dp(2*n, vector<L>(2*n, 0));
// for (int i = 0; i < n; i++)
//     for (int j = -d; j <= d; j++)
//         dp[i][(i + j % n + n) % n] = 1;
// for (int i = 0; i < n; i++)
//     dp[n+i][i] = dp[n+i][n+i] = 1;