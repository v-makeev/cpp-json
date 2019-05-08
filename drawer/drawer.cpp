#include "drawer.h"

namespace Drawer {
    using std::make_shared;    
    vector<GeometryObject *> ObjectsContainer::objects{};
    void draw_object(GeometryObject* p) {
        if (p->type == TO_POINT) {
            glColor3d(1, 0, 0);
            glPointSize(5);
            glBegin(GL_POINTS);
            auto point = (Point*)p;
            glVertex2d(point->get_x(), point->get_y());
            glEnd();
        } else if (p->type == TO_SEGMENT) {
            glColor3d(1, 1, 1);
            glPointSize(1);
            glBegin(GL_LINES);
            auto points = (Segment*)p;
            glVertex2d(points->get_begin().get_x(), points->get_begin().get_y());
            glVertex2d(points->get_end().get_x(), points->get_end().get_y());
            glEnd();
        }
    }
    Window::Window(unsigned short width, unsigned short height, double max_width, double max_height)
        : width(width)
        , height(height)
        , max_width(max_width)
        , max_height(max_height)
        , point_size(1)
        {
        }
    Window::Window(unsigned short width, unsigned short height)
        : width(width)
        , height(height)
        , max_width(width)
        , max_height(height)
        , point_size(1) 
        {
        }
    Window::Window(const Window& w) 
        : width(w.width)
        , height(w.height)
        , max_height(w.max_height)
        , max_width(w.max_width)
        {
        }
    void Window::init(int &argc, char** argv) const {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("graph");
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, max_width, 0, max_height, -5, 5);
        glClear(GL_COLOR_BUFFER_BIT);
        glutDisplayFunc(display);
        glutTimerFunc(50, timer, 0);
        glutMainLoop();
    }
    void Window::draw_point(const Point& p) const {
        ObjectsContainer::push_back(new Point(p));
    }
    void Window::draw_segment(const Point& p1, const Point& p2) const {
        ObjectsContainer::push_back(new Segment(p1, p2));
    }
    void Window::clear() const {
        glClear(GL_COLOR_BUFFER_BIT);
        ObjectsContainer::objects.clear();
    }
    void ObjectsContainer::push_back(GeometryObject* go) {
        objects.push_back(go);
    }
    void Window::set_size_point(int size) {
        point_size = size;
    }
    void display() {
        glClear(GL_COLOR_BUFFER_BIT);
        auto& objects = ObjectsContainer::objects;
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            draw_object(*it);
        }
        glutSwapBuffers();
    }
    void timer(int = 0) {
        display();
        glutTimerFunc(50, timer, 0);
    }
};