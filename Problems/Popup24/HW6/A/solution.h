/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

A bicycle race is being organized in a land far, far away. There are N towns in the land, numbered 1 through N. There
are also M one-way roads between the towns. The race will start in town 1 and end in town 2.

How many different ways can the route be set? Two routes are considered different if they do not use the exact same
roads.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line of input contains two integers N and M (1 <= N <= 10000, 1 <= M <= 100000), the number of towns and
roads.

Each of the next M lines contains two different integers A and B, representing a road from town A to town B.

Towns may be connected by more than one road.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Output the number of distinct routes that can be set on a single line. If that number has more than nine digits, output
only the last nine digits of the number. If there are infinitely many routes, output “inf”.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
6 7
1 3
1 4
3 2
4 2
5 6
6 5
3 4

Sample Output 1:
3

Sample Input 2:
6 8
1 3
1 4
3 2
4 2
5 6
6 5
3 4
4 3

Sample Output 2:
inf

----------------------------------------------------- SOLUTION -----------------------------------------------------

First, we need to check if there is a path from town 1 (the start town) to town 2 through a cycle (a "good" cycle). If
that is the case, then there are infinitely many different paths. We do this with a DFS that checks for back-edges and
cross-edges.

If there is no "good" cycle from town 1 to town 2, then we can look at the DFS tree that is generated from town 1 (which
is a DAG). We then add the cross edges to the DFS tree and get the reverse topological sorting. Then there is 1 way to
get to the end and then we can go through the vertices in the reverse topological ordering and set their number of ways
to reach the end to the sum of the ways of all its neighbours. (so if we have a vertex v with three neighbours that have
3, 1, 2 ways to get to the end vertex, then v has 6 = 3 + 1 + 2 ways)

*/

#include "graph.h"

#include <stack>
#include <tuple>
#include <vector>

void dfs_helper(const Graph &g, const int &vertex, AdjacencyListGraph &dfs_tree, std::vector<int> &state,
                std::vector<std::tuple<int, int, double>> &back_edges,
                std::vector<std::tuple<int, int, double>> &cross_edges)
{
    // set state of vertex to processing
    state[vertex] = 1;
    for (const std::pair<int, double> &neighbour : g.getNeighbours(vertex))
    {
        // neighbour is unseen
        if (!state[neighbour.first])
        {
            dfs_tree.addEdge(vertex, neighbour.first, neighbour.second, false);
            dfs_helper(g, neighbour.first, dfs_tree, state, back_edges, cross_edges);
        }
        // neighbour is processing -> back edge
        else if (state[neighbour.first] == 1)
        {
            back_edges.emplace_back(vertex, neighbour.first, neighbour.second);
        }
        // neighbour is done -> cross edge
        else
        {
            cross_edges.emplace_back(vertex, neighbour.first, neighbour.second);
        }
    }
    // set state of vertex to done
    state[vertex] = 2;
}

// runs a dfs on the given graph from start_vertex and returns the dfs tree + cross edges + back edges of the search
// the cross edges and back edges are not included in the graph
std::tuple<AdjacencyListGraph, std::vector<std::tuple<int, int, double>>, std::vector<std::tuple<int, int, double>>>
dfs(const Graph &g, const int &start_vertex)
{
    AdjacencyListGraph dfs_tree = AdjacencyListGraph(g.getNumVertices());
    // set the state of all vertices to unseen
    std::vector<int> state(g.getNumVertices(), 0);
    std::vector<std::tuple<int, int, double>> back_edges;
    std::vector<std::tuple<int, int, double>> cross_edges;
    dfs_helper(g, start_vertex, dfs_tree, state, back_edges, cross_edges);

    return {dfs_tree, cross_edges, back_edges};
}

// non-recursive dfs to check which vertices are reachable from the start vertex
std::vector<bool> getReachableVertices(const Graph &g, const int &start_vertex)
{
    std::stack<int> stack;
    stack.push(start_vertex);
    std::vector<bool> visited(g.getNumVertices(), false);
    visited[start_vertex] = true;

    while (!stack.empty())
    {
        int cur = stack.top();
        stack.pop();

        for (const std::pair<int, double> &neighbour : g.getNeighbours(cur))
        {
            if (!visited[neighbour.first])
            {
                visited[neighbour.first] = true;
                stack.push(neighbour.first);
            }
        }
    }

    return visited;
}

// similar to postorder traversal of a tree, but we also have cross edges which is why the visited array is needed
void reverse_toplogical_sorting_helper(const Graph &g, const int &cur, std::vector<int> &postorder,
                                       std::vector<bool> &visited)
{
    for (const std::pair<int, double> neighbour : g.getNeighbours(cur))
    {
        if (!visited[neighbour.first])
        {
            visited[neighbour.first] = true;
            reverse_toplogical_sorting_helper(g, neighbour.first, postorder, visited);
        }
    }

    postorder.push_back(cur);
}

// for DAGs
std::vector<int> reverse_toplogical_sorting(const Graph &g, const int &root)
{
    std::vector<int> postorder;
    std::vector<bool> visited(g.getNumVertices(), false);
    visited[root] = true;
    reverse_toplogical_sorting_helper(g, root, postorder, visited);
    return postorder;
}

std::string solve_problem(const std::pair<int, std::vector<std::pair<int, int>>> &test_case)
{
    int start_vertex = 0;
    int end_vertex = 1;

    // create graph from test case
    AdjacencyListGraph g = AdjacencyListGraph(test_case.first);
    // also create a graph with flipped edges for later
    AdjacencyListGraph g_flipped = AdjacencyListGraph(test_case.first);

    for (const std::pair<int, int> &edge : test_case.second)
    {
        g.addEdge(edge.first, edge.second, 1, false);
        g_flipped.addEdge(edge.second, edge.first, 1, false);
    }

    // run the dfs on it
    AdjacencyListGraph dfs_tree;
    std::vector<std::tuple<int, int, double>> cross_edges, back_edges;
    std::tie(dfs_tree, cross_edges, back_edges) = dfs(g, start_vertex);

    // if there are any back edges that means there is a cycle and we need to check if the end vertex can be reached
    // from that cycle
    if (back_edges.size())
    {
        // run a dfs on the flipped graph to check which vertices are reachable from the end vertex
        std::vector<bool> reachable = getReachableVertices(g_flipped, end_vertex);

        for (const std::tuple<int, int, double> &edge : back_edges)
        {
            // if the target of a back edge is reachable from the end vertex that means that there is a path from the
            // start vertex to the end vertex through a cycle, which means that there are infinitely many different
            // paths from the start vertex to the end vertex
            if (reachable[std::get<1>(edge)])
            {
                return "inf";
            }
        }
    }

    // add the cross edges to the dfs tree
    for (const std::tuple<int, int, double> &edge : cross_edges)
    {
        dfs_tree.addEdge(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge), false);
    }

    std::vector<int> postorder_dfs_tree = reverse_toplogical_sorting(dfs_tree, start_vertex);

    // for each vertex calculate the number of different ways to go from the start vertex to the end vertex
    std::vector<long long> num_different_ways(g.getNumVertices(), 0);
    num_different_ways[end_vertex] = 1;
    // we only need the 9 last digits of the number of combinations, so we modulo by 10^9
    long long modulo = 1000000000LL;
    bool any_over_modulo = false;

    for (const int &vertex : postorder_dfs_tree)
    {
        for (const std::pair<int, double> &neighbour : g.getNeighbours(vertex))
        {
            if ((num_different_ways[vertex] + num_different_ways[neighbour.first]) >= modulo)
            {
                any_over_modulo = true;
            }

            num_different_ways[vertex] = (num_different_ways[vertex] + num_different_ways[neighbour.first]) % modulo;
        }
    }

    // if the number is bigger than 9 digits, then we may need to add leading zeroes (since the output requires this)
    std::string output = std::to_string(num_different_ways[start_vertex]);
    if (any_over_modulo && output.size() < 9)
    {
        while (output.size() < 9)
        {
            output = "0" + output;
        }
    }

    return output;
}