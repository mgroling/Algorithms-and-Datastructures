/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Wallace the Weightlifting Walrus is training for a contest where it will have to lift 1000 kg. Wallace has some weight
plates lying around, possibly of different weights, and its goal is to add some of the plates to a bar so that it can
train with a weight as close as possible to 1000 kg.

In case there exist two such numbers which are equally close to 1000 (e.g. 998 and 1002), Wallace will pick the greater
one (in this case 1002).

Help Wallace the Weightlifting Walrus and tell it which weight it will have to lift.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line of the input contains the number of plates n (1 <= n <= 1000). Each of the following n lines contains one
positive integer less than or equal to 1000, denoting the weight of each plate.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Output one integer, the combined weight closest to 1000.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
4
900
500
498
4

Sample Output 1:
1002


Sample Input 2:
1
1

Sample Output 2:
1

----------------------------------------------------- SOLUTION -----------------------------------------------------

This problem is a variation of the subset-sum problem where we have to get as close to the target as possible. We can
use a dynamic programming approach. Let (i, s) be a state: There exists a subset of x_1, ..., x_i that sums to s. For
each state, we can create two new ones: (i + 1, s) and (i + 1, s + x_i). Now we can just search through the whole tree
and save the best total weight while traversing it (here with a BFS).

The tree has a maximum size of N * M, where N is the number of weights and M is the number of different total weight
combinations. M is capped by 2*N (since each weight is <= N). As such, the tree has a total size of <= 2 * N^2.

*/

#include "kattisio.h"

#include <queue>
#include <tuple>
#include <unordered_map>
#include <vector>

int solve_problem(const std::vector<int> &weights)
{
    std::queue<std::tuple<int, int>> node_queue;

    node_queue.emplace(0, 0);
    int goal_weight = 1000;
    int best_total_weight = 0;
    int best_distance_to_goal_weight = 1000;
    std::unordered_map<int, bool> visited;

    while (!node_queue.empty())
    {
        std::tuple<int, int> node = node_queue.front();
        int index = std::get<0>(node);
        int weight = std::get<1>(node);
        node_queue.pop();
        int distance_to_goal_weight = std::abs(goal_weight - weight);
        if (distance_to_goal_weight == 0)
        {
            return goal_weight;
        }
        if (distance_to_goal_weight == best_distance_to_goal_weight && weight > best_total_weight)
        {
            best_total_weight = weight;
        }
        if (distance_to_goal_weight < best_distance_to_goal_weight)
        {
            best_total_weight = weight;
            best_distance_to_goal_weight = distance_to_goal_weight;
        }

        if (index < weights.size())
        {
            int visited_index = (index + 1) + weight * weights.size();
            if (visited.find(visited_index) == visited.end())
            {
                node_queue.emplace(index + 1, std::get<1>(node));
                visited[visited_index] = true;
            }
            if (std::get<1>(node) + weights[std::get<0>(node)] < 2 * goal_weight)
            {
                visited_index += weights[index] * weights.size();
                if (visited.find(visited_index) == visited.end())
                {
                    node_queue.emplace(std::get<0>(node) + 1, weight + weights[index]);
                    visited[visited_index] = true;
                }
            }
        }
    }

    return best_total_weight;
}