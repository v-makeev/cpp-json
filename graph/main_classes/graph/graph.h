#pragma once
#include "../vertex/vertex.h"
#include "../edge/edge.h"
#include "../../../include/vector/Vector.h"
#include "../../../include/map/Map.h"

namespace GraphStruct {
    class Graph {
        vector<Vertex> vertexes;
        vector<Edge> edges;
    public:
        Graph();
        Graph(const Graph& gr);
        void add_vertex(const Vertex& v);
        void connect(int x, int y);
        vector<Edge>::iterator begin();
        vector<Edge>::iterator end();
        vector<Edge>::const_iterator begin() const;
        vector<Edge>::const_iterator end() const;
        Vertex& operator[] (int i) { return vertexes[i]; }
        Vertex operator[] (int i) const { return vertexes[i]; }
        size_t count_vertex() const;
    };
};