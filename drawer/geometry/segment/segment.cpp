#include "segment.h"

namespace Geometry {
    Segment::Segment() : begin{}, end{}, GeometryObject(TO_SEGMENT) { }
    Segment::Segment(const Point& begin, const Point& end) : begin(begin), end(end), GeometryObject(TO_SEGMENT) { }
    Point& Segment::get_begin() { return begin; }
    Point& Segment::get_end() { return end; }
    Point Segment::get_begin() const { return begin; }
    Point Segment::get_end() const { return end; }
};