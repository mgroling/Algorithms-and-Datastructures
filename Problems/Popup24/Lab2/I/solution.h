// Authors: Marc Gröling

#include "../eulerian_path.h"
#include "../graph.h"
#include "kattisio.h"

std::string solve_problem(const Test_case &test_case)
{
    std::string output;
    // convert test_case struct to instance of graph class
    AdjacencyListGraph g = AdjacencyListGraph(test_case.num_nodes);

    for (int i = 0; i < test_case.edges.size(); i++)
    {
        g.addEdge(test_case.edges[i].first, test_case.edges[i].second, 0, false);
    }

    std::vector<int> eulerian_path = hierholzersAlgorithm(g);

    if (!eulerian_path.size())
    {
        return "Impossible";
    }

    for (int i = 0; i < eulerian_path.size(); i++)
    {
        output += std::to_string(eulerian_path[i]);
        if (i != eulerian_path.size() - 1)
        {
            output += " ";
        }
    }

    return output;
}