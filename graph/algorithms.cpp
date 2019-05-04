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
            static int cnt = 2500;
            --cnt;
            if (temp < 1.0)
                temp = 100.0;
            return cnt ? temp * 0.9999 : 0.0;
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
            size_t cnt = gr.count_vertex();
            double angle = 0, da = 2 * M_PI / cnt;
            double r = w / 3.0;
            for (int i = 0; i < cnt; ++i) {
                res.push_back(Point(w / 2 + r * cos(angle), h / 2 + r * sin(angle)));
                angle += da;
            }
            r /= 2;
            angle = M_PI / 2.0;
            for (int i = 0; i < cnt; ++i) {
                res.push_back(Point(w / 2 + r * cos(angle), h / 2 + r * sin(angle)));
                angle += da;
            }
            r /= 1.5;
            angle = M_PI * 0.75;
            for (int i = 0; i < cnt; ++i) {
                res.push_back(Point(w / 2 + r * cos(angle), h / 2 + r * sin(angle)));
                angle += da;
            }
            return res;
        }
        double estimate(const value_type& st) const {
            for (size_t i = 0; i < gr.count_vertex(); ++i) {
                gr[i].get_x() = st[i].get_x();
                gr[i].get_y() = st[i].get_y();
            }
            double res = 0;
            for (auto ed1 = gr.begin(); ed1 != gr.end(); ++ed1) {
                for (auto ed2 = ed1 + 1; ed2 != gr.end(); ++ed2) {
                    auto s1 = Segment(vertex_to_point(*ed1->get_from()), vertex_to_point(*ed1->get_to()));
                    auto s2 = Segment(vertex_to_point(*ed2->get_from()), vertex_to_point(*ed2->get_to()));
                    if (intersect_segments(s1, s2))
                        res += 1.0;
                }
            }
            return -res * 15;
        }
        void get_next(const value_type& cur, value_type& next) const {
            int l = Random::random_int(cur.size());
            int r = Random::random_int(cur.size());
            while (l == r) { r = Random::random_int(cur.size()); }
            next = cur;
            std::swap(next[l], next[r]);
        }
    };
    void VisualPresent::optimal(double mx, double my) {
        AnnealingProcess::Annealing an(100, 0.1);
        StateGen gen_state(gr, mx, my);
        vector<Point> v = an.solve<Random, TemperatureGen>(gen_state);
        for (size_t i = 0; i < gr.count_vertex(); ++i) {
            gr[i].get_x() = v[i].get_x(), gr[i].get_y() = v[i].get_y();
        }
    }
};