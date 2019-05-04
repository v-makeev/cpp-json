#include "graph/algorithms.h"

#include <iostream>

using namespace Functions;

int main(int argc, char **argv) {
    
    int size_w = 400, size_h = 400;
    Window window(size_w, size_h);
    int n, m;
    std::cout << "n, m\n";
    std::cin >> n >> m;
    Graph gr;
    for (int i = 0; i < n; ++i) {
        gr.add_vertex(Vertex(Random::random(0.0, size_w), Random::random(0.0, size_h)));
    }
    for (int j = 0; j < m; ++j) {
        int u, v;
        std::cin >> u >> v;
        gr.connect(u - 1, v - 1);
    }
    VisualPresent vp(gr);
    vp.optimal(size_w, size_h);
    vp.draw(window);
    window.init(argc, argv);
    return 0;
}