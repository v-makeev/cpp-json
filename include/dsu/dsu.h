#pragma once
#include "../map/Map.h"
namespace Dsu {
    class Dsu {
        map<int, int> parent;
        map<int, int> rng;
        int cnt_sets;
    public:
        Dsu();
        Dsu(const Dsu& d);
        void make_set(int x);
        int get_set(int x);
        bool union_sets(int x, int y);
        int get_count_sets() const;
    };
};