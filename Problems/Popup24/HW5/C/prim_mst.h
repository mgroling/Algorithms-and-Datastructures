// Authors: Marc Gröling

#ifndef prim_mst
#define prim_mst

#include <limits>
#include <tuple>
#include <vector>

#include "dictHeap.h"
#include "graph.h"

std::tuple<std::vector<std::tuple<int, int>>, double> primsAlgorithm(Graph &g)
{
    // Init a priority queue and add a random vertex to it
    BinaryDictHeap<int> prioQ = BinaryDictHeap<int>(true);
    prioQ.insert(0, 0);
    // Init an array to keep track of which vertices are already part of our tree
    std::vector<bool> mstVertices(g.getNumVertices(), false);
    // Init an array to keep track of the minimum distance of any vertex to the current tree
    std::vector<double> distance(g.getNumVertices(), std::numeric_limits<double>::max());
    // Init an array to store which edge is used to achieve that minimum distance
    std::vector<int> connector(g.getNumVertices());
    // Init an array to store the edges which will make up the mst
    std::vector<std::tuple<int, int>> edges;
    edges.reserve(g.getNumVertices() - 1);
    double cost_mst = 0;

    while (!prioQ.empty())
    {
        int u = prioQ.extract();
        // add u to the current mst
        mstVertices[u] = true;
        // add the edge connecting u to the current mst to the edge set
        if (u)
        {
            edges.push_back(std::tuple<int, int>{std::min(u, connector[u]), std::max(u, connector[u])});
            cost_mst += distance[u];
        }

        for (const std::tuple<int, double> &neighbour : g.getNeighbours(u))
        {
            int v = std::get<0>(neighbour);
            double cost = std::get<1>(neighbour);
            // check if neighbour is already in current mst and if no, check if the connection over that edge is better
            // than the current connection to the current mst
            if (!mstVertices[v] && cost < distance[v])
            {
                distance[v] = cost;
                connector[v] = u;
                if (prioQ.contains(v))
                {
                    prioQ.changeKey(v, cost);
                }
                else
                {
                    prioQ.insert(v, cost);
                }
            }
        }
    }

    // check if the mst contains all vertices, if not return an empty set of edges
    if (edges.size() < g.getNumVertices() - 1)
    {
        return std::tuple{std::vector<std::tuple<int, int>>{}, std::numeric_limits<double>::max()};
    }
    return std::tuple{edges, cost_mst};
}

#endif