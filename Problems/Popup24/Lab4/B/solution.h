// Authors: Marc Gröling

#include "../polygon.h"
#include "kattisio.h"

#include <vector>

std::vector<std::pair<bool, double>> solve_problem(std::vector<Test_case> &input)
{
    std::vector<std::pair<bool, double>> output;

    for (Test_case &test_case : input)
    {
        test_case.points.push_back(test_case.points[0]);
        double signed_area = compute_signed_area_polygon(test_case.points);
        output.emplace_back(signed_area < 0, std::abs(signed_area));
    }

    return output;
}