// Authors: Marc Gröling

#include "../hashing.h"

#include <string>
#include <vector>

std::vector<uint64_t> solve_problem(std::pair<std::string, std::vector<std::pair<int, int>>> &input)
{
    std::vector<uint64_t> output;

    Polynomial_Hash_Family h = Polynomial_Hash_Family(input.first);

    for (const std::pair<int, int> &query : input.second)
    {
        output.push_back(h.get_hash(query.first, query.second));
    }

    return output;
}