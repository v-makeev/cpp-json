#pragma once
#include "../point/point.h"

namespace Geometry {
    class Segment : public GeometryObject {
        Point begin;
        Point end;
    public:
        Segment();
        Segment(const Point& begin, const Point& end);
        Point& get_begin();
        Point get_begin() const;
        Point& get_end();
        Point get_end() const;
    };
};