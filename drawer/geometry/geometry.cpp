#include "geometry.h"

namespace Geometry {
    bool intersect_segments(const Segment& s1, const Segment& s2) {
        auto A1 = s1.get_begin();
        auto B1 = s1.get_end();
        auto A2 = s2.get_begin();
        auto B2 = s2.get_end();
        if (std::fmin(A1.get_x(), B1.get_x()) > std::fmax(A2.get_x(), B2.get_x()))
            return false;
        if (std::fmin(A1.get_y(), B1.get_y()) > std::fmax(A2.get_y(), B2.get_y()))
            return false;
        if (std::fmax(A1.get_y(), B1.get_y()) < std::fmin(A2.get_y(), B2.get_y()))
            return false;
        if (std::fmax(A1.get_y(), B1.get_y()) < std::fmin(A2.get_y(), B2.get_y()))
            return false;
        return true;
    }
};