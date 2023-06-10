//
// Created by denok on 20.05.2023.
//

#ifndef TECHNOPARK_ALGO_IGRAPH_HPP
#define TECHNOPARK_ALGO_IGRAPH_HPP

#include <vector>

struct IGraph {
    virtual ~IGraph() = default;

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //TECHNOPARK_ALGO_IGRAPH_HPP
