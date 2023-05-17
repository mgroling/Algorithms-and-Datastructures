#include <cassert>

#include "../../../Datastructures/graph.h"
#include "../sssp.h"
#include "tuple"

std::tuple<Graph*, int, int> generate_graph_startEqualsEnd() {
    std::array<double, 9> weights = {0, 2, 8, 0, 0, 5, 0, 0, 0};
    // have to allocate in on the heap, otherwise it will go out of scope after return
    AdjacencyMatrixGraph<3>* g = new AdjacencyMatrixGraph<3>(weights);
    return std::tuple<Graph*, int, int>{g, 0, 0};
}

void assert_path_startEqualsEnd(std::vector<int> path, double distance) {
    assert(distance == 0);
    assert(path.size() == 1);
    assert(path[0] == 0);
}

std::tuple<Graph*, int, int> generate_graph_9vertices() {
    AdjacencyMatrixGraph<9>* g = new AdjacencyMatrixGraph<9>();
    g->addEdge(0, 1, 4, true);
    g->addEdge(0, 6, 7, true);
    g->addEdge(1, 2, 9, true);
    g->addEdge(1, 6, 11, true);
    g->addEdge(2, 3, 6, true);
    g->addEdge(2, 4, 2, true);
    g->addEdge(3, 4, 10, true);
    g->addEdge(3, 5, 5, true);
    g->addEdge(4, 5, 15, true);
    g->addEdge(4, 7, 1, true);
    g->addEdge(4, 8, 5, true);
    g->addEdge(5, 8, 12, true);
    g->addEdge(6, 7, 1, true);
    g->addEdge(7, 8, 3, true);
    return std::tuple<Graph*, int, int>{g, 0, 5};
}

void assert_path_9vertices(std::vector<int> path, double distance) {
    assert(distance == 22);
    std::vector<int> correct_path = {0, 6, 7, 4, 2, 3, 5};
    assert(path.size() == correct_path.size());
    for (int i = 0; i < correct_path.size(); i++) {
        assert(path[i] == correct_path[i]);
    }
}

void test_dijkstra_startEqualsEnd() {
    std::vector<int> path;
    double distance;
    Graph* g;
    int start, end;
    std::tie(g, start, end) = generate_graph_startEqualsEnd();
    std::tie(path, distance) = dijkstra(*g, start, end);
    assert_path_startEqualsEnd(path, distance);
    delete g;
}

void test_dijkstra_9vertices() {
    std::vector<int> path;
    double distance;
    Graph* g;
    int start, end;
    std::tie(g, start, end) = generate_graph_9vertices();
    std::tie(path, distance) = dijkstra(*g, start, end);
    assert_path_9vertices(path, distance);
    delete g;
}