// Authors: Marc Gröling

#include "../dijkstra.h"
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

    std::vector<double> distances = std::get<1>(dijkstrasAlgorithm(g, test_case.start_node));

    for (int i = 0; i < test_case.queries.size(); i++)
    {
        double distance = distances[test_case.queries[i]];
        if (distance == std::numeric_limits<double>::infinity())
        {
            output.push_back("Impossible");
        }
        else
        {
            output.push_back(std::to_string((int)distance));
        }
    }
    return output;
}