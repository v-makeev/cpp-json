#pragma once
#include "../vertex/vertex.h"

namespace GraphStruct {
    class Edge {
        Vertex* from;
        Vertex* to;
        double weight;
    public:
        Edge();
        Edge(Vertex* from, Vertex* to);
        Edge(Vertex* from, Vertex* to, double weight);
        Vertex* get_from();
        Vertex* get_to();
        const Vertex* get_from() const;
        const Vertex* get_to() const;
        double& get_weight();
        double get_weight() const;
    };
};