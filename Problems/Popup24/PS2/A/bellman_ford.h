// Authors: Marc Gröling

#ifndef bellman_ford
#define bellman_ford

#include <algorithm>
#include <limits>
#include <stack>
#include <vector>

#include "graph.h"

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

void markNegativeCycleVertices(const Graph &g, const int &vertex_from, std::vector<bool> &negative_cycle_vertices)
{
    std::stack<int> vertex_stack;
    vertex_stack.push(vertex_from);

    while (!vertex_stack.empty())
    {
        int current = vertex_stack.top();
        vertex_stack.pop();
        negative_cycle_vertices[current] = true;

        for (const std::tuple<int, int, double, int> &neighbour : g.getNeighbours(current))
        {
            if (!negative_cycle_vertices[std::get<0>(neighbour)])
            {
                vertex_stack.push(std::get<0>(neighbour));
            }
        }
    }
}

// Input: graph, start_vertex should be between 0 and num_vertices-1 of the graph
// Output: vector of the previous node (parent) in the search tree structure and vector of the distance to each node
// if a vertex is unreachable, then its distance will be std::numeric_limits<double>::infinity() and if there is an
// arbitrarily short path to it, then it will be -std::numeric_limits<double>::infinity()
std::tuple<std::vector<int>, std::vector<double>> bellmanFord(const Graph &g, const int &start_vertex)
{
    // Init an a array to store the distances
    std::vector<double> distance(g.getNumVertices(), std::numeric_limits<double>::infinity());
    distance[start_vertex] = 0;
    // Init an array to store the previous nodes of each vertex to later reconstruct the path
    std::vector<int> previous(g.getNumVertices(), -1);
    previous[start_vertex] = start_vertex;

    // continously relax all edges (|V| - 1 times since that's the maximal length of a shortest path without negative
    // cycles)
    bool any_relaxed = true;
    int i = 0;
    while (any_relaxed && i < g.getNumVertices() - 1)
    {
        any_relaxed = false;
        for (int j = 0; j < g.getNumVertices(); j++)
        {
            for (const std::tuple<int, int, double, int> &neighbour : g.getNeighbours(j))
            {
                double alt_dist = distance[j] + std::get<2>(neighbour);
                // check if the edge can be relaxed (if the path over j is shorter than directly going to the neighbour)
                if (std::get<3>(neighbour) < std::get<1>(neighbour) && alt_dist < distance[std::get<0>(neighbour)])
                {
                    distance[std::get<0>(neighbour)] = alt_dist;
                    previous[std::get<0>(neighbour)] = j;
                    any_relaxed = true;
                }
            }
        }

        i++;
    }

    // loop went through |V| - 1 times, there might be a negative cycle in the graph
    // => check for negative cycles (if any edge can still be relaxed then there is a negative cycle)
    if (any_relaxed)
    {
        // for each vertex store if it can be reached through a negative cycle (or is part of a negative cycle)
        std::vector<bool> negative_cycle_vertices(g.getNumVertices(), false);
        for (int i = 0; i < g.getNumVertices(); i++)
        {
            for (const std::tuple<int, int, double, int> &neighbour : g.getNeighbours(i))
            {
                double alt_dist = distance[i] + std::get<2>(neighbour);
                // edge can be reached through a negative cycle, since it can be relaxed
                if (alt_dist < distance[std::get<0>(neighbour)])
                {
                    // both i and the neighbour can be reached through a negative cycle
                    // mark all vertices that can be reached from i as ones being part of an arbitrarily short path
                    markNegativeCycleVertices(g, i, negative_cycle_vertices);
                }
            }
        }

        // change the distance to all vertices that are reachable through a negative cycle to -infinity
        for (int i = 0; i < g.getNumVertices(); i++)
        {
            if (negative_cycle_vertices[i])
            {
                distance[i] = -std::numeric_limits<double>::infinity();
            }
        }
    }

    return std::tuple{previous, distance};
}

#endif