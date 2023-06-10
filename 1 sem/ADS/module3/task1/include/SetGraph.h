//
// Created by denok on 20.05.2023.
//

#ifndef TECHNOPARK_ALGO_SETGRAPH_H
#define TECHNOPARK_ALGO_SETGRAPH_H

#include <set>
#include <cassert>

struct SetGraph : public IGraph {
public:
    explicit SetGraph(size_t size) : hashTableList(size) {}

    explicit SetGraph(const IGraph &graph) : hashTableList(graph.VerticesCount()) {
        for (int from = 0; from < graph.VerticesCount(); from++) {
            for (int to: graph.GetNextVertices(from)) {
                hashTableList[from].insert(to);
            }
        }
    }

    ~SetGraph() override = default;

    void AddEdge(int from, int to) override {
        assert(0 <= from && from < hashTableList.size());
        assert(0 <= to && to < hashTableList.size());
        hashTableList[from].insert(to);
    }

    int VerticesCount() const override {
        return static_cast<int>(hashTableList.size());
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        assert(0 <= vertex && vertex < hashTableList.size());
        std::vector<int> nextVertices;
        for (int i: hashTableList[vertex]) {
            nextVertices.push_back(i);
        }
        return nextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        assert(0 <= vertex && vertex < hashTableList.size());
        std::vector<int> prevVertices;

        for (int from = 0; from < hashTableList.size(); from++) {
            for (int to: hashTableList[from]) {
                if (to == vertex) {
                    prevVertices.push_back(from);
                }
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::set<int>> hashTableList;
};

#endif //TECHNOPARK_ALGO_SETGRAPH_H
