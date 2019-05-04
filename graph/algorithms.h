#pragma once
#include "main_classes/graph/graph.h"
#include "../drawer/drawer.h"

#include <random>

namespace Functions {
    using namespace GraphStruct;
    using namespace Geometry;
    using namespace Drawer;
    class Random {
        static std::mt19937 gen;
    public:
        Random();
        static int random_int(int max_rand);
        static double random();
        static double random(double l, double r);
    };
    class VisualPresent {
        Graph gr;
    public:
        VisualPresent();
        VisualPresent(const Graph& gr);
        VisualPresent(const VisualPresent& vp);
        void show() const;
        void draw(const Window& window);
        void optimal(double mx, double my);
    };
};