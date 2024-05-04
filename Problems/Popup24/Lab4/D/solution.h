// Authors: Marc Gröling

#include "../geometry.h"
#include "kattisio.h"

#include <vector>

std::vector<std::vector<std::pair<double, double>>> solve_problem(const std::vector<std::vector<int>> &input)
{
    std::vector<std::vector<std::pair<double, double>>> output(input.size(), std::vector<std::pair<double, double>>{});

    int i = 0;
    for (const std::vector<int> &test_case : input)
    {
        std::pair<Point<double>, Point<double>> l1{Point<double>(test_case[0], test_case[1]),
                                                   Point<double>(test_case[2], test_case[3])};
        std::pair<Point<double>, Point<double>> l2{Point<double>(test_case[4], test_case[5]),
                                                   Point<double>(test_case[6], test_case[7])};
        std::vector<Point<double>> result = line_segment_intersection(l1, l2);
        for (const Point<double> &p : result)
        {
            output[i].emplace_back(p.x, p.y);
        }
        i++;
    }

    return output;
}