#include "algorithms.h"
#include "annealing/annealing.h"

#include <algorithm>
#include <iostream>

namespace Functions {
    const double probably_mutation = 0.5;
    const int size_population = 50;

    std::mt19937 Random::gen(time(0));
    Random::Random() { }
    int Random::random_int(int max_rand) {
        static int cnt = time(0);
        srand(cnt++);
        return rand() % max_rand;
    }
    double Random::random() {
        int max_rand = 1000000;
        return random_int(max_rand) / double(max_rand);
    }
    double Random::random(double l, double r) {
        int max_rand = 1000000;
        return l + (r - l) * (random_int(max_rand) / (double)max_rand);
    }
    Point vertex_to_point(const Vertex& e) {
        return Point(e.get_x(), e.get_y());
    }
    Segment edge_to_segment(const Edge& e) {
        return Segment(vertex_to_point(*e.get_from()), vertex_to_point(*e.get_to()));
    }
    VisualPresent::VisualPresent() : gr{} { }
    VisualPresent::VisualPresent(const Graph& gr) : gr(gr) {}
    VisualPresent::VisualPresent(const VisualPresent& vp) : gr(vp.gr) { }
    void VisualPresent::show() const {
        for (size_t i = 0; i < gr.count_vertex(); ++i) {
            std::cout << gr[i].get_x() << ' ' << gr[i].get_y() << std::endl;
        }
        for (auto el : gr)
            std::cout << el.get_from()->get_x() << ' ' << el.get_from()->get_y() << std::endl;
    }
    void VisualPresent::draw(const Window& window) {
        for (size_t i = 0; i < gr.count_vertex(); ++i) {
            window.draw_point(vertex_to_point(gr[i]));
        }
        for (auto el : gr) {
            auto p1 = vertex_to_point(*el.get_from());
            auto p2 = vertex_to_point(*el.get_to());
            window.draw_segment(p1, p2);
        }
    }
    class TemperatureGen {
    public:
        TemperatureGen() {}
        static double next_temperature(double temp) {
            return temp * 0.9999;
        }
    };
    class StateGen {
        Graph gr;
        double w, h;
    public:
        typedef vector<Point> value_type;
        StateGen() : w(400), h(400), gr{} { }
        StateGen(const Graph& gr, double w, double h) : gr(gr), w(w), h(h) { } 
        value_type first_state() const {
            value_type res;
            size_t cnt = gr.count_vertex() * 3;
            double angle = Random::random(0.0, M_PI), da = 2 * M_PI / cnt;
            double r = w / 2.3;
            int cnt_loop = 0;
            while ((cnt_loop++ << 1) < cnt);
            for (int j = 0; j < cnt_loop; ++j) {
                angle = Random::random(0.0, M_PI);
                r /= 1.2;
                for (int i = 0; i < cnt; ++i) {
                    res.push_back(Point(w / 2 + r * cos(angle), h / 2 + r * sin(angle)));
                    angle += da;
                }
            }
            return res;
        }
        double estimate(const value_type& st) const {
            auto ngr(gr);
            for (size_t i = 0; i < gr.count_vertex(); ++i) {
                ngr[i].get_x() = st[i].get_x();
                ngr[i].get_y() = st[i].get_y();
            }
            double res = 0;
            for (auto ed1 = ngr.begin(); ed1 != ngr.end(); ++ed1) {
                for (auto ed2 = ed1 + 1; ed2 != ngr.end(); ++ed2) {
                    auto s1 = Segment(vertex_to_point(*ed1->get_from()), vertex_to_point(*ed1->get_to()));
                    auto s2 = Segment(vertex_to_point(*ed2->get_from()), vertex_to_point(*ed2->get_to()));
                    if (ed1->get_from() == ed2->get_to()) continue;
                    if (ed1->get_from() == ed2->get_from()) continue;
                    if (ed1->get_to() == ed2->get_from()) continue;
                    if (ed1->get_to() == ed2->get_to()) continue;
                    if (intersect_segments(s1, s2)) {
                        res += 1.0;
                    }
                }
            }
            return res;
        }
        void get_next(const value_type& cur, value_type& next) const {
            int l = Random::random_int(cur.size());
            int r = Random::random_int(cur.size());
            while (l == r) { r = Random::random_int(cur.size()); }
            next = cur;
            if (l > r) { std::swap(l, r); }
            std::reverse(next.begin() + l, next.begin() + r);
        }
    };
    void VisualPresent::optimal(double mx, double my) {
        AnnealingProcess::Annealing an(1000, 0.5);
        StateGen gen_state(gr, mx, my);
        vector<Point> v = an.solve<Random>(gen_state, TemperatureGen());
        std::cout << gen_state.estimate(v) << "\n";
        for (size_t i = 0; i < gr.count_vertex(); ++i) {
            gr[i].get_x() = v[i].get_x();
            gr[i].get_y() = v[i].get_y();
        }
    }
};