// Authors: Marc Gröling

#ifndef time_dijkstra
#define time_dijkstra

#include <algorithm>
#include <functional>
#include <limits>
#include <unordered_map>
#include <vector>

#include "dictHeap.h"
#include "time_graph.h"

std::vector<int> reconstructPath(const std::vector<int> &previous, const int &start_vertex, int end_vertex)
{
    std::vector<int> path;

    // go through parent after parent of the end_vertex until the start_vertex is found, resulting in the path in
    // reverse
    while (previous.at(end_vertex) != end_vertex)
    {
        // if the current node doesn't have a parent, return an empty path (not reachable)
        if (previous.at(end_vertex) == -1)
        {
            return std::vector<int>{};
        }
        path.push_back(end_vertex);
        end_vertex = previous.at(end_vertex);
    }
    path.push_back(start_vertex);
    std::reverse(path.begin(), path.end());

    return path;
}

// Input: graph, start_vertex should be between 0 and num_vertices-1 of the graph, if end_vertex is given, then the
// algorithm terminates early once it is found
// edge_available should be a function that tells given the current time and the time info of that edge, when that edge
// is available again (integer), if the edge is not available at any point in the future from now, then the function
// should return std::numeric_limits<int>::max()
// Output: vector of the previous node (parent) in the search tree structure and vector of the distance to each node
std::tuple<std::vector<int>, std::vector<int>> dijkstrasAlgorithmTime(
    const TimeGraph &g, const int &start_vertex,
    const std::function<int(const int &, const std::vector<int> &)> &edge_available, const int &end_vertex = -1)
{
    // Init a priority queue
    BinaryDictHeap<int> prioQ = BinaryDictHeap<int>(true);
    prioQ.insert(start_vertex, 0);
    // Init an a array to store the distances
    std::vector<int> distance(g.getNumVertices(), std::numeric_limits<int>::max());
    distance[start_vertex] = 0;
    // Init an array to store the previous nodes of each vertex to later reconstruct the path
    std::vector<int> previous(g.getNumVertices(), -1);
    previous[start_vertex] = start_vertex;

    while (!prioQ.empty())
    {
        int u = prioQ.extract();
        int dist_u = distance[u];
        if (u == end_vertex)
        {
            return std::tuple{previous, distance};
        }

        // go through all neighbours (v_1,..,v_k) of the current vertex u and check if the path from u to v_i is shorter
        // than the direct path to v_i
        for (const std::tuple<int, int, std::vector<int>> &neighbour : g.getNeighbours(u))
        {
            int v = std::get<0>(neighbour);
            // take the edge on the next time that it is available
            int wait_time = edge_available(dist_u, std::get<2>(neighbour));
            // edge is available at some point in the future
            if (wait_time != std::numeric_limits<int>::max())
            {
                int alt_dist = dist_u + wait_time + std::get<1>(neighbour);
                // check if the path using u is shorter than the current distance to v
                if (alt_dist < distance[v])
                {
                    distance[v] = alt_dist;
                    previous[v] = u;
                    if (prioQ.contains(v))
                    {
                        prioQ.changeKey(v, alt_dist);
                    }
                    else
                    {
                        prioQ.insert(v, alt_dist);
                    }
                }
            }
        }
    }

    return std::tuple{previous, distance};
}

#endif