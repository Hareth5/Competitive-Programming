#include<bits/stdc++.h>
using namespace std;
# define ll long long

struct PrefixSum2D {
    int n, m;
    vector<vector<ll> > p;

    PrefixSum2D(const vector<vector<int> > &a): n(a.size()), m(a[0].size()) {
        p.resize(n, vector<ll>(m));
        p[0][0] = a[0][0];
        for (int i = 1; i < m; i++) {
            p[0][i] = p[0][i - 1] + a[0][i];
        }

        for (int i = 1; i < n; i++) {
            p[i][0] = p[i - 1][0] + a[i][0];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                p[i][j] = a[i][j] + p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
            }
        }
    }

    ll sum(int i, int j, int x, int y) {
        if (i < 0 || i > x || x >= n || j < 0 || j > y || y >= m) return 0;
        return p[x][y] - (i ? p[i - 1][y] : 0) - (j ? p[x][j - 1] : 0) + (i && j ? p[i - 1][j - 1] : 0);
    }
};

struct PrefixBits {
    int n, m;
    vector<vector<ll>> pref;

    PrefixBits(const vector<int>& v): n(v.size()), m(62) {
        pref.resize(n + 1, vector<ll>(m, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                pref[i][j] = pref[i - 1][j];
                pref[i][j] += (v[i - 1] >> j) & 1;
            }
        }
    }

    ll countBits(int l, int r, int bit) {
        return pref[r + 1][bit] - pref[l][bit];
    }
};
