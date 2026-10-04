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