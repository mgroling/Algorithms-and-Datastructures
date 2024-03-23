// Authors: Marc Gröling

#include "../suffix_array.h"
#include "kattisio.h"

#include <string>
#include <vector>

std::vector<int> solve_test_case(const Test_case &test_case)
{
    std::vector<int> indices;
    indices.reserve(test_case.indices.size());
    std::vector<int> suffix_array = create_suffix_array(test_case.text);

    for (const int &index : test_case.indices)
    {
        indices.push_back(suffix_array[index]);
    }

    return indices;
}

std::vector<std::vector<int>> solve_problem(const std::vector<Test_case> &input)
{
    std::vector<std::vector<int>> indices;

    for (const Test_case &test_case : input)
    {
        indices.emplace_back(solve_test_case(test_case));
    }

    return indices;
}