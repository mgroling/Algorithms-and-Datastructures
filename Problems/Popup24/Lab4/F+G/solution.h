// Authors: Marc Gröling

#include "../geometry.h"
#include "kattisio.h"

#include <vector>

std::vector<double> solve_test_case(std::vector<Point<double>> &points)
{
    std::pair<Point<double>, Point<double>> closest = closest_pair(points);

    return {closest.first.x, closest.first.y, closest.second.x, closest.second.y};
}

std::vector<std::vector<double>> solve_problem(std::vector<std::vector<Point<double>>> &input)
{
    std::vector<std::vector<double>> output;
    output.reserve(input.size());

    for (std::vector<Point<double>> &test_case : input)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}