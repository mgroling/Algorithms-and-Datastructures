#include <cassert>

#include "../../../Datastructures/graph.h"
#include "../sssp.h"
#include "tuple"

std::tuple<Graph*, int, int> generate_graph_startEqualsEnd() {
    std::array<double, 9> weights = {0, 2, 0, 0, 0, 1, 1, 0, 0};
    AdjacencyMatrixGraph<3> g = AdjacencyMatrixGraph<3>(weights);
    return std::tuple<Graph*, int, int>{&g, 0, 0};
}

void assert_path_startEqualsEnd(std::vector<int> path, double distance) {
    assert(distance == 0);
    assert(path.size() == 1);
    assert(path[0] == 0);
}

void test_dijkstra_startEqualsEnd() {
    std::vector<int> path;
    double distance;
    Graph* g;
    int start, end;
    std::tie(g, start, end) = generate_graph_startEqualsEnd();
    std::tie(path, distance) = dijkstra(*g, start, end);
    assert_path_startEqualsEnd(path, distance);
}