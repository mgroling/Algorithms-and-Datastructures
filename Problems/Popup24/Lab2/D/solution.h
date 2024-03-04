// Authors: Marc Gröling

#include "../apsp.h"
#include "../graph.h"
#include "kattisio.h"

#include <limits>

std::vector<std::string> solve_problem(const Test_case &test_case)
{
    std::vector<std::string> output;
    // convert test_case struct to instance of graph class
    AdjacencyListGraph g = AdjacencyListGraph(test_case.num_nodes);

    for (int i = 0; i < test_case.edges.size(); i++)
    {
        g.addEdge(std::get<0>(test_case.edges[i]), std::get<1>(test_case.edges[i]), std::get<2>(test_case.edges[i]),
                  false);
    }

    std::vector<std::vector<double>> distances = floydWarshall(g);

    // check if the graph contains any negative cycles
    // save all vertices that can go to and back to a negative cycle (or are part of one themselves)
    std::vector<int> vertices_connected_to_negative_cycles;

    for (int i = 0; i < distances.size(); i++)
    {
        if (distances[i][i] < 0)
        {
            vertices_connected_to_negative_cycles.push_back(i);
        }
    }

    for (const std::tuple<int, int> &query : test_case.queries)
    {
        // check if there is a connection from start_vertex to a vertex that can produce arbitrarily short paths and
        // then to end_vertex (in case there are no negative cycles in the graph, this will never be a connection)
        bool any_connection = false;
        int start_vertex = std::get<0>(query);
        int end_vertex = std::get<1>(query);

        for (const int &vertex : vertices_connected_to_negative_cycles)
        {
            if (distances[start_vertex][vertex] != std::numeric_limits<double>::max() &&
                distances[vertex][end_vertex] != std::numeric_limits<double>::max())
            {
                any_connection = true;
                break;
            }
        }

        if (any_connection)
        {
            output.push_back("-Infinity");
        }
        // no negative cycle connection, just check the distances normally
        else
        {
            double distance = distances[start_vertex][end_vertex];
            if (distance == std::numeric_limits<double>::max())
            {
                output.push_back("Impossible");
            }
            else
            {
                output.push_back(std::to_string((int)distance));
            }
        }
    }

    return output;
}