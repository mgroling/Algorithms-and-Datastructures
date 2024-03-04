/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------

*/

#include "kattisio.h"

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <vector>

long double euclidean_distance(const std::tuple<long double, long double> &pos1,
                               const std::tuple<long double, long double> &pos2)
{
    return std::sqrt(std::pow(std::get<0>(pos1) - std::get<0>(pos2), 2) +
                     std::pow(std::get<1>(pos1) - std::get<1>(pos2), 2));
}

long double solve_problem(const long double &length, const long double &width, std::vector<long double> &tree_positions)
{
    long double best_distance = LDBL_MAX;

    std::sort(tree_positions.begin(), tree_positions.end());
    std::vector<long double> tree_goal_positions;
    tree_goal_positions.push_back(0);
    long double spacing_tree_positions = length / (tree_positions.size() / 2 - 1);
    for (int i = 0; i < tree_positions.size() / 2; i++)
    {
        tree_goal_positions.push_back(tree_goal_positions[i] + spacing_tree_positions);
    }

    std::queue<std::tuple<int, int, long double>> node_queue;
    node_queue.emplace(0, 0);
    std::unordered_map<int, long double> cache;

    while (!node_queue.empty())
    {
        std::tuple<int, int, long double> node = node_queue.front();
        node_queue.pop();
        int trees_assigned_to_left = std::get<0>(node);
        int trees_assigned_to_right = std::get<1>(node);
        long double distance_this_solution = std::get<2>(node);
        int id_this_solution = trees_assigned_to_left + trees_assigned_to_right * (tree_positions.size() / 2);

        auto pointer = cache.find(id_this_solution);
        // check that this solution is still relevant, otherwise discard it
        if (pointer != cache.end() && distance_this_solution == pointer->second)
        {
            int trees_assigned_total = trees_assigned_to_left + trees_assigned_to_right;
            if (trees_assigned_total < tree_positions.size())
            {
                // check if any side already has the max number of trees
                if (trees_assigned_to_left == tree_positions.size() / 2)
                {
                }
                else if (trees_assigned_to_right == tree_positions.size() / 2)
                {
                }
                else
                {
                    // assign tree to the left
                    auto pointer = cache.find(id_this_solution + 1);
                    long double new_distance =
                        distance_this_solution +
                        std::abs(tree_positions[trees_assigned_total] - tree_goal_positions[trees_assigned_total / 2]);
                    // check that element either doesn't exist yet or that this solution is better
                    // TODO: restructure to put into one if statement
                    if (pointer != cache.end())
                    {
                        if (new_distance < pointer->second)
                        {
                            cache[id_this_solution + 1] = new_distance;
                            node_queue.emplace(trees_assigned_to_left + 1, trees_assigned_to_right);
                        }
                    }
                    else
                    {
                        cache[id_this_solution + 1] = new_distance;
                        node_queue.emplace(trees_assigned_to_left + 1, trees_assigned_to_right);
                    }
                }
            }
            else
            {
                if (distance_this_solution < best_distance)
                {
                    best_distance = distance_this_solution;
                }
            }
        }
    }

    return best_distance;
}