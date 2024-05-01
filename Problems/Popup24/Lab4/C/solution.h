// Authors: Marc Gröling

#include "../geometry.h"
#include "kattisio.h"

#include <vector>

std::vector<int> solve_problem(std::vector<Test_case> &input)
{
    std::vector<int> output;

    for (Test_case &test_case : input)
    {
        std::vector<Point<int>> polygon;
        for (const std::pair<int, int> &p : test_case.vertices)
        {
            polygon.emplace_back(p.first, p.second);
        }
        // make it a closed polygon
        polygon.push_back(polygon[0]);

        for (const std::pair<int, int> &p : test_case.query_points)
        {
            output.push_back(Point(p.first, p.second).inside_polygon(polygon));
        }
    }

    return output;
}