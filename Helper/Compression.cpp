struct coordinateCopmression {
private:
    vector<ll> init;

    void compress(vector<ll> &v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

public:
    coordinateCopmression(vector<ll> &v) {
        init = v;
        compress(init);
    }

    int index(ll val) {
        return lower_bound(init.begin(), init.end(), val) - init.begin();
    }

    int upperIndex(ll val) {
        return upper_bound(init.begin(), init.end(), val) - init.begin() - 1;
    }

    ll initValue(int idx) {
        return init[idx];
    }

    int size() {
        return init.size();
    }
};