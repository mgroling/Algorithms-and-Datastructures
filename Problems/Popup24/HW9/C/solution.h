/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

“Arrange” is a planetary popular Flash game. In “Arrange” the player is given a permutation of numbers 1 to N and a list
of allowed swaps. He then has to perform a sequence of swaps that transforms the initial permutation back to the ordered
sequence 1, 2, .., N.

In order to break the high score list, you need to perform the minimum amount of swaps possible. You can’t do that, but
you can write a program that does it for you!

----------------------------------------------------- INPUT -----------------------------------------------------

The first line of input contains two integers, N (2 <= N <= 11), the length of the initial sequence and M (1 <= M <= N *
(N - 1) / 2), the number of allowed swaps.

The second line of input contains a permutation of the numbers 1 to N.

The next M lines contain descriptions of allowed swaps. Each such line contains two distinct numbers 1 <= A < B <= N,
indicating that you are allowed to swap the A-th number in the sequence with the B-th number. The input never contains
two identical swaps.

You may assume that the input is such that a solution exists.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Output the minimum possible number of swaps to transform the permutation to 1, 2, .., N.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
2 1
2 1
1 2

Sample Output 1:
1

Sample Input 2:
3 2
2 1 3
1 3
2 3

Sample Output 2:
3

Sample Input 3:
5 5
1 2 3 4 5
1 5
2 5
1 4
1 2
3 5

Sample Output 3:
0

----------------------------------------------------- SOLUTION -----------------------------------------------------

Since N is quite small (<= 11), we can solve this with a simple BFS with a meet in the middle approach. The only problem
that we could run into would be that the space usage is too high (there is a limit of 1024 MB on the submission
platform). I therefore save the permutation in a 64-bit integer, where 4 bits represent one number.

The solution is basically identical to the one in problem A of this homework set. (both use a meet in the middle bfs
approach)

*/

#include <queue>
#include <unordered_map>
#include <vector>

uint8_t get_element(const uint64_t &permutation, const uint16_t &index)
{
    // shift the permutation to the right until we have the number + AND it with 15 (1111 in bit representation)
    return (permutation >> (index << 2)) & 15;
}

// assumes that element at the index is 0000 (in bits)
void add_element(uint64_t &permutation, const uint8_t &elem, const uint16_t &index)
{
    // need to cast elem, otherwise we might get an overflow
    permutation += ((uint64_t)elem << (index << 2));
}

uint8_t remove_element(uint64_t &permutation, const uint16_t &index)
{
    uint8_t elem = get_element(permutation, index);
    // need to cast elem, otherwise we might get an overflow
    permutation -= ((uint64_t)elem << (index << 2));
    return elem;
}

// 0 1 2 3 4 5 6 7 8 9 10
// most-left four bits represent the element at index 0
// second-most-left four bits represent element at index 1
// ...
uint64_t encode_permutation(const std::vector<uint8_t> &permutation)
{
    uint64_t encoded = 0;

    for (auto it = permutation.rbegin(); it != permutation.rend(); it++)
    {
        // need 4 bits to represent a number between 1 and 11
        encoded = encoded << 4;
        encoded += *it;
    }

    return encoded;
}

uint64_t execute_swap(uint64_t permutation, const std::pair<uint8_t, uint8_t> &swap)
{
    uint8_t elem1 = remove_element(permutation, swap.first);
    uint8_t elem2 = remove_element(permutation, swap.second);
    add_element(permutation, elem2, swap.first);
    add_element(permutation, elem1, swap.second);
    return permutation;
}

int8_t solve_problem(const std::pair<std::vector<uint8_t>, std::vector<std::pair<uint16_t, uint16_t>>> &problem)
{
    uint64_t start = encode_permutation(problem.first);
    std::vector<uint8_t> goal_vector;
    for (int i = 0; i < problem.first.size(); i++)
    {
        goal_vector.push_back(i + 1);
    }
    // goal is 1, 2, .., N
    uint64_t goal = encode_permutation(goal_vector);
    if (start == goal)
    {
        return 0;
    }

    // do a bfs starting from the initial position and the goal position simultaneously (meet in the middle)
    // save board config + whether the element was explored from the start or the goal
    std::queue<std::pair<uint64_t, bool>> state_queue;
    state_queue.emplace(start, true);
    state_queue.emplace(goal, false);
    // need to save distance for each board position (better to use hashmap than array since we won't visit all states)
    std::unordered_map<uint64_t, uint8_t> start_distance;
    start_distance[start] = 0;
    std::unordered_map<uint64_t, uint8_t> goal_distance;
    goal_distance[goal] = 0;

    while (!state_queue.empty())
    {
        std::pair<uint64_t, bool> cur = state_queue.front();
        state_queue.pop();
        uint8_t cur_distance =
            cur.second ? start_distance.find(cur.first)->second : goal_distance.find(cur.first)->second;

        // go through all swaps
        for (const std::pair<uint8_t, uint8_t> &swap : problem.second)
        {
            uint64_t new_position = execute_swap(cur.first, swap);
            auto ptr_start_map = start_distance.find(new_position);
            auto ptr_goal_map = goal_distance.find(new_position);

            // found from start position
            if (cur.second)
            {
                // unvisited position from start
                if (ptr_start_map == start_distance.end())
                {
                    // also present in the other map => sequence of moves found to move from start to goal
                    if (ptr_goal_map != goal_distance.end())
                    {
                        return cur_distance + 1 + ptr_goal_map->second;
                    }
                    start_distance[new_position] = cur_distance + 1;
                    state_queue.emplace(new_position, cur.second);
                }
            }
            // found from goal position
            else
            {
                // unvisited position from goal
                if (ptr_goal_map == goal_distance.end())
                {
                    // also present in the other map => sequence of moves found to move from start to goal
                    if (ptr_start_map != start_distance.end())
                    {
                        return ptr_start_map->second + cur_distance + 1;
                    }
                    goal_distance[new_position] = cur_distance + 1;
                    state_queue.emplace(new_position, cur.second);
                }
            }
        }
    }

    // no solution found
    return -1;
}