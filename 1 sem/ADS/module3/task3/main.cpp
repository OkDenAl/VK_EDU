// 3 задача. Окутин Денис

//Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога,
// которая возвращается в этот же город.
//
//Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
//N ≤ 10000, M ≤ 250000.
//Длина каждой дороги ≤ 10000.

#include <vector>
#include <iostream>
#include <set>
#include <limits>

struct ListGraph {
public:
    explicit ListGraph(size_t size)
            : adjacencyLists(size) {
    }

    ~ListGraph() = default;

    void AddEdge(int from, int to, int weight) {
        adjacencyLists[from].push_back({to, weight});
        adjacencyLists[to].push_back({from, weight});
    }

    int VerticesCount() const {
        return static_cast<int>(adjacencyLists.size());
    }

    const std::vector<std::pair<int, int>> &GetNextVertices(int vertex) const {
        return adjacencyLists[vertex];
    }

private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyLists;
};

int dijkstra(const ListGraph &graph, int startIndex, int endIndex) {
    std::vector<int> d(graph.VerticesCount(), std::numeric_limits<int>::max());
    std::set<std::pair<int, int>> q;
    d[startIndex] = 0;
    q.insert({0, startIndex});
    while (!q.empty()) {
        int currentVertex = q.begin()->second;
        q.erase(q.begin());
        for (std::pair<int, int> nextVertex: graph.GetNextVertices(currentVertex)) {
            if (d[nextVertex.first] > d[currentVertex] + nextVertex.second) {
                q.erase({d[nextVertex.first], nextVertex.first});
                d[nextVertex.first] = d[currentVertex] + nextVertex.second;
                q.insert({d[nextVertex.first], nextVertex.first});
            }
        }
    }
    return d[endIndex];
}


int main() {
    size_t vertexCount = 0;
    size_t edgesCount = 0;
    std::cin >> vertexCount >> edgesCount;
    ListGraph graph(vertexCount);
    for (size_t t = 0; t < edgesCount; t++) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
    }
    int startIndex, endIndex;
    std::cin >> startIndex >> endIndex;
    int ans = dijkstra(graph, startIndex, endIndex);
    std::cout << ans << std::endl;
}