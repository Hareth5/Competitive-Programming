#include<bits/stdc++.h>
using namespace std;
# define ll long long

int LIS(vector<int> &a) {
    vector<int> dp;
    for (int i = 0; i < a.size(); ++i) {
        int k = a[i];
        auto it = lower_bound(dp.begin(), dp.end(), k);
        if (it == dp.end()) dp.push_back(k);
        else *it = k;
    }

    return dp.size();
}

bool containsSubsequence(const string &text, const string &sub) {
    int j = 0;
    for (int i = 0; i < text.size() && j < sub.size(); i++) {
        if (text[i] == sub[j]) j++;
    }

    return j == sub.size();
}

// minimum swaps to make s = w
ll minimum_swaps(string s, string w) {
    int n = s.size();
    vector<int> p[26];
    for (int i = n - 1; ~i; --i) {
        p[s[i] - 'a'].push_back(i);
    }

    ordered_set<int> os;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int c = w[i] - 'a';
        if (p[c].empty()) {
            return -1;
        }

        ans += p[c].back() - os.order_of_key(p[c].back());
        os.insert(p[c].back());
        p[c].pop_back();
    }

    return ans;
}