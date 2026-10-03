#include<bits/stdc++.h>
using namespace std;
# define ll long long

bool cmp(const array<int, 3> a, const array<int, 3> b) {
    return a[1] < b[1];
}

struct cmp {
    bool operator()(const Node &a, const Node &b) const {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        if (a.z != b.z) return a.z < b.z;
        return a.idx < b.idx;
    }
};

void syntax() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cc(fixed << setprecision(6) << ans);

    sort(v.begin(), v.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.first < b.first || (a.first == b.first && a.second > b.second);
    });

    sort(v.begin(), v.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
    });

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

    cc(fun(fun, 0, 0));
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
