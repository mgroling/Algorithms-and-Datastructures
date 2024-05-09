/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Your boss gave you the task of creating a walking maze, and you are evaluating different designs. Before you commit to
one, you want to know how quickly people can move in and out of each different maze. After all, your boss is interested
in making money on this venture and, the faster people can move through, the more paying customers you can handle.

A maze is a set of numbered rooms and passages connecting the rooms. The maze’s only entrance is at the lowest-numbered
room and the only exit is at the highest-numbered room.

Each passage has a limit in the number of people that can pass through at a time. For two rooms numbered x
and y, if x and y have a common factor greater than one, then there is a passage between x and y. The largest common
factor p is the number of people per minute that can walk from x to y. Simultaneously, p people per minute can also be
walking from y to x. The entrance, exit, and rooms can handle any number of people walking through at a time. People
want to get through the maze as quickly as possible, so they do not wait around in the rooms.

Here are illustrations of the two sample inputs. Boxes represent the numbered rooms, and each arrow is a passage labeled
by the number of people per minute that can walk through it.

----------------------------------------------------- INPUT -----------------------------------------------------

Input is a single maze description. The first line is an integer 2 <= n <= 1000 indicating the number of rooms in the
maze. This is followed by n unique integers, one per line, which are the room numbers for the maze. Each room number is
in the range [2, 2 * 10^9].

----------------------------------------------------- OUTPUT -----------------------------------------------------

Print the maximum number of people per minute that can enter the maze, assuming that people are exiting the maze at the
same speed as people entering. No maze supports more than 10^9 people entering per minute.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
4
4
6
8
9

Sample Output 1:
3

Sample Input 2:
7
25289
17017
2601
325
225
55223
190969

Sample Output 2:
18

----------------------------------------------------- SOLUTION -----------------------------------------------------

The rooms form a graph for which the max flow will be the number of people that can go through the maze per minute.
Constructing the graph can be done via getting the factors for each room and then pairwise getting the greatest common
factors of a pair (the edge then has the weight of the greatest common factor (as long as it is not 1)).

*/

#include "graph.h"
#include "max_flow.h"

#include <algorithm>
#include <cmath>
#include <set>
#include <vector>

// returns all factors of a number
std::set<int> find_factors(const int &number)
{
    std::set<int> factors;
    double sqrt = std::sqrt(number);
    for (int i = 1; i < sqrt; i++)
    {
        if (number % i == 0)
        {
            factors.insert(i);
            factors.insert(number / i);
        }
    }
    if (sqrt == (int)sqrt && number % (int)sqrt == 0)
    {
        factors.insert(sqrt);
    }

    return factors;
}

int find_greatest_common_factor(const std::set<int> &a, const std::set<int> &b)
{
    // ensure that set a is the smaller set
    if (a.size() > b.size())
    {
        return find_greatest_common_factor(b, a);
    }

    // loop through set a's elements starting from the largest and check if it is also present in b
    for (auto it = a.rbegin(); it != a.rend(); it++)
    {
        if (b.find(*it) != b.end())
        {
            return *it;
        }
    }

    // no common factors
    return 1;
}

int solve_problem(std::vector<int> &input)
{
    // sort rooms ascendingly so that the first room is the entry room and the last room is the exit room
    // could do this faster but n <= 1000, so this takes basically no time
    std::sort(input.begin(), input.end());

    // for each room get the factors
    std::vector<std::set<int>> factors_numbers;
    factors_numbers.reserve(input.size());

    for (const int &num : input)
    {
        factors_numbers.emplace_back(find_factors(num));
    }

    AdjacencyListGraph g = AdjacencyListGraph(input.size());

    // go through each pair of numbers and (possibly) add an edge
    for (int i = 0; i < factors_numbers.size(); i++)
    {
        for (int j = i + 1; j < factors_numbers.size(); j++)
        {
            int greatest_common_factor = find_greatest_common_factor(factors_numbers[i], factors_numbers[j]);

            if (greatest_common_factor != 1)
            {
                g.addEdge(i, j, greatest_common_factor, true);
            }
        }
    }

    return edmondsKarp(g, 0, input.size() - 1);
}