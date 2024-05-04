// Authors: Marc Gröling

#include "../geometry.h"
#include "kattisio.h"

#include <vector>

std::vector<Point<int>> solve_test_case(std::vector<Point<int>> &points)
{
    return convex_hull(points);
}

std::vector<std::vector<Point<int>>> solve_problem(std::vector<std::vector<Point<int>>> &input)
{
    std::vector<std::vector<Point<int>>> output;
    output.reserve(input.size());

    for (std::vector<Point<int>> &test_case : input)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}