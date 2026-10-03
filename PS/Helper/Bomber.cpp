struct bomber {
    map<int, int> seg;

    int get(int x) {
        auto it = seg.upper_bound(x);
        if (it == seg.begin()) return x;

        --it;
        if (it->second < x) return x;
        return it->first - 1;
    }

    void insert(int x) {
        auto it = seg.upper_bound(x);

        if (it != seg.begin()) {
            auto prv = prev(it);
            if (prv->second >= x)
                return;
        }

        bool left = false, right = false;
        auto L = seg.end();
        if (it != seg.begin()) {
            L = prev(it);
            if (L->second + 1 == x) left = true;
        }

        if (it != seg.end() && it->first == x + 1) right = true;
        if (left && right) {
            L->second = it->second;
            seg.erase(it);
        } else if (left) {
            L->second = x;
        } else if (right) {
            int r = it->second;
            seg.erase(it);
            seg[x] = r;
        } else {
            seg[x] = x;
        }
    }

    void erase(int x) {
        auto it = seg.upper_bound(x);
        if (it == seg.begin()) return;

        --it;
        int l = it->first;
        int r = it->second;
        if (x < l || x > r) return;

        seg.erase(it);
        if (l <= x - 1) seg[l] = x - 1;
        if (x + 1 <= r) seg[x + 1] = r;
    }
};
