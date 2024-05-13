/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


 */

#include "geometry.h"

#include <set>
#include <vector>

long long convert_double(const long double &num)
{
    return num * 1e3L;
}

int solve_problem(const std::vector<std::pair<Point<long double>, Point<long double>>> &input)
{
    int count = 0;
    std::set<std::pair<long long, long long>> intersection_points;

    for (int i = 0; i < input.size(); i++)
    {
        for (int j = i + 1; j < input.size(); j++)
        {
            std::vector<Point<long double>> intersections = line_segment_intersection(input[i], input[j]);
            if (intersections.size() == 1)
            {
                std::pair<long long, long long> point = {convert_double(intersections[0].x),
                                                         convert_double(intersections[0].y)};
                // new intersection point
                if (intersection_points.find(point) == intersection_points.end())
                {
                    intersection_points.insert(point);
                    count++;
                }
            }
            if (intersections.size() == 2)
            {
                return -1;
            }
        }
    }

    return count;
}