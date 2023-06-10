// Задание 1. Окутин Денис.

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include "IGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "ArcGraph.h"
#include "SetGraph.h"

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, std::function<void(int)> &func) {
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty()) {
        int currentVertex = qu.front();
        qu.pop();

        func(currentVertex);

        for (int nextVertex: graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void BFS(const IGraph &graph, std::function<void(int)> func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            BFS(graph, i, visited, func);
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, std::function<void(int)> &func) {
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex: graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex])
            DFS(graph, nextVertex, visited, func);
    }
}

void DFS(const IGraph &graph, std::function<void(int)> func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            DFS(graph, i, visited, func);
    }
}

int main(int argc, const char *argv[]) {
    ListGraph listGraph(9);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);
    listGraph.AddEdge(7, 8);

    std::cout << "ListGraph" << std::endl;
    std::cout << "BFS:\t";
    BFS(listGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS:\t";
    DFS(listGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;

    MatrixGraph matrixGraph(listGraph);

    std::cout << "MatrixGraph" << std::endl;
    std::cout << "BFS:\t";
    BFS(matrixGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS:\t";
    DFS(matrixGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;

    ArcGraph arcGraph(matrixGraph);

    std::cout << "ArcGraph" << std::endl;
    std::cout << "BFS:\t";
    BFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS:\t";
    DFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;

    SetGraph setGraph(arcGraph);

    std::cout << "SetGraph" << std::endl;
    std::cout << "BFS:\t";
    BFS(setGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS:\t";
    DFS(setGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;

    return 0;
}
