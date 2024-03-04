// Authors: Marc Gröling

#include "../graph.h"
#include "../prim_mst.h"
#include "kattisio.h"

#include <algorithm>

std::vector<std::string> solve_problem(const Test_case &test_case)
{
    std::vector<std::string> output;
    // convert test_case struct to instance of graph class
    AdjacencyListGraph g = AdjacencyListGraph(test_case.num_nodes);

    for (int i = 0; i < test_case.edges.size(); i++)
    {
        g.addEdge(std::get<0>(test_case.edges[i]), std::get<1>(test_case.edges[i]), std::get<2>(test_case.edges[i]),
                  true);
    }

    std::vector<std::tuple<int, int>> edges;
    double cost;
    std::tie(edges, cost) = primsAlgorithm(g);

    if (!edges.size())
    {
        return std::vector<std::string>{"Impossible"};
    }

    output.push_back(std::to_string((int)cost));

    std::sort(edges.begin(), edges.end());
    for (const std::tuple<int, int> &edge : edges)
    {
        std::string temp;
        temp += std::to_string(std::get<0>(edge));
        temp += " ";
        temp += std::to_string(std::get<1>(edge));
        output.push_back(temp);
    }

    return output;
}