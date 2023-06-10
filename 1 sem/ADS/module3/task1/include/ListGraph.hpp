//
// Created by denok on 20.05.2023.
//

#ifndef TECHNOPARK_ALGO_LISTGRAPH_HPP
#define TECHNOPARK_ALGO_LISTGRAPH_HPP

#include "IGraph.hpp"
#include <cassert>

struct ListGraph : public IGraph {
public:
    explicit ListGraph(int size)
            : adjacencyLists(size) {
    }

    explicit ListGraph(const IGraph &graph)
            : adjacencyLists(graph.VerticesCount()) {
        for (int i = 0; i < graph.VerticesCount(); i++) {
            adjacencyLists[i] = graph.GetNextVertices(i);
        }
    }

    ~ListGraph() override = default;

    void AddEdge(int from, int to) override {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
    }

    int VerticesCount() const override {
        return static_cast<int>(adjacencyLists.size());
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;

        for (int from = 0; from < adjacencyLists.size(); from++) {
            for (int to: adjacencyLists[from]) {
                if (to == vertex) {
                    prevVertices.push_back(from);
                }
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::vector<int>> adjacencyLists;
};

#endif //TECHNOPARK_ALGO_LISTGRAPH_HPP
