/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "apsp.h"
#include "graph.h"
#include "kattisio.h"

#include <algorithm>
#include <limits>
#include <vector>

bool compare_first(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return a.first < b.first;
}

int compute_pairwise_elevator_distance(int remainder_elevator1, int modulo_elevator1, int remainder_elevator2,
                                       int modulo_elevator2, int num_floors)
{
    // if (modulo_elevator1 == modulo_elevator2)
    // {
    //     return std::abs(remainder_elevator1 - remainder_elevator2);
    // }

    int min_distance = std::numeric_limits<int>::max();
    int next_elevator1 = remainder_elevator1 + modulo_elevator1;
    int next_elevator2 = remainder_elevator2 + modulo_elevator2;
    while (remainder_elevator1 < num_floors && remainder_elevator2 < num_floors)
    {
        int distance = std::abs(remainder_elevator1 - remainder_elevator2);
        if (distance < min_distance)
        {
            min_distance = distance;
        }

        if (std::abs(next_elevator1 - remainder_elevator2) < std::abs(next_elevator2 - remainder_elevator1))
        {
            remainder_elevator1 = next_elevator1;
            next_elevator1 += modulo_elevator1;
        }
        else
        {
            remainder_elevator2 = next_elevator2;
            next_elevator2 += modulo_elevator2;
        }
    }

    return min_distance;
}

std::pair<int, int> solve_test_case(const Test_case &test_case)
{
    // no elevators
    if (!test_case.elevators.size())
    {
        return std::pair<int, int>{test_case.num_floors - 1, test_case.num_floors - 1};
    }

    // vertex 0 is elevator 0, vertex 1 is elevator 1, etc. the last vertex is the floor
    AdjacencyListGraph g = AdjacencyListGraph(test_case.elevators.size() + 1);

    for (int i = 0; i < test_case.elevators.size(); i++)
    {
        for (int j = i + 1; j < test_case.elevators.size(); j++)
        {
            // add edge from elevator i to elevator j
            g.addEdge(i, j,
                      compute_pairwise_elevator_distance(test_case.elevators[i].first, test_case.elevators[i].second,
                                                         test_case.elevators[j].first, test_case.elevators[j].second,
                                                         test_case.num_floors),
                      true);
        }

        // add edge from elevator i to floor
        g.addEdge(i, test_case.elevators.size(), test_case.elevators[i].first, true);
    }

    // compute APSP
    std::vector<std::vector<double>> distances = floydWarshall(g);

    // array containing each floor of each elevator with (floor, id_elevator)
    std::vector<std::pair<int, int>> elevator_floors;

    for (int i = 0; i < test_case.elevators.size(); i++)
    {
        int floor = test_case.elevators[i].first;
        int modulo = test_case.elevators[i].second;
        while (floor < test_case.num_floors)
        {
            elevator_floors.emplace_back(floor, i);
            floor += modulo;
        }
    }

    // sort array according to floors (ascendingly)
    std::sort(elevator_floors.begin(), elevator_floors.end(), compare_first);

    int ground_floor = test_case.elevators.size();
    int left;
    int right;
    int max_dist = std::numeric_limits<int>::min();
    int max_floor = -1;
    for (int i = 0; i < elevator_floors.size() - 1; i++)
    {
        left = elevator_floors[i].first - distances[ground_floor][elevator_floors[i].second];
        right = elevator_floors[i + 1].first + distances[ground_floor][elevator_floors[i + 1].second];

        int floor = left + (right - left) / 2;
        int dist = floor - left;
        if (dist > max_dist)
        {
            max_dist = dist;
            max_floor = floor;
        }
    }

    // special case last elevator to last floor
    left = elevator_floors[elevator_floors.size() - 1].first -
           distances[ground_floor][elevator_floors[elevator_floors.size() - 1].second];
    int floor = test_case.num_floors - 1;
    int dist = floor - left;
    if (dist > max_dist)
    {
        max_dist = dist;
        max_floor = floor;
    }

    return std::pair<int, int>{max_dist, max_floor};
}

std::vector<std::pair<int, int>> solve_problem(const std::vector<Test_case> &test_cases)
{
    std::vector<std::pair<int, int>> output;

    for (const Test_case &test_case : test_cases)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}