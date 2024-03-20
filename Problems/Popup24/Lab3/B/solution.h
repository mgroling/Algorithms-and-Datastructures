// Authors: Marc Gröling

#include "../substring_search.h"
#include "kattisio.h"

#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::vector<int>> solve_problem(const std::vector<Test_case> &input)
{
    std::vector<std::vector<int>> positions;

    for (int i = 0; i < input.size(); i++)
    {
        std::vector<std::vector<int>> word_positions = substring_search(input[i].text, input[i].words);
        positions.insert(positions.end(), word_positions.begin(), word_positions.end());
    }

    return positions;
}