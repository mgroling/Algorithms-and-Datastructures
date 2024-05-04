// Authors: Marc Gröling

#include "../geometry.h"
#include "kattisio.h"

#include <vector>

std::vector<double> solve_test_case(const std::vector<Point<double>> &test_case)
{
    std::pair<int, int> indices = closest_pair(test_case);

    return {test_case[indices.first].x, test_case[indices.first].y, test_case[indices.second].x,
            test_case[indices.second].y};
}

std::vector<std::vector<double>> solve_problem(const std::vector<std::vector<Point<double>>> &input)
{
    std::vector<std::vector<double>> output;
    output.reserve(input.size());

    for (const std::vector<Point<double>> &test_case : input)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}