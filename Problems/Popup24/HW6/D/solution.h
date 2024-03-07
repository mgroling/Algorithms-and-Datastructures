/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

The city executive board in Lund wants to construct a sightseeing tour by bus in Lund, so that tourists can see every
corner of the beautiful city. They want to construct the tour so that every street in the city is visited exactly once.
The bus should also start and end at the same junction. As in any city, the streets are either one-way or two-way,
traffic rules that must be obeyed by the tour bus. Help the executive board and determine if it’s possible to construct
a sightseeing tour under these constraints.

----------------------------------------------------- INPUT -----------------------------------------------------

On the first line of the input is a single positive integer n <= 20, indicating the number of test scenarios to follow.
Each scenario begins with a line containing two positive integers m and s, 1 <= m <= 200, 1 <= s <= 1000 being the
number of junctions and streets, respectively. The following s lines contain the streets. Each street is described with
three integers, x, y, and d, 1 <= x, y <= m, 0 <= d <= 1, where x and y are the junctions connected by a street. If d =
1, then the street is a one-way street (going from x to y), otherwise it is a two-way street. You may assume that there
exists a junction from which all other junctions can be reached.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each scenario, output one line containing the word “possible” or “impossible”, depending on whether or not it is
possible to construct a sightseeing tour.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
4
5 8
2 1 0
1 3 0
4 1 1
1 5 0
5 4 1
3 4 0
4 2 1
2 2 0
4 4
1 2 1
2 3 0
3 4 0
1 4 1
3 3
1 2 0
2 3 0
3 2 0
3 4
1 2 0
2 3 1
1 2 0
3 2 0

Sample Output 2:
possible
impossible
impossible
possible

----------------------------------------------------- SOLUTION -----------------------------------------------------

We are looking for a eulerian cycle, i.e. the in-degree and out-degree of each vertex must be the same. The two-way
streets allow us to select the direction of an edge. For each vertex, we compute how many more two-way streets must be
out-going. Each edge can increase the out-degree of one of its connectors by 1. We can solve this with a max-flow
algorithm, each two-way edge in the original graph is then an agent that needs to be assigned to a mission. And
different missions have a different number of required agents. If we can assign all agents (edges) to a mission
(vertex), then the in-degree can equal the out-degree for each vertex and thus a eulerian cycle exists.

*/

#include "graph.h"
#include "kattisio.h"
#include "max_flow.h"

#include <tuple>
#include <vector>

bool solve_test_case(Test_case &test_case)
{
    // calculate the out- and in-degree for each vertex and how many edges it is connected to
    std::vector<int> out_degree(test_case.num_vertices, 0);
    std::vector<int> in_degree(test_case.num_vertices, 0);
    std::vector<int> degree(test_case.num_vertices, 0);
    for (const std::pair<int, int> &edge : test_case.one_way_edges)
    {
        out_degree[edge.first]++;
        in_degree[edge.second]++;
        degree[edge.first]++;
        degree[edge.second]++;
    }

    for (const std::pair<int, int> &edge : test_case.two_way_edges)
    {
        degree[edge.first]++;
        degree[edge.second]++;
    }

    // if any vertex has an odd degree or if any vertex v has an out- or in-degree higher than degree(v)/2, then there
    // can't be eulerian cycle
    // also calculate how many more out edges each vertex needs
    std::vector<int> out_edges_needed;
    int required_total_flow = 0;
    for (int i = 0; i < test_case.num_vertices; i++)
    {
        int degree_halved = degree[i] / 2;
        if (degree[i] % 2 == 1 || out_degree[i] > degree_halved || in_degree[i] > degree_halved)
        {
            return false;
        }

        out_edges_needed.push_back(degree_halved - out_degree[i]);
        required_total_flow += degree_halved - out_degree[i];
    }

    // construct a graph for max flow with 4 layers: source, all two-way edges, all vertices, target
    AdjacencyListGraph g = AdjacencyListGraph(test_case.two_way_edges.size() + test_case.num_vertices + 2);
    int source = 0;
    int offset_first_layer = 1;
    int offset_second_layer = offset_first_layer + test_case.two_way_edges.size();
    int target = offset_second_layer + test_case.num_vertices;

    for (int i = 0; i < test_case.two_way_edges.size(); i++)
    {
        int edge_id = offset_first_layer + i;
        int vertex1_id = offset_second_layer + test_case.two_way_edges[i].first;
        int vertex2_id = offset_second_layer + test_case.two_way_edges[i].second;

        // source to first layer (edges)
        g.addEdge(source, edge_id, 1, false);
        g.addEdge(edge_id, source, 0, false);

        // first layer (edges) to second layer (vertices)
        g.addEdge(edge_id, vertex1_id, 1, false);
        g.addEdge(vertex1_id, edge_id, 0, false);

        g.addEdge(edge_id, vertex2_id, 1, false);
        g.addEdge(vertex2_id, edge_id, 0, false);
    }

    for (int i = 0; i < test_case.num_vertices; i++)
    {
        // second layer (vertices) to target
        g.addEdge(offset_second_layer + i, target, out_edges_needed[i], false);
        g.addEdge(target, offset_second_layer + i, 0, false);
    }

    // all vertices need to have their needs met (get enough out-going edges)
    return required_total_flow == (int)edmondsKarp(g, source, target);
}

std::vector<bool> solve_problem(std::vector<Test_case> &test_cases)
{
    std::vector<bool> output;

    for (Test_case &test_case : test_cases)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}