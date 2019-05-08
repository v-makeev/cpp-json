#include "geometry.h"

#include <algorithm>
#include <cmath>

namespace Geometry {
    double min(double a, double b) {
        return a < b ? a : b;
    }
    double max(double a, double b) {
        return a > b ? a : b;
    }
    inline double area (const Point& a, const Point& b, const Point& c) {
        return (b - a) ^ (c - a);
    }
    inline bool intersect_1 (double a, double b, double c, double d) {
        if (a > b)  std::swap (a, b);
        if (c > d)  std::swap (c, d);
        return max(a,c) <= min(b,d);
    }
    bool intersect_bp(const Point& a, const Point& b, const Point& c, const Point& d) {
        return intersect_1 (a.get_x(), b.get_x(), c.get_x(), d.get_x())
            && intersect_1 (a.get_y(), b.get_y(), c.get_y(), d.get_y())
            && area(a,b,c) * area(a,b,d) <= 0
            && area(c,d,a) * area(c,d,b) <= 0;
    }
    bool intersect_segments(const Segment& s1, const Segment& s2) {
        return intersect_bp(s1.get_begin(), s1.get_end(), s2.get_begin(), s2.get_end());
    }
    Point homotate(const Point& O, const Point& p, double k) {
        return O + (p - O) * k;
    }
    Segment homotate(const Point& O, const Segment& s, double k) {
        return Segment(O + (s.get_begin() - O) * k, O + (s.get_end() - O) * k);
    }
};