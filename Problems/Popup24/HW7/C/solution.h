/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include <queue>
#include <string>
#include <vector>

struct CustomComparator
{
    bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) const
    {
        if (a.second == b.second)
        {
            return true;
        }
        return a.second > b.second;
    }
};

std::vector<int> solve_problem(std::vector<std::vector<int>> &problem)
{
    // first elem of pair is the index of the sequences that the element is from and the second value is the value of
    // the first element of that sequence
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, CustomComparator> sequence_pq;

    // reminder: sequences were reversed while reading them in kattisio.h
    for (int i = 0; i < problem.size(); i++)
    {
        sequence_pq.emplace(i, problem[i].back());
        problem[i].pop_back();
    }

    std::vector<int> output;
    while (!sequence_pq.empty())
    {
        std::pair<int, int> elem = sequence_pq.top();
        sequence_pq.pop();

        output.push_back(elem.second);
        // insert next value from that card stack
        if (problem[elem.first].size())
        {
            sequence_pq.emplace(elem.first, problem[elem.first].back());
            problem[elem.first].pop_back();
        }
    }

    return output;
}