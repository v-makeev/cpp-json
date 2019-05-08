#include "algorithms.h"
#include "annealing/annealing.h"

#include <algorithm>
#include <iostream>

namespace Functions {

    const double eps = 0.0000001;

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
        for (auto el : gr) {
            auto p1 = vertex_to_point(*el.get_from());
            auto p2 = vertex_to_point(*el.get_to());
            window.draw_segment(p1, p2);
        }
        for (size_t i = 0; i < gr.count_vertex(); ++i) {
            window.draw_point(vertex_to_point(gr[i]));
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
        double energy;
        vector<Point> points;
    public:
        typedef vector<Point> value_type;
        StateGen() : w(400), h(400), gr{}, energy(-1.0), points{} { }
        StateGen(const Graph& g, double w, double h) : gr(g), w(w), h(h), energy(-1.0) {
            for (size_t i = 0; i < gr.count_vertex(); ++i)
                points.push_back(vertex_to_point(gr[i]));
            for (auto ed1 = gr.begin(); ed1 != gr.end(); ++ed1) {
                    for (auto ed2 = ed1 + 1; ed2 != gr.end(); ++ed2) {
                        auto s1 = Segment(vertex_to_point(*ed1->get_from()), vertex_to_point(*ed1->get_to()));
                        auto s2 = Segment(vertex_to_point(*ed2->get_from()), vertex_to_point(*ed2->get_to()));
                        if (ed1->get_from() == ed2->get_to()) continue;
                        if (ed1->get_from() == ed2->get_from()) continue;
                        if (ed1->get_to() == ed2->get_from()) continue;
                        if (ed1->get_to() == ed2->get_to()) continue;
                        if (intersect_segments(s1, s2)) {
                            energy += 1.0;
                        }
                    }
                }
        }
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
        double estimate(const value_type& st, bool change = false) {
            int v = 0;
            for (auto el : st) {
                if ((el - points[v]).mod() > eps) {
                    break;
                }
                ++v;
            }
            if (v == points.size()) { return energy; }
            vector<std::pair<int, int>> oth, own;
            for (auto el : gr) {
                auto n1 = el.get_from() - &gr[0];
                auto n2 = el.get_to() - &gr[0];
                if (n1 == v || n2 == v)
                    own.push_back({ v, n1 + n2 - v });
                else
                    oth.push_back({ n1, n2 });
            }
            double res = 0.0;
            for (auto Own : own)
                for (auto Oth : oth) {
                    if (intersect_segments(Segment(points[Own.first], points[Own.second]), Segment(points[Oth.first], points[Oth.second])))
                        res -= 1.0;
                    if (intersect_segments(Segment(st[v], points[Own.second]), Segment(points[Oth.first], points[Oth.second])))
                        res += 1.0;
                    }
            if (change) {
                points[v].get_x() = st[v].get_x();
                points[v].get_y() = st[v].get_y();
                return (energy += res);
            } else
                return (energy + res);
        }
        void set_next_state(const value_type& st) {
            energy = estimate(st, true);
        }
        void set_all(const value_type& st) {
            points = st;
        }
        void get_next(const value_type& cur, value_type& next) {
            int l = Random::random_int(cur.size());
            next = cur;
            next[l] = Point(Random::random(0, w), Random::random(0, h));
        }
    };
    class Rectangle {
        double down_x, down_y;
        double up_x, up_y;
    public:
        Rectangle(const Point& p1, const Point& p2) {
            down_x = std::fmin(p1.get_x(), p2.get_x());
            down_y = std::fmin(p1.get_y(), p2.get_y());
            up_x = std::fmax(p1.get_x(), p2.get_x());
            up_y = std::fmax(p1.get_y(), p2.get_y());
        }
        Rectangle(double x1, double y1, double x2, double y2) {
            down_x = std::fmin(x1, x2);
            down_y = std::fmin(y1, y2);
            up_x = std::fmax(x1, x2);
            up_y = std::fmax(y1, y2);
        }
        Rectangle() : down_x{}, down_y{}, up_x{}, up_y{} { }
        double square() const { return (up_x - down_x) * (up_y - down_y); }
        friend Rectangle operator ^(const Rectangle& r1, const Rectangle& r2);
        Point get_down() const { return Point(down_x, down_y); }
        Point get_up() const { return Point(up_x, up_y); }
        Point get_middle() const { return Point((down_x + up_x) / 2.0, (down_y + up_y) / 2.0); }
    };
    Rectangle operator^(const Rectangle& r1, const Rectangle& r2) {
        double x1, x2, y1, y2;
        x1 = std::fmax(r1.down_x, r2.down_x);
        x2 = std::fmin(r1.up_x, r2.up_x);
        y1 = std::fmax(r1.down_y, r2.down_y);
        y2 = std::fmin(r1.up_y, r2.up_y);
        if (x1 > x2 || y1 > y2)
            return Rectangle(0, 0, 0, 0);
        return Rectangle(x1, y1, x2, y2);
    }
    class Scalable {
    public:
        static Rectangle get_rect(const Rectangle& r, const Point& O, double k) {
            k = 1.0 / (1.0 - k);
            return Rectangle(homotate(O, r.get_down(), k), homotate(O, r.get_up(), k));
        }
        static bool check_coef(double k, const vector<Point>& v, double w, double h, Point& center) {
            Rectangle r = Rectangle(0, 0, w, h);
            for (auto el : v) {
                r = (r ^ get_rect(Rectangle(0, 0, w, h), el, k));
            }
            if (r.square() > eps) {
                center = r.get_middle();
                return true;
            }
            return false;
        }
        static void scalable(vector<Point>& v, double w, double h) {
            double l = 1.000001, r = std::max(w, h);
            Point center = Point(0, 0);
            while (r - l > eps) {
                double mid = (l + r) / 2.0;
                if (check_coef(mid, v, w, h, center)) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            for (size_t i = 0; i < v.size(); ++i) {
                v[i] = homotate(center, v[i], l);
            }
        }
    };
    void VisualPresent::optimal(double mx, double my) {
        AnnealingProcess::Annealing an(3000, 0.05);
        StateGen gen_state(gr, mx, my);
        vector<Point> v = an.solve<Random>(gen_state, TemperatureGen());
        v.resize(gr.count_vertex());
        Scalable::scalable(v, mx, my);
        for (size_t i = 0; i < gr.count_vertex(); ++i) {
            gr[i].get_x() = v[i].get_x();
            gr[i].get_y() = v[i].get_y();
        }
    }
};
