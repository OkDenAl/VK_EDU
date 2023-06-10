// Задание номер 2. Окутин Денис
// Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей
// между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами.
// Требуемая сложность O(V+E).

#include <vector>
#include <cassert>
#include <iostream>
#include <queue>

struct ListGraph {
public:
    explicit ListGraph(size_t size)
            : adjacencyLists(size) {
    }

    ~ListGraph() = default;

    void AddEdge(int from, int to) {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
        adjacencyLists[to].push_back(from);
    }

    int VerticesCount() const {
        return static_cast<int>(adjacencyLists.size());
    }

    std::vector<int> GetNextVertices(int vertex) const {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }

private:
    std::vector<std::vector<int>> adjacencyLists;
};

int findCountOfShortestDist(const ListGraph &graph, int startVertex, int endVertex, std::vector<bool> &visited) {
    std::vector<int> dist(graph.VerticesCount(), graph.VerticesCount());
    dist[startVertex] = 0;
    std::vector<int> k(graph.VerticesCount(), 0);
    k[startVertex] = 1;
    visited[startVertex] = true;
    std::queue<int> qu;
    qu.push(startVertex);

    while (!qu.empty()) {
        int currentVertex = qu.front();
        qu.pop();

        for (int nextVertex: graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
            if (dist[nextVertex] > dist[currentVertex] + 1) {
                dist[nextVertex] = dist[currentVertex] + 1;
                k[nextVertex] = k[currentVertex];
            } else if (dist[nextVertex] == dist[currentVertex] + 1) {
                k[nextVertex] += k[currentVertex];
            }
        }
    }
    return k[endVertex];
}

int main() {
    size_t vertexCount = 0;
    size_t edgesCount = 0;
    std::cin >> vertexCount >> edgesCount;
    ListGraph graph(vertexCount);
    for (size_t t = 0; t < edgesCount; t++) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }
    int startTarget, endTarget;
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::cin >> startTarget >> endTarget;
    int ans = findCountOfShortestDist(graph, startTarget, endTarget, visited);
    std::cout << ans << std::endl;
}
