
#include "bellman_ford.h"
#include "graph.h"

#include <limits>

// for each std::tuple: edge_destination, capacity, cost, flow
std::vector<long double> fordFulkerson(AdjacencyListGraph &g, int source, int target)
{
    std::tuple<std::vector<int>, std::vector<double>> previous_dist = bellmanFord(g, source);
    std::vector<int> path = reconstructPath(std::get<0>(previous_dist), source, target);
    std::vector<long double> cost;

    while (std::get<1>(previous_dist)[target] != std::numeric_limits<double>::infinity())
    {
        for (int i = 0; i < path.size() - 1; i++)
        {
            if (i == 1)
            {
                cost.push_back(g.changeEdge(path[i], path[i + 1], 1));
            }
            else
            {
                g.changeEdge(path[i], path[i + 1], 1);
            }
            g.changeEdge(path[i + 1], path[i], 0);
        }
        previous_dist = bellmanFord(g, source);
        path = reconstructPath(std::get<0>(previous_dist), source, target);
    }

    return cost;
}