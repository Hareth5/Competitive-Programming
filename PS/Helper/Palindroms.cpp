#include<bits/stdc++.h>
using namespace std;
# define ll long long

vector<vector<bool> > pal;

template<class T>
void BuildPalindrome(T &s) {
    int n = s.size();
    pal = vector<vector<bool> >(n, vector<bool>(n, 0));
    for (int i = 0; i < n; ++i) {
        pal[i][i] = 1;
        for (int j = i - 1; j >= 0; --j) {
            pal[j][i] = s[i] == s[j] && (j + 1 == i || pal[j + 1][i - 1]);
        }
    }
}

int countPalindromes(string s) {
    int n = s.size();
    vector<int> d1(n), d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;

        d1[i] = k;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }

    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;

        d2[i] = k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }

    int ans = 0;
    for (int x: d1) ans += x;
    for (int x: d2) ans += x;
    return ans;
}

vector<pair<int, int> > getPalindromes(string s) {
    int n = s.size();
    vector<int> d1(n), d2(n);
    vector<pair<int, int> > res;

    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);

        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;

        d1[i] = k;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }

    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);

        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;

        d2[i] = k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int k = 1; k <= d1[i]; k++) {
            int l = i - k + 1;
            int r = i + k - 1;
            res.emplace_back(l, r);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int k = 1; k <= d2[i]; k++) {
            int l = i - k;
            int r = i + k - 1;
            res.emplace_back(l, r);
        }
    }

    return res;
}
