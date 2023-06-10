//
// Created by denok on 20.05.2023.
//

#ifndef TECHNOPARK_ALGO_ARCGRAPH_H
#define TECHNOPARK_ALGO_ARCGRAPH_H

#include <cassert>

struct ArcGraph : public IGraph {
public:
    explicit ArcGraph(int size) : vertCount(size) {};

    explicit ArcGraph(const IGraph &graph) : vertCount(graph.VerticesCount()) {
        for (int from = 0; from < graph.VerticesCount(); from++) {
            for (int to: graph.GetNextVertices(from)) {
                arr.emplace_back(from, to);
            }
        }
    }

    ~ArcGraph() override = default;

    void AddEdge(int from, int to) override {
        assert(0 <= from && from < arr.size());
        assert(0 <= to && to < arr.size());
        arr.emplace_back(from, to);
    }

    int VerticesCount() const override {
        return vertCount;
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        assert(0 <= vertex && vertex < arr.size());
        std::vector<int> nextVertices;
        for (const auto &i: arr) {
            if (i.first == vertex) {
                nextVertices.push_back(i.second);
            }
        }
        return nextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        assert(0 <= vertex && vertex < arr.size());
        std::vector<int> prevVertices;

        for (const auto &i: arr) {
            if (i.second == vertex) {
                prevVertices.push_back(i.first);
            }
        }
        return prevVertices;
    }

private:
    int vertCount;
    std::vector<std::pair<int, int>> arr;
};

#endif //TECHNOPARK_ALGO_ARCGRAPH_H
