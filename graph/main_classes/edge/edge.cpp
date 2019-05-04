#include "edge.h"

namespace GraphStruct {
    Edge::Edge() : from{}, to{}, weight(0) { }
    Edge::Edge(Vertex* from, Vertex* to) : from(from), to(to), weight(0) { }
    Edge::Edge(Vertex* from, Vertex* to, double weight) : from(from), to(to), weight(weight) { }
    Vertex* Edge::get_from() { return from; }
    Vertex* Edge::get_to() { return to; }
    const Vertex* Edge::get_from() const { return (const Vertex*)from; }
    const Vertex* Edge::get_to() const { return (const Vertex*)to; }
    double& Edge::get_weight() { return weight; }
    double Edge::get_weight() const { return weight; }
};