#include "ford_fulkerson.h"
#include "graph.h"

#include <cmath>

long double solve_problem(std::vector<std::vector<int>> agents)
{
    AdjacencyListGraph g = AdjacencyListGraph(agents.size() * 2 + 2);
    // 0 source
    // agents.size() * 2 + 1 sink
    int source = 0;
    int target = agents.size() * 2 + 1;
    int offset_first_layer = 1;
    int offset_second_layer = agents.size() + 1;

    for (int i = 0; i < agents.size(); i++)
    {
        g.addEdge(source, offset_first_layer + i, 1, 0, 0);
        g.addEdge(offset_first_layer + i, source, 1, 0, 1);
        g.addEdge(offset_second_layer + i, target, 1, 0, 0);
        g.addEdge(target, offset_second_layer + i, 1, 0, 1);
        for (int j = 0; j < agents.size(); j++)
        {
            g.addEdge(offset_first_layer + i, offset_second_layer + j, 1, 100 - agents[i][j], 0);
            g.addEdge(offset_second_layer + j, offset_first_layer + i, 1, agents[i][j] - 100, 1);
        }
    }
    std::vector<long double> temp = fordFulkerson(g, source, target);
    long double cost = 1;
    int power = 0;

    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i] != 0 && temp[i] != 100)
        {
            cost *= (100 - temp[i]);
            power++;
        }
        if (temp[i] == 100)
        {
            return 0;
        }
    }

    return cost / (std::pow(100.0L, power - 1));
}