#include "point.h"

#include <cmath>

namespace Geometry {
    GeometryObject::GeometryObject(TypeObject type) : type(type) { }
    Point::Point() : x{}, y{}, GeometryObject(TO_POINT) { }
    Point::Point(double x, double y) : x(x), y(y), GeometryObject(TO_POINT) { }
    Point::Point(const Point& p) : x(p.x), y(p.y), GeometryObject(TO_POINT) { }
    double Point::mod() const {
        return sqrt(x * x + y * y);
    }
    double Point::mod2() const {
        return x * x + y * y;
    }
    Point Point::operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }
    Point Point::operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }
    double Point::operator*(const Point& p) const {
        return x * p.x + y * p.y;
    }
    Point Point::operator*(double k) const {
        return Point(x * k, y * k);
    }
    Point& Point::operator+=(const Point& p) {
        x += p.x, y += p.y;
        return *this;
    }
    double Point::operator^(const Point& p) const {
        return x * p.y - y * p.x;
    }
    Point Point::operator-() const {
        return Point(-x, -y);
    }
    double Point::get_x() const { return x; }
    double Point::get_y() const { return y; }
};