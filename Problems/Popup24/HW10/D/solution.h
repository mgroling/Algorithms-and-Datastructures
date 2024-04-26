/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "kattisio.h"

#include <set>
#include <stack>
#include <string>
#include <vector>

std::pair<bool, int> place_element(const std::pair<int, int> &hashes, std::vector<bool> &pos_filled)
{
    if (!pos_filled[hashes.first])
    {
        pos_filled[hashes.first] = true;
        return {true, hashes.first};
    }
    if (!pos_filled[hashes.second])
    {
        pos_filled[hashes.second] = true;
        return {true, hashes.second};
    }
    return {false, -1};
}

bool cascade_choices(const std::vector<std::pair<int, int>> &items, const std::vector<std::vector<int>> &pos_to_items,
                     std::vector<bool> pos_filled, std::set<int> to_be_placed, const bool &first_elem_first_pos)
{
    // need to rethink which data structures are suited for this problem... (2SAT like)

    // take a random element of the set and place it to its first or second position (depending on function parameters)
    auto it = to_be_placed.begin();
    int elem = *it;
    to_be_placed.erase(it);

    // items that need to be put in their alternative position
    std::stack<int> alternative_pos;

    if (first_elem_first_pos)
    {
        int pos = items[elem].first;
        pos_filled[pos] = true;
        for (const int &other : pos_to_items[pos])
        {
            if (to_be_placed.find(other) != to_be_placed.end())
            {
                alternative_pos.push(other);
            }
        }
    }
    else
    {
    }
}

bool solve_test_case(const Test_case &test_case)
{
    // create a mapping from a position in the hash table to all elements that use it (at least once)
    std::vector<std::vector<int>> pos_to_items(test_case.size_dictionary, std::vector<int>{});

    for (int i = 0; i < test_case.items.size(); i++)
    {
        pos_to_items[test_case.items[i].first].push_back(i);
        pos_to_items[test_case.items[i].second].push_back(i);
    }
}

std::vector<bool> solve_problem(const std::vector<Test_case> &test_cases)
{
    std::vector<bool> success;

    for (const Test_case &test_case : test_cases)
    {
        success.push_back(solve_test_case(test_case));
    }

    return success;
}