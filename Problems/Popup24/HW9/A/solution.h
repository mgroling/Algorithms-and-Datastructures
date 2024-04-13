/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

There are black and white knights on a 5 by 5 chessboard. There are twelve of each color, and there is one square that
is empty. At any time, a knight can move into an empty square as long as it moves like a knight in normal chess (what
else did you expect?).

Given an initial position of the board, the question is: “what is the minimum number of moves in which we can reach the
final position”, which is (1 corresponding to a black knight, 0 to a white knight, and the empty space corresponding to
the empty position):

1 1 1 1 1
0 1 1 1 1
0 0   1 1
0 0 0 0 1
0 0 0 0 0

----------------------------------------------------- INPUT -----------------------------------------------------

First line of the input file contains an integer N (N < 14) that indicates how many sets of inputs are there. The
description of each set is given below:

Each set consists of five lines; each line represents one row of a chessboard. The positions occupied by white knights
are marked by 0 and the positions occupied by black knights are marked by 1. The space corresponds to the empty square
on board.

There is no blank line between the two sets of input.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each set your task is to find the minimum number of moves leading from the starting input configuration to the final
one. If that number is bigger than 10, then output one line stating

Unsolvable in less than 11 move(s).

otherwise output one line stating

Solvable in n move(s).

where n <= 10.

The output for each set is produced in a single line as shown in the sample output.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input:
2
01011
110 1
01110
01010
00100
10110
01 11
10111
01001
00000

Sample Output:
Unsolvable in less than 11 move(s).
Solvable in 7 move(s).

----------------------------------------------------- SOLUTION -----------------------------------------------------

We can simply run a bfs from the starting position and the goal position simultaneously and when a position is
encountered that is visited by both (from the start and the goal), then we have found a solution. This is also referred
to as a meet in the middle approach in combinatorial search.

One thing that is pretty cool here, is the way that the state of the game is encoded. We use a single integer that on
the first 25 bits stores the value of each field of the chess board (1 if black knight, 0 otherwise), the rest of the
integer is used to store the position of the empty space. This makes this solution very memory efficient and fast.

*/

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

const int MAX_ALLOWED_MOVES_ONE_SIDE = 5;
const int BOARD_SIZE = 25;
// valid moves depending on the empty space position
// 0  1  2  3  4
// 5  6  7  8  9
// 10 11 12 13 14
// 15 16 17 18 19
// 20 21 22 23 24
const std::vector<std::vector<int>> VALID_HORSE_MOVES = {{7, 11},
                                                         {8, 10, 12},
                                                         {5, 9, 11, 13},
                                                         {6, 12, 14},
                                                         {7, 13},
                                                         {2, 12, 16},
                                                         {3, 13, 15, 17},
                                                         {0, 4, 10, 14, 16, 18},
                                                         {1, 11, 17, 19},
                                                         {2, 12, 18},
                                                         {1, 7, 17, 21},
                                                         {0, 2, 8, 18, 20, 22},
                                                         {1, 3, 5, 9, 15, 19, 21, 23},
                                                         {2, 4, 6, 16, 22, 24},
                                                         {3, 7, 17, 23},
                                                         {6, 12, 22},
                                                         {5, 7, 13, 23},
                                                         {6, 8, 10, 14, 20, 24},
                                                         {7, 9, 11, 21},
                                                         {8, 12, 22},
                                                         {11, 17},
                                                         {10, 12, 18},
                                                         {11, 13, 15, 19},
                                                         {12, 14, 16},
                                                         {13, 17}};

// helper functions to modify the encoded board
int get_empty_space_position(const int &board_encoded)
{
    return board_encoded >> BOARD_SIZE;
}

void remove_empty_space_position(int &board_encoded)
{
    board_encoded -= (get_empty_space_position(board_encoded) << BOARD_SIZE);
}

// assumes that the empty space position is currently 0 in the encoded board configuration
void add_empty_space_position(int &board_encoded, const int &empty_space_position)
{
    board_encoded += (empty_space_position << BOARD_SIZE);
}

void replace_empty_space_position(int &board_encoded, const int &empty_space_position)
{
    remove_empty_space_position(board_encoded);
    add_empty_space_position(board_encoded, empty_space_position);
}

// transform board configuration into one int
// (the empty space is represented by a 0 in the bit map)
// 0  1  2  3  4
// 5  6  7  8  9
// 10 11 12 13 14
// 15 16 17 18 19
// 20 21 22 23 24
// right-most bit of the encoded board is position 0, the one to the left of it is position 1 etc.
// left to all the positions, the rest of the integer is used to encode where the empty space is (as a normal number)
int transform_board_configuration(const std::string &board_configuration)
{
    int board_encoded = 0;
    int empty_space_position = 0;

    for (int i = board_configuration.size() - 1; i >= 0; i--)
    {
        board_encoded = board_encoded << 1;
        if (board_configuration[i] == '1')
        {
            board_encoded++;
        }
        else if (board_configuration[i] == ' ')
        {
            empty_space_position = i;
        }
    }
    add_empty_space_position(board_encoded, empty_space_position);

    return board_encoded;
}

// goal position corresponding to
// 1 1 1 1 1
// 0 1 1 1 1
// 0 0   1 1
// 0 0 0 0 1
// 0 0 0 0 0
int GOAL_POSITION = transform_board_configuration("111110111100 110000100000");

int move_horse(int board_configuration, const int &horse_position, const int &empty_space_position)
{
    // check if the horse is a 1-horse (black)
    // if no, then we don't need to do anything, but change the empty space position (to the horse position)
    if ((board_configuration >> horse_position) & 1)
    {
        // horse is a 1-horse (black)
        // remove 1-horse
        board_configuration -= (1 << horse_position);
        // add 1-horse at new position
        board_configuration += (1 << empty_space_position);
    }

    // change empty space position
    replace_empty_space_position(board_configuration, horse_position);

    return board_configuration;
}

int solve_test_case(const std::string &board_configuration)
{
    int start_position = transform_board_configuration(board_configuration);
    if (start_position == GOAL_POSITION)
    {
        return 0;
    }
    // do a bfs starting from the initial position and the goal position simultaneously (meet in the middle)
    // save board config + whether the element was explored from the start or the goal
    std::queue<std::pair<int, bool>> game_position_queue;
    game_position_queue.emplace(start_position, true);
    game_position_queue.emplace(GOAL_POSITION, false);
    // need to save distance for each board position (better to use hashmap than array since we won't visit all states)
    std::unordered_map<int, uint8_t> start_distance;
    start_distance[start_position] = 0;
    std::unordered_map<int, uint8_t> goal_distance;
    goal_distance[GOAL_POSITION] = 0;

    while (!game_position_queue.empty())
    {
        std::pair<int, bool> cur = game_position_queue.front();
        game_position_queue.pop();
        int cur_distance = cur.second ? start_distance.find(cur.first)->second : goal_distance.find(cur.first)->second;

        // consider all possible 8 moves
        int empty_space_position = get_empty_space_position(cur.first);

        for (const int &horse_position : VALID_HORSE_MOVES[empty_space_position])
        {
            int new_position = move_horse(cur.first, horse_position, empty_space_position);
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

                    // still allowed to search more from new_position
                    if (cur_distance + 1 < MAX_ALLOWED_MOVES_ONE_SIDE)
                    {
                        game_position_queue.emplace(new_position, cur.second);
                    }
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

                    // still allowed to search more from new_position
                    if (cur_distance + 1 < MAX_ALLOWED_MOVES_ONE_SIDE)
                    {
                        game_position_queue.emplace(new_position, cur.second);
                    }
                }
            }
        }
    }

    // no solution found within the given parameters
    return -1;
}

std::vector<int> solve_problem(const std::vector<std::string> &test_cases)
{
    std::vector<int> output;

    for (const std::string &test_case : test_cases)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}