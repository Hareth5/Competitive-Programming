#include<bits/stdc++.h>
using namespace std;
# define ll long long

// Some properties of bitwise operations:
// A | B = A ^ B + A & B
// A ^ (A & B) = (A | B) ^ B
// (A & B) ^ (A | B) = A ^ B
// A ^ B = 2 (A | B)^2 - (A + B)

// Addition:
// A + B = A | B + A & B
// A + B = A ^ B + 2 * (A & B)

// Subtraction:
// A - B = (A ^ (A & B)) - ((A | B) ^ A)
// A - B = ((A | B) ^ B) - ((A | B) ^ A)
// A - B = (A ^ (A & B)) - (B ^ (A & B))
// A - B = ((A | B) ^ B) - (B ^ (A & B))

int bits = floor(log2(n));
int lowestSetBit = n & -n;
int ones = __builtin_popcount(n);
int onesll = __builtin_popcountll(n);
int idxOfFirstMostRightBit = __builtin_ffs(n);
int msb = 31 - __builtin_clz(n);
int leadingZeros = __builtin_clz(n);
int trailingZeros = __builtin_ctz(n);

bool knowBit(ll n, int i) {
    return n >> i & 1;
}

void setBit(ll &n, int i) {
    n = n | 1 << i;
}

void resetBit(ll &n, int i) {
    n = n & ~(1 << i);
}

void flip(ll &n, int i) {
    n = n ^ 1 << i;
}

bool isPowerOfTwo(ll n) {
    if (n == 0)
        return false;

    return !(n & n - 1);
}

bool isDivisibleByPowerOf2(int n, int k) {
    int powerOf2 = 1 << k;
    return (n & powerOf2 - 1) == 0;
}

int countDigits(int n) {
    if (n == 0) return 1;
    return floor(log10(abs(n))) + 1;
}

int idxOfFirstMostLeftBit(int x) {
    int idx = 0;
    while (x >>= 1)
        idx++;

    return idx;
}

int computeXOR(int n) {
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    return 0;
}

void completeSearch() {
    vector<vi> ans;
    for (int mask = 0; mask < 1 << n; mask++) {
        vi f;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                f.push_back(v[i]);
            }
        }

        ans.push_back(f);
    }

    sort(ans.begin(), ans.end());
}

string decToBinary(int n) {
    if (n == 0) return "0";

    string bin = "";
    while (n > 0) {
        bin.push_back('0' + n % 2);
        n /= 2;
    }

    reverse(bin.begin(), bin.end());
    return bin;
}

int binaryToDecimal(const string &bin) {
    int dec = 0;
    for (char c: bin) {
        dec = dec * 2 + (c - '0');
    }

    return dec;
}