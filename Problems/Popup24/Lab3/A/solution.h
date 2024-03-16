// Authors: Marc Gröling

#include "../substring_search.h"

#include <string>
#include <vector>

std::vector<std::vector<int>> solve_problem(const std::vector<std::pair<std::string, std::string>> &input)
{
    std::vector<std::vector<int>> positions;

    for (const std::pair<std::string, std::string> word_text : input)
    {
        positions.emplace_back(substring_search(word_text.second, word_text.first));
    }

    return positions;
}