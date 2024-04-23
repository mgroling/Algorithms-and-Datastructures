// Authors: Marc Gröling

#include "../geometry.h"
#include "kattisio.h"

#include <vector>

std::vector<std::pair<bool, double>> solve_problem(std::vector<Test_case> &input)
{
    std::vector<std::pair<bool, double>> output;

    for (Test_case &test_case : input)
    {
        std::vector<Point<int>> points_temp;
        for (const std::pair<int, int> &p : test_case.points)
        {
            points_temp.emplace_back(p.first, p.second);
        }
        // make it a closed polygon
        points_temp.push_back(points_temp[0]);
        double signed_area = compute_signed_area_polygon(points_temp);
        output.emplace_back(signed_area < 0, std::abs(signed_area));
    }

    return output;
}