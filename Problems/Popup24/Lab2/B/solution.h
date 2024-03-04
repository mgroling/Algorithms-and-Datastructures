// Authors: Marc Gröling

#include "../time_dijkstra.h"
#include "../time_graph.h"
#include "kattisio.h"

#include <cmath>
#include <limits>

int edge_available(const int &current_time, const std::vector<int> &time_info)
{
    int t_0 = time_info[0];
    int P = time_info[1];

    if (!P)
    {
        if (current_time <= t_0)
        {
            return t_0 - current_time;
        }
        else
        {
            return std::numeric_limits<int>::max();
        }
    }

    // cur_time = t_0 + x * P => x = (cur_time - t_0) / P
    // then round up x to get the next time step, where the edge can be taken
    int x_rounded_up = std::ceil((double)(current_time - t_0) / P);
    if (x_rounded_up < 0)
    {
        x_rounded_up = 0;
    }
    int next_time = t_0 + x_rounded_up * P;

    return next_time - current_time;
}

std::vector<std::string> solve_problem(const Test_case &test_case)
{
    std::vector<std::string> output;
    // convert test_case struct to instance of graph class
    AdjacencyListTimeGraph g = AdjacencyListTimeGraph(test_case.num_nodes);

    for (int i = 0; i < test_case.edges.size(); i++)
    {
        g.addEdge(std::get<0>(test_case.edges[i]), std::get<1>(test_case.edges[i]), std::get<4>(test_case.edges[i]),
                  std::vector<int>{std::get<2>(test_case.edges[i]), std::get<3>(test_case.edges[i])}, false);
    }

    std::vector<int> distances = std::get<1>(dijkstrasAlgorithmTime(g, test_case.start_node, edge_available));

    for (int i = 0; i < test_case.queries.size(); i++)
    {
        int distance = distances[test_case.queries[i]];
        if (distance == std::numeric_limits<int>::max())
        {
            output.push_back("Impossible");
        }
        else
        {
            output.push_back(std::to_string(distance));
        }
    }
    return output;
}