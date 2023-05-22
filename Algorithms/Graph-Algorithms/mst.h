// Algorithms for solving the minimum spanning tree problem (mst)

#ifndef mst
#define mst

#include <limits>

#include "../../Datastructures/dictHeap.h"
#include "../../Datastructures/graph.h"
#include "vector"

std::vector<int> primsAlgorithm(Graph& g) {
    // Init a priority queue and add a random vertex to it
    FibonacciDictHeap<int> h = FibonacciDictHeap<int>(true);
    h.insert(0, 0);
    // Init an array to keep track of which vertices are already part of our tree
    std::vector<bool> mstVertices(g.getNumVertices(), false);
    // Init an array to keep track of the minimum distance of any vertex to the current tree
    std::vector<double> distance(g.getNumVertices(), std::numeric_limits<double>::max());
    // Init an array to store which edge is used to achieve that minimum distance
    std::vector<int> connector(g.getNumVertices());
    // Init an array to store the edges which will make up the mst
    // An edge will be identified by using two int values (start, end)
    std::vector<int> edges;
    edges.reserve((g.getNumVertices() - 1) << 1);

    while (!h.empty()) {
        int u = h.extract();
        // add u to the current mst
        mstVertices[u] = true;
        // add the edge connecting u to the current mst to the edge set
        if (u) {
            edges.push_back(u);
            edges.push_back(connector[u]);
        }

        std::vector<int> neighbours;
        std::vector<double> costs;
        std::tie(neighbours, costs) = g.getNeighbours(u);
        for (int j = 0; j < neighbours.size(); j++) {
            int v = neighbours[j];
            // check if neighbour is already in current mst and if no, check if the connection over that edge is better than the current connection
            if (!mstVertices[v] && costs[j] < distance[v]) {
                distance[v] = costs[j];
                connector[v] = u;
                if (h.contains(v)) {
                    h.changeKey(v, costs[j]);
                } else {
                    h.insert(v, costs[j]);
                }
            }
        }
    }

    return edges;
}

#endif