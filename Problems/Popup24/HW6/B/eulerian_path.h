#include "graph.h"

#include <algorithm>
#include <stack>

// check if all vertices of the graph that have at least one edge (outgoing or incoming) are reachable from the start
// vertex
bool allVerticesReachable(const Graph &g, int start_vertex, const std::vector<int> &in_degree,
                          const std::vector<int> &out_degree)
{
    // simple dfs
    std::vector<int> visited(g.getNumVertices(), false);
    std::stack<int> vertex_stack;
    vertex_stack.push(start_vertex);

    while (!vertex_stack.empty())
    {
        int current = vertex_stack.top();
        vertex_stack.pop();
        visited[current] = true;

        for (const std::pair<int, double> &neighbour : g.getNeighbours(current))
        {
            if (!visited[neighbour.first])
            {
                vertex_stack.push(neighbour.first);
            }
        }
    }

    for (int i = 0; i < visited.size(); i++)
    {
        if (!visited[i] && (in_degree[i] > 0 || out_degree[i] > 0))
        {
            return false;
        }
    }

    return true;
}

// check if the graph has a eulerian path
// also returns the start vertex that the path has to start from (in case the out-degree of one vertex is higher than
// the in-degree of it)
std::pair<bool, int> graphHasEulerianPath(const Graph &g, const std::vector<int> &in_degree,
                                          const std::vector<int> &out_degree)
{
    // conditions for existence:
    // (1) In each node, the indegree equals the outdegree, OR
    // (2) in one node, the indegree is one larger than the outdegree, in another node ,the outdegree is one larger than
    // the indegree, and in all other nodes, the indegree equals the outdegree
    // finally all vertices that have edges must be reachable from the vertex that the eulerian path starts from
    bool in_minus_out_equal_1 = false;
    bool out_minus_in_equal_1 = false;
    // if there is a vertex with higher outdegree than indegree then the eulerian path must start from this one
    int out_minus_in_equal_1_vertex = -1;
    int any_outgoing_vertex = -1;
    for (int i = 0; i < g.getNumVertices(); i++)
    {
        if (in_degree[i] != out_degree[i])
        {
            if (in_degree[i] - out_degree[i] == 1)
            {
                // only one allowed
                if (in_minus_out_equal_1)
                {
                    return std::pair{false, -1};
                }
                in_minus_out_equal_1 = true;
            }
            else if (out_degree[i] - in_degree[i] == 1)
            {
                // only one allowed
                if (out_minus_in_equal_1)
                {
                    return std::pair{false, -1};
                }
                out_minus_in_equal_1 = true;
                out_minus_in_equal_1_vertex = i;
            }
            // difference is higher than 1, no eulerian path
            else
            {
                return std::pair{false, -1};
            }
        }
        // also save any vertex with outgoing edges
        if (out_degree[i] > 0)
        {
            any_outgoing_vertex = i;
        }
    }

    // it is not allowed to only have one of them be true (XOR) (cause then one edge couldn't be used)
    if (in_minus_out_equal_1 ^ out_minus_in_equal_1)
    {
        return std::pair{false, -1};
    }

    if (out_minus_in_equal_1_vertex != -1)
    {
        return std::pair{allVerticesReachable(g, out_minus_in_equal_1_vertex, in_degree, out_degree),
                         out_minus_in_equal_1_vertex};
    }
    else
    {
        return std::pair{allVerticesReachable(g, any_outgoing_vertex, in_degree, out_degree), any_outgoing_vertex};
    }
}

std::vector<int> hierholzersAlgorithm(const Graph &g)
{
    // create a vector to store the eulerian path
    std::vector<int> eulerian_path;
    // store the neighbours for all vertices
    std::vector<std::vector<int>> neighbours(g.getNumVertices());
    // compute the in- and out-degree for all vertices to check for the existence of a eulerian path
    std::vector<int> in_degree(g.getNumVertices(), 0);
    std::vector<int> out_degree(g.getNumVertices(), 0);
    for (int i = 0; i < g.getNumVertices(); i++)
    {
        for (const std::pair<int, double> neighbour : g.getNeighbours(i))
        {
            neighbours[i].push_back(neighbour.first);
            out_degree[i]++;
            in_degree[neighbour.first]++;
        }
    }

    std::pair<bool, int> info = graphHasEulerianPath(g, in_degree, out_degree);

    if (!info.first)
    {
        return eulerian_path;
    }

    // select the vertex that has a higher outgoing degree than ingoing degree as the start vertex if it exists,
    // otherwise just any vertex with outgoing edges
    std::stack<int> vertex_stack;
    vertex_stack.push(info.second);

    while (!vertex_stack.empty())
    {
        int v = vertex_stack.top();
        // if the vertex still has any unused outgoing edges, use it and add the connected vertex to the stack
        if (neighbours[v].size())
        {
            vertex_stack.push(neighbours[v].back());
            neighbours[v].pop_back();
        }
        // no neighbours anymore, add it to the eulerian path and remove the vertex (can't create any new subtours
        // from it)
        else
        {
            vertex_stack.pop();
            eulerian_path.push_back(v);
        }
    }
    std::reverse(eulerian_path.begin(), eulerian_path.end());

    return eulerian_path;
}