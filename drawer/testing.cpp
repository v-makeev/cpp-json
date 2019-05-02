#include "drawer.h"

using namespace Geometry;

int main(int argc, char **argv) {
    Drawer::Window window(400, 400);
    window.draw_point(Point(250, 250));
    window.draw_segment(Point(100, 100), Point(200, 200));
    window.init(argc, argv);
    return 0;
}