#include "vertex.h"

namespace GraphStruct {
    Vertex::Vertex() : x{}, y{} { }
    Vertex::Vertex(double x, double y) : x(x), y(y) { }
    double& Vertex::get_x() { return x; }
    double& Vertex::get_y() { return y; }
    double Vertex::get_x() const { return x; }
    double Vertex::get_y() const { return y; }
};