/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "kattisio.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

int find_nest(const int &cuckoo_id, const std::pair<int, int> &cuckoo_possible_spots, std::vector<int> &nests)
{
    // check if either of the nesting spots are unoccupied
    if (nests[cuckoo_possible_spots.first] == -1)
    {
        nests[cuckoo_possible_spots.first] = cuckoo_id;
        return -1;
    }
    if (nests[cuckoo_possible_spots.second] == -1)
    {
        nests[cuckoo_possible_spots.second] = cuckoo_id;
        return -1;
    }
    // if both spots are occupied, then kick out the other cuckoo from the first available spot
    int kicked_out_cuckoo = nests[cuckoo_possible_spots.first];
    nests[cuckoo_possible_spots.first] = cuckoo_id;
    return kicked_out_cuckoo;
}

bool solve_test_case_slow(const Test_case &test_case)
{
    // create an array to save which spots are occupied by which cuckoos (-1 marks that a spot is empty)
    std::vector<int> nests(test_case.size_dictionary, -1);

    for (int i = 0; i < test_case.items.size(); i++)
    {
        // try to find a nest for that cuckoo (item)
        int kicked_out_cuckoo = find_nest(i, test_case.items[i], nests);
        // another cuckoo had to be kicked out of their nest, this might lead to a loop, count the number of times the
        // initial cuckoo appears
        if (kicked_out_cuckoo != -1)
        {
            int initial_cuckoo = i;
            int count_initial_cuckoo = 0;
            // try to find a spot for the kicked out cuckoo
            while (kicked_out_cuckoo != -1)
            {
                kicked_out_cuckoo = find_nest(kicked_out_cuckoo, test_case.items[kicked_out_cuckoo], nests);
                count_initial_cuckoo += kicked_out_cuckoo == initial_cuckoo;
                // had to relocate the initial cuckoo twice => no solution possible
                if (count_initial_cuckoo == 2)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

// state of a solution (we need this later for rollbacks)
struct State
{
    std::vector<int> nests;
    std::set<int> nest_not_found;
    std::set<int> nest_forced;

    State()
    {
    }

    State(std::vector<int> nests, std::set<int> nest_not_found, std::set<int> nest_forced)
    {
        this->nests = nests;
        this->nest_not_found = nest_not_found;
        this->nest_forced = nest_forced;
    }
};

bool make_assumption(const Test_case &test_case, const std::vector<std::set<int>> &nest_to_cuckoos,
                     std::vector<int> &nests, std::set<int> &nest_forced, std::set<int> &nest_not_found,
                     const bool &assumption_value)
{
    auto it = nest_not_found.begin();
    int cuckoo = *it;
    // the nest positions of cuckoo cannot be occupied, because otherwise cuckoo would have been in the
    // nest_forced set
    // assume where the first cuckoo in nest_not_found goes
    int cuckoo_pos;
    if (assumption_value)
    {
        cuckoo_pos = test_case.items[cuckoo].first;
    }
    else
    {
        cuckoo_pos = test_case.items[cuckoo].second;
    }
    nests[cuckoo_pos] = cuckoo;
    nest_not_found.erase(cuckoo);
    // check if any other cuckoos have their position forced by this
    std::set_intersection(nest_to_cuckoos[cuckoo_pos].begin(), nest_to_cuckoos[cuckoo_pos].end(),
                          nest_not_found.begin(), nest_not_found.end(), std::inserter(nest_forced, nest_forced.end()));
    // no other cuckoo was forced into a position by this assumption, so it is definetly correct
    if (!nest_forced.size())
    {
        return true;
    }
    return false;
}

bool resolve_forced_cuckoos(const Test_case &test_case, const std::vector<std::set<int>> &nest_to_cuckoos,
                            std::vector<int> &nests, std::set<int> &nest_forced, std::set<int> &nest_not_found)
{
    // resolve the cuckoos that are forced to move into a nest now
    while (nest_forced.size())
    {
        auto it = nest_forced.begin();
        int cuckoo = *it;
        nest_forced.erase(cuckoo);
        nest_not_found.erase(cuckoo);
        if (nests[test_case.items[cuckoo].first] == -1)
        {
            int cuckoo_pos = test_case.items[cuckoo].first;
            nests[cuckoo_pos] = cuckoo;
            // add all other cuckoos that have their position forced by this
            std::set_intersection(nest_to_cuckoos[cuckoo_pos].begin(), nest_to_cuckoos[cuckoo_pos].end(),
                                  nest_not_found.begin(), nest_not_found.end(),
                                  std::inserter(nest_forced, nest_forced.end()));
        }
        else if (nests[test_case.items[cuckoo].second] == -1)
        {
            int cuckoo_pos = test_case.items[cuckoo].second;
            nests[cuckoo_pos] = cuckoo;
            // add all other cuckoos that have their position forced by this
            std::set_intersection(nest_to_cuckoos[cuckoo_pos].begin(), nest_to_cuckoos[cuckoo_pos].end(),
                                  nest_not_found.begin(), nest_not_found.end(),
                                  std::inserter(nest_forced, nest_forced.end()));
        }
        else
        {
            // assumption is false
            return false;
        }
    }

    return true;
}

bool solve_test_case(const Test_case &test_case)
{
    // create a vector representing which nest is occupied by which cuckoo (-1 marks that a nest is empty)
    std::vector<int> nests(test_case.size_dictionary, -1);

    // create a set that represents which cuckoos have not found a nest so far
    std::set<int> nest_not_found;

    // create a set that represents which cuckoos don't have a choice of nest (one of the nests that they could settle
    // for is already occupied)
    std::set<int> nest_forced;

    // compute mapping from nest position to cuckoos
    std::vector<std::set<int>> nest_to_cuckoos(test_case.size_dictionary, std::set<int>{});

    for (int i = 0; i < test_case.items.size(); i++)
    {
        nest_to_cuckoos[test_case.items[i].first].insert(i);
        nest_to_cuckoos[test_case.items[i].second].insert(i);
        nest_not_found.insert(i);

        // cuckoo can only go for one nest, so its nest position is forced
        if (test_case.items[i].first == test_case.items[i].second)
        {
            nest_forced.insert(i);
        }
    }

    // resolve all the cuckoos that can only go into one nest (and the ones that are forced to move into one by this)
    bool assumption_correct = resolve_forced_cuckoos(test_case, nest_to_cuckoos, nests, nest_forced, nest_not_found);
    // if this doesn't work then there is no solution (we didn't assume anything)
    if (!assumption_correct)
    {
        return false;
    }

    while (nest_not_found.size())
    {
        // check if either assuming that the first cuckoo goes into its first or second position is trivial
        // assume first position
        auto it = nest_not_found.begin();
        int cuckoo = *it;
        // the nest positions of cuckoo cannot be occupied, because otherwise cuckoo would have been in the
        // nest_forced set
        // assume where the first cuckoo in nest_not_found goes
        int cuckoo_pos = test_case.items[cuckoo].first;
        // check if any other cuckoos have their position forced by this
        std::set_intersection(nest_to_cuckoos[cuckoo_pos].begin(), nest_to_cuckoos[cuckoo_pos].end(),
                              nest_not_found.begin(), nest_not_found.end(),
                              std::inserter(nest_forced, nest_forced.end()));
        nest_forced.erase(cuckoo);
        // no other cuckoo was forced into a position by this assumption, so it is definetly correct
        if (!nest_forced.size())
        {
            nests[cuckoo_pos] = cuckoo;
            nest_not_found.erase(cuckoo);
            continue;
        }
        else
        {
            // check if the assumption to put it in the second nest holds trivially
            cuckoo_pos = test_case.items[cuckoo].second;
            std::set<int> nest_forced_temp;
            std::set_intersection(nest_to_cuckoos[cuckoo_pos].begin(), nest_to_cuckoos[cuckoo_pos].end(),
                                  nest_not_found.begin(), nest_not_found.end(),
                                  std::inserter(nest_forced_temp, nest_forced_temp.begin()));
            nest_forced_temp.erase(cuckoo);
            if (!nest_forced_temp.size())
            {
                nests[cuckoo_pos] = cuckoo;
                nest_not_found.erase(cuckoo);
                nest_forced.clear();
                continue;
            }
        }
        // save the state before the assumption
        State before_assumption = State(nests, nest_not_found, std::set<int>{});
        nests[cuckoo_pos] = cuckoo;
        nest_not_found.erase(cuckoo);

        assumption_correct = resolve_forced_cuckoos(test_case, nest_to_cuckoos, nests, nest_forced, nest_not_found);
        // the assumption was correct, as such this point is "safe"
        if (assumption_correct)
        {
            continue;
        }

        // assumption was not correct, now assume the opposite
        // first roll back to the saved point
        nests = std::move(before_assumption.nests);
        nest_not_found = std::move(before_assumption.nest_not_found);
        nest_forced = std::move(before_assumption.nest_forced);

        // make the assumption that the first cukoo in nest_not_found goes into its second assigned nest
        assumption_correct = make_assumption(test_case, nest_to_cuckoos, nests, nest_forced, nest_not_found, false);
        // no other cuckoos were forced into a nest by this, so the assumption is definetly correct
        if (assumption_correct)
        {
            continue;
        }

        assumption_correct = resolve_forced_cuckoos(test_case, nest_to_cuckoos, nests, nest_forced, nest_not_found);
        // neither of the assumptions was correct (first cuckoo can't go into its first or second nest), so there is no
        // solution
        if (!assumption_correct)
        {
            return false;
        }
    }

    return true;
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