#include <bits/stdc++.h>
using namespace std;

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

    auto valid = [&](int x) -> bool {
    };

    int l = 0, r = n, res = 0;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (valid(mid)) res = mid, l = mid + 1;
        else r = mid - 1;
    }

    vector<vi> dp(n, vi(n, -1));
    auto fun = [&](auto &self, int i, int ctr) -> int {
        if (i == n) return 0;

        // int &ans = dp[i][ctr];
        // if (~ans) return ans;

        int a = self(self, i + 1, ctr);
        int b = self(self, i + 1, ctr);

        return max(a, b);
    };

    cout << (fun(fun, 0, 0)) << endl;
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
