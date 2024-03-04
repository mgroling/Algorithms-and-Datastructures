/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "kattisio.h"
#include "time_dijkstra.h"
#include "time_graph.h"

#include <functional>
#include <unordered_map>
#include <vector>

int edge_available(const int &current_time, const std::vector<int> &time_info)
{
    if (!time_info.size())
    {
        return 0;
    }

    int george_start = time_info[0];
    int george_end = time_info[1];
    int delay = time_info[2];
    int actual_time = current_time + delay;

    if (actual_time < george_start || actual_time >= george_end)
    {
        return 0;
    }

    return george_end - actual_time;
}

int edge_to_id(int start, int end, int num_vertices)
{
    return start + end * num_vertices;
}

int solve_problem(const Test_case &test_case)
{
    std::vector<std::vector<int>> weights(test_case.num_nodes, std::vector<int>(test_case.num_nodes, 0));
    for (const std::tuple<int, int, int> &edge : test_case.edges)
    {
        weights[std::get<0>(edge)][std::get<1>(edge)] = std::get<2>(edge);
        weights[std::get<1>(edge)][std::get<0>(edge)] = std::get<2>(edge);
    }

    std::vector<std::vector<int>> george_times(test_case.george_path.size() - 1);
    std::unordered_map<int, int> map;
    int time = 0;
    for (int i = 0; i < test_case.george_path.size() - 1; i++)
    {
        int start = test_case.george_path[i];
        int end = test_case.george_path[i + 1];
        george_times[i] = std::vector<int>{time, time + weights[start][end], test_case.time_delay};
        time += weights[start][end];
        map[edge_to_id(start, end, test_case.num_nodes)] = i;
        map[edge_to_id(end, start, test_case.num_nodes)] = i;
    }

    AdjacencyListTimeGraph g = AdjacencyListTimeGraph(test_case.num_nodes);

    for (const std::tuple<int, int, int> &edge : test_case.edges)
    {
        int start = std::get<0>(edge);
        int end = std::get<1>(edge);

        auto it = map.find(edge_to_id(start, end, test_case.num_nodes));
        if (it != map.end())
        {
            g.addEdge(start, end, std::get<2>(edge), george_times[it->second], true);
        }
        else
        {
            g.addEdge(start, end, std::get<2>(edge), std::vector<int>{}, true);
        }
    }

    return std::get<1>(
        dijkstrasAlgorithmTime(g, test_case.start_node, edge_available, test_case.end_node))[test_case.end_node];
}