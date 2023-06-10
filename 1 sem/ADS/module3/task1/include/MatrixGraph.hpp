//
// Created by denok on 20.05.2023.
//

#ifndef TECHNOPARK_ALGO_MATRIXGRAPH_HPP
#define TECHNOPARK_ALGO_MATRIXGRAPH_HPP

#include "IGraph.hpp"
#include <cassert>

struct MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(size_t size) : matrix(size, std::vector<int>(size, 0)) {};

    explicit MatrixGraph(const IGraph &graph)
            : matrix(graph.VerticesCount(), std::vector<int>(graph.VerticesCount(), 0)) {
        for (int i = 0; i < graph.VerticesCount(); i++) {
            for (int to: graph.GetNextVertices(i)) {
                matrix[i][to] = 1;
            }
        }
    }

    ~MatrixGraph() override = default;;

    void AddEdge(int from, int to) override {
        assert(0 <= from && from < matrix.size());
        assert(0 <= to && to < matrix.size());
        matrix[from][to] = 1;
    }

    int VerticesCount() const override {
        return static_cast<int>(matrix.size());
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        assert(0 <= vertex && vertex < matrix.size());
        std::vector<int> nextVertices;
        for (int to = 0; to < matrix[vertex].size(); to++) {
            if (matrix[vertex][to] == 1) {
                nextVertices.push_back(to);
            }
        }
        return nextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        assert(0 <= vertex && vertex < matrix.size());
        std::vector<int> prevVertices;

        for (int from = 0; from < matrix.size(); from++) {
            if (matrix[from][vertex] == 1) {
                prevVertices.push_back(from);
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::vector<int>> matrix;
};

#endif //TECHNOPARK_ALGO_MATRIXGRAPH_HPP
