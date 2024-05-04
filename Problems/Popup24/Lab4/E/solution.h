// Authors: Marc Gröling

#include "../geometry.h"
#include "kattisio.h"

#include <vector>

std::vector<double> solve_problem(std::vector<std::vector<int>> &input)
{
    std::vector<double> output;
    output.reserve(input.size());

    int i = 0;
    for (const std::vector<int> &test_case : input)
    {
        std::pair<Point<double>, Point<double>> l1{Point<double>(test_case[0], test_case[1]),
                                                   Point<double>(test_case[2], test_case[3])};
        std::pair<Point<double>, Point<double>> l2{Point<double>(test_case[4], test_case[5]),
                                                   Point<double>(test_case[6], test_case[7])};
        output.push_back(line_segment_distance(l1, l2));
        i++;
    }

    return output;
}