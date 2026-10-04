#include<bits/stdc++.h>
using namespace std;
# define ll long long
const int mod = 1e9 + 7;
const int N = 2e5 + 5;

ll addmod(ll a, ll b) {
    return (a % mod + b % mod + mod) % mod;
}

ll submod(ll a, ll b) {
    return (a % mod - b % mod + mod) % mod;
}

ll mulmod(ll a, ll b) {
    return (ll) ((__int128) (a % mod) * (b % mod) % mod);
}

ll powmod(ll a, ll e) {
    a %= mod;
    ll res = 1 % mod;
    while (e > 0) {
        if (e & 1) res = (ll) ((__int128) res * a % mod);
        a = (ll) ((__int128) a * a % mod);
        e >>= 1;
    }

    return res;
}

ll invmod(ll b) {
    return powmod(b, mod - 2);
}

ll divmod(ll a, ll b) {
    return mulmod(a, invmod(b));
}

void pascal(vector<vector<ll> > &triangle) {
    int rows = triangle.size();
    for (int i = 0; i < rows; i++) {
        triangle[i].resize(i + 1);
        triangle[i][0] = 1;
        triangle[i][i] = 1;

        for (int j = 1; j < i; j++) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }
}

ll fac[N], inv[N], finv[N];

void pre() {
    fac[0] = inv[0] = inv[1] = finv[0] = finv[1] = 1;
    fac[1] = fac[0] % mod;
    for (ll i = 2; i < N; ++i) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - mod / i * inv[mod % i] % mod;
        finv[i] = finv[i - 1] * inv[i] % mod;
    }
}

ll npr(ll x,ll y) {
    if (x < 0 || y > x || y < 0) return 0;
    return fac[x] * finv[x - y] % mod;
}

ll ncr(int n, int r) {
    if (n < 0 || r > n || r < 0) return 0;
    return fac[n] * finv[r] % mod * finv[n - r] % mod;
}

// C(n,k) + C(n,k+1) + ... + C(n,n)
ll atLeast(int n, int k) {
    ll sum = 0;
    for (int i = k; i <= n; i++) sum = addmod(sum, ncr(n, i));
    return sum;
}

// C(n,0) + C(n,1) + ... + C(n,k)
ll atMost(int n, int k) {
    ll sum = 0;
    for (int i = 0; i <= k; i++) sum = addmod(sum, ncr(n, i));
    return sum;
}

// C(n,lo) + ... + C(n,hi)
ll inRange(int n, int lo, int hi) {
    ll sum = 0;
    for (int i = lo; i <= hi; i++) sum = addmod(sum, ncr(n, i));
    return sum;
}
