#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct monotonicStack {
    int n;
    vector<int> prevGreater;
    vector<int> prevGreaterEqual;
    vector<int> prevSmaller;
    vector<int> prevSmallerEqual;
    vector<int> nextGreater;
    vector<int> nextGreaterEqual;
    vector<int> nextSmaller;
    vector<int> nextSmallerEqual;

    monotonicStack(const vector<int> &a) {
        n = a.size();
        prevGreater.resize(n);
        prevGreaterEqual.resize(n);
        prevSmaller.resize(n);
        prevSmallerEqual.resize(n);
        nextGreater.resize(n);
        nextGreaterEqual.resize(n);
        nextSmaller.resize(n);
        nextSmallerEqual.resize(n);

        stack<int> st;

        // Previous Greater >
        while (!st.empty()) st.pop();
        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.top()] <= a[i]) st.pop();
            prevGreater[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        // Previous Greater or Equal >=
        while (!st.empty()) st.pop();
        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.top()] < a[i]) st.pop();
            prevGreaterEqual[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        // Previous Smaller <
        while (!st.empty()) st.pop();
        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.top()] >= a[i] st.pop();
            prevSmaller[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        // Previous Smaller or Equal <=
        while (!st.empty()) st.pop();
        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.top()] > a[i] st.pop();
            prevSmallerEqual[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        // Next Greater >
        while (!st.empty()) st.pop();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && a[st.top()] <= a[i]) st.pop();
            nextGreater[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        // Next Greater or Equal >=
        while (!st.empty()) st.pop();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && a[st.top()] < a[i]) st.pop();
            nextGreaterEqual[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        // Next Smaller <
        while (!st.empty()) st.pop();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && a[st.top()] >= a[i]) st.pop();
            nextSmaller[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        // Next Smaller or Equal <=
        while (!st.empty()) st.pop();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && a[st.top()] > a[i]) st.pop();
            nextSmallerEqual[i] = st.empty() ? n : st.top();
            st.push(i);
        }
    }
};

struct monotonicQueue {
    int n, k;
    vector<int> mx, mn;
    deque<int> dqMax, dqMin;

    monotonicQueue(const vector<int> &a, int windowSize)
        : n(a.size()), k(windowSize), mx(n - k + 1), mn(n - k + 1) {
        int idx = 0;
        for (int i = 0; i < n; i++) {
            while (!dqMax.empty() && dqMax.front() <= i - k) dqMax.pop_front();
            while (!dqMin.empty() && dqMin.front() <= i - k) dqMin.pop_front();
            while (!dqMax.empty() && a[dqMax.back()] <= a[i]) dqMax.pop_back();
            while (!dqMin.empty() && a[dqMin.back()] >= a[i]) dqMin.pop_back();

            dqMax.push_back(i);
            dqMin.push_back(i);

            if (i >= k - 1) {
                mx[idx] = a[dqMax.front()];
                mn[idx] = a[dqMin.front()];
                idx++;
            }
        }
    }
};
