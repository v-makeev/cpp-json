#include "graph.h"

#include <iostream>

namespace GraphStruct {
    Graph::Graph() : vertexes{}, edges{} { }
    Graph::Graph(const Graph& gr) : vertexes(gr.vertexes), edges{} {
        for (auto edge : gr.edges) {
            auto i1 = edge.get_from() - &(gr.vertexes[0]);
            auto i2 = edge.get_to() - &(gr.vertexes[0]);
            edges.push_back(Edge(&vertexes[i1], &vertexes[i2]));
        }
    }
    void Graph::add_vertex(const Vertex& v) {
        vertexes.push_back(v);
        auto p = &(*vertexes.rbegin());
    }
    void Graph::connect(int x, int y) {
        auto e = Edge(&vertexes[x], &vertexes[y]);
        edges.push_back(e);
    }
    vector<Edge>::iterator Graph::begin() { return edges.begin();}
    vector<Edge>::iterator Graph::end() { return edges.end(); }
    vector<Edge>::const_iterator Graph::begin() const { return edges.begin(); }
    vector<Edge>::const_iterator Graph::end() const { return edges.end(); }
    size_t Graph::count_vertex() const { return vertexes.size(); }
};