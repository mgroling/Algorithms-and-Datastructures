#ifndef sssp
#define sssp

#include <algorithm>
#include <functional>

#include "../../Datastructures/dictHeap.h"
#include "../../Datastructures/graph.h"
#include "unordered_map"
#include "vector"

std::vector<int> reconstructPath(const std::unordered_map<int, int>& previous, const int& start_vertex, int end_vertex) {
    std::vector<int> path;

    while (previous.at(end_vertex) != end_vertex) {
        path.push_back(end_vertex);
        end_vertex = previous.at(end_vertex);
    }
    path.push_back(start_vertex);
    std::reverse(path.begin(), path.end());

    return path;
}

std::tuple<std::vector<int>, double> dijkstra(Graph& g, int start_vertex, int end_vertex) {
    // Init a priority queue
    BinaryDictHeap<int> h = BinaryDictHeap<int>(true);
    h.insert(start_vertex, 0);
    // Init a map to store the distance to each node
    std::unordered_map<int, double> distance;
    distance[start_vertex] = 0;
    // Init a map to store the previous nodes of each vertex to later reconstruct the path
    std::unordered_map<int, int> previous;
    previous[start_vertex] = start_vertex;

    while (!h.empty()) {
        int u = h.extract();
        double dist_u = distance[u];
        if (u == end_vertex) {
            return std::tuple<std::vector<int>, double>{reconstructPath(previous, start_vertex, end_vertex), dist_u};
        }

        std::vector<int> neighbours;
        std::vector<double> costs;
        std::tie(neighbours, costs) = g.getNeighbours(u);
        for (int i = 0; i < neighbours.size(); i++) {
            int v = neighbours[i];
            double alt_dist = dist_u + costs[i];
            // check if the path using u is shorter than the current distance to v
            if (!distance.count(v) || alt_dist < distance.at(v)) {
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

    return std::tuple<std::vector<int>, double>{std::vector<int>{}, 0};
}

#endif