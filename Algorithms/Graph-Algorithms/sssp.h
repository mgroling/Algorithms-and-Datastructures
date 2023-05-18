// Algorithms for solving the single source single path problem (sssp)

#ifndef sssp
#define sssp

#include <algorithm>
#include <functional>
#include <limits>

#include "../../Datastructures/dictHeap.h"
#include "../../Datastructures/graph.h"
#include "unordered_map"
#include "vector"

std::vector<int> reconstructPath(const std::vector<int>& previous, const int& start_vertex, int end_vertex) {
    std::vector<int> path;

    while (previous.at(end_vertex) != end_vertex) {
        path.push_back(end_vertex);
        end_vertex = previous.at(end_vertex);
    }
    path.push_back(start_vertex);
    std::reverse(path.begin(), path.end());

    return path;
}

std::vector<int> dijkstrasAlgorithm(Graph& g, int start_vertex, int end_vertex = -1) {
    // Init a priority queue
    BinaryDictHeap<int> h = BinaryDictHeap<int>(true);
    h.insert(start_vertex, 0);
    // Init an a array to store the distances
    std::vector<double> distance(g.getNumVertices(), std::numeric_limits<double>::max());
    distance[start_vertex] = 0;
    // Init an array to store the previous nodes of each vertex to later reconstruct the path
    std::vector<int> previous(g.getNumVertices(), -1);
    previous[start_vertex] = start_vertex;

    while (!h.empty()) {
        int u = h.extract();
        double dist_u = distance[u];
        if (u == end_vertex) {
            return previous;
        }

        std::vector<int> neighbours;
        std::vector<double> costs;
        std::tie(neighbours, costs) = g.getNeighbours(u);
        for (int i = 0; i < neighbours.size(); i++) {
            int v = neighbours[i];
            double alt_dist = dist_u + costs[i];
            // check if the path using u is shorter than the current distance to v
            if (alt_dist < distance[v]) {
                distance[v] = alt_dist;
                previous[v] = u;
                if (h.contains(v)) {
                    h.changeKey(v, alt_dist);
                } else {
                    h.insert(v, alt_dist);
                }
            }
        }
    }

    return previous;
}

#endif