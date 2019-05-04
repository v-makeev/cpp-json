#include "dsu.h"

namespace Dsu {
    Dsu::Dsu() : cnt_sets(0) {
        rng.clear();
        parent.clear();
    }
    Dsu::Dsu(const Dsu& d) : parent(d.parent), cnt_sets(d.cnt_sets), rng(d.rng) { }
    int Dsu::get_count_sets() const { return cnt_sets; }
    void Dsu::make_set(int x) {
        auto it = parent.find(x);
        if (it == parent.end()) {
            rng.insert({x, 1});
            parent.insert({x, x});
            ++cnt_sets;
        }
    }
    int Dsu::get_set(int x) {
        auto it = parent.find(x);
        if (it == parent.end()) { return -1; }
        if (it->second == x) { return x; }
        return parent[x] = get_set(it->second);
    }
    bool Dsu::union_sets(int x, int y) {
        x = get_set(x);
        y = get_set(y);
        if (x < 0 || y < 0 || x == y) { return false; }
        --cnt_sets;
        auto rx = rng.find(x);
        auto ry = rng.find(y);
        if (rx->second < ry->second) {
            parent[x] = y;
        } else if (rx->second > ry->second) {
            parent[y] = x;
        } else {
            parent[x] = y;
            rng[y]++;
        }
        return true;
    }
};