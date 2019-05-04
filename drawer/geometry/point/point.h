#pragma once

namespace Geometry {
    enum TypeObject { TO_POINT, TO_SEGMENT };
    struct GeometryObject {
        TypeObject type;
        GeometryObject(TypeObject type);
    };
    class Point : public GeometryObject {
        double x;
        double y;
    public:
        Point();
        Point(double x, double y);
        Point(const Point& p);
        double mod() const;
        double mod2() const;
        Point operator+(const Point& p) const;
        Point operator-(const Point& p) const;
        double operator*(const Point& p) const;
        double operator^(const Point& p) const;
        Point operator*(double k) const;
        Point& operator+=(const Point& p);
        Point operator-() const;
        double get_x() const;
        double get_y() const;
        double& get_x();
        double& get_y();
    };
};