#include <cassert>

#include "../../../Datastructures/graph.h"
#include "../sssp.h"

void test_dijkstra_startEqualsEnd() {
    std::array<double, 9> weights = {0, 2, 0, 0, 0, 1, 1, 0, 0};
    AdjacencyMatrixGraph<3> g = AdjacencyMatrixGraph<3>(weights);

    std::vector<int> path;
    double distance;
    std::tie(path, distance) = dijkstra(g, 0, 0);
    assert(distance == 0);
    assert(path.size() == 1);
    assert(path[0] == 0);
}