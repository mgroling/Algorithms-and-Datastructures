/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

You are given a puzzle that can be represented as a 4x4 grid of colored cells. The solved puzzle contains 4
monochromatic rows, in this order: red, green, blue, yellow. Although we will analyze this puzzle using its 2D
representation, it is actually a 3D puzzle! Imagine that the grid is stretched over a torus (in other words, top edge is
connected to the bottom one and left edge is connected to the right one). If you are not familiar with the word “torus”
or what it is supposed to represent, just replace it with the word(s) “donut (with the hole in the middle)”.

For each move you are allowed to either move one row left or right, or one column up or down. The fact that the outer
edges are connected means that if a cell is “pushed out” of the grid, it will reappear on the other side of the grid. If
you had a torus or a donut handy (or a cup! HAHAha...ha... <sniff>), this would be much clearer.

Given a description of a state of this puzzle, what is the minimum number of moves you need to solve it? Note that all
possible puzzle configurations are solvable in less than 13 moves.

----------------------------------------------------- INPUT -----------------------------------------------------

Input file contains exactly 4 lines, containing 4 characters each, each character being either “R”, “G”, “B” or “Y’. The
input will describe a valid state of the puzzle.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Output the minimum number of moves needed to solve the given puzzle.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
RGGR
GBGB
BYBY
YRYR

Sample Output 1:
3

Sample Input 2:
RRRR
GBGG
GYBB
BYYY

Sample Output 2:
4

----------------------------------------------------- SOLUTION -----------------------------------------------------

Again, this can be solved using meet in the middle bfs (like A and C).

I think that this is not intended to work to be honest and that you are supposed to run into memory problems (since
there is only 1024 MB available on the submission platform). But it seems efficiently representing the state of the game
makes this week's homeworks much easier :).

(This time we have 16 colors of 4 possible values => need 32 bits of information, for which an unsigned 32-bit integer
is perfect)

*/

#include <array>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

uint8_t get_element(const uint32_t &permutation, const uint8_t &index)
{
    // shift the permutation to the right until we have the number + AND it with 3 (11 in bit representation)
    return (permutation >> (index << 1)) & 3;
}

// assumes that element at the index is 0000 (in bits)
void add_element(uint32_t &permutation, const uint8_t &elem, const uint8_t &index)
{
    // need to cast elem, otherwise we might get an overflow
    permutation += ((uint32_t)elem << (index << 1));
}

uint8_t remove_element(uint32_t &permutation, const uint8_t &index)
{
    uint8_t elem = get_element(permutation, index);
    // need to cast elem, otherwise we might get an overflow
    permutation -= ((uint32_t)elem << (index << 1));
    return elem;
}

// 0  1  2  3
// 4  5  6  7
// 8  9  10 11
// 12 13 14 15
// first two-right-most bits represent index 0
// second two-right-most bits represent index 1
// ...
uint32_t encode_permutation(const std::string &permutation)
{
    std::unordered_map<char, uint8_t> color_map = {{'R', 0}, {'G', 1}, {'B', 2}, {'Y', 3}};

    uint32_t encoded = 0;
    for (auto it = permutation.rbegin(); it != permutation.rend(); it++)
    {
        // need 2 bits to represent the numbers from 0 to 3
        encoded = encoded << 2;
        encoded += color_map.at(*it);
    }

    return encoded;
}

uint32_t rotate(uint32_t permutation, const bool &down_right_direction, const bool &rotate_row, const uint8_t index)
{
    std::array<uint8_t, 4> indices;
    // get the indices of the to-be-rotated elements
    if (rotate_row)
    {
        for (int i = 0; i < 4; i++)
        {
            if (down_right_direction)
            {
                indices[i] = index * 4 + i;
            }
            else
            {
                indices[3 - i] = index * 4 + i;
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            if (down_right_direction)
            {
                indices[i] = index + i * 4;
            }
            else
            {
                indices[3 - i] = index + i * 4;
            }
        }
    }

    std::array<uint8_t, 4> elems;
    // collect elements at indices
    for (int i = 0; i < 4; i++)
    {
        elems[i] = remove_element(permutation, indices[i]);
    }
    // shift them by 1
    for (int i = 0; i < 4; i++)
    {
        add_element(permutation, elems[i], indices[(i + 1) % 4]);
    }

    return permutation;
}

int8_t solve_problem(const std::string &problem)
{
    uint32_t start = encode_permutation(problem);
    // corresponds to
    // RRRR
    // GGGG
    // BBBB
    // YYYY
    uint32_t goal = encode_permutation("RRRRGGGGBBBBYYYY");
    if (start == goal)
    {
        return 0;
    }

    // do a bfs starting from the initial position and the goal position simultaneously (meet in the middle)
    // save board config + whether the element was explored from the start or the goal
    std::queue<std::pair<uint32_t, bool>> state_queue;
    state_queue.emplace(start, true);
    state_queue.emplace(goal, false);
    // need to save distance for each board position (better to use hashmap than array since we won't visit all states)
    std::unordered_map<uint32_t, uint8_t> start_distance;
    start_distance[start] = 0;
    std::unordered_map<uint32_t, uint8_t> goal_distance;
    goal_distance[goal] = 0;

    while (!state_queue.empty())
    {
        std::pair<uint32_t, bool> cur = state_queue.front();
        state_queue.pop();
        uint8_t cur_distance =
            cur.second ? start_distance.find(cur.first)->second : goal_distance.find(cur.first)->second;

        std::array<bool, 2> values{true, false};
        // go through all possible moves
        for (uint8_t index = 0; index < 4; index++)
        {
            for (const bool &rotate_row : values)
            {
                for (const bool &down_right_direction : values)
                {
                    uint32_t new_position = rotate(cur.first, down_right_direction, rotate_row, index);
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
        }
    }

    // no solution found, i.e. not a valid starting state
    return -1;
}