#pragma once

namespace GraphStruct {
    class Vertex {
        double x;
        double y;
    public:
        Vertex();
        Vertex(double x, double y);
        double& get_x();
        double& get_y();
        double get_x() const;
        double get_y() const;
    };
};