#include<bits/stdc++.h>
using namespace std;
# define ll long long

const int mod = 1e9 + 7;

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

ll permutation(ll n, ll k) {
    if (k <= 0 || k > n) return 0;

    ll res = 1;
    for (int i = 0; i < k; i++) {
        res = res * ((n - i) % mod) % mod;
    }

    return res;
}

ll combinations(ll n, ll k) {
    if (k <= 0 || k > n) return 0;

    k = min(k, n - k);
    ll res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * ((n - i + 1) % mod) % mod;
        res = res * invmod(i) % mod;
    }

    return res;
}

ll starsBars(ll n, ll s) {
    if (n <= 0) return s == 0 ? 1 : 0;
    return combinations(s + n - 1, n - 1);
}

ll starsBarsLower(ll n, ll s, ll minVal) {
    ll s2 = s - n * minVal;
    if (s2 < 0) return 0;
    return starsBars(n, s2);
}

ll starsBarsUpper(ll n, ll s, ll maxVal) {
    ll result = 0;
    for (int i = 0; i <= n; i++) {
        ll rem = s - (ll) i * (maxVal + 1);
        if (rem < 0) break;

        ll term = mulmod(combinations(n, i), starsBars(n, rem));
        result = i % 2 == 0 ? addmod(result, term) : submod(result, term);
    }

    return result;
}

void inclusionExclusion(vector<int> &v) {
    ll ans = 0;
    for (int mask = 0; mask < 1 << n; mask++) {
        int res = 1;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                res *= v[i];
            }
        }

        int bits = __builtin_popcount(mask);
        if (bits % 2) ans -= res;
        else ans += res;
    }
}

// the number of permutations where no element remains in its original position
ll derangement(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;

    vector<ll> dp(n + 1);
    dp[0] = 1;
    dp[1] = 0;
    for (int i = 2; i <= n; i++) {
        dp[i] = mulmod(i - 1, addmod(dp[i - 1], dp[i - 2]));
    }

    return dp[n];
}