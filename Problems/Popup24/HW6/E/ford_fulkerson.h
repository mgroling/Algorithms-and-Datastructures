#include "graph.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

std::pair<std::vector<int>, double> reconstructPath(const std::vector<std::pair<int, double>> &previous,
                                                    const int &start_vertex, int end_vertex)
{
    std::vector<int> path;
    double cost = std::numeric_limits<int>::max();

    // check that the end vertex is reachable
    if (previous[end_vertex].first == -1)
    {
        return {std::vector<int>{}, 0};
    }

    // go through parent after parent of the end_vertex until the start_vertex is found, resulting in the path in
    // reverse
    while (previous[end_vertex].first != end_vertex)
    {
        path.push_back(end_vertex);
        cost = std::min(cost, previous[end_vertex].second);
        end_vertex = previous[end_vertex].first;
    }
    path.push_back(start_vertex);
    std::reverse(path.begin(), path.end());

    return {path, cost};
}

std::vector<std::pair<int, double>> bfs(const Graph &g, const int &source, const int &target)
{
    std::queue<int> q;
    q.push(source);
    std::vector<std::pair<int, double>> previous(g.getNumVertices(), {-1, 0});
    previous[source] = {source, std::numeric_limits<int>::max()};

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (const std::pair<int, double> &neighbour : g.getNeighbours(cur))
        {
            if (previous[neighbour.first].first == -1 && neighbour.second > 0)
            {
                q.push(neighbour.first);
                previous[neighbour.first] = {cur, neighbour.second};
            }
        }
    }

    return previous;
}

double ford_fulkerson(Graph &g, const int &source, const int &target)
{
    std::pair<std::vector<int>, double> path_flow = reconstructPath(bfs(g, source, target), source, target);
    double total_flow = 0;

    // there is still a path with positive flow
    while (path_flow.first.size())
    {
        for (int i = 0; i < path_flow.first.size() - 1; i++)
        {
            // decrease flow of taken edge
            g.changeEdge(path_flow.first[i], path_flow.first[i + 1], -path_flow.second);
            // increase flow of reverse edge
            g.changeEdge(path_flow.first[i + 1], path_flow.first[i], path_flow.second);
        }
        total_flow += path_flow.second;
        path_flow = reconstructPath(bfs(g, source, target), source, target);
    }

    return total_flow;
}