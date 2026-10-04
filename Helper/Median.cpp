struct Median {
    multiset<int> mn, mx;
    ll sumMn = 0, sumMx = 0;

    void balance() {
        while (mn.size() > mx.size() + 1) {
            auto it = prev(mn.end());
            int x = *it;

            mn.erase(it);
            sumMn -= x;

            mx.insert(x);
            sumMx += x;
        }

        while (mn.size() < mx.size()) {
            auto it = mx.begin();
            int x = *it;

            mx.erase(it);
            sumMx -= x;

            mn.insert(x);
            sumMn += x;
        }
    }

    void insert(int x) {
        if (mn.empty() || x <= *prev(mn.end())) {
            mn.insert(x);
            sumMn += x;
        } else {
            mx.insert(x);
            sumMx += x;
        }

        balance();
    }

    bool erase(int x) {
        auto it = mn.find(x);

        if (it != mn.end()) {
            mn.erase(it);
            sumMn -= x;
            balance();
            return true;
        }

        it = mx.find(x);

        if (it != mx.end()) {
            mx.erase(it);
            sumMx -= x;
            balance();
            return true;
        }

        return false;
    }

    int median() {
        return *prev(mn.end());
    }

    ll cost() {
        int med = median();

        return mn.size() * 1LL * med - sumMn
               + sumMx - mx.size() * 1LL * med;
    }

    int size() {
        return mn.size() + mx.size();
    }

    bool empty() {
        return mn.empty() && mx.empty();
    }
};
