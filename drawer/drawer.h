#pragma once
#include "geometry/geometry.h"
#include "../include/vector/Vector.h"

#include <GL/glut.h>
#include <memory>

namespace Drawer {
    using namespace Geometry;
    using std::shared_ptr;
    void draw_object(GeometryObject* p);
    struct ObjectsContainer {
        static vector<GeometryObject *> objects;
        static void push_back(GeometryObject* p);
    };
    void display();
    void timer(int);
    class Window {
        double max_width;
        double max_height;
        unsigned short width;
        unsigned short height;
        int point_size;
    public:
        Window(unsigned short width, unsigned short height, double max_width, double max_height);
        Window(unsigned short width, unsigned short height);
        Window(const Window& w);
        void init(int &argc, char** argv) const;
        void draw_point(const Point& p) const;
        void draw_segment(const Point& p1, const Point& p2) const;
        void set_size_point(int size);
        void clear() const;
    };
};