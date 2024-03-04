// Authors: Marc Gröling

#ifndef apsp
#define apsp

#include <limits>
#include <vector>

#include "graph.h"

std::vector<std::vector<double>> floydWarshall(const Graph &g)
{
    std::vector<std::vector<double>> distances(
        g.getNumVertices(), std::vector<double>(g.getNumVertices(), std::numeric_limits<double>::max()));

    for (int i = 0; i < g.getNumVertices(); i++)
    {
        distances[i][i] = 0;
        // add all edges of the graph
        for (const std::tuple<int, double> &neighbour : g.getNeighbours(i))
        {
            // only update the weight if it's smaller
            if (std::get<1>(neighbour) < distances[i][std::get<0>(neighbour)])
            {
                distances[i][std::get<0>(neighbour)] = std::get<1>(neighbour);
            }
        }
    }

    for (int k = 0; k < g.getNumVertices(); k++)
    {
        for (int i = 0; i < g.getNumVertices(); i++)
        {
            for (int j = 0; j < g.getNumVertices(); j++)
            {
                if (distances[i][j] > distances[i][k] + distances[k][j])
                {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }

    return distances;
}

#endif