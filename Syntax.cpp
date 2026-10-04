#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define sz(v) (int) (v.size())
#define all(v) v.begin(), v.end()
#define endl '\n'
int N = 2e5 + 5;
const ll inf = 4e18;
const int mod = 1e9 + 7;

void solve() {

}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
        solve();

    return 0;
}

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
}

struct cmp {
    bool operator()(const array<int, 3> &a, const array<int, 3> &b) const {
        if (a[0] != b[0]) return a[0] < b[0];
        if (a[1] != b[1]) return a[1] < b[1];
        return a[2] < b[2];
    }
};

void syntax() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cout << (fixed << setprecision(6) << ans) << endl;

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

__int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * f;
}

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
