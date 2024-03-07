/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

It has recently been discovered how to run open-source software on the Y-Crate gaming device. A number of enterprising
designers have developed Advent-style games for deployment on the Y-Crate. Your job is to test a number of these designs
to see which are winnable.

Each game consists of a set of up to 100 rooms. One of the rooms is the start and one of the rooms is the finish. Each
room has an energy value between -1000 and 1000. One-way doorways interconnect pairs of rooms.

The player begins in the start room with 100 energy points. She may pass through any doorway that connects the room she
is in to another room, thus entering the other room. The energy value of this room is added to the player’s energy. This
process continues until she wins by entering the finish room or dies by running out of energy (or quits in frustration).
During her adventure the player may enter the same room several times, receiving its energy each time.

----------------------------------------------------- INPUT -----------------------------------------------------

The input consists of several test cases (at most 50). Each test case begins with n, the number of rooms. The rooms are
numbered from 1 (the start room) to n (the finish room). Input for the n rooms follows. The input for each room consists
of one or more lines containing:

    the energy value for room

    the number of doorways leaving room

    a list of the rooms that are reachable by the doorways leaving room

The start and finish rooms will always have energy level 0. A line containing -1 follows the last test case.

----------------------------------------------------- OUTPUT -----------------------------------------------------

In one line for each case, output “winnable” if it is possible for the player to win, otherwise output “hopeless”.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
5
0 1 2
-60 1 3
-60 1 4
20 1 5
0 0
5
0 1 2
20 1 3
-60 1 4
-60 1 5
0 0
5
0 1 2
21 1 3
-60 1 4
-60 1 5
0 0
5
0 1 2
20 2 1 3
-60 1 4
-60 1 5
0 0
-1

Sample Output 1:
hopeless
hopeless
winnable
winnable

----------------------------------------------------- SOLUTION -----------------------------------------------------

This problem can be solved by a modified bellman ford algorithm. Instead of looking for shortest distances we try to
maximize the energy levels. Furthermore, we can only relax an edge if the energy level allows it. In the end, if after
|V| - 1 (attempted) relaxations of all edges, we can still relax some, that means that they are reachable through a (in
this case) positive cycle. We can use a dfs to mark all vertices reachable through positive cycles then. If the finish
room cannot be reached through normal paths nor positive cycles, that means that it is unreachable (hopeless).

*/

#include "kattisio.h"

#include <limits>
#include <stack>
#include <tuple>
#include <vector>

// dfs to mark all vertices reachable from vertex_from
void markPositiveCycleVertices(const Test_case &Test_case, const int &vertex_from,
                               std::vector<bool> &positive_cycle_rooms)
{
    std::stack<int> vertex_stack;
    vertex_stack.push(vertex_from);

    while (!vertex_stack.empty())
    {
        int current = vertex_stack.top();
        vertex_stack.pop();

        for (const int &neighbour : Test_case.rooms[current].second)
        {
            if (!positive_cycle_rooms[neighbour])
            {
                positive_cycle_rooms[neighbour] = true;
                vertex_stack.push(neighbour);
            }
        }
    }
}

bool solve_test_case(const Test_case &test_case)
{
    int start_room = 0;
    int finish_room = test_case.rooms.size() - 1;
    std::vector<int> energy_level(test_case.rooms.size(), std::numeric_limits<int>::min());
    energy_level[start_room] = 100;

    // use a modified bellman ford algorithm
    // relax all edges |V| - 1 times
    bool any_relaxed = true;
    int iteration = 0;
    while (any_relaxed && iteration < test_case.rooms.size() - 1)
    {
        any_relaxed = false;

        // relax all edges (if the energy level permits it)
        for (int i = 0; i < test_case.rooms.size(); i++)
        {
            if (energy_level[i] == std::numeric_limits<int>::min())
            {
                continue;
            }
            // go through neighbours
            for (const int &neighbour : test_case.rooms[i].second)
            {
                // add energy levels of the current room (using our path) to the energy level of the destination
                int energy_level_after_traversal = energy_level[i] + test_case.rooms[neighbour].first;
                // can only take an edge if we're not stuck afterwards
                if (energy_level_after_traversal > 0)
                {
                    if (neighbour == finish_room)
                    {
                        return true;
                    }
                    // relax edge
                    if (energy_level_after_traversal > energy_level[neighbour])
                    {
                        energy_level[neighbour] = energy_level_after_traversal;
                        any_relaxed = true;
                    }
                }
            }
        }
        iteration++;
    }

    std::vector<bool> positive_cycle_rooms(test_case.rooms.size(), false);
    if (any_relaxed)
    {
        // relax all edges one more time to check for the existence of in this case positive cycles
        for (int i = 0; i < test_case.rooms.size(); i++)
        {
            if (energy_level[i] == std::numeric_limits<int>::min())
            {
                continue;
            }
            // go through neighbours
            for (const int &neighbour : test_case.rooms[i].second)
            {
                // add energy levels of the current room (using our path) to the energy level of the destination
                int energy_level_after_traversal = energy_level[i] + test_case.rooms[neighbour].first;
                // can only take an edge if we're not stuck afterwards
                if (energy_level_after_traversal > 0)
                {
                    if (neighbour == finish_room)
                    {
                        return true;
                    }
                    // edge is part of positive cycle or can be reached through a positive cycle
                    // set the energy level of all vertices that can be reached from i to infinity
                    if (energy_level_after_traversal > energy_level[neighbour])
                    {
                        positive_cycle_rooms[i] = true;
                        markPositiveCycleVertices(test_case, i, positive_cycle_rooms);
                    }
                }
            }
        }
    }

    return energy_level[finish_room] != std::numeric_limits<int>::min() || positive_cycle_rooms[finish_room];
}

std::vector<bool> solve_problem(std::vector<Test_case> &test_cases)
{
    std::vector<bool> output;

    for (Test_case &test_case : test_cases)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}