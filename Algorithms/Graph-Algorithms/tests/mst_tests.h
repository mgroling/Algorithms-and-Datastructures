#include <cassert>

#include "../../../Datastructures/graph.h"
#include "../mst.h"
#include "tuple"
#include "vector"

Graph* generate_graph_18vertices() {
    AdjacencyMatrixGraph<18>* g = new AdjacencyMatrixGraph<18>();
    g->addEdge(0, 1, 7, true);
    g->addEdge(0, 14, 8, true);
    g->addEdge(1, 4, 1, true);
    g->addEdge(1, 5, 4, true);
    g->addEdge(2, 3, 4, true);
    g->addEdge(2, 5, 5, true);
    g->addEdge(3, 10, 4, true);
    g->addEdge(3, 17, 4, true);
    g->addEdge(4, 5, 3, true);
    g->addEdge(4, 7, 6, true);
    g->addEdge(4, 8, 7, true);
    g->addEdge(5, 6, 1, true);
    g->addEdge(5, 9, 3, true);
    g->addEdge(6, 9, 7, true);
    g->addEdge(7, 8, 5, true);
    g->addEdge(7, 11, 7, true);
    g->addEdge(7, 14, 5, true);
    g->addEdge(8, 9, 4, true);
    g->addEdge(8, 11, 1, true);
    g->addEdge(8, 12, 6, true);
    g->addEdge(9, 12, 1, true);
    g->addEdge(9, 13, 7, true);
    g->addEdge(10, 13, 6, true);
    g->addEdge(10, 17, 2, true);
    g->addEdge(11, 12, 9, true);
    g->addEdge(11, 14, 2, true);
    g->addEdge(11, 15, 7, true);
    g->addEdge(12, 13, 8, true);
    g->addEdge(12, 15, 1, true);
    g->addEdge(13, 16, 6, true);
    g->addEdge(15, 16, 7, true);
    g->addEdge(16, 17, 2, true);
    return g;
}

void assert_mst(Graph& g, std::vector<int> mstEdges, double actual_cost) {
    double cost = 0;
    std::vector<bool> mstVertices(g.getNumVertices(), false);
    for (int i = 0; i < mstEdges.size(); i += 2) {
        cost += g.getCost(mstEdges[i], mstEdges[i + 1]);
        mstVertices[mstEdges[i]] = true;
        mstVertices[mstEdges[i + 1]] = true;
    }
    // check that cost of mst equals the actual cost
    assert(cost == actual_cost);
    // check that all vertices of the graph are part of the mst
    for (int i = 0; i < mstVertices.size(); i++) {
        assert(mstVertices[i]);
    }
}

void test_prim_17vertices() {
    Graph* g = generate_graph_18vertices();
    std::vector<int> mstEdges = primsAlgorithm(*g);
    assert_mst(*g, mstEdges, 52);
    delete g;
}