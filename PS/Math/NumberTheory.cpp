#include<bits/stdc++.h>
using namespace std;
# define ll long long

const int mod = 1e9 + 7;
int N = 1e7 + 5;
vector<int> primes;
vector<int> spf(N);
vector<int> lpf(N);
vector<int> pr;

ll ceil(ll a, ll b) {
    return a / b + (a % b != 0);
}

bool isPrime(ll n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;

    for (ll i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

vector<ll> getDivisors(ll x) {
    vector<ll> small, large;

    for (ll i = 1; i <= x / i; ++i) {
        if (x % i == 0) {
            small.push_back(i);

            if (i != x / i)
                large.push_back(x / i);
        }
    }

    reverse(large.begin(), large.end());
    small.insert(small.end(), large.begin(), large.end());

    return small;
}

vector<ll> commonDivisors(ll a, ll b) {
    return getDivisors(gcd(a, b));
}

vector<ll> primeFactors(ll x) {
    vector<ll> f;

    while (x > 1) {
        ll p = spf[x];
        f.push_back(p);

        while (x % p == 0)
            x /= p;
    }

    return f;
}

vector<ll> primeFactors(ll x) {
    vector<ll> fac;

    if (x % 2 == 0) {
        fac.push_back(2);
        while (x % 2 == 0) x /= 2;
    }

    if (x % 3 == 0) {
        fac.push_back(3);
        while (x % 3 == 0) x /= 3;
    }

    for (ll i = 5; i <= x / i; i += 6) {
        if (x % i == 0) {
            fac.push_back(i);
            while (x % i == 0) x /= i;
        }

        if (x % (i + 2) == 0) {
            fac.push_back(i + 2);
            while (x % (i + 2) == 0) x /= i + 2;
        }
    }

    if (x > 1) fac.push_back(x);
    return fac;
}

vector<pair<ll, int> > primeFactorization(ll n) {
    vector<pair<ll, int> > fac;
    if (n <= 1) return fac;

    auto addFactor = [&](ll p) {
        if (n % p != 0) return;

        int cnt = 0;
        while (n % p == 0) {
            n /= p;
            ++cnt;
        }

        fac.push_back({p, cnt});
    };

    addFactor(2);
    addFactor(3);

    for (ll i = 5; i <= n / i; i += 6) {
        addFactor(i);
        addFactor(i + 2);
    }

    if (n > 1) fac.push_back({n, 1});
    return fac;
}

void spfSieve() {
    for (int i = 2; i < N; ++i) spf[i] = i;
    for (int i = 2; i * i < N; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j < N; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

void lpfSieve() {
    for (int i = 2; i < N; ++i) lpf[i] = 0;
    for (int i = 2; i < N; ++i) {
        if (lpf[i] == 0) {
            for (int j = i; j < N; j += i) {
                lpf[j] = i;
            }
        }
    }
}

void linearSieve() {
    primes.clear();
    for (int i = 2; i < N; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }

        for (int p: primes) {
            if (p > spf[i] || 1LL * i * p > N) break;
            spf[i * p] = p;
        }
    }
}

void buildLPF() {
    for (int i = 2; i < N; ++i) {
        int p = spf[i];
        int x = i / p;
        spf[i] = (x == 1 ? p : spf[x]); // LPF
    }
}

vector<ll> segmentedSieve(ll L, ll R) {
    vector<ll> primesInRange;
    if (L > R || R < 2) return primesInRange;

    L = max(L, 2LL);
    if (L <= 2 && 2 <= R) primesInRange.push_back(2);

    ll root = sqrtl((long double) R);
    while (root + 1 <= R / (root + 1)) ++root;
    while (root > R / root) --root;

    vector<int> primes;
    vector<bool> compositeBase(root / 2 + 1, false);
    for (ll i = 3; i <= root; i += 2) {
        if (!compositeBase[i / 2]) {
            primes.push_back((int) i);
            if (i <= root / i) {
                for (ll j = i * i; j <= root; j += 2 * i)
                    compositeBase[j / 2] = true;
            }
        }
    }

    ll startOdd = max(L, 3LL);
    if ((startOdd & 1) == 0) ++startOdd;
    if (startOdd > R) return primesInRange;

    ll cnt = (R - startOdd) / 2 + 1;
    vector<bool> composite(cnt, false);
    for (ll p: primes) {
        __int128 first = max<__int128>((__int128) p * p, (__int128) ((startOdd + p - 1) / p) * p);

        if ((first & 1) == 0) first += p;
        if (first > R) continue;

        for (ll j = (ll) first; j <= R; j += 2 * p)
            composite[(j - startOdd) / 2] = true;
    }

    for (ll i = 0; i < cnt; ++i) {
        if (!composite[i])
            primesInRange.push_back(startOdd + 2 * i);
    }

    return primesInRange;
}

// count the number of divisors for each number from 1 to N, nlogn
int divisors[N];

void harmonic() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divisors[j]++;
        }
    }
}

void buildDivisorCount() {
    divisors[1] = 1;
    vector<unsigned char> powerCnt(N + 1);

    for (int i = 2; i < N; ++i) {
        int p = spf[i];
        int x = i / p;
        if (x > 1 && spf[x] == p) {
            powerCnt[i] = powerCnt[x] + 1;
            divisors[i] = divisors[x] / (powerCnt[x] + 1) * (powerCnt[i] + 1);
        } else {
            powerCnt[i] = 1;
            divisors[i] = divisors[x] * 2;
        }
    }
}
