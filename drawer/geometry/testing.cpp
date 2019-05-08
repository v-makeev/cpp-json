#include "geometry.h"
#include "../../include/vector/Vector.h"

#include <iostream>

namespace Solve {
    const double eps = 0.0001;
    using namespace Geometry;
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
        // is empty
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
            double l = 1.02, r = std::max(w, h);
            Point center = Point(0, 0);
            while (r - l > eps) {
                double mid = (l + r) / 2.0;
                if (check_coef(mid, v, w, h, center)) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            for (size_t i = 0; i < v.size(); ++i)
                v[i] = homotate(center, v[i], l);
        }
    };
};

using std::cin;
using std::cout;
using std::endl;

int main() {
    using namespace Solve;
    int n;
    cin >> n;
    vector<Point> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i].get_x() >> v[i].get_y();
    Scalable::scalable(v, 400, 400);
    for (int i = 0; i < n; ++i)
        cout << v[i].get_x() << ' ' << v[i].get_y() << endl;
    return 0;
}