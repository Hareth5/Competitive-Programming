#include <bits/stdc++.h>
using namespace std;
#define ll long long

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T>
using ordered_multiset = tree<pair<T, int>, null_type, less<pair<T, int> >, rb_tree_tag,
    tree_order_statistics_node_update>;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ x >> 30) * 0xbf58476d1ce4e5b9;
        x = (x ^ x >> 27) * 0x94d049bb133111eb;
        return x ^ x >> 31;
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

gp_hash_table<int, int, custom_hash> mp;
