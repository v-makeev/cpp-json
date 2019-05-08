#pragma once
#include "point/point.h"
#include "segment/segment.h"

#include <cmath>

namespace Geometry {
    bool intersect_segments(const Segment& s1, const Segment& s2);
    Point homotate(const Point& O, const Point& p, double k);
    Segment homotate(const Segment& O, const Segment& p, double k);
};