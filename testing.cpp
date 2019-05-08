#include "graph/algorithms.h"
#include "graph/annealing/annealing.h"

#include <iostream>
#include <algorithm>

//#define TEST_ANNEALING

using namespace Functions;

#ifdef TEST_ANNEALING
    vector<double> v;
    int cnt_start = 10000;
    class TemperatureGen {
    public:
        TemperatureGen() {
            cnt_start = (10000);
            v = vector<double>(cnt_start);
            for (int i = 0; i < cnt_start; ++i)
                v[i] = Random::random(0, 50.0);
            std::sort(v.begin(), v.end());
        }
        double next_temperature(double temp) {
            static int cnt = cnt_start;
            if (cnt < 1) { return temp * 0.99; }
            return v[--cnt];
        }
    };
    class StateGen {
    public:
        typedef std::pair<double, double> value_type;
        StateGen() { }
        value_type first_state() const {
            return { Random::random(0.0, 20.0), Random::random(0.0, 20.0)};
        }
        double estimate(const value_type& st) const {
            return (st.first + 1.0 / st.first) + (st.second + 1.0 / st.second);
        }
        void get_next(const value_type& cur, value_type& next) const {
            next = cur;
            double p = Random::random();
            int ri = Random::random_int(3);
            if (ri == 1) {
                next.first = Random::random(0.0, 20.0);
            } else if (ri == 2) {
                next.second = Random::random(0.0, 20.0);
            }
        }
    };
#endif

int main(int argc, char **argv) {
#ifdef TEST_ANNEALING
    AnnealingProcess::Annealing an(50, 0.015);
    StateGen sg;
    auto res = an.solve<Random>(sg, TemperatureGen());
    std::cout << res.first << ' ' << res.second << ' ' << sg.estimate(res);
#endif
#ifndef TEST_ANNEALING
    int size_w = 400, size_h = 400;
    Window window(size_w, size_h);
    int n, m;
    std::cin >> n >> m;
    Graph gr;
    for (int i = 0; i < n; ++i) {
        gr.add_vertex(Vertex(Random::random(0.0, size_w), Random::random(0.0, size_h)));
    }
    for (int j = 0; j < m; ++j) {
        int u, v;
        std::cin >> u >> v;
        gr.connect(u - 1, v - 1);
    }
    VisualPresent vp(gr);
    vp.optimal(size_w, size_h);
    vp.draw(window);
    window.init(argc, argv);
#endif
    return 0;
}